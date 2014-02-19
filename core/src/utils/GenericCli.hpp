#ifndef GENERIC_CLI_HPP
#define GENERIC_CLI_HPP


#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <string>

#include "cliError.hpp"
#include "CLICmd.hpp"
#include "utilVishnu.hpp"
#include "UserException.hpp"
#include "cliUtil.hpp"
#include "sessionUtils.hpp"
#include "Options.hpp"
#include "api_ums.hpp"  // for vishnuInitialize


namespace po = boost::program_options;

/**
 * \brief A generic class to handle some command line operations like run a
 * function
 * \param function the api function
 * \param configFile the VISHNU client config file
 * \param ac The number of command line arguments
 * \param av The command line arguments
 * \return 0 if it succeeds or an error code otherwise
 */


class GenericCli {

public:
  /**
     * \brief A generic class to handle some command line operations like run a
     * function
     * \param function the api function
     * \param configFile the VISHNU client config file
     * \param ac The number of command line arguments
     * \param av The command line arguments
     * \return 0 if it succeeds or an error code otherwise
     */


  template <class ApiFunc>
  int run(ApiFunc function, std::string configFile, int ac, char*  av[]) {

    try {
      if (vishnu::vishnuInitialize(const_cast<char*>(configFile.c_str()), ac, av)) {
        errorUsage(av[0],communicationErrorMsg,EXECERROR);
        return  ERRCODE_CLI_ERROR_COMMUNICATION ;
      }

      std::string sessionKey = getLastSessionKey(getpid());

      // VISHNU call
      if(! sessionKey.empty()){
        return function(sessionKey);
      }
      errorUsage(av[0],"cannot retrieve sessionKey");
      return CLI_ERROR_RUNTIME;

    } catch(VishnuException& e){// catch all Vishnu runtime error
      std::string  msg = e.getMsg()+" ["+e.getMsgComp()+"]";
      errorUsage(av[0], msg,EXECERROR);
      //check the bad session key
      if (checkBadSessionKeyError(e)){
        removeBadSessionKeyFromFile(getppid());
      }
      return e.getMsgI() ;
    } catch(std::exception& e){// catch all std runtime error
      errorUsage(av[0],e.what());
      return ERRCODE_CLI_ERROR_RUNTIME;
    }

  }

  /**
     * \brief A generic class to handle some command line operations like run a
     * functioni without managing the session
     * \param function the api function
     * \param configFile the VISHNU client config file
     * \param ac The number of command line arguments
     * \param av The command line arguments
     * \return 0 if it succeeds or an error code otherwise
     */


  template <class ApiFunc>
  int runWithoutSessionKey(ApiFunc function, std::string configFile, int ac, char*  av[]) {

    try{

      // initializing VISHNU

      if (vishnu::vishnuInitialize(const_cast<char*>(configFile.c_str()), ac, av)) {

        errorUsage(av[0],communicationErrorMsg,EXECERROR);

        return  ERRCODE_CLI_ERROR_COMMUNICATION ;
      }

      //call of the api fuction
      int ret =function();
      return ret;
    } catch(VishnuException& e){// catch all Vishnu runtime error
      std::string  msg = e.getMsg()+" ["+e.getMsgComp()+"]";
      errorUsage(av[0], msg,EXECERROR);
      return e.getMsgI() ;
    } catch(std::exception& e){// catch all std runtime error
      errorUsage(av[0],e.what());
      return ERRCODE_CLI_ERROR_RUNTIME;
    }

  }


  /**
     * \brief To parse command line options
     * \param opt the description of the command line options
     * \param isEmpty To check if command line does not contain option
     * \param ac The number of command line arguments
     * \param av The command line arguments
     * \param signature The signature of the command
     */
  void
  processListOpt(const boost::shared_ptr<Options>& opt, bool& isEmpty,
                 int ac, char*  av[],
                 const std::string& signature = "") {
    CLICmd cmd = CLICmd (ac, av, opt);

    try {
      opt->parse_cli(ac, av);

      isEmpty = opt->empty(); //if no value was given in the command line
      // Parse the cli and setting the options found
      int ret = cmd.parse(env_name_mapper());

      if (ret != VISHNU_OK) {
        helpUsage(*opt, signature);
        exit(ret);
      }

      // PreProcess (adapt some parameters if necessary)
      checkVishnuConfig(*opt);
      if (opt->count("help")) {
        helpUsage(*opt, signature);
        exit(VISHNU_OK);
      }
    } catch(po::error& e) { // catch all other bad parameter errors
      helpUsage(*opt, signature);
      exit(ERRCODE_INVALID_PARAM);
    } catch(std::exception& e) {// catch all std runtime error
      errorUsage(av[0],e.what());
      exit(ERRCODE_INVALID_PARAM);
    }
  }
};

#endif
