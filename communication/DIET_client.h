//
// DIET_client.h
// Mock de la couche DIET par ZMQ dans VISHNU pour UMS
// Le 02/05/2012
// Auteur K. COULOMB
//

#ifndef __DIETMOCK__
#define __DIETMOCK__

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "sslhelpers.hpp"
#include "Server.hpp"

namespace TMS_Data  {
  class Job;
}

/**
 * \brief Separator for zmq communication
 */
#define VISHNU_COMM_SEPARATOR "$$$$####$$$$"
/**
 * \brief Separator for zmq communication (regex form)
 */
#define VISHNU_COMM_REGEX     "\\${4}\\#{4}\\${4}"
/**
 * \brief Short timeout
 */
#define SHORT_TIMEOUT 2
/**
 * \brief Overload of DIET structure
 */
typedef struct diet_profile_t {
  /**
   * \brief Overload of DIET param, last IN param in the array
   */
  int IN;
  /**
   * \brief Overload of DIET param, last INOUT param in the array
   */
  int INOUT;
  /**
   * \brief Overload of DIET param, last OUT param in the array
   */
  int OUT;
  /**
   * \brief Overload of DIET param, name of the service
   */
  std::string name;
  /**
   * \brief Overload of DIET param
   */
  std::vector<std::string> params;
} diet_profile_t;



/**
 * \brief Overload of DIET function, allocate the profile of a service
 * \param name The name of the service
 * \param IN number of IN parameters
 * \param INOUT number of IN+INOUT parameters
 * \param OUT number of IN+INOUT+OUT parameters
 * \return The allocated profile
 */
diet_profile_t*
diet_profile_alloc(const std::string &name, int IN, int INOUT, int OUT);

/**
 * \brief Overload of DIET function, set a param value in a profile to a string(char *)
 * \param prof The profile
 * \param pos The position of the desired parameter
 * \param value The value to set
 * \return 0 on success, an error code otherwise
 */
int
diet_string_set(diet_profile_t* prof, int pos, const std::string& value = "");

/**
 * \brief Overload of DIET function, call to a DIET service
 * \param prof The profile of the service to call
 * \return 0 on success, an error code otherwise
 */
int
diet_call(diet_profile_t* prof);

/**
 * \brief Generic function created to encapsulate the code
 */
int
diet_call_gen(diet_profile_t* prof, const std::string& uri, bool shortTimeout = false);
/**
 * \brief Generic function created to encapsulate the code
 */
int
abstract_call_gen(diet_profile_t* prof, const std::string& uri, bool shortTimeout = false);
/**
 * @brief ssl_call_gen
 * @param prof
 * @param host
 * @param port
 * @param cafile
 * @return
 */
int
ssl_call_gen(diet_profile_t* prof,
             const std::string& host,
             const int& port,
             const std::string& cafile);

/**
 * \brief Overload of DIET function, get the value of a string in the profile
 * \param prof profile
 * \param value the output value
 * \param pos
 * \return 0 on success, an error code otherwise
 */
int
diet_string_get(diet_profile_t* prof, int pos, std::string& value);

/**
 * \brief Overload of DIET function, free an allocated profile
 * \param prof The profile to free
 * \return 0 on success, an error code otherwise
 */
int
diet_profile_free(diet_profile_t* prof);

/**
 * @brief getTimeout
 * @return
 */
int
getTimeout();

/**
 * \brief To deserialize a profile
 * \param prof The serialized profile
 * \return The deserialized profile
 */
boost::shared_ptr<diet_profile_t>
my_deserialize(const std::string& prof);

/**
 * \brief To serialize a profile
 * \param prof The profile
 * \return The serialized profile
 */
std::string
my_serialize(diet_profile_t* prof);


/**
 * \brief To serialize a profile into a json string
 * \param prof The profile
 * \return The serialized json profile
 */
std::string
json_serialize(diet_profile_t* prof);

/**
 * \brief To serialize a job into a json stringt
 * \param job The job
 * \return The serialized json profile
 */
std::string
json_serialize(const TMS_Data::Job& job);

/**
 * \brief To deserialize a json encoded profile
 * \param prof The json string
 * \return The deserialized profile
 */
boost::shared_ptr<diet_profile_t>
json_deserialize(const std::string& encodedJson);

/**
 * \brief Overload of DIET function, to initialize
 * \param cfg DEPRECATED, kept for compatibility
 * \param argc DEPRECATED, kept for compatibility
 * \param argv DEPRECATED, kept for compatibility
 * \return 0 on success, an error code otherwise or throws exceptions:
 *         (SystemException, UserException, std::exception)
 */
int
diet_initialize(const char* cfg, int argc, char** argv);

/**
 * \brief To ask something to the dispatcher and get the answer
 * \param requestData The request for the dispatcher
 * \param response The answer from the dispatcher
 * \return 0 on success
 */
int
communicate_dispatcher(const std::string& requestData, std::string& response, bool shortTimeout = false);

/**
 * \brief Extract the servers from a serialized message list
 * \param msg : The message
 * \param res : vector of deserialized servers
 */
void
extractServersFromMessage(std::string msg, std::vector<boost::shared_ptr<Server> >& res);
/**
 * \brief Fill servers with a list of servers from config file
 */
void
getServersListFromConfig(std::vector<boost::shared_ptr<Server> >& allServers);
#endif // __DIETMOCK__
