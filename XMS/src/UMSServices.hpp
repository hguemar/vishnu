/**
 * \file UMSServices.hpp
 * \brief This file lists the services provided by UMS servers.
 * \author Benjamin Depardon (benjamin.depardon@sysfera.com)
 * \date 21/02/2013
 */

#ifndef _UMSSERVICES_HPP_
#define _UMSSERVICES_HPP_


/**
 * \brief UMS services enumeration
 */
typedef enum {
  SESSIONCONNECT = 0,
  SESSIONRECONNECT,
  SESSIONCLOSE,
  USERCREATE,
  USERUPDATE,
  USERDELETE,
  USERPASSWORDCHANGE,
  USERPASSWORDRESET,
  MACHINECREATE,
  MACHINEUPDATE,
  MACHINEDELETE,
  LOCALACCOUNTCREATE,
  LOCALACCOUNTUPDATE,
  LOCALACCOUNTDELETE,
  OPTIONVALUESET,
  OPTIONVALUESETDEFAULT,
  SESSIONLIST,
  LOCALACCOUNTLIST,
  MACHINELIST,
  COMMANDLIST,
  OPTIONVALUELIST,
  USERLIST,
  RESTORE,
  AUTHSYSTEMCREATE,
  AUTHSYSTEMUPDATE,
  AUTHSYSTEMDELETE,
  AUTHSYSTEMLIST,
  AUTHACCOUNTCREATE,
  AUTHACCOUNTUPDATE,
  AUTHACCOUNTDELETE,
  AUTHACCOUNTLIST,
  INT_DEFINEUSERIDENTIFIER,
  INT_DEFINEJOBIDENTIFIER,
  INT_DEFINETRANSFERIDENTIFIER,
  INT_DEFINEMACHINEIDENTIFIER,
  INT_DEFINEAUTHIDENTIFIER,
  INT_DEFINEWORKIDENTIFIER,
  EXPORT,
  NB_SRV_UMS  // MUST always be the last
} ums_service_t;

static const char* SERVICES_UMS[NB_SRV_UMS] = {
  "sessionConnect",  // 0
  "sessionReconnect",  // 1
  "sessionClose",  // 2
  "userCreate",  // 3
  "userUpdate",  // 4
  "userDelete",  // 5
  "userPasswordChange",  // 6
  "userPasswordReset",  // 7
  "machineCreate",  // 8
  "machineUpdate",  // 9
  "machineDelete",  // 10
  "localAccountCreate",  // 11
  "localAccountUpdate",  // 12
  "localAccountDelete",  // 13
  "optionValueSet",  // 16
  "optionValueSetDefault",  // 17
  "sessionList",  // 18
  "localAccountList",  // 19
  "machineList",  // 20
  "commandList",  // 21
  "optionValueList",  // 22
  "userList",  // 23
  "restore",  // 24
  "authSystemCreate",  // 25
  "authSystemUpdate",  // 26
  "authSystemDelete",  // 27
  "authSystemList",  // 28
  "authAccountCreate",  // 29
  "authAccountUpdate",  // 30
  "authAccountDelete",  // 31
  "authAccountList",  // 32
  "int_defineUserIdentifier", // 33
  "int_defineJobIdentifier", // 34
  "int_defineTransferIdentifier", // 35
  "int_defineMachineIdentifier", // 36
  "int_defineAuthIdentifier", // 37
  "int_defineWorkIdentifier", // 38
  "exportCommands" // 40
};

// FIXME: compilation fails without inlining
// needs to be moved in an implementation file
inline bool
isMachineSpecificServicesUMS(unsigned id) {
  return false;
}


#endif  // _UMSSERVICES_HPP_
