/**
  * \file JobProxy.hpp
  * \brief This file contains the VISHNU JobProxy class.
  * \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
  * \date March 2011
  */

#ifndef _JOB_PROXY_H
#define _JOB_PROXY_H

#include "TMS_Data.hpp"
/**
 * \class JobProxy
 * \brief JobProxy class implementation
 */
class JobProxy {

public:

  /**
  * \param sessionKey The object which encapsulates the session information
  * \param machineId The id of the machine. Optional
  * \brief Constructor
  */
  explicit JobProxy(const std::string& sessionKey,
                    const std::string& machineId = "");
  /**
  * \brief Function to submit job
  * \param scriptPath the local path of the script
  * \param scriptContent the content of the script
  * \param options the options to submit job
  * \return raises an exception on error
  */
  int
  submitJob(const std::string& scriptPath,
            const std::string& scriptContent,
            const TMS_Data::SubmitOptions& options);

  
  /**
  * \brief Function to cancel job
  * \param options An object containing options
  * \return raises an exception on error
  */
  int
  cancelJob(const TMS_Data::CancelOptions& options);

  /**
   * \brief Function to get job information
   * \param jobId the identifier of the job
   * \return raises an exception on error
   */
  TMS_Data::Job
  getJobInfo(const std::string& jobId);

  /**
  * \brief Function to get job information
  * \return The job data structure
  */
  TMS_Data::Job
  getData() const;

  /**
    * \brief Destructor
    */
  ~JobProxy();

private:

  /////////////////////////////////
  // Attributes
  /////////////////////////////////

  /**
  * \brief The session object
  */
  std::string msessionKey;
  /**
  * \brief The job data structure
  */
  TMS_Data::Job mjob;
  /**
  * \brief The id of the machine
  */
  std::string mmachineId;

};
#endif //_JOB_PROXY_H
