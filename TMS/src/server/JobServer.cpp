/**
 * \file JobServer.cpp
 * \brief This file contains the VISHNU JobServer class.
 * \author Daouda Traore (daouda.traore@sysfera.com)
 * \date April 2011
 */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/format.hpp>
#include <boost/scoped_ptr.hpp>
#include "JobServer.hpp"
#include "TMSVishnuException.hpp"
#include "LocalAccountServer.hpp"
#include "SSHJobExec.hpp"
#include "utilVishnu.hpp"
#include "utilServer.hpp"
#include "DbFactory.hpp"
#include "ScriptGenConvertor.hpp"
#include "api_fms.hpp"
#include "utils.hpp"
#include "BatchFactory.hpp"
#include <pwd.h>
#include <cstdlib>


/**
 * \brief Constructor
 * \param authKey The session info
 * \param machineId The machine identifier
 * \param job The job data structure
 * \param sedConfig A pointer to the SeD configuration
 */
JobServer::JobServer(const std::string& authKey,
                     const std::string& machineId,
                     const ExecConfiguration_Ptr sedConfig)
  : mauthKey(authKey), mmachineId(machineId), mjob(TMS_Data::Job()), msedConfig(sedConfig) {

  DbFactory factory;
  mdatabaseInstance = factory.getDatabaseInstance();

  if (msedConfig) {
    std::string value;
    msedConfig->getRequiredConfigValue<std::string>(vishnu::BATCHTYPE, value);
    mbatchType = vishnu::convertToBatchType(value);

    if (mbatchType != DELTACLOUD) {
      msedConfig->getRequiredConfigValue<std::string>(vishnu::BATCHVERSION, value);
      mbatchVersion = value;
    } else {
      mbatchVersion = "";
    }
  }

  vishnu::validateAuthKey(mauthKey, mmachineId, mdatabaseInstance, muserSessionInfo);
}


/**
 * \brief Destructor
 */
JobServer::~JobServer() { }

/**
 * \brief Function to submit job
 * \param scriptContent the content of the script
 * \param options a json object describing options
 * \param vishnuId The VISHNU identifier
 * \param defaultBatchOption The default batch options
 * \return raises an exception on error
 */
int JobServer::submitJob(std::string& scriptContent,
                         JsonObject* options,
                         const int& vishnuId,
                         const std::vector<std::string>& defaultBatchOption)
{
  bool standaloneSed;
  if (! msedConfig->getConfigValue<bool>(vishnu::STANDALONE, standaloneSed)) {
    standaloneSed = false;
  }

  mlastError.clear();
  int errCode = ERRCODE_RUNTIME_ERROR;
  try {

    // Get user info
    std::string vishnuJobId = vishnu::getObjectId(vishnuId, "formatidjob", vishnu::JOB, mmachineId);
    mjob.setSubmitMachineId(mmachineId);
    mjob.setJobId(vishnuJobId);
    mjob.setStatus(vishnu::STATE_UNDEFINED);
    mjob.setOutputDir("");
    mjob.setWorkId(options->getIntProperty("workid"));
    mjob.setJobPath(options->getStringProperty("scriptpath"));

    if (options->getIntProperty("posix")) {
      mbatchType = POSIX;
    }

    std::string suffix = vishnuJobId+vishnu::createSuffixFromCurTime();
    setRealPaths(options, suffix);
    if (scriptContent.find("VISHNU_OUTPUT_DIR") != std::string::npos || mbatchType == DELTACLOUD ) {
      setJobOutputDir(options->getStringProperty("workingdir"), suffix, scriptContent);
    }

    std::string scriptPath = options->getStringProperty("scriptpath");
    vishnu::saveInFile(scriptPath, processScript(scriptContent,
                                                 options,
                                                 defaultBatchOption,
                                                 muserSessionInfo.machine_name)
                       );
    if(0 != chmod(scriptPath.c_str(),
                  S_IRUSR|S_IXUSR|
                  S_IRGRP|S_IXGRP|
                  S_IROTH|S_IXOTH)) {
      throw SystemException(ERRCODE_INVDATA, "Unable to make the script executable" + scriptPath) ;
    }

    if (standaloneSed) {
      handleSshSubmit(scriptPath, options);
    } else {
      handleNativeBatchExec(SubmitBatchAction, options, scriptPath);
    }

    size_t pos = mjob.getOutputPath().find(":");
    std::string prefixOutputPath = (pos == std::string::npos)? muserSessionInfo.machine_name+":" : "";
    mjob.setOutputPath(prefixOutputPath+mjob.getOutputPath());
    pos = mjob.getErrorPath().find(":");
    std::string prefixErrorPath = (pos == std::string::npos)? muserSessionInfo.machine_name+":" : "";
    mjob.setErrorPath(prefixErrorPath+mjob.getErrorPath());
  } catch (VishnuException& ex) {
    scanErrorMessage(ex.buildExceptionString(), errCode, mlastError);
    std::string errorPath = (boost::format("/%1%/vishnu-%2%.err")
                             % std::getenv("HOME")
                             % mjob.getJobId()
                             ).str();
    vishnu::saveInFile(errorPath, mlastError);
    mjob.setErrorPath(errorPath);
    mjob.setOutputPath("");
    mjob.setOutputDir("");
    mjob.setStatus(vishnu::STATE_FAILED);
    LOG((boost::format("[ERROR] Submission failed: %1% [%2%]")%mjob.getJobId() %mlastError).str(), 4);
  }

  if (! standaloneSed) {
    recordJob2db();
  }

  if (! mlastError.empty()) {
    throw TMSVishnuException(errCode, mlastError);
  } else {
    LOG(boost::format("[INFO] Job created: %1%. User: %2%. Owner: %3%" )
        % mjob.getJobId() % mjob.getUserId() % muserSessionInfo.user_aclogin, 1);
  }
  return 0;
}

/**
     * @brief Submit job using ssh mechanism
     * @param scriptPath The path of the script to executed
     * @param options: an object containing options
     */
void
JobServer::handleSshSubmit(const std::string& scriptPath, JsonObject* options) {

  SSHJobExec sshJobExec(muserSessionInfo.user_aclogin,
                        muserSessionInfo.machine_name,
                        mbatchType,
                        mbatchVersion, // it will work for POSIX at the POSIX backend ignores the batch version
                        JsonObject::serialize(mjob),
                        options->encode());

  sshJobExec.setDebugLevel(mdebugLevel);
  sshJobExec.sshexec("SUBMIT", scriptPath);

  // Submission with deltacloud doesn't make copy of the script
  // So the script needs to be kept until the end of the execution
  // Clean the temporary script if not deltacloud
  if (mbatchType != DELTACLOUD && mdebugLevel) {
    vishnu::deleteFile(scriptPath.c_str());
  }
  std::string errorInfo = sshJobExec.getErrorInfo(); // Check if some errors occured during the submission
  if (! errorInfo.empty()) {
    int code;
    std::string message;
    scanErrorMessage(errorInfo, code, message);
    throw TMSVishnuException(code, message);
  }

  mjob = sshJobExec.getResultJob();
}

/**
     * @brief Handle action to batch scheduler
     * @param action action The type of action
     * @param options user-specific options
     * @param scriptPath The path of the script to executed. Only required for submit action
     */
void
JobServer::handleNativeBatchExec(int action, JsonObject* options, const std::string& scriptPath) {

  BatchFactory factory;
  BatchServer* batchServer = factory.getBatchServerInstance(mbatchType, mbatchVersion);
  if (! batchServer) {
    throw TMSVishnuException(ERRCODE_BATCH_SCHEDULER_ERROR, "getBatchServerInstance return NULL");
  }

  pid_t pid = fork();
  if (pid <= -1) {
    throw TMSVishnuException(ERRCODE_RUNTIME_ERROR, "Fork failed");
  }
  if (pid == 0) {
    int handlerExitCode = setuid(getSystemUid(muserSessionInfo.user_aclogin));
    if (handlerExitCode != 0) {
      LOG("[ERROR] " + std::string(strerror(errno)), 2);
      exit(handlerExitCode);
    }
    switch(action) {
    case SubmitBatchAction:
      handlerExitCode = batchServer->submit(scriptPath, options->getSubmitOptions(), mjob);
      break;

    case CancelBatchAction:
      if (mbatchType == DELTACLOUD) {
        handlerExitCode = batchServer->cancel(mjob.getJobId()+"@"+mjob.getVmId());
      } else {
        handlerExitCode = batchServer->cancel(mjob.getBatchJobId());
      }
      break;
    default:
      break;
    }
    exit(handlerExitCode);
  } else {
    int retCode;
    waitpid(pid, &retCode, 0);
    if (! WIFEXITED(retCode) || WEXITSTATUS(retCode) != 0) {
      throw TMSVishnuException(ERRCODE_RUNTIME_ERROR, "Unexpected batch exec terminaison");
    }
  }
}

/**
     * \brief Function to treat the default submission options
     * \param scriptOptions The list of the option value
     * \param cmdsOptions The list of the option value
     * \return raises an exception on error
     */
void
JobServer::processDefaultOptions(const std::vector<std::string>& defaultBatchOption,
                                 std::string& content, std::string& key) {
  size_t position = 0;
  std::string key1;
  int count = 0;
  int countOptions = defaultBatchOption.size();
  while (count < countOptions) {
    key1 =  defaultBatchOption.at(count);
    position = 0;
    int found =0;
    while (position!=std::string::npos && !found) {
      position = content.find(key.c_str(), position);
      if(position!=std::string::npos) {
        size_t pos1 = content.find("\n", position);
        std::string line = content.substr(position, pos1-position);
        position++;
        size_t pos2 = line.find(key1.c_str());
        if (pos2 != std::string::npos) {
          found =1;
          break;
        }
      }
    }
    if (!found) {
      std::string lineoption = key + " " + defaultBatchOption.at(count) + " " + defaultBatchOption.at(count +1) + "\n";
      insertOptionLine(lineoption, content, key);
    }
    count +=2;
  }
}
/**
     * \brief Function to insert option into string
     * \param optionLineToInsert the option to insert
     * \param content The buffer containing the inserted option
     * \return raises an exception on error
     */
void
JobServer::insertOptionLine(std::string& optionLineToInsert,
                            std::string& content, std::string& key) {
  size_t pos = 0;
  size_t posLastDirective = 0;

  while (pos!=std::string::npos) {
    pos = content.find(key.c_str(), pos);
    if (pos!=std::string::npos) {
      size_t pos1 = 0;
      pos1 = content.find("\n", pos);
      while (content.compare(pos1-1,1,"\\") == 0) {
        pos1 = content.find("\n", pos1 + 1);
      }
      std::string line = content.substr(pos, pos1-pos);
      if(content.compare(pos-1,1,"\n")==0) {
        if(mbatchType==LOADLEVELER) {
          std::string line_tolower(line);
          std::transform(line.begin(), line.end(), line_tolower.begin(), ::tolower);
          if(line_tolower.find("queue")!=std::string::npos) {
            break;
          }
        }
        posLastDirective = pos + line.size() + 1;
      }
      pos++;
    }
  }
  content.insert(posLastDirective, optionLineToInsert);
}

/**
     * \brief Function to cancel job
     * \param options Object containing options
     * \return raises an exception on error
     */
int JobServer::cancelJob(JsonObject* options)
{
  std::string jobId = options->getStringProperty("jobId");
  std::string userId = options->getStringProperty("userId");

  // Only a admin user can use the option 'all' for the job id
  if (userId == ALL_KEYWORD && muserSessionInfo.user_privilege != vishnu::PRIVILEGE_ADMIN) {
    throw TMSVishnuException(ERRCODE_PERMISSION_DENIED,
                             (boost::format("Option privileged users can cancel all user jobs")).str());
  }

  // Only a admin user can delete jobs from another user
  if (! userId.empty() && muserSessionInfo.user_privilege != vishnu::PRIVILEGE_ADMIN) {
    throw TMSVishnuException(ERRCODE_PERMISSION_DENIED,
                             (boost::format("Only privileged users can cancel other users jobs")).str());
  }

  bool cancelAllJobs = jobId.empty() || jobId == ALL_KEYWORD || userId == ALL_KEYWORD;
  std::string baseSqlQuery = (boost::format("SELECT job.owner, job.status, job.jobId, job.batchJobId, job.vmId, job.batchType"
                                            " FROM job, vsession "
                                            " WHERE job.status < %1%"
                                            ) % vishnu::STATE_COMPLETED
                              ).str();
  std::string sqlQuery;
  if (! cancelAllJobs) {

    sqlQuery = (boost::format("%1%"
                              " AND vsession.numsessionid=job.vsession_numsessionid"
                              " AND jobId='%2%';"
                              )
                % baseSqlQuery
                % mdatabaseInstance->escapeData(jobId)
                ).str();

    LOG(boost::format("[WARN] received request to cancel the job %1%") % jobId, 2);
  } else {
    // This block works as follow:
    // * if admin:
    //    ** if JobId = 'all', then cancel all jobs submitted through vishnu, regardless of the users
    //    ** else perform cancel as for a normal user
    // *if normal user (not admin), cancel alls jobs submitted through vishnu by the user

    bool addUserFilter = true;
    if (muserSessionInfo.user_privilege == vishnu::PRIVILEGE_ADMIN && userId == ALL_KEYWORD) {
      addUserFilter = false;
    }

    // Set the SQL query accordingly
    if (addUserFilter) {
      if (userId.empty()) {
        // here we'll delete all the jobs of the logged user
        sqlQuery = (boost::format("%1%"
                                  " AND vsession.numsessionid=job.vsession_numsessionid"
                                  " AND owner='%2%'"
                                  " AND submitMachineId='%3%';"
                                  )
                    % baseSqlQuery
                    % mdatabaseInstance->escapeData(muserSessionInfo.user_aclogin)
                    % mdatabaseInstance->escapeData(mmachineId)
                    ).str();
        LOG(boost::format("[WARN] received request to cancel all jobs submitted through authKey %1%")%muserSessionInfo.user_aclogin, 2);
      } else {
        // here we'll delete jobs submitted by the given user
        sqlQuery = (boost::format("SELECT job.owner, job.status, job.jobId, job.batchJobId, job.vmId, job.batchType"
                                  " FROM users, job"
                                  " WHERE job.status < %1%"
                                  "  AND users.numuserid=job.job_owner_id"
                                  "  AND users.userid='%2%'"
                                  "  AND submitMachineId='%3%';"
                                  )
                    %  vishnu::STATE_COMPLETED
                    % mdatabaseInstance->escapeData(userId)
                    % mdatabaseInstance->escapeData(mmachineId)
                    ).str();
      }
      LOG(boost::format("[WARN] received request to cancel all jobs submitted through user %1%")%userId, 2);
    } else {
      sqlQuery = (boost::format("%1%"
                                " AND vsession.numsessionid=job.vsession_numsessionid"
                                " AND submitMachineId='%2%';")
                  % baseSqlQuery
                  % mdatabaseInstance->escapeData(mmachineId)
                  ).str();
      LOG(boost::format("[WARN] received request to cancel all user jobs from %1%"
                        ) % muserSessionInfo.user_aclogin, 2);
    }
  }

  // Process the query and treat the resulting jobs
  boost::scoped_ptr<DatabaseResult> sqlQueryResult(mdatabaseInstance->getResult(sqlQuery));

  if (sqlQueryResult->getNbTuples() == 0) {
    if (! cancelAllJobs) {
      LOG(boost::format("[INFO] invalid cancel request with job id %1%") % jobId, 1);
      throw TMSVishnuException(ERRCODE_INVALID_PARAM, "The is not valid or is not longer running");
    } else {
      LOG(boost::format("[INFO] no job matching the call"), 1);
    }
  } else {
    int resultCount = sqlQueryResult->getNbTuples();
    std::vector<std::string> results;
    for (size_t i = 0; i < resultCount; ++i) {
      results.clear();
      results = sqlQueryResult->get(i);

      TMS_Data::Job currentJob;
      std::vector<std::string>::iterator resultIterator = results.begin();
      currentJob.setOwner( *resultIterator++ );  // IMPORTANT: gets the value and increments the iterator
      currentJob.setStatus(vishnu::convertToInt( *resultIterator++ ));
      currentJob.setJobId( *resultIterator++ );
      currentJob.setBatchJobId( *resultIterator++ );
      currentJob.setVmId( *resultIterator++ );
      BatchType serverBatchType = static_cast<BatchType>(vishnu::convertToInt( *resultIterator++ ));

      switch (currentJob.getStatus()) {
      case vishnu::STATE_COMPLETED:
        throw TMSVishnuException(ERRCODE_ALREADY_TERMINATED, currentJob.getJobId());
        break;
      case vishnu::STATE_CANCELLED:
        throw TMSVishnuException(ERRCODE_ALREADY_CANCELED, currentJob.getJobId());
        break;
      default:
        break;
      }

      if (currentJob.getOwner() != muserSessionInfo.user_aclogin
          && muserSessionInfo.user_privilege != vishnu::PRIVILEGE_ADMIN) {
        throw TMSVishnuException(ERRCODE_PERMISSION_DENIED);
      }

      ::ecorecpp::serializer::serializer jobSer;
      std::string jobSerialized =  jobSer.serialize_str(const_cast<TMS_Data::Job_ptr>(&currentJob));
      SSHJobExec sshJobExec(currentJob.getOwner(),
                            muserSessionInfo.machine_name,
                            serverBatchType,
                            mbatchVersion,  // it will work for POSIX at the POSIX backend ignores the batch version
                            jobSerialized);
      sshJobExec.sshexec("CANCEL");

      std::string errorInfo = sshJobExec.getErrorInfo();
      if (! errorInfo.empty()) {
        int code;
        std::string message;
        scanErrorMessage(errorInfo, code, message);
        throw TMSVishnuException(code, message);
      } else {
        std::string query = (boost::format("UPDATE job SET status=%1%"
                                           " WHERE jobId='%2%';"
                                           )
                             % vishnu::convertToString(vishnu::STATE_CANCELLED)
                             % mdatabaseInstance->escapeData(currentJob.getJobId())).str();
        mdatabaseInstance->process(query);


        LOG(boost::format("[INFO] Job cancelled: %1%")% currentJob.getJobId(), mdebugLevel);
      }
    }
  }

  return 0;
}

/**
     * \brief Function to get job information
     * \param jobId The id of the job
     * \return The job data structure
     */
TMS_Data::Job JobServer::getJobInfo(const std::string& jobId) {

  std::vector<std::string> results;
  std::vector<std::string>::iterator  iter;
  std::string sqlRequest =
      "SELECT vsessionid, submitMachineId, submitMachineName, jobId, jobName, jobPath, workId, "
      "  outputPath, errorPath, outputDir, jobPrio, nbCpus, jobWorkingDir, job.status, "
      "  submitDate, endDate, owner, jobQueue,wallClockLimit, groupName, jobDescription, "
      "  memLimit, nbNodes, nbNodesAndCpuPerNode, batchJobId, userid, vmId, vmIp"
      " FROM job, vsession, users "
      " WHERE vsession.numsessionid=job.vsession_numsessionid "
      "   AND vsession.users_numuserid=users.numuserid"
      "   AND job.jobId='"+mdatabaseInstance->escapeData(jobId)+"'";

  boost::scoped_ptr<DatabaseResult> sqlResult(mdatabaseInstance->getResult(sqlRequest.c_str()));

  if (sqlResult->getNbTuples() == 0) {
    throw TMSVishnuException(ERRCODE_UNKNOWN_JOBID);
  }

  results.clear();
  results = sqlResult->get(0);
  iter = results.begin();

  mjob.setSessionId(*iter);
  mjob.setSubmitMachineId(*(++iter));
  mjob.setSubmitMachineName(*(++iter));
  mjob.setJobId(*(++iter));
  mjob.setJobName(*(++iter));
  mjob.setJobPath(*(++iter));
  mjob.setWorkId(vishnu::convertToLong(*(++iter)));
  mjob.setOutputPath(*(++iter));
  mjob.setErrorPath(*(++iter));
  mjob.setOutputDir(*(++iter));
  mjob.setJobPrio(vishnu::convertToInt(*(++iter)));
  mjob.setNbCpus(vishnu::convertToInt(*(++iter)));
  mjob.setJobWorkingDir(*(++iter));
  mjob.setStatus(vishnu::convertToInt(*(++iter)));
  mjob.setSubmitDate(vishnu::convertLocaltimeINUTCtime(vishnu::convertToTimeType(*(++iter)))); //convert the submitDate into UTC date
  mjob.setEndDate(vishnu::convertLocaltimeINUTCtime(vishnu::convertToTimeType(*(++iter)))); //convert the endDate into UTC date
  mjob.setOwner(*(++iter));
  mjob.setJobQueue(*(++iter));
  mjob.setWallClockLimit(vishnu::convertToInt(*(++iter)));
  mjob.setGroupName(*(++iter));
  mjob.setJobDescription(*(++iter));
  mjob.setMemLimit(vishnu::convertToInt(*(++iter)));
  mjob.setNbNodes(vishnu::convertToInt(*(++iter)));
  mjob.setNbNodesAndCpuPerNode(*(++iter));
  mjob.setBatchJobId(*(++iter));
  mjob.setUserId(*(++iter));
  mjob.setVmId(*(++iter));
  mjob.setVmIp(*(++iter));

  return mjob;
}

/**
     * \brief Function to scan VISHNU error message
     * \param errorInfo the error information to scan
     * \param code The code The code of the error
     * \param message The message associeted to the error code
     * \return raises an exception on erroor
     */
void JobServer::scanErrorMessage(const std::string& errorInfo, int& code, std::string& message) {

  code = ERRCODE_INVEXCEP;

  size_t pos = errorInfo.find('#');
  if (pos!=std::string::npos) {
    std::string codeInString = errorInfo.substr(0,pos);
    if (codeInString.size()!=0) {
      try {
        code = boost::lexical_cast<int>(codeInString);
      }
      catch(boost::bad_lexical_cast &){
        code = ERRCODE_INVEXCEP;
      }
      message = errorInfo.substr(pos+1);
    }
  }
}

/**
     * \brief Function to convert a given date into correspondant long value
     * \param date The date to convert
     * \return The converted value
     */
long long JobServer::convertToTimeType(std::string date) {

  if (date.size()==0 ||
      // For mysql, the empty date is 0000-00-00, not empty, need this test to avoid problem in ptime
      date.find("0000-00-00")!=std::string::npos) {
    return 0;
  }

  boost::posix_time::ptime pt(boost::posix_time::time_from_string(date));
  boost::posix_time::ptime epoch(boost::gregorian::date(1970,1,1));
  boost::posix_time::time_duration::sec_type time = (pt - epoch).total_seconds();

  return (long long) time_t(time);

}

/**
     * \brief To get the main configuration
     * \return the pointer to configuration object
     */
ExecConfiguration_Ptr
JobServer::getSedConfig() const {
  return msedConfig;
}


/**
     * \brief Function to set the path of output directory
     * \param parentDir The directory in which to create the output dir
     * \param dirSuffix the suffix of the output dir
     * \param content the script content to be update which the generated path
     */
void JobServer::setJobOutputDir(const std::string& parentDir,
                                const std::string& dirSuffix,
                                std::string& content) {

  std::string prefix = (boost::algorithm::ends_with(parentDir, "/"))? "OUTPUT_" : "/OUTPUT_" ;
  std::string outdir = parentDir + prefix + dirSuffix ;
  vishnu::replaceAllOccurences(content, "$VISHNU_OUTPUT_DIR", outdir);
  vishnu::replaceAllOccurences(content, "${VISHNU_OUTPUT_DIR}", outdir);
  mjob.setOutputDir(outdir);
  setenv("VISHNU_OUTPUT_DIR", outdir.c_str(), 1);
}

/*
     * \brief Return the directive associated to the batch scheduler
     * \param seperator Hold the seperator used to define parameter
     */
std::string JobServer::getBatchDirective(std::string& seperator) const {

  seperator =  " ";
  std::string directive = "";
  switch(mbatchType) {
  case TORQUE :
    directive = "#PBS";
    break;
  case LOADLEVELER :
    directive = "# @";
    seperator = " = ";
    break;
  case SLURM :
    directive = "#SBATCH";
    break;
  case LSF :
    directive = "#BSUB";
    break;
  case SGE :
    directive = "#$";
    break;
  case PBSPRO :
    directive = "#PBS";
    break;
  case POSIX :
    directive = "#%";
    break;
  case DELTACLOUD : // return default ""
  default :
    break;
  }
  return directive;
}

/**
     * \brief Set specific parameters for job submission
     * \param specificParamss The string containing the list of parameters
     * \param scriptContent The content of the script when required
     */
void JobServer::handleSpecificParams(const std::string& specificParams,
                                     std::string& scriptContent) {

  std::string sep = " ";
  std::string directive = getBatchDirective(sep);
  size_t pos1 = 0;
  size_t pos2 = 0;
  std::string& params = const_cast<std::string&>(specificParams);
  pos2 = params.find("=");
  while (pos2 != std::string::npos) {
    size_t pos3 = 0;
    pos3 = params.find(" ");
    if(pos3 != std::string::npos) {
      std::string lineoption = directive +" "+ params.substr(pos1, pos2-pos1) + sep +  params.substr(pos2+1, pos3-pos2-1) + "\n";
      insertOptionLine(lineoption, scriptContent, directive);
      params.erase(0, pos3);
      boost::algorithm::trim_left(params);
    } else {
      std::string lineoption = directive +" "+ params.substr(pos1, pos2-pos1)+ sep +  params.substr(pos2+1, params.size()-pos2) + "\n";
      insertOptionLine(lineoption, scriptContent, directive);
      break;
    }
    pos2 = params.find("=");
  }
}

/**
     * \brief Function to set the Working Directory
     * \param options a json object describing options
     * \param suffix the suffix of the working directory
     * \return none
     */
void
JobServer::setRealPaths(JsonObject* options, const std::string& suffix)
{
  std::string workingDir = boost::filesystem::temp_directory_path().string();
  std::string scriptPath = "";
  if(mbatchType == DELTACLOUD) {
    std::string mountPoint = vishnu::getVar(vishnu::CLOUD_ENV_VARS[vishnu::CLOUD_NFS_MOUNT_POINT], true);
    workingDir = mountPoint.empty()? "/tmp/" + suffix : mountPoint + "/" + suffix;
    std::string inputDir =  workingDir + "/INPUT";
    scriptPath = inputDir + "/script.xsh";
    vishnu::createDir(workingDir, true); // create the working directory
    vishnu::createDir(inputDir, true); // create the input directory
    std::string directory = "";
    try {
      directory = vishnu::moveFileData(options->getStringProperty("fileparams"), inputDir);
    } catch(bfs::filesystem_error &ex) {
      throw SystemException(ERRCODE_RUNTIME_ERROR, ex.what());
    }
    if(directory.length() > 0) {
      std::string fileparams = options->getStringProperty("fileparams");
      vishnu::replaceAllOccurences(fileparams, directory, inputDir);
      options->setProperty("fileparams", fileparams);
    }
  } else {
    scriptPath = workingDir +"/"+ bfs::unique_path("job_script%%%%%%").string();
    std::string workingDir = options->getStringProperty("workingdir");
    if (workingDir.empty()) {
      workingDir = muserSessionInfo.user_achome;
    }
  }
  options->setProperty("workingdir", workingDir);
  options->setProperty("scriptpath", scriptPath);
}


/**
     * \brief Function to process the script with options
     * \param the script content
     * \param options the options to submit job
     * \param defaultBatchOption The default batch options
     * \return the processed script content
     */
std::string
JobServer::processScript(std::string& scriptContent,
                         JsonObject* options,
                         const std::vector<std::string>& defaultBatchOption,
                         const std::string& machineName)
{
  std::string convertedScript;

  vishnu::replaceAllOccurences(scriptContent, "$VISHNU_SUBMIT_MACHINE_NAME", machineName);
  vishnu::replaceAllOccurences(scriptContent, "${VISHNU_SUBMIT_MACHINE_NAME}", machineName);

  std::string currentOption = options->getStringProperty("textparams");
  if (! currentOption.empty()) {
    vishnu::setParams(scriptContent, currentOption);
  }
  currentOption = options->getStringProperty("fileparams");
  if (! currentOption.empty()) {
    vishnu::setParams(scriptContent, currentOption) ;
  }
  boost::shared_ptr<ScriptGenConvertor> scriptConvertor(vishnuScriptGenConvertor(mbatchType, scriptContent));
  if(scriptConvertor->scriptIsGeneric()) {
    std::string genScript = scriptConvertor->getConvertedScript();
    convertedScript = genScript;
  } else {
    convertedScript = scriptContent;
  }
  std::string sep = " ";
  std::string directive = getBatchDirective(sep);
  currentOption = options->getStringProperty("specificparams");
  if (! currentOption.empty()) {
    handleSpecificParams(currentOption, convertedScript);
  }

  if (! defaultBatchOption.empty()){
    processDefaultOptions(defaultBatchOption, convertedScript, directive);
  }
  if(mbatchType == DELTACLOUD) {
    vishnu::replaceAllOccurences(scriptContent, "$VISHNU_BATCHJOB_NODEFILE", mjob.getOutputDir()+"/NODEFILE");
    vishnu::replaceAllOccurences(scriptContent, "${VISHNU_BATCHJOB_NODEFILE}", mjob.getOutputDir()+"/NODEFILE");
  }
  return convertedScript;
}

/**
     * \brief Function to save the encapsulated job into the database
     */
void
JobServer::recordJob2db()
{
  std::string sqlUpdate = "UPDATE job set ";
  sqlUpdate+="vsession_numsessionid="+vishnu::convertToString(muserSessionInfo.num_session)+", ";
  sqlUpdate+="job_owner_id="+vishnu::convertToString(muserSessionInfo.num_user)+", ";
  sqlUpdate+="owner='"+mdatabaseInstance->escapeData(muserSessionInfo.user_aclogin)+"', ";
  sqlUpdate+="submitMachineId='"+mdatabaseInstance->escapeData(mmachineId)+"', ";
  sqlUpdate+="submitMachineName='"+mdatabaseInstance->escapeData(muserSessionInfo.machine_name)+"', ";
  sqlUpdate+="batchJobId='"+mdatabaseInstance->escapeData(mjob.getBatchJobId())+"', ";
  sqlUpdate+="batchType="+vishnu::convertToString(mbatchType)+", ";
  sqlUpdate+="jobName='"+mdatabaseInstance->escapeData(mjob.getJobName())+"', ";
  sqlUpdate+="jobPath='"+mdatabaseInstance->escapeData(mjob.getJobPath())+"', ";
  sqlUpdate+="outputPath='"+mdatabaseInstance->escapeData(mjob.getOutputPath())+"',";
  sqlUpdate+="errorPath='"+mdatabaseInstance->escapeData(mjob.getErrorPath())+"',";
  sqlUpdate+="scriptContent='job', ";
  sqlUpdate+="jobPrio="+vishnu::convertToString(mjob.getJobPrio())+", ";
  sqlUpdate+="nbCpus="+vishnu::convertToString(mjob.getNbCpus())+", ";
  sqlUpdate+="jobWorkingDir='"+mdatabaseInstance->escapeData(mjob.getJobWorkingDir())+"', ";
  sqlUpdate+="status="+vishnu::convertToString(mjob.getStatus())+", ";
  sqlUpdate+="submitDate=CURRENT_TIMESTAMP, ";
  sqlUpdate+="jobQueue='"+mdatabaseInstance->escapeData(mjob.getJobQueue())+"', ";
  sqlUpdate+="wallClockLimit="+vishnu::convertToString(mjob.getWallClockLimit())+", ";
  sqlUpdate+="groupName='"+mdatabaseInstance->escapeData(mjob.getGroupName())+"',";
  sqlUpdate+="jobDescription='"+mdatabaseInstance->escapeData(mjob.getJobDescription())+"', ";
  sqlUpdate+="memLimit="+vishnu::convertToString(mjob.getMemLimit())+", ";
  sqlUpdate+="nbNodes="+vishnu::convertToString(mjob.getNbNodes())+", ";
  sqlUpdate+="nbNodesAndCpuPerNode='"+mdatabaseInstance->escapeData(mjob.getNbNodesAndCpuPerNode())+"', ";
  sqlUpdate+="outputDir='"+mdatabaseInstance->escapeData(mjob.getOutputDir())+"', ";
  sqlUpdate+= mjob.getWorkId()? "workId="+vishnu::convertToString(mjob.getWorkId())+", " : "";
  sqlUpdate+="vmId='"+mdatabaseInstance->escapeData(mjob.getVmId())+"', ";
  sqlUpdate+="vmIp='"+mdatabaseInstance->escapeData(mjob.getVmIp())+"' ";
  sqlUpdate+="WHERE jobid='"+mdatabaseInstance->escapeData(mjob.getJobId())+"';";
  mdatabaseInstance->process(sqlUpdate);
}


/**
 * @brief Get the uid corresponding to given system user name
 * @param username
 * @return
 */
uid_t
JobServer::getSystemUid(const std::string& name)
{
  passwd* info = getpwnam(name.c_str());
  if (! info) {
    throw TMSVishnuException(ERRCODE_INVALID_PARAM,
                             "The user doesn't have a valid uid "+name);
  }
  return info->pw_uid;
}
