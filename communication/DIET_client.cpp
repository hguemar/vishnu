//
// DIET_client.c
// Implémentation du mock de la couche DIET par ZMQ dans VISHNU pour UMS
// Le 02/05/2012
// Auteur K. COULOMB
//

#include "DIET_client.h"

#include <jansson.h>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>                    // for copy, transform
#include <stdexcept>                    // for out_of_range
#include <utility>                      // for pair
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>  // for starts_with
#include <boost/algorithm/string/regex.hpp>  // for split_regex
#include <boost/algorithm/string/split.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/make_shared.hpp>
#include <zmq.hpp>                      // for context_t

#include "constants.hpp"                // for ::DISP_URIADDR, etc
#include "zhelpers.hpp"
#include "SystemException.hpp"
#include "ExecConfiguration.hpp"
#include "TMSServices.hpp"
#include "UMSServices.hpp"
#include "IMSServices.hpp"
#include "FMSServices.hpp"
#include "utilVishnu.hpp"

// private declarations
static ExecConfiguration config;

typedef std::map<std::string, std::string> ServiceMap;
boost::shared_ptr<ServiceMap> sMap;

// defines minimal number of elements in a diet profile
static const int PROFILE_ELT_NB = 4;


static void
fill_sMap() {
  unsigned int nb;
  sMap = boost::shared_ptr<ServiceMap>(new ServiceMap);
  /* UMS services */
  for (nb = 0; nb < NB_SRV_UMS; nb++) {
    (*sMap)[SERVICES_UMS[nb]] = "UMS";
  }
  (*sMap)["heartbeatumssed"] = "UMS";


  /* TMS services */
  for (nb = 0; nb < NB_SRV_TMS; nb++) {
    (*sMap)[SERVICES_TMS[nb]] = "TMS";
  }
  (*sMap)["heartbeattmssed"] = "TMS";

  /* IMS services */
  for (nb = 0; nb < NB_SRV_IMS; nb++) {
    (*sMap)[SERVICES_IMS[nb]] = "IMS";
  }
  (*sMap)["heartbeatimssed"] = "IMS";

  /* FMS services */
  for (nb = 0; nb < NB_SRV_FMS; nb++) {
    (*sMap)[SERVICES_FMS[nb]] = "FMS";
  }
  (*sMap)["heartbeatfmssed"] = "FMS";
}


std::string
get_module(const std::string& service) {
  std::size_t pos = service.find("@");
  ServiceMap::const_iterator it;
  fill_sMap();

  if (std::string::npos != pos) {
    it = sMap->find(service.substr(0, pos));
  } else {
    it = sMap->find(service);
  }

  if (it != sMap->end()) {
    return it->second;
  }

  // Service not found
  return "";
}


/**
 * @brief getTimeout
 * @return
 */
int getTimeout() {
  int timeout = -1;
  if (!config.getConfigValue(vishnu::TIMEOUT, timeout) || timeout <= 0) {
    timeout =  DEFAULT_TIMEOUT;
  }
  return timeout;
}


diet_profile_t*
diet_profile_alloc(const std::string &name, int IN, int INOUT, int OUT) {
  // TODO : Do not handle -1 for input (no input param)
  diet_profile_t* res = new diet_profile_t;
  res->IN = IN;
  res->INOUT = INOUT;
  res->OUT = OUT;
  (res->params).resize(OUT+1, "");
  res->name = name;
  return res;
}

int
diet_string_set(diet_profile_t* prof, int pos,
                const std::string& value) {
  try {
    (prof->params).at(pos) = value;
  } catch (const std::out_of_range& err) {
    throw
    SystemException(ERRCODE_SYSTEM, "Invalid index, unallocated parameter");
  }
  return 0;
}

int
diet_call(diet_profile_t* prof) {
  std::string uri;
  std::vector<std::string> uriv;
  std::string disp;
  std::vector<std::string> dispv;

  // get the service and the related module
  std::string service(prof->name);
  std::string module = get_module(service);
  std::transform(module.begin(), module.end(), module.begin(), ::tolower);

  vishnu::param_type_t param;
  if (module == "ums") {
    param = vishnu::UMS_URIADDR;
  } else if (module == "fms") {
    param = vishnu::FMS_URIADDR;
  } else if (module == "ims") {
    param = vishnu::IMS_URIADDR;
  } else if (module == "tms") {
    param = vishnu::TMS_URIADDR;
  } else {
    // Currently do not throw anything as diet_call is meant to return an error and not throw an exception
    // No module or server found
    // throw SystemException(ERRCODE_SYSTEM,
    //                       boost::str(
    //                         boost::format("No corresponding %1% server found")
    //                         % service));
    std::cerr << boost::format("No corresponding %1% server found") % service;
    return 1;
  }

  config.getConfigValues(param, uriv);
  std::vector<std::string> tokens;
  boost::algorithm::split(tokens, service, boost::algorithm::is_any_of("@"));

  if (!uriv.empty()) {
    std::istringstream iss(uriv[0]);
    iss >> uri;
  }
  try {
    std::string mid = tokens.at(1);
    tokens.clear();
    bool validMid(false);

    BOOST_FOREACH(const std::string& v, uriv) {
      boost::algorithm::split(tokens, v, boost::algorithm::is_space());
      if (tokens.size() > 1 && mid == tokens[1]) {
        uri = tokens[0];
        validMid = true;
        break;
      }
    }

    if (!validMid) {
      uri.clear();
    }
  } catch (const std::out_of_range& err) {}

  config.getConfigValues(vishnu::DISP_URIADDR, dispv);
  if (!dispv.empty()) {
    disp = dispv[0];
  }

  if (uri.empty() && disp.empty()) {
    // Currently do not throw anything as diet_call is meant to return an error and not throw an exception
    // No module or server found
    // throw SystemException(ERRCODE_SYSTEM,
    //                       boost::str(
    //                         boost::format("No corresponding %1% server found")
    //                         % service));
    std::cerr << boost::format("No corresponding %1% server found") % service;
    return 1;
  }

  // If no direct data but dispatcher found
  if (uri == "") {
    uri = disp;
  }

  return abstract_call_gen(prof, uri);
}

int
diet_call_gen(diet_profile_t* prof, const std::string& uri, bool shortTimeout) {
  int timeout = shortTimeout?SHORT_TIMEOUT:getTimeout();
  zmq::context_t ctx(5);
  LazyPirateClient lpc(ctx, uri, timeout);
  std::string s1 = my_serialize(prof);
  if (!lpc.send(s1)) {
    std::cerr << "E: request failed, exiting ...\n";
    return -1;
  }

  std::string response = lpc.recv();
  boost::shared_ptr<diet_profile_t> tmp(my_deserialize(response));
  if (!tmp) {
    std::cerr << boost::format("[ERROR] %1%\n")%response;
    return 1;
  }
  // To signal a communication problem (bad server receive request)
  // Otherwize client does not get any error message
  if (tmp->OUT == -1) {
    return 1;
  }

  prof->IN = tmp->IN;
  prof->OUT = tmp->OUT;
  prof->INOUT = tmp->INOUT;
  prof->params = tmp->params;
  return 0;
}

int
ssl_call_gen(diet_profile_t* prof,
             const std::string& host,
             const int& port,
             const std::string& cafile) {
  TlsClient tlsClient(host, port, cafile);

  if (tlsClient.send( my_serialize(prof) )) {
    std::cerr << boost::format("[ERROR] %1%\n")%tlsClient.getErrorMsg();
    return -1;
  }

  std::string response = tlsClient.recv();
  try {
    boost::shared_ptr<diet_profile_t> tmp(my_deserialize(response));
    if (tmp) {
      prof->IN = tmp->IN;
      prof->OUT = tmp->OUT;
      prof->INOUT = tmp->INOUT;
      prof->params = tmp->params;
      return 0;
    } else {
      std::cerr << boost::format("[ERROR] %1%\n")%response;
    }
  } catch (const VishnuException& ex) {
    std::cerr << boost::format("[ERROR] %1%\n")%ex.what();
  }
  return -1;
}


int
diet_string_get(diet_profile_t* prof, int pos, std::string& value) {
  value = (prof->params).at(pos);
  return 0;
}

int
diet_profile_free(diet_profile_t* prof) {
  delete prof;
  return 0;
}


std::string
my_serialize(diet_profile_t* prof) {

  return json_serialize(prof);
}


std::string
json_serialize(diet_profile_t* prof) {

  if (!prof) {
    throw SystemException(ERRCODE_SYSTEM, "Cannot serialize a null pointer profile");
  }

  json_t* jsonProfile = json_object();
  json_t* params = json_array();

  if (0 != json_object_set_new(jsonProfile, "NAME", json_string(prof->name.c_str()))) {
    throw SystemException(ERRCODE_SYSTEM, "Invalid profile");
  }
  if (0 != json_object_set_new(jsonProfile, "IN", json_integer(prof->IN))) {
    throw SystemException(ERRCODE_SYSTEM, "Invalid profile");
  }
  if (0 != json_object_set_new(jsonProfile, "INOUT", json_integer(prof->INOUT))) {
    throw SystemException(ERRCODE_SYSTEM, "Invalid profile");
  }
  if (0 != json_object_set_new(jsonProfile, "OUT", json_integer(prof->OUT))) {
    throw SystemException(ERRCODE_SYSTEM, "Invalid profile");
  }
  if (0 != json_object_set_new(jsonProfile, "PARAMS", params)) {
    throw SystemException(ERRCODE_SYSTEM, "Invalid profile");
  }


  // Set params
  for (int i = 0; i<(prof->OUT); ++i) {
    if (0 != json_array_append_new(params, json_string(prof->params[i].c_str()))) {
      throw SystemException(ERRCODE_SYSTEM, "Invalid profile");
    }
  }
  if (prof->OUT > 0) {
    if (0 != json_array_append_new(params, json_string(prof->params[(prof->OUT)].c_str()))) {
      throw SystemException(ERRCODE_SYSTEM, "Invalid profile");
    }
  }

  char* encodedJson = json_dumps(jsonProfile, 0);
  std::string result = std::string(encodedJson);
  free(encodedJson);

  json_decref(params);
  json_decref(jsonProfile);

  return result;
}


std::string
json_serialize(const TMS_Data::Job& job) {

  return "TODO";
}

boost::shared_ptr<diet_profile_t>
json_deserialize(const std::string& encodedJson) {

  boost::shared_ptr<diet_profile_t> profile;

  if (encodedJson.empty()) {
    throw SystemException(ERRCODE_SYSTEM, "Cannot deserialize an empty string");
  }

  json_error_t error;
  json_t* jsonObject = json_loads(encodedJson.c_str(), 0, &error);
  if (! jsonObject) {
    throw SystemException(ERRCODE_SYSTEM, error.text);
  }

  profile.reset(new diet_profile_t);

  json_t * jsonValue;
  if (! (jsonValue = json_object_get(jsonObject, "NAME"))) {
    throw SystemException(ERRCODE_SYSTEM, "Invalid profile received");
  }
  profile->name = json_string_value(jsonValue);

  if (! (jsonValue = json_object_get(jsonObject, "IN"))) {
    throw SystemException(ERRCODE_SYSTEM, "Invalid profile received");
  }
  profile->IN = json_integer_value(jsonValue);

  if (! (jsonValue = json_object_get(jsonObject, "INOUT"))) {
    throw SystemException(ERRCODE_SYSTEM, "Invalid profile received");
  }
  profile->INOUT = json_integer_value(jsonValue);

  if (! (jsonValue = json_object_get(jsonObject, "OUT"))) {
    throw SystemException(ERRCODE_SYSTEM, "Invalid profile received");
  }
  profile->OUT = json_integer_value(jsonValue);

  json_t* params = json_object_get(jsonObject, "PARAMS");
  size_t index(0);

#if JANSSON_VERSION_HEX >= 0x020500
  json_array_foreach(params, index, jsonValue) {
#else
  for(;
      index < json_array_size(params) &&
      (jsonValue = json_array_get(params, index));
      ++index) {
#endif
    profile->params.push_back(json_string_value(jsonValue));
  }

  if (profile->params.size() <= profile->OUT) {
    throw SystemException(ERRCODE_INVDATA, "Incoherent profile, wrong number of parameters");
  }

  json_decref(jsonObject);
  return profile;
}

boost::shared_ptr<diet_profile_t>
my_deserialize(const std::string& prof) {


  return json_deserialize(prof);
}

int
diet_initialize(const char* cfg, int argc, char** argv) {
  if (!cfg) {
    throw SystemException(ERRCODE_SYSTEM, "Invalid NULL initialization file");
  }
  config.initFromFile(cfg);
  return 0;
}

int
communicate_dispatcher(const std::string& requestData, std::string& response, bool shortTimeout){
  int timeout = shortTimeout?SHORT_TIMEOUT:getTimeout();
  std::string uriDispatcher;
  config.getRequiredConfigValue<std::string>(vishnu::DISP_URISUBS, uriDispatcher);
  bool useSsl = false;
  if (config.getConfigValue<bool>(vishnu::USE_SSL, useSsl) && useSsl) {
    std::string req = requestData;
    std::string host;
    int port;
    host = vishnu::getHostFromUri(uriDispatcher);
    port = vishnu::getPortFromUri(uriDispatcher);
    std::string cafile;
    config.getConfigValue<std::string>(vishnu::SSL_CA, cafile);
    TlsClient tlsClient(host, port, cafile);
    req.append("\n\n");      /* required for the internal protocol */
    if (tlsClient.send(req) == 0) {
      response = tlsClient.recv();
    }
  } else {
    zmq::context_t ctx(1);
    LazyPirateClient lpc(ctx, uriDispatcher, timeout);
    if (!lpc.send(requestData)) {
      return -1; // Dont throw exception
    }
    response = lpc.recv();
  }

  return 0;
}

void
extractServersFromMessage(std::string msg, std::vector<boost::shared_ptr<Server> >& res){
  using boost::algorithm::split_regex;
  std::vector<std::string> vecString;
  split_regex(vecString, msg, boost::regex(VISHNU_COMM_REGEX));
  std::vector<std::string>::iterator it;
  for (it = vecString.begin() ; it != vecString.end() ; ++it){
    std::string val(it->c_str()); // CREATE A STRING BECAUSE IT->EMPTY = FALSE WHEN IT EMPTY
    // URI is the key
    if ( !val.empty()){
      res.push_back(Server::fromString(val));
    }
  }
}

int
abstract_call_gen(diet_profile_t* prof, const std::string& uri, bool shortTimeout){
  bool useSsl = false;
  std::string cafile;
  if (config.getConfigValue<bool>(vishnu::USE_SSL, useSsl) && useSsl)
  {
    config.getConfigValue<std::string>(vishnu::SSL_CA, cafile);
    return ssl_call_gen(prof, vishnu::getHostFromUri(uri), vishnu::getPortFromUri(uri), cafile);
  }
  return diet_call_gen(prof, uri, shortTimeout);
}


void
extractServersFromLine(const std::vector<std::string>& uriv, std::vector<boost::shared_ptr<Server> >& allServers, const std::string& module){
  using boost::algorithm::split_regex;
  std::vector<std::string> tokens;
  std::vector<std::string> tmp;
  tmp.push_back("heartbeat");
  std::vector<std::string>::iterator it;
  std::string uri;

  BOOST_FOREACH(const std::string& v, uriv) {
    boost::algorithm::split(tokens, v, boost::algorithm::is_any_of(";")); // In client config files, URI are separated by ;
    for (it = tokens.begin() ; it != tokens.end() ; ++it){
      uri = *it;
      allServers.push_back(boost::make_shared<Server>(module, tmp, uri));
    }
    tokens.clear();
  }
}

void
extractMachineServersFromLine(const std::vector<std::string>& uriv, std::vector<boost::shared_ptr<Server> >& allServers, const std::string& module){
  using boost::algorithm::split_regex;
  std::vector<std::string> tokens;
  std::vector<std::string> tokens2;
  std::vector<std::string> tmp;
  tmp.push_back("heartbeat");
  std::vector<std::string>::iterator it;
  std::string uri;

  BOOST_FOREACH(const std::string& v, uriv) {
    boost::algorithm::split(tokens, v, boost::algorithm::is_any_of(";")); // In client config files, URI are separated by ;
    BOOST_FOREACH(const std::string& w, tokens) {
      boost::algorithm::split(tokens2, w, boost::algorithm::is_space());
      uri = tokens2[0];
      allServers.push_back(boost::make_shared<Server>(module, tmp, uri));
    }
    tokens.clear();
  }
}


void
getServersListFromConfig(std::vector<boost::shared_ptr<Server> >& allServers){
  vishnu::param_type_t param;
  std::vector<std::string> uriv;
  param = vishnu::UMS_URIADDR;
  config.getConfigValues(param, uriv);
  if (uriv.size()>0)
    extractServersFromLine(uriv, allServers, "umssed");
  uriv.clear();
  param = vishnu::IMS_URIADDR;
  config.getConfigValues(param, uriv);
  if (uriv.size()>0)
    extractServersFromLine(uriv, allServers, "imssed");
  uriv.clear();
  param = vishnu::FMS_URIADDR;
  config.getConfigValues(param, uriv);
  if (uriv.size()>0)
    extractServersFromLine(uriv, allServers, "fmssed");
  uriv.clear();
  param = vishnu::TMS_URIADDR;
  config.getConfigValues(param, uriv);
  if (uriv.size()>0)
    extractMachineServersFromLine(uriv, allServers, "tmssed");
  uriv.clear();
}

