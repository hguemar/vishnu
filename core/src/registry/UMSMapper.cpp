/**
 * \file UMSMapper.ccp
 * \brief Implementation of the UMS mapper
 * \author Kevin Coulomb (kevin.coulomb@sysfera.com)
 * \date 10/02/11
 */

#include "UMSMapper.hpp"

#include <map>                          // for map, _Rb_tree_iterator, etc
#include <utility>                      // for pair
#include <string>
#include <vector>

#include <pthread.h>                    // for pthread_mutex_lock, etc
#include <boost/date_time/posix_time/conversion.hpp>  // for from_time_t
#include <boost/date_time/posix_time/ptime.hpp>  // for ptime
#include <boost/date_time/posix_time/time_formatters.hpp>


#include "UMS_Data.hpp"
#include "UMS_Data_forward.hpp"
#include "utilServer.hpp"               // for parseEmfObject

#include "Mapper.hpp"
#include "MapperRegistry.hpp"
#include "SystemException.hpp"          // for ERRCODE_SYSTEM, etc
#include "UMSVishnuException.hpp"       // for UMSVishnuException
#include "UserException.hpp"            // for ERRCODE_INVALID_PARAM
#include "ecore_forward.hpp"            // for EString
#include "ecorecpp/parser/parser.hpp"   // for parser
#include "utilVishnu.hpp"               // for convertToString, etc



using namespace vishnu;
using namespace std;

UMSMapper::UMSMapper() {
};

UMSMapper::~UMSMapper() {
};

UMSMapper::UMSMapper(MapperRegistry* reg, string na):Mapper(reg) {
  mname = na;
  mmap.insert(pair<int, string>(VISHNU_CONNECT                 , "vishnu_connect"));
  mmap.insert(pair<int, string>(VISHNU_RECONNECT               , "vishnu_reconnect"));
  mmap.insert(pair<int, string>(VISHNU_CLOSE                   , "vishnu_close"));
  mmap.insert(pair<int, string>(VISHNU_ADD_VISHNU_USER         , "vishnu_add_user"));
  mmap.insert(pair<int, string>(VISHNU_UPDATE_VISHNU_USER      , "vishnu_update_user"));
  mmap.insert(pair<int, string>(VISHNU_DELETE_VISHNU_USER      , "vishnu_delete_user"));
  mmap.insert(pair<int, string>(VISHNU_CHANGE_PASSWORD         , "vishnu_change_password"));
  mmap.insert(pair<int, string>(VISHNU_RESET_PASSWORD          , "vishnu_reset_password"));
  mmap.insert(pair<int, string>(VISHNU_ADD_LOCAL_ACCOUNT       , "vishnu_add_local_account"));
  mmap.insert(pair<int, string>(VISHNU_UPDATE_LOCAL_ACCOUNT    , "vishnu_update_local_account"));
  mmap.insert(pair<int, string>(VISHNU_DELETE_LOCAL_ACCOUNT    , "vishnu_delete_local_account"));
  mmap.insert(pair<int, string>(VISHNU_ADD_MACHINE             , "vishnu_add_machine"));
  mmap.insert(pair<int, string>(VISHNU_UPDATE_MACHINE          , "vishnu_update_machine"));
  mmap.insert(pair<int, string>(VISHNU_DELETE_MACHINE          , "vishnu_delete_machine"));
  mmap.insert(pair<int, string>(VISHNU_LIST_LOCAL_ACCOUNT      , "vishnu_list_local_accounts"));
  mmap.insert(pair<int, string>(VISHNU_LIST_MACHINE            , "vishnu_list_machines"));
  mmap.insert(pair<int, string>(VISHNU_LIST_HISTORY_CMD        , "vishnu_list_history_cmd"));
  mmap.insert(pair<int, string>(VISHNU_LIST_OPTIONS            , "vishnu_list_options"));
  mmap.insert(pair<int, string>(VISHNU_LIST_USERS              , "vishnu_list_users"));
  mmap.insert(pair<int, string>(VISHNU_LIST_SESSIONS           , "vishnu_list_sessions"));
  mmap.insert(pair<int, string>(VISHNU_CONFIGURE_DEFAULT_OPTION, "vishnu_configure_default_option"));
  mmap.insert(pair<int, string>(VISHNU_CONFIGURE_OPTION        , "vishnu_configure_option"));
  mmap.insert(pair<int, string>(VISHNU_ADD_AUTHSYS             , "vishnu_add_auth_system"));
  mmap.insert(pair<int, string>(VISHNU_UPDATE_AUTHSYS          , "vishnu_update_auth_system"));
  mmap.insert(pair<int, string>(VISHNU_DELETE_AUTHSYS          , "vishnu_delete_auth_system"));
  mmap.insert(pair<int, string>(VISHNU_LIST_AUTHSYS            , "vishnu_list_auth_systems"));
  mmap.insert(pair<int, string>(VISHNU_ADD_AUTHACC             , "vishnu_add_auth_account"));
  mmap.insert(pair<int, string>(VISHNU_UPDATE_AUTHACC          , "vishnu_update_auth_account"));
  mmap.insert(pair<int, string>(VISHNU_DELETE_AUTHACC          , "vishnu_delete_auth_account"));
  mmap.insert(pair<int, string>(VISHNU_LIST_AUTHACC            , "vishnu_list_auth_accounts"));
  mmap.insert(pair<int, string>(VISHNU_DEFINE_UID              , "vishnu_define_user_identifier"));
  mmap.insert(pair<int, string>(VISHNU_DEFINE_MID              , "vishnu_define_machine_identifier"));
  mmap.insert(pair<int, string>(VISHNU_DEFINE_TID              , "vishnu_define_job_identifier"));
  mmap.insert(pair<int, string>(VISHNU_DEFINE_FID              , "vishnu_define_transfer_identifier"));
  mmap.insert(pair<int, string>(VISHNU_DEFINE_AID              , "vishnu_define_auth_identifier"));
  mmap.insert(pair<int, string>(VISHNU_DEFINE_WID              , "vishnu_define_work_identifier"));
  mmap.insert (pair<int, string>(VISHNU_EXPORT                 , "vishnu_export_commands"));
};

int
UMSMapper::registerMapper() {
  mreg->addMapper(mname, this);
  return 0;
}

int
UMSMapper::unregisterMapper() {
  return mreg->removeMapper(mname);
}

int
UMSMapper::getCommand(const int& key, string& command) {
  map<int, string>::const_iterator it;
  for (it = mmap.begin() ; it != mmap.end() ; ++it) {
    if (key == it->first) {
      command = it->second;
      return 0;
    }
  }
  return 0;
}

int
UMSMapper::getKey(const string& command, int& key) {
  map<int, string>::const_iterator it;
  for (it = mmap.begin() ; it != mmap.end() ; ++it) {
    if (command.compare(it->second) == 0) {
      key = it->first;
      return 0;
    }
  }
  return 0;
}

int
UMSMapper::code(const string& cmd, unsigned int code) {
  map<int, string>::iterator it;
  int size;
  string key;
  int keycode;
  // If existing code -> add to the existing entry
  if (code) {
    it = mcmd.find(code);
    if (it == mcmd.end()) {
      throw new SystemException(ERRCODE_SYSTEM, "Error wrong code to build command: "+cmd);
    }
    it->second += "#";
    if (cmd.compare("") == 0) {
      it->second += " ";
    } else {
      it->second += cmd;
    }
    return 0;
  }

  // Else creating a new unique key and insert in the map
  pthread_mutex_lock(&mutex);
  size = mcmd.size() + 1;
  while (true) {
    it = mcmd.find(size);
    if (it == mcmd.end()) {
      break;
    }
    size++;
  }
  getKey(cmd, keycode);
  key = convertToString(keycode);
  mcmd.insert(pair<int, string>(size, key));
  pthread_mutex_unlock(&mutex);
  return size;
}

string
UMSMapper::decode(const string& msg) {
  vector<unsigned int> separatorPos;
  string      func;
  int         funcCode;
  string res;

  // Getting separator position
  findSeparator(msg, separatorPos);

  // Getting function code
  if (!separatorPos.empty()) {
    func = msg.substr(0, separatorPos.at(0));
  } else {
    func = msg;
  }

  // Convert code to int
  funcCode = convertToInt(func);

  switch (funcCode) {
  case VISHNU_CONNECT           	    :
    break;
  case VISHNU_RECONNECT 	  	:
    break;
  case VISHNU_CLOSE 	          	:
    res = decodeClose(separatorPos, msg);
    break;
  case VISHNU_ADD_VISHNU_USER   	:
    res = decodeAddUser(separatorPos, msg);
    break;
  case VISHNU_UPDATE_VISHNU_USER	:
    res = decodeUpUser(separatorPos, msg);
    break;
  case VISHNU_DELETE_VISHNU_USER	:
    res = decodeDelUser(separatorPos, msg);
    break;
  case VISHNU_CHANGE_PASSWORD   	:
    res = decodeChangePwd(separatorPos, msg);
    break;
  case VISHNU_RESET_PASSWORD    	:
    res = decodeResetPwd(separatorPos, msg);
    break;
  case VISHNU_ADD_LOCAL_ACCOUNT 	:
    res = decodeAddAcc(separatorPos, msg);
    break;
  case VISHNU_UPDATE_LOCAL_ACCOUNT    :
    res = decodeUpAcc(separatorPos, msg);
    break;
  case VISHNU_DELETE_LOCAL_ACCOUNT    :
    res = decodeDelAcc(separatorPos, msg);
    break;
  case VISHNU_ADD_MACHINE 	       :
    res = decodeAddM(separatorPos, msg);
    break;
  case VISHNU_UPDATE_MACHINE 	   	:
    res = decodeUpM(separatorPos, msg);
    break;
  case VISHNU_DELETE_MACHINE 	   	:
    res = decodeDelM(separatorPos, msg);
    break;
  case VISHNU_LIST_LOCAL_ACCOUNT      :
    res = decodeListAcc(separatorPos, msg);
    break;
  case VISHNU_LIST_MACHINE 	       :
    res = decodeListM(separatorPos, msg);
    break;
  case VISHNU_LIST_HISTORY_CMD        :
    res = decodeListH(separatorPos, msg);
    break;
  case VISHNU_LIST_OPTIONS 	       :
    res = decodeListOp(separatorPos, msg);
    break;
  case VISHNU_LIST_USERS 	        :
    res = decodeListUser(separatorPos, msg);
    break;
  case VISHNU_LIST_SESSIONS 	        :
    res = decodeListSession(separatorPos, msg);
    break;
  case VISHNU_CONFIGURE_DEFAULT_OPTION:
    res = decodeConfDefaultOp(separatorPos, msg);
    break;
  case VISHNU_CONFIGURE_OPTION	:
    res = decodeConfOp(separatorPos, msg);
    break;
  case VISHNU_ADD_AUTHSYS 	:
    res = decodeAddAuthSys(separatorPos, msg);
    break;
  case VISHNU_UPDATE_AUTHSYS    :
    res = decodeUpAuthSys(separatorPos, msg);
    break;
  case VISHNU_DELETE_AUTHSYS    :
    res = decodeDelAuthSys(separatorPos, msg);
    break;
  case VISHNU_ADD_AUTHACC 	:
    res = decodeAddAuthAcc(separatorPos, msg);
    break;
  case VISHNU_UPDATE_AUTHACC    :
    res = decodeUpAuthAcc(separatorPos, msg);
    break;
  case VISHNU_DELETE_AUTHACC    :
    res = decodeDelAuthAcc(separatorPos, msg);
    break;
  case VISHNU_LIST_AUTHSYS 	        :
    res = decodeListAuthSys(separatorPos, msg);
    break;
  case VISHNU_LIST_AUTHACC 	        :
    res = decodeListAuthAcc(separatorPos, msg);
    break;
  case VISHNU_DEFINE_FID    	:
    res = decodeFid(separatorPos, msg);
    break;
  case VISHNU_DEFINE_TID 	:
    res = decodeTid(separatorPos, msg);
    break;
  case VISHNU_DEFINE_MID 	:
    res = decodeMid(separatorPos, msg);
    break;
  case VISHNU_DEFINE_UID 	:
    res = decodeUid(separatorPos, msg);
    break;
  case VISHNU_DEFINE_AID 	:
    res = decodeAid(separatorPos, msg);
    break;
  case VISHNU_DEFINE_WID 	:
    res = decodeAid(separatorPos, msg);
    break;
  case VISHNU_EXPORT           	    :
    res = decodeExp(separatorPos, msg);
    break;
  default :
    res = "";
    break;
  }
  return res;
}



// %RELAX<MISRA_0_1_3> Because no explicit parameter to close session, useless to parse, just return the function name
string
UMSMapper::decodeClose(vector<unsigned int> separator, const string& msg) {
  return (mmap.find(VISHNU_CLOSE))->second;
}

string
UMSMapper::decodeAddUser(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string u;
  res += (mmap.find(VISHNU_ADD_VISHNU_USER))->second;
  u    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));
  res += getU(u);
  return res;
}

string
UMSMapper::decodeUpUser(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string u;
  res += (mmap.find(VISHNU_UPDATE_VISHNU_USER))->second;
  u    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));
  res += getUupdate(u);
  return res;
}

string
UMSMapper::decodeDelUser(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  res += (mmap.find(VISHNU_DELETE_VISHNU_USER))->second;
  if (!separator.empty()) {
    res += " ";
    res += msg.substr(separator.at(0)+1, msg.size()-separator.at(0));
  }
  return res;
}

string
UMSMapper::decodeChangePwd(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string u;
  res += (mmap.find(VISHNU_CHANGE_PASSWORD))->second;
  res += " ";
  u    = msg.substr(separator.at(0)+1, separator.at(1)-2);
  res += u;
  res += " ";
  u    = msg.substr(separator.at(1)+1, msg.size()-separator.at(1));
  res += u;
  return res;
}

string
UMSMapper::decodeResetPwd(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  res += (mmap.find(VISHNU_RESET_PASSWORD))->second;
  res += " ";
  res += msg.substr(separator.at(0)+1, msg.size()-separator.at(0));
  return res;
}

string
UMSMapper::decodeAddAcc(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string a;
  res += (mmap.find(VISHNU_ADD_LOCAL_ACCOUNT))->second;
  a    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));

  UMS_Data::LocalAccount_ptr ac = NULL;

  // To parse the object serialized
  if (!parseEmfObject(std::string(std::string(a)), ac)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM);
  }

  res += " ";
  res += ac->getUserId();
  res += " ";
  res += ac->getMachineId();
  res += " ";
  res += ac->getAcLogin();
  res += " ";
  res += ac->getHomeDirectory();

  if (ac != NULL) {
    delete ac;
  }

  return res;
}

string
UMSMapper::decodeAddAuthAcc(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string a;
  res += (mmap.find(VISHNU_ADD_AUTHACC))->second;
  a    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));

  UMS_Data::AuthAccount_ptr ac = NULL;

  // To parse the object serialized
  if (!parseEmfObject(std::string(std::string(a)), ac)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM);
  }

  res += " ";
  res += ac->getAuthSystemId();
  res += " ";
  res += ac->getAcLogin();

  a = ac->getUserId();
  if (a.compare("")) {
    res +=" -u ";
    res += a;
  }

  if (ac != NULL) {
    delete ac;
  }

  return res;
}

string
UMSMapper::decodeAddAuthSys(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string a;
  res += (mmap.find(VISHNU_ADD_AUTHSYS))->second;
  a    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));

  UMS_Data::AuthSystem_ptr ac = NULL;

  // To parse the object serialized
  if (!parseEmfObject(std::string(std::string(a)), ac)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM);
  }

  res +=" ";
  res += ac->getName();
  res +=" ";
  res += ac->getURI();
  res +=" ";
  res += ac->getAuthLogin();
  res +=" ";
  res += ac->getAuthPassword();
  res +=" ";
  res += convertToString(ac->getUserPasswordEncryption());
  res +=" ";
  res += convertToString(ac->getType());

  if (ac->getLdapBase().compare("")) {
    res +=" -b ";
    res += ac->getLdapBase();
  }

  if (ac != NULL) {
    delete ac;
  }

  return res;
}



string
UMSMapper::decodeUpAcc(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string a;
  res += (mmap.find(VISHNU_UPDATE_LOCAL_ACCOUNT))->second;
  a    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));

  UMS_Data::LocalAccount_ptr ac = NULL;

  // To parse the object serialized
  if (!parseEmfObject(std::string(std::string(a)), ac)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM);
  }

  a = ac->getAcLogin();
  if (a.compare("")) {
    res+=" -l ";
    res+=a;
  }
  a = ac->getHomeDirectory();
  if (a.compare("")) {
    res+=" -d ";
    res+=a;
  }
  res+=" ";
  res += ac->getUserId();
  res+=" ";
  res += ac->getMachineId();

  if (ac != NULL) {
    delete ac;
  }
  return res;
}


string
UMSMapper::decodeUpAuthAcc(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string a;
  res += (mmap.find(VISHNU_UPDATE_AUTHACC))->second;
  a    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));

  UMS_Data::AuthAccount_ptr ac = NULL;

  // To parse the object serialized
  if (!parseEmfObject(std::string(std::string(a)), ac)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM);
  }

  res+=" ";
  res += ac->getAuthSystemId();

  a = ac->getAcLogin();
  if (a.compare("")) {
    res+=" -l ";
    res += a;
  }

  a = ac->getUserId();
  if (a.compare("")) {
    res+=" -u ";
    res += a;
  }

  if (ac != NULL) {
    delete ac;
  }
  return res;
}

string
UMSMapper::decodeUpAuthSys(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string a;
  res += (mmap.find(VISHNU_UPDATE_AUTHSYS))->second;
  a    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));

  UMS_Data::AuthSystem_ptr ac = NULL;

  // To parse the object serialized
  if (!parseEmfObject(std::string(std::string(a)), ac)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM);
  }

  res+=" ";
  res += ac->getAuthSystemId();

  a = ac->getName();
  if (a.compare("")) {
    res+=" -n ";
    res += a;
  }


  a = ac->getURI();
  if (a.compare("")) {
    res+=" -i ";
    res += a;
  }

  a = ac->getAuthLogin();
  if (a.compare("")) {
    res+=" -u ";
    res += a;
  }

  a = ac->getAuthPassword();
  if (a.compare("")) {
    res+=" -w ";
    res += a;
  }

  a = convertToString(ac->getUserPasswordEncryption());
  if (a.compare("")) {
    res+=" -e ";
    res += a;
  }

  a = convertToString(ac->getType());
  if (a.compare("")) {
    res+=" -t ";
    res += a;
  }

  if (ac->getLdapBase().compare("")) {
    res+=" -b ";
    res += ac->getLdapBase();
  }

  if (ac != NULL) {
    delete ac;
  }

  return res;
}


string
UMSMapper::decodeDelAcc(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string u;
  res += (mmap.find(VISHNU_DELETE_LOCAL_ACCOUNT))->second;
  u    = msg.substr(separator.at(0)+1, separator.at(1)-3);
  res += " ";
  res += u;
  res+= " ";
  u    = msg.substr(separator.at(1)+1, msg.size()-separator.at(1));
  res += u;
  return res;
}

string
UMSMapper::decodeDelAuthSys(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string u;
  res += (mmap.find(VISHNU_DELETE_AUTHSYS))->second;
  res+= " ";
  u    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));
  res += u;
  return res;
}

string
UMSMapper::decodeDelAuthAcc(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string u;
  res += (mmap.find(VISHNU_DELETE_LOCAL_ACCOUNT))->second;
  u    = msg.substr(separator.at(0)+1, separator.at(1)-3);
  res += " ";
  res += u;
  res+= " ";
  u    = msg.substr(separator.at(1)+1, msg.size()-separator.at(1));
  if (u.compare("")) {
    res += " -u ";
    res += u;
  }

  return res;
}

string
UMSMapper::decodeListAuthAcc(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string a;
  res += (mmap.find(VISHNU_LIST_AUTHACC))->second;
  a    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));

  UMS_Data::ListAuthAccOptions_ptr ac = NULL;

  // To parse the object serialized
  if (!parseEmfObject(std::string(std::string(a)), ac)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM);
  }

  if (ac->isListAll()) {
    res+=" -a ";
  }
  a = ac->getUserId();
  if (a.compare("")) {
    res+=" -u ";
    res+=a;
  }
  a = ac->getAuthSystemId();
  if (a.compare("")) {
    res+=" -i ";
    res+=a;
  }

  if (ac != NULL) {
    delete ac;
  }

  return res;
}

string
UMSMapper::decodeListAuthSys(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string a;
  res += (mmap.find(VISHNU_LIST_AUTHSYS))->second;
  a    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));

  UMS_Data::ListAuthSysOptions_ptr ac = NULL;

  // To parse the object serialized
  if (!parseEmfObject(std::string(std::string(a)), ac)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM);
  }

  if (ac->isListAllAuthSystems()) {
    res+=" -a ";
  }

  if (ac->isListFullInfo()) {
    res+=" -a ";
  }

  a = ac->getUserId();
  if (a.compare("")) {
    res+=" -u ";
    res+=a;
  }
  a = ac->getAuthSystemId();
  if (a.compare("")) {
    res+=" -i ";
    res+=a;
  }

  if (ac != NULL) {
    delete ac;
  }

  return res;
}


string
UMSMapper::decodeAddM(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string a;
  res += (mmap.find(VISHNU_ADD_MACHINE))->second;
  a    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));

  UMS_Data::Machine_ptr ac = NULL;

  // To parse the object serialized
  if (!parseEmfObject(std::string(std::string(a)), ac)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM);
  }

  res+=" ";
  res += ac->getName();
  res+=" ";
  res += ac->getSite();
  res+=" ";
  res += ac->getLanguage();

  if (ac != NULL) {
    delete ac;
  }

  return res;
}

string
UMSMapper::decodeUpM(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string a;
  res += (mmap.find(VISHNU_UPDATE_MACHINE))->second;
  a    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));

  UMS_Data::Machine_ptr ac = NULL;

  // To parse the object serialized
  if (!parseEmfObject(std::string(std::string(a)), ac)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM);
  }

  res+= " ";
  res+= ac->getMachineId();
  res+=" ";
  a = ac->getName();
  if (a.compare("")) {
    res+=" -n ";
    res+=a;
  }
  a = ac->getSite();
  if (a.compare("")) {
    res+=" -s ";
    res+=a;
  }
  a = ac->getMachineDescription();
  if (a.compare("")) {
    res+=" -d ";
    res+=a;
  }
  a = convertToString(ac->getStatus());
  if (a.compare("")) {
    res+=" -t ";
    res+=a;
  }
  a = ac->getLanguage();
  if (a.compare("")) {
    res+=" -l ";
    res+=a;
  }

  if (ac != NULL) {
    delete ac;
  }

  return res;
}

string
UMSMapper::decodeDelM(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string u;
  res += (mmap.find(VISHNU_DELETE_MACHINE))->second;
  u    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));
  res += " ";
  res += u;
  return res;
}

string
UMSMapper::decodeListAcc(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string a;
  res += (mmap.find(VISHNU_LIST_LOCAL_ACCOUNT))->second;
  a    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));

  UMS_Data::ListLocalAccOptions_ptr ac = NULL;

  // To parse the object serialized
  if (!parseEmfObject(std::string(std::string(a)), ac)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM);
  }

  if (ac->isAdminListOption()) {
    res+=" -a ";
  }
  a = ac->getUserId();
  if (a.compare("")) {
    res+=" -u ";
    res+=a;
  }
  a = ac->getMachineId();
  if (a.compare("")) {
    res+=" -i ";
    res+=a;
  }

  if (ac != NULL) {
    delete ac;
  }

  return res;
}

string
UMSMapper::decodeListM(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string a;
  res += (mmap.find(VISHNU_LIST_MACHINE))->second;
  a    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));

  UMS_Data::ListMachineOptions_ptr ac = NULL;

  // To parse the object serialized
  if (!parseEmfObject(std::string(std::string(a)), ac)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM);
  }

  a = ac->getUserId();
  if (a.compare("")) {
    res+=" -u ";
    res+=a;
  }
  if (ac->isListAllMachine()) {
    res+=" -a ";
  }
  a = ac->getMachineId();
  if (a.compare("")) {
    res+=" -m ";
    res+=a;
  }

  if (ac != NULL) {
    delete ac;
  }

  return res;
}

string
UMSMapper::decodeListH(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string a;
  long date;
  boost::posix_time::ptime pt;
  res += (mmap.find(VISHNU_LIST_HISTORY_CMD))->second;
  a    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));

  UMS_Data::ListCmdOptions_ptr ac = NULL;

  // To parse the object serialized
  if (!parseEmfObject(std::string(std::string(a)), ac)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM);
  }

  if (ac->isAdminListOption()) {
    res+=" -a ";
  }
  a = ac->getUserId();
  if (a.compare("")) {
    res+=" -u ";
    res+=a;
  }
  a = ac->getSessionId();
  if (a.compare("")) {
    res+=" -i ";
    res+=a;
  }
  date = ac->getStartDateOption();
  if (date>0) {
    pt = boost::posix_time::from_time_t(date);
    a = boost::posix_time::to_simple_string(pt);
    res+=" -s '";
    res+=a;
    res += "'";
  }
  date = ac->getEndDateOption();
  if (date>0) {
    pt = boost::posix_time::from_time_t(date);
    a = boost::posix_time::to_simple_string(pt);
    res+=" -e '";
    res+=a;
    res += "'";
  }

  if (ac != NULL) {
    delete ac;
  }

  return res;
}

string
UMSMapper::decodeListOp(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string a;
  res += (mmap.find(VISHNU_LIST_OPTIONS))->second;
  a    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));

  UMS_Data::ListOptOptions_ptr ac = NULL;

  // To parse the object serialized
  if (!parseEmfObject(std::string(std::string(a)), ac)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM);
  }

  if (ac->isListAllDeftValue()) {
    res+=" -a ";
  }
  a = ac->getUserId();
  if (a.compare("")) {
    res+=" -u ";
    res+=a;
  }
  a = ac->getOptionName();
  if (a.compare("")) {
    res+=" -n ";
    res+=a;
  }

  if (ac != NULL) {
    delete ac;
  }

  return res;
}

string
UMSMapper::decodeListUser(vector<unsigned int> separator, const string& msg) {
  string a;
  string res = string("");
  res += (mmap.find(VISHNU_LIST_USERS))->second;
  a = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));

  UMS_Data::ListUsersOptions_ptr ac = NULL;

  // To parse the object serialized
  if (!parseEmfObject(std::string(std::string(a)), ac)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM);
  }

  a = ac->getUserId();
  if (a.compare("")) {
    res +=" -u ";
    res +=a;
  }

  a = ac->getAuthSystemId();
  if (a.compare("")) {
    res +=" -i ";
    res +=a;
  }

  return res;
}

string
UMSMapper::decodeListSession(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string a;
  long date;
  int delay;
  boost::posix_time::ptime pt;
  res += (mmap.find(VISHNU_LIST_SESSIONS))->second;
  a    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));

  UMS_Data::ListSessionOptions_ptr ac = NULL;

  // To parse the object serialized
  if (!parseEmfObject(std::string(std::string(a)), ac)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM);
  }

  res+=" -t ";
  res += convertToString(ac->getStatus());
  if (ac->getSessionClosePolicy() > 0) {
    res+=" -p ";
    res += convertToString(ac->getSessionClosePolicy());
  }
  a = ac->getMachineId();
  delay = ac->getSessionInactivityDelay();
  if (delay>0) {
    res+=" -d ";
    res += convertToString(delay);
  }
  a = ac->getMachineId();
  if (a.compare("")) {
    res+=" -m ";
    res+=a;
  }
  if (ac->isAdminListOption()) {
    res+=" -a ";
  }
  a = ac->getUserId();
  if (a.compare("")) {
    res+=" -u ";
    res+=a;
  }
  a = ac->getMachineId();
  if (a.compare("")) {
    res+=" -m ";
    res+=a;
  }
  a = ac->getSessionId();
  if (a.compare("")) {
    res+=" -i ";
    res+=a;
  }
  date = ac->getStartDateOption();
  if (date>0) {
    pt =  boost::posix_time::from_time_t(date);
    a = boost::posix_time::to_simple_string(pt);
    res+=" -s '";
    res+=a;
    res += "'";
  }
  date = ac->getEndDateOption();
  if (date>0) {
    pt =  boost::posix_time::from_time_t(date);
    a = boost::posix_time::to_simple_string(pt);
    res+=" -e '";
    res+=a;
    res += "'";
  }

  if (ac != NULL) {
    delete ac;
  }

  return res;
}

string
UMSMapper::decodeConfDefaultOp(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string u;
  u    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));

  UMS_Data::OptionValue_ptr opt = NULL;

  // To parse the object serialized
  if (!parseEmfObject(std::string(std::string(u)), opt)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM);
  }

  res += (mmap.find(VISHNU_CONFIGURE_DEFAULT_OPTION))->second;

  u = opt->getOptionName();
  if (u.compare("") != 0) {
    res += " ";
    res += u;
  }
  u = opt->getValue();
  if (u.compare("") != 0) {
    res += " ";
    res += u;
  }

  if (opt != NULL) {
    delete opt;
  }

  return res;
}

string
UMSMapper::decodeConfOp(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string u;
  res += (mmap.find(VISHNU_CONFIGURE_OPTION))->second;
  u    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));

  UMS_Data::OptionValue_ptr opt = NULL;

  // To parse the object serialized
  if (!parseEmfObject(std::string(std::string(u)), opt)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM);
  }

  u = opt->getOptionName();
  if (u.compare("") != 0) {
    res += " ";
    res += u;
  }
  u = opt->getValue();
  if (u.compare("") != 0) {
    res += " ";
    res += u;
  }

  if (opt != NULL) {
    delete opt;
  }

  return res;
}


string
UMSMapper::getU(string serial) {
  string res = string("");
  string tmp;

  UMS_Data::User_ptr user = NULL;

  // To parse the object serialized
  if (!parseEmfObject(std::string(std::string(serial)), user)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM);
  }

  tmp = user->getFirstname();
  if (tmp.compare("") != 0) {
    res+=" ";
    res += user->getFirstname();
  }
  tmp = user->getLastname();
  if (tmp.compare("") != 0) {
    res+=" ";
    res += user->getLastname();
  }

  if (user->getPrivilege()>0) {
    res+=" ";
    res += convertToString(user->getPrivilege());
  } else {
    res += " 0";
  }
  tmp = user->getEmail();
  if (tmp.compare("") != 0) {
    res+=" ";
    res += user->getEmail();
  }

  if (user != NULL) {
    delete user;
  }

  return res;
}

string
UMSMapper::getUupdate(string serial) {
  string res = string("");
  string tmp;

  UMS_Data::User_ptr user = NULL;

  // To parse the object serialized
  if (!parseEmfObject(std::string(std::string(serial)), user)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM);
  }

  res+= " ";
  res += user->getUserId();

  tmp = user->getFirstname();
  if (tmp.compare("") != 0) {
    res +=" -f ";
    res += user->getFirstname();
  }
  tmp = user->getLastname();
  if (tmp.compare("") != 0) {
    res +=" -l ";
    res += user->getLastname();
  }

  if (user->getPrivilege()>0) {
    res+=" -p  ";
    res += convertToString(user->getPrivilege());
  } else {
    res += " -p ";
    res += " 0";
  }
  tmp = user->getEmail();
  if (tmp.compare("") != 0) {
    res +=" -m ";
    res += user->getEmail();
  }

  if (user != NULL) {
    delete user;
  }
  return res;
}

string
UMSMapper::decodeFid(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string u;
  res += (mmap.find(VISHNU_DEFINE_FID))->second;
  res += " ";
  u    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));
  res += u;
  return res;
}

string
UMSMapper::decodeMid(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string u;
  res += (mmap.find(VISHNU_DEFINE_MID))->second;
  res += " ";
  u    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));
  res += u;
  return res;
}

string
UMSMapper::decodeAid(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string u;
  res += (mmap.find(VISHNU_DEFINE_AID))->second;
  res += " ";
  u    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));
  res += u;
  return res;
}

string
UMSMapper::decodeUid(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string u;
  res += (mmap.find(VISHNU_DEFINE_UID))->second;
  res += " ";
  u    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));
  res += u;
  return res;
}
string
UMSMapper::decodeTid(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string u;
  res += (mmap.find(VISHNU_DEFINE_TID))->second;
  res += " ";
  u    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));
  res += u;
  return res;
}
string
UMSMapper::decodeWid(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string u;
  res += (mmap.find(VISHNU_DEFINE_WID))->second;
  res += " ";
  u    = msg.substr(separator.at(0)+1, msg.size()-separator.at(0));
  res += u;
  return res;
}

string
UMSMapper::decodeExp(vector<unsigned int> separator, const string& msg) {
  string res = string("");
  string u;
  res += (mmap.find(VISHNU_EXPORT))->second;
  res += " ";
  u    = msg.substr(separator.at(0)+1, separator.at(1)-2);
  res += u;
  res += " ";
  u    = msg.substr(separator.at(1)+1, msg.size()-separator.at(1));
  res += u;
  return res;
}
