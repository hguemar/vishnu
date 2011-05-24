#include "internalApiIMS.hpp"
#include <exception>
#include "VishnuException.hpp"
#include "SystemException.hpp"
#include "IMSMapper.hpp"
#include "MapperRegistry.hpp"
#include <iostream>
#include "SessionServer.hpp"
#include <ecore.hpp> // Ecore metamodel
#include <ecorecpp.hpp> // EMF4CPP utils
#include "IMS_Data.hpp"
#include "DIET_server.h"
#include "data/ProcessServer.hpp"
#include "data/MetricServer.hpp"
#include "data/ObjectIdServer.hpp"
#include "data/SysInfoServer.hpp"
#include "data/ThresholdServer.hpp"
#include "controller/process/ProcessCtl.hpp"
#include "data/ExportServer.hpp"
#include "data/ExportFactory.hpp"

using namespace std;
using namespace vishnu;

int
solveExport(diet_profile_t* pb){

  char* sessionKey = NULL;
  char* oldSessionId = NULL;
  char* filename  = NULL;
  char* options  = NULL;
  string content;
  int mapperkey;
  string cmd;
  string error;
  string retErr = "";

  diet_string_get(diet_parameter(pb,0), &sessionKey, NULL);
  diet_string_get(diet_parameter(pb,1), &oldSessionId, NULL);
  diet_string_get(diet_parameter(pb,2), &filename, NULL);
  diet_string_get(diet_parameter(pb,3), &options, NULL);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);

  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_export_command");
    mapper->code(string(oldSessionId), mapperkey);
    mapper->code(string(filename), mapperkey);
    mapper->code(string(options), mapperkey);
    cmd = mapper->finalize(mapperkey);

    // Getting options
    IMS_Data::ExportOp_ptr expOp = NULL;
    if(!parseEmfObject(string(options), expOp)) {
      throw UserException(ERRCODE_INVALID_PARAM, "solve_export: Curent restart option object is not well built");
    }
    // Creating the process server with the options
    ExportServer* exp = ExportFactory::getExporter(userServer, expOp);

    // Exporting and setting the results in content
    exp->exporte(oldSessionId, content);

    // Setting out diet param
    diet_string_set(diet_parameter(pb,4), strdup(content.c_str()), DIET_VOLATILE);
    diet_string_set(diet_parameter(pb,5), strdup(retErr.c_str()), DIET_VOLATILE);

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);
  } catch (VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,4), strdup(""), DIET_VOLATILE);
    diet_string_set(diet_parameter(pb,5), strdup(retErr.c_str()), DIET_VOLATILE);
  }
  return 0;
}

// TODO FAIRE CE SERVICE COMME NOMME
int 
solveCurMetric(diet_profile_t* pb){
  char *sessionKey   = NULL;
  char *curOpSer = NULL;
  char *mid = NULL;
  char *curSer   = NULL;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;

  diet_string_get(diet_parameter(pb,0), &sessionKey,NULL);
  diet_string_get(diet_parameter(pb,1), &mid,NULL);
  diet_string_get(diet_parameter(pb,2), &curOpSer,NULL);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);

  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_get_current_metric");
    mapper->code(string(mid), mapperkey);
    mapper->code(string(curOpSer), mapperkey);
    cmd = mapper->finalize(mapperkey);

    // Getting options
    IMS_Data::CurMetricOp_ptr curOp = NULL;
    if(!parseEmfObject(string(curOpSer), curOp)) {
      throw UserException(ERRCODE_INVALID_PARAM, "solve_getCurentMetricValue: Curent metric option object is not well built");
    }
    // Creating the process server with the options
    MetricServer met(userServer, curOp);

    // Listing the old metric
    IMS_Data::ListMetric* res;
    res = met.getCurMet();
    // Serializing the results
    const char* name = "solve_getCurMetric";
    ::ecorecpp::serializer::serializer _ser(name);
    curSer = strdup(_ser.serialize(const_cast<IMS_Data::ListMetric_ptr>(res)).c_str());

    // Setting out diet param
    diet_string_set(diet_parameter(pb,3), strdup(curSer), DIET_VOLATILE);
    diet_string_set(diet_parameter(pb,4), strdup(retErr.c_str()), DIET_VOLATILE);

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);
  } catch (VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,3), strdup(""), DIET_VOLATILE);
    diet_string_set(diet_parameter(pb,4), strdup(retErr.c_str()), DIET_VOLATILE);

  }
  return 0;
}

int
solveOldMetric(diet_profile_t* pb){
  char *sessionKey   = NULL;
  char *histOpSer = NULL;
  char *mid = NULL;
  char *histSer   = NULL;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;

  diet_string_get(diet_parameter(pb,0), &sessionKey,NULL);
  diet_string_get(diet_parameter(pb,1), &mid,NULL);
  diet_string_get(diet_parameter(pb,2), &histOpSer,NULL);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);

  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_get_history_metric");
    mapper->code(string(mid), mapperkey);
    mapper->code(string(histOpSer), mapperkey);
    cmd = mapper->finalize(mapperkey);

    // Getting options
    IMS_Data::MetricHistOp_ptr histOp = NULL;
    if(!parseEmfObject(string(histOpSer), histOp)) {
      throw UserException(ERRCODE_INVALID_PARAM, "solve_getMetricHistory: Metric history option object is not well built");
    }
    // Creating the process server with the options
    MetricServer met(userServer, histOp);

    // Listing the old metric
    IMS_Data::ListMetric* res;
    res = met.getHistMet(string(mid));

    // Serializing the results
    const char* name = "solve_getHistMetric";
    ::ecorecpp::serializer::serializer _ser(name);
    histSer = strdup(_ser.serialize(const_cast<IMS_Data::ListMetric_ptr>(res)).c_str());

    // Setting out diet param
    diet_string_set(diet_parameter(pb,3), strdup(histSer), DIET_VOLATILE);
    diet_string_set(diet_parameter(pb,4), strdup(retErr.c_str()), DIET_VOLATILE);

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  } catch (VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,3), strdup(""), DIET_VOLATILE);
    diet_string_set(diet_parameter(pb,4), strdup(retErr.c_str()), DIET_VOLATILE);

  }
  return 0;
}

int
solvePS(diet_profile_t* pb){
  char *sessionKey   = NULL;
  char *processOpSer = NULL;
  char *processSer   = NULL;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;

  diet_string_get(diet_parameter(pb,0), &sessionKey,NULL);
  diet_string_get(diet_parameter(pb,1), &processOpSer,NULL);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);

  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_get_processes");
    mapper->code(string(processOpSer), mapperkey);
    cmd = mapper->finalize(mapperkey);

    // Getting options
    IMS_Data::ProcessOp_ptr processOp = NULL;
    if(!parseEmfObject(string(processOpSer), processOp)) {
      throw UserException(ERRCODE_INVALID_PARAM, "solve_getProcesses: Process option object is not well built");
    }

    // Creating the process server with the options
    ProcessServer proc(processOp, userServer);

    // Listing the processes
    IMS_Data::ListProcesses* res;
    res = proc.list();

    // Serializing the results
    const char* name = "solve_getProcesses";
    ::ecorecpp::serializer::serializer _ser(name);
    processSer = strdup(_ser.serialize(const_cast<IMS_Data::ListProcesses_ptr>(res)).c_str());

    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), strdup(processSer), DIET_VOLATILE);
    diet_string_set(diet_parameter(pb,3), strdup(retErr.c_str()), DIET_VOLATILE);

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), strdup(""), DIET_VOLATILE);
    diet_string_set(diet_parameter(pb,3), strdup(retErr.c_str()), DIET_VOLATILE);
  }

  return 0;
}

int
solveSetSysInfo(diet_profile_t* pb){
  char *sessionKey   = NULL;
  char* sys = NULL;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;
  char *sysSer   = NULL;


  diet_string_get(diet_parameter(pb,0), &sessionKey,NULL);
  diet_string_get(diet_parameter(pb,1), &sys,NULL);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  try {
    // Getting options
    IMS_Data::SystemInfo_ptr sysinf = NULL;
    if(!parseEmfObject(string(sys), sysinf)) {
      throw UserException(ERRCODE_INVALID_PARAM, "solve_setSysInfo: system info object is not well built");
    }
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_set_system_info");
    mapper->code(string(sys), mapperkey);
    cmd = mapper->finalize(mapperkey);

    // Creating the process server with the options
    SysInfoServer sysser(userServer);

    // Listing the old metric
    sysser.setSysInfo(sysinf);
    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);
  }
  return 0;
}

int
solveGetThreshold(diet_profile_t* pb){
  char *sessionKey   = NULL;
  char *treeOpSer = NULL;
  char *treeSer   = NULL;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;

  diet_string_get(diet_parameter(pb,0), &sessionKey,NULL);
  diet_string_get(diet_parameter(pb,1), &treeOpSer,NULL);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);

  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_get_system_info");
    mapper->code(string(treeOpSer), mapperkey);
    cmd = mapper->finalize(mapperkey);

    // Getting options
    IMS_Data::ThresholdOp_ptr treeOp = NULL;
    if(!parseEmfObject(string(treeOpSer), treeOp)) {
      throw UserException(ERRCODE_INVALID_PARAM, "solve_getThreshold: threshold option object is not well built");
    }

    // Creating the process server with the options
    ThresholdServer tree(userServer, *treeOp);

    // Listing the processes
    IMS_Data::ListThreshold* res;
    res = tree.getThreshold();

    // Serializing the results
    const char* name = "solve_getThreshold";
    ::ecorecpp::serializer::serializer _ser(name);
    treeSer = strdup(_ser.serialize(const_cast<IMS_Data::ListThreshold_ptr>(res)).c_str());

    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), strdup(treeSer), DIET_VOLATILE);
    diet_string_set(diet_parameter(pb,3), strdup(retErr.c_str()), DIET_VOLATILE);

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);
  }
  return 0;
}

int 
solveGetUpFreq(diet_profile_t* pb){
  char *sessionKey   = NULL;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;
  char *freqSer   = NULL;

  diet_string_get(diet_parameter(pb,0), &sessionKey,NULL);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);

  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_get_update_frequency");
    cmd = mapper->finalize(mapperkey);

    // Creating the process server with the options
    MetricServer met(userServer);

    // Listing the old metric
    int res;
    res = met.checkUpFreq();

    freqSer = new char[convertToString(res).size()+1];
    memcpy(freqSer, convertToString(res).c_str(), convertToString(res).size());

    // Setting out diet param
    diet_string_set(diet_parameter(pb,1), freqSer, DIET_VOLATILE);
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);
  } catch (VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,1), strdup(""), DIET_VOLATILE);
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);
  }
  return 0;
}

int
solveSetThreshold(diet_profile_t* pb){
  char *sessionKey   = NULL;
  char* tree = NULL;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;
  char *treeSer   = NULL;


  diet_string_get(diet_parameter(pb,0), &sessionKey,NULL);
  diet_string_get(diet_parameter(pb,1), &tree,NULL);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  try {
    // Getting options
    IMS_Data::Threshold_ptr treeinf = NULL;
    if(!parseEmfObject(string(tree), treeinf)) {
      throw UserException(ERRCODE_INVALID_PARAM, "solve_setSysInfo: system info object is not well built");
    }
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_set_system_info");
    mapper->code(string(tree), mapperkey);
    cmd = mapper->finalize(mapperkey);

    // Creating the process server with the options
    ThresholdServer treeser(userServer);

    // Listing the old metric
    treeser.setThreshold(treeinf);
    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);
  }
  return 0;
}

int
solveSetUID(diet_profile_t* pb){
  char *sessionKey   = NULL;
  char* fmt = NULL;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;
  char *fmtSer   = NULL;


  diet_string_get(diet_parameter(pb,0), &sessionKey,NULL);
  diet_string_get(diet_parameter(pb,1), &fmt,NULL);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_define_user_format");
    mapper->code(string(fmt), mapperkey);
    cmd = mapper->finalize(mapperkey);

    // Creating the process server with the options
    ObjectIdServer ob(userServer);

    // Listing the old metric
    ob.setUID(fmt);
    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);
  }
  return 0;
}

int
solveSetJID(diet_profile_t* pb){
  char *sessionKey   = NULL;
  char* fmt = NULL;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;
  char *fmtSer   = NULL;


  diet_string_get(diet_parameter(pb,0), &sessionKey,NULL);
  diet_string_get(diet_parameter(pb,1), &fmt,NULL);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_define_user_format");
    mapper->code(string(fmt), mapperkey);
    cmd = mapper->finalize(mapperkey);

    // Creating the process server with the options
    ObjectIdServer ob(userServer);

    // Listing the old metric
    ob.setTID(fmt);
    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);
  }
  return 0;
}

int
solveSetTID(diet_profile_t* pb){
  char *sessionKey   = NULL;
  char* fmt = NULL;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;
  char *fmtSer   = NULL;


  diet_string_get(diet_parameter(pb,0), &sessionKey,NULL);
  diet_string_get(diet_parameter(pb,1), &fmt,NULL);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_define_user_format");
    mapper->code(string(fmt), mapperkey);
    cmd = mapper->finalize(mapperkey);

    // Creating the process server with the options
    ObjectIdServer ob(userServer);

    // Listing the old metric
    ob.setFID(fmt);
    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);
  }
  return 0;
}

int
solveSetMID(diet_profile_t* pb){
  char *sessionKey   = NULL;
  char* fmt = NULL;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;
  char *fmtSer   = NULL;


  diet_string_get(diet_parameter(pb,0), &sessionKey,NULL);
  diet_string_get(diet_parameter(pb,1), &fmt,NULL);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_define_user_format");
    mapper->code(string(fmt), mapperkey);
    cmd = mapper->finalize(mapperkey);

    // Creating the process server with the options
    ObjectIdServer ob(userServer);

    // Listing the old metric
    ob.setMID(fmt);
    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);
  }
  return 0;
}

int
solveLoadShed(diet_profile_t* pb){
  char *sessionKey   = NULL;
  char* mid = NULL;
  char* type = NULL;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;


  diet_string_get(diet_parameter(pb,0), &sessionKey,NULL);
  diet_string_get(diet_parameter(pb,1), &mid,NULL);
  diet_string_get(diet_parameter(pb,2), &type,NULL);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_define_user_format");
    mapper->code(string(mid), mapperkey);
    mapper->code(string(type), mapperkey);
    cmd = mapper->finalize(mapperkey);

    // Creating the process server with the options
    ProcessCtl proc(mid, userServer);

    // Load shedding
    proc.loadShed(convertToInt(string(type)));
    // Setting out diet param
    diet_string_set(diet_parameter(pb,3), strdup(retErr.c_str()), DIET_VOLATILE);

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,3), strdup(retErr.c_str()), DIET_VOLATILE);
  }
  return 0;
}

int
solveSetUpFreq(diet_profile_t* pb){
  char *sessionKey   = NULL;
  char* freq = NULL;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;
  char *freqSer   = NULL;


  diet_string_get(diet_parameter(pb,0), &sessionKey,NULL);
  diet_string_get(diet_parameter(pb,1), &freq,NULL);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_set_update_frequency");
    mapper->code(string(freq), mapperkey);
    cmd = mapper->finalize(mapperkey);

    // Creating the process server with the options
    MetricServer met(userServer);

    // Listing the old metric
    met.setUpFreq(convertToInt(string(freq)));
    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);
  }
  return 0;
}

int
solveGetUpFreq(diet_profile_t* pb){
  char *sessionKey   = NULL;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;
  char *freqSer   = NULL;

  diet_string_get(diet_parameter(pb,0), &sessionKey,NULL);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);

  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_get_update_frequency");
    cmd = mapper->finalize(mapperkey);

    // Creating the process server with the options
    MetricServer met(userServer);

    // Listing the old metric
    int res;
    res = met.checkUpFreq();

    freqSer = new char[convertToString(res).size()+1];
    memcpy(freqSer, convertToString(res).c_str(), convertToString(res).size());

    // Setting out diet param
    diet_string_set(diet_parameter(pb,1), strdup(freqSer), DIET_VOLATILE);
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);
  } catch (VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,1), strdup(""), DIET_VOLATILE);
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);
  }
  return 0;
}

int
solveRestart(diet_profile_t* pb){
  char *sessionKey = NULL;
  char *mid        = NULL;
  char *op         = NULL;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;

  diet_string_get(diet_parameter(pb,0), &sessionKey,NULL);
  diet_string_get(diet_parameter(pb,1), &mid,NULL);
  diet_string_get(diet_parameter(pb,2), &op,NULL);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);

  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_restart");
    mapper->code(string(mid), mapperkey);
    mapper->code(string(op), mapperkey);
    cmd = mapper->finalize(mapperkey);

    // Getting options
    IMS_Data::RestartOp_ptr reOp = NULL;
    if(!parseEmfObject(string(op), reOp)) {
      throw UserException(ERRCODE_INVALID_PARAM, "solve_restart: restart option object is not well built");
    }

    // Creating the process server with the options
    ProcessCtl ctl(string(mid), userServer);

    // Listing the old metric
    ctl.restart(reOp);

    // Setting out diet param
    diet_string_set(diet_parameter(pb,3), strdup(retErr.c_str()), DIET_VOLATILE);

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);
  } catch (VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,3), strdup(retErr.c_str()), DIET_VOLATILE);
  }
  return 0;
}

int
solveStop(diet_profile_t* pb){
  char *sessionKey = NULL;
  char *proc       = NULL;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;

  diet_string_get(diet_parameter(pb,0), &sessionKey,NULL);
  diet_string_get(diet_parameter(pb,1), &proc,NULL);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);

  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_restart");
    mapper->code(string(proc), mapperkey);
    cmd = mapper->finalize(mapperkey);

    // Getting options
    IMS_Data::Process_ptr procObj = NULL;
    if(!parseEmfObject(string(proc), procObj)) {
      throw UserException(ERRCODE_INVALID_PARAM, "solve_restart: restart option object is not well built");
    }

    // Creating the process server with the options
    ProcessCtl ctl("", userServer);

    char hname[200];
    gethostname(hname, 199);

    // If have to stop a local process 
    if (procObj->getMachineId().compare(getMidFromHost(string(hname)))==0) {
      procObj->setMachineId("");
    }

    // Listing the old metric
    ctl.stop(procObj);

    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);
  } catch (VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), strdup(retErr.c_str()), DIET_VOLATILE);
  }
  return 0;
}

int
solveGetSysInfo(diet_profile_t* pb){
  char *sessionKey   = NULL;
  char *sysOpSer = NULL;
  char *sysSer   = NULL;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;

  diet_string_get(diet_parameter(pb,0), &sessionKey,NULL);
  diet_string_get(diet_parameter(pb,1), &sysOpSer,NULL);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);

  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_get_system_info");
    mapper->code(string(sysOpSer), mapperkey);
    cmd = mapper->finalize(mapperkey);

    // Getting options
    IMS_Data::SysInfoOp_ptr sysOp = NULL;
    if(!parseEmfObject(string(sysOpSer), sysOp)) {
      throw UserException(ERRCODE_INVALID_PARAM, "solve_getSysInfo: sys info option object is not well built");
    }

    // Creating the process server with the options
    SysInfoServer sys(userServer, *sysOp);

    // Listing the processes
    IMS_Data::ListSysInfo* res;
    res = sys.getSysInfo();

    // Serializing the results
    const char* name = "solve_getSysInfo";
    ::ecorecpp::serializer::serializer _ser(name);
    sysSer = strdup(_ser.serialize(const_cast<IMS_Data::ListSysInfo_ptr>(res)).c_str());

    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), strdup(sysSer), DIET_VOLATILE);
    diet_string_set(diet_parameter(pb,3), strdup(retErr.c_str()), DIET_VOLATILE);

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), strdup(""), DIET_VOLATILE);
    diet_string_set(diet_parameter(pb,3), strdup(retErr.c_str()), DIET_VOLATILE);
  }

  return 0;
}

