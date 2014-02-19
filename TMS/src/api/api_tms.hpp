/**
 * \file api_tms.hpp
 * \brief This file contains the VISHNU api functions for TMS package.
 * \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
 * \date March 2011
 */

#ifndef _API_TMS_H
#define _API_TMS_H

#include <iostream>
#include <string>

#include "UserException.hpp"
#include "SystemException.hpp"
#include "UMSVishnuException.hpp"
#include "TMSVishnuException.hpp"
#include "TMS_Data.hpp"
#include "UMS_Data/Session.hpp"


namespace vishnu {
  /**
  * \brief The submitJob function submits job on a machine through the use of a script (scriptFilePath).
  * \param session : Session information
  * \param scriptFilePath : The path to the file containing the characteristics (job command, and batch scheduler directive required or optional) of the job to submit.
  * \param jobInfo : The  Job object containing the output information (ex: jobId and jobPath) of the job to submit
  * \param options : Is an instance of the class SubmitOptions. Each optionnal value is associated to a set operation (e.g: setNbCpu(...)) in the class SubmitOptions.  If no set operation is not called on the instance object  options, the job is submitted with the options defined in the scriptFilePath. Otherewise the job is submitted with the optionnal values set by the options object and optionnal values defined in the scriptFilePath, but optionnal values set by SubmitOptions object take precedence over those in scriptFilePath. With in the object options or within the scriptFilePath, the last occurance of an optionnal value takes precedence over earlier occurance.
  * \return int : an error code
  */
  int
  submitJob(const std::string& sessionKey,
            const std::string& scriptFilePath,
            TMS_Data::Job& jobInfo,
            const TMS_Data::SubmitOptions& options = TMS_Data::SubmitOptions())
  throw (UMSVishnuException, TMSVishnuException, UserException, SystemException);


  /**
  * \brief Add a work
  * \param sessionKey the session key
  * \param newWork the work to add
  * \param options the options to add the work
  * \return an exception on error, 0 otherwize
  */
  int
  addWork(const std::string& sessionKey,
          TMS_Data::Work& newWork,
          const TMS_Data::AddWorkOptions& options = TMS_Data::AddWorkOptions())
  throw (UMSVishnuException, TMSVishnuException, UserException, SystemException);


  /**
  * \brief The cancelJob function cancels a job from its id
  * \param session : The session information
  * \param options : An object containing user-provided options
  * \return int : an error code
  */
  int
  cancelJob(const std::string& sessionKey,
            const TMS_Data::CancelOptions& options)
  throw (UMSVishnuException, TMSVishnuException, UserException, SystemException);

  /**
  * \brief The getJobInfo function gets information on a job from its id
  * \param session: The session information
  * \param jobId: The id of the job
  * \param jobInfos: The resulting information on the job
  * \return int: an error code
  */
  int
  getJobInfo(const std::string& sessionKey,
             const std::string& jobId,
             TMS_Data::Job& jobInfos)
  throw (UMSVishnuException, TMSVishnuException, UserException, SystemException);

  /**
  * \brief The listJobs function gets a list of all submitted jobs
  * \param sessionKey : The session key
  * \param listOfJobs : The constructed object list of jobs
  * \param options : Additional options for jobs listing
  * \return int : an error code
  */
  int
  listJobs(const std::string& sessionKey,
           TMS_Data::ListJobs& listOfJobs,
           const TMS_Data::ListJobsOptions& options = TMS_Data::ListJobsOptions())
  throw (UMSVishnuException, TMSVishnuException, UserException, SystemException);

  /**
   * \brief getJobProgress: function gets the progression status of jobs
   * \param sessionKey: The session key
   * \param listOfProgress: The object containing jobs progression information
   * \param options: The object containing the available options jobs for progression .
   * \return int: an error code
  */
  int
  getJobProgress(const std::string& sessionKey,
                 TMS_Data::ListProgression& listOfProgress,
                 const TMS_Data::ProgressOptions& options = TMS_Data::ProgressOptions())
  throw (UMSVishnuException, TMSVishnuException, UserException, SystemException);

  /**
  * \brief The listQueues function gets queues information
  * \param sessionKey : The session key
  * \param machineId : The id of the machine
  * \param listofQueues : The list of queues
  * \param queueName The option value, if it is given, listQueues gives information only of this queue
  * \return int : an error code
  */
  int
  listQueues(const std::string& sessionKey,
             const std::string& machineId,
             TMS_Data::ListQueues& listofQueues,
             const std::string& queueName = std::string())
  throw (UMSVishnuException, TMSVishnuException, UserException, SystemException);


  /**
   * \brief The getJobOutput function gets outputPath and errorPath of a job from its id
   * \param session : The session information
   * \param jobId : The Id of the job
   * \param outputInfo : The  Job object  containing the job output information (ex: outputPath and errorPath) of the job to submit
   * \param options : Object containing the user-provided options (e.g: it contains a possible output directory set by the user)
   * \return 0 on success, or raises exception on error
   */
  int
  getJobOutput(const std::string& sessionKey,
               const std::string& jobId,
               TMS_Data::JobResult& outputInfo,
               const TMS_Data::JobOutputOptions& options)
  throw (UMSVishnuException, TMSVishnuException, UserException, SystemException);

  /**
   * \brief The getCompletedJobsOutput() function gets standard output and error output files
   * of completed jobs (applies only once for each job)
   * \param sessionKey: The session key
   * \param listOfResults : Is the list of jobs results
   * \param options: Object containing options
   * \param listOfResults : Is the list of jobs results
   * \return int: an error code
   */
  int
  getCompletedJobsOutput(const std::string& sessionKey,
                         TMS_Data::ListJobResults& listOfResults,
                         const TMS_Data::JobOutputOptions& options)
  throw (UMSVishnuException, TMSVishnuException, UserException, SystemException);

}//END namespace vishnu

#endif
