
#ifndef _CONSTANTS_HPP_
#define _CONSTANTS_HPP_

#include <string>
#include <map>

namespace vishnu {
  /**
 * \brief Define a constant type
 */
  typedef enum {
    NONE_PARAMETER,
    BOOL_PARAMETER,
    INT_PARAMETER,
    ULONG_PARAMETER,
    STRING_PARAMETER,
    URI_PARAMETER
  } c_type_t ;

  /**
 * \brief Define a parameter type
 */

  typedef enum {
    VISHNUID=0,
    DBTYPE,
    DBHOST,
    DBPORT,
    DBNAME,
    DBUSERNAME,
    DBPASSWORD,
    SENDMAILSCRIPT,
    BATCHTYPE,
    BATCHVERSION,
    MACHINEID,
    TIMEOUT,
    REMOTEBINDIR,
    INTERVALMONITOR,
    DBPOOLSIZE,
    AUTHENTYPE,
    DEFAULTBATCHCONFIGFILE,
    URISUPERVISOR,
    DISP_URIADDR,
    DISP_URISUBS,
    DISP_NBTHREAD,
    HOST_URIADDR,
    SED_URIADDR,
    CLOUDENDPOINT,
    DEBUG_LEVEL,
    DB_USE_SSL,
    DB_SSL_CA_FILE,
    USE_SSL,
    SERVER_PUBLIC_KEY,
    SERVER_PRIVATE_KEY,
    SERVER_SSL_CERTICATE,
    SSL_CA,
    SUBSCRIBE,
    STANDALONE,
    HAS_UMS,
    HAS_TMS
  } param_type_t;

  /**
 * \brief For cloud
 */
  typedef enum {
    CLOUD_ENDPOINT,
    CLOUD_USER,
    CLOUD_USER_PASSWORD,
    CLOUD_TENANT,
    CLOUD_VM_IMAGE,
    CLOUD_VM_USER,
    CLOUD_VM_USER_KEY,
    CLOUD_CONTEXT_INIT,
    CLOUD_VIRTUAL_NET,
    CLOUD_VIRTUAL_NET_MASK,
    CLOUD_VIRTUAL_NET_DNS,
    CLOUD_VIRTUAL_NET_GATEWAY,
    CLOUD_DEFAULT_FLAVOR,
    CLOUD_NFS_SERVER,
    CLOUD_NFS_MOUNT_POINT
  } cloud_env_vars_t;

  /**
 * \brief States of jobs
 */
  typedef enum {
    STATE_UNDEFINED=0,
    STATE_SUBMITTED=1,
    STATE_QUEUED=2,
    STATE_WAITING=3,
    STATE_RUNNING=4,
    STATE_COMPLETED=5,
    STATE_CANCELLED=6,
    STATE_DOWNLOADED=7,
    STATE_FAILED=8
  } job_status_t;

  /**
   * \brief States of components
   */
  typedef enum {
    STATUS_UNDEFINED=-1,
    STATUS_LOCKED=0,
    STATUS_ACTIVE=1,
    STATUS_DELETED=2
  } component_status_t;

  typedef enum {
    SESSION_CLOSED=0,
    SESSION_ACTIVE=1
  }session_state_t;

  typedef enum {
    PRIVILEGE_UNDEFINED = -1,
    PRIVILEGE_USER = 0,
    PRIVILEGE_ADMIN = 1
  } privilege_type_t;

  /**
 * \brief A convenient data type to store a parameter
 */
  struct param_t {
    /**
   * \brief key to retrieve the parameter
   */
    param_type_t key;
    /**
   * \brief the value of the parameter
   */
    const std::string value;
    /**
   * \brief the type of the parameter
   */
    c_type_t type;
  };

  /**
 * \brief An array to store all parameters
 */
  extern param_t params[];  //%RELAX<MISRA_3_1_3> Because this table is defined in constants.cpp
  extern std::map<cloud_env_vars_t, std::string> CLOUD_ENV_VARS;
}

#endif /* _CONSTANTS_HPP_ */
