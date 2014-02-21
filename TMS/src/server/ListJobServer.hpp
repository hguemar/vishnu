/**
 * \file ListJobServer.hpp
 * \brief This file contains the VISHNU ListJobServer class.
 * \author Daouda Traore (daouda.traore@sysfera.com) and
 *   Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
 * \date February 2011
 */
#ifndef _LIST_JOB_SERVER_
#define _LIST_JOB_SERVER_

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "boost/date_time/posix_time/posix_time.hpp"


#include "QueryServer.hpp"
#include "TMS_Data.hpp"
#include "BatchServer.hpp"
#include "BatchFactory.hpp"
#include <boost/foreach.hpp>

/**
 * \class ListJobServer
 * \brief ListJobServer class implementation
 */
class ListJobServer: public QueryServer<TMS_Data::ListJobsOptions, TMS_Data::ListJobs> {

public:

  /**
   * \param machineId The identifier of the machine in which the jobs will be listed
   * \brief Constructor, raises an exception on error
   */
  ListJobServer(std::string machineId)
    : QueryServer<TMS_Data::ListJobsOptions, TMS_Data::ListJobs>() {
    mcommandName = "vishnu_list_jobs";
    mmachineId = machineId;
  }

  /**
   * \brief Function to treat the listJobServer options
   * \param options the object which contains the ListJobServer options values
   * \param sqlRequest the sql data base request
   * \return raises an exception on error
   */
  void
  processOptions(const TMS_Data::ListJobsOptions_ptr& options, std::string& sqlRequest) {

    //To check if the jobId is defined
    if (options->getJobId().size() != 0) {
      //To check if the jobIf exists
      checkJobId(options->getJobId());
      //To add the jobId on the request
      addOptionRequest("jobId", options->getJobId(), sqlRequest);
    }

    //To check if the number of cpu is defined and positive
    if (options->getNbCpu() > 0) {
      //To add the number of the cpu to the request
      addOptionRequest("nbCpus", vishnu::convertToString(options->getNbCpu()), sqlRequest);
    } else {
      //If the options is not the default value -1
      if (options->getNbCpu() != -1) {
        throw UserException(ERRCODE_INVALID_PARAM, "The number of cpu is incorrect");
      }
    }

    time_t fromSubmitDate = static_cast<time_t>(options->getFromSubmitDate());
    if(fromSubmitDate != -1) {
      fromSubmitDate = vishnu::convertUTCtimeINLocaltime(fromSubmitDate);
      std::string submitDateStr =  boost::posix_time::to_iso_string(boost::posix_time::from_time_t(fromSubmitDate));
      addTimeRequest("submitDate", submitDateStr, sqlRequest, ">=");
    }

    time_t toSubmitDate = static_cast<time_t>(options->getToSubmitDate());
    if(toSubmitDate != -1) {
      toSubmitDate = vishnu::convertUTCtimeINLocaltime(toSubmitDate);
      std::string submitDateStr =  boost::posix_time::to_iso_string(boost::posix_time::from_time_t(toSubmitDate));
      addTimeRequest("submitDate", submitDateStr, sqlRequest, "<=");
    }

    //Check the job status
    if (options->getStatus() != -1) {
      vishnu::checkJobStatus(options->getStatus()); //check the job state options
      addOptionRequest("job.status", vishnu::convertToString(options->getStatus()), sqlRequest); //Append the amount of the cpu
    } else {
      if (options->getJobId().empty() && options->getMultipleStatus().empty()) {
        sqlRequest.append(" and job.status < "+vishnu::convertToString(vishnu::STATE_COMPLETED));
      }
    }

    if(!options->getMultipleStatus().empty()) {
      std::string multStat = options->getMultipleStatus();
      std::string::iterator iter;
      std::string::iterator beg = multStat.begin();
      std::string::iterator end = multStat.end();
      std::vector<std::string> vec;
      for (iter=beg; iter!=end; ++iter) {
        switch(*iter) {
        case 'S':
        case 48+vishnu::STATE_SUBMITTED:
          vec.push_back("job.status="+vishnu::convertToString(vishnu::STATE_SUBMITTED));
          break;
        case 'Q':
        case 48+vishnu::STATE_QUEUED:
          vec.push_back("job.status="+vishnu::convertToString(vishnu::STATE_QUEUED));
          break;
        case 'W':
        case 48+vishnu::STATE_WAITING:
          vec.push_back("job.status="+vishnu::convertToString(vishnu::STATE_WAITING));
          break;
        case 'R':
        case 48+vishnu::STATE_RUNNING:
          vec.push_back("job.status="+vishnu::convertToString(vishnu::STATE_RUNNING));
          break;
        case 'T':
        case 48+vishnu::STATE_COMPLETED:
          vec.push_back("job.status="+vishnu::convertToString(vishnu::STATE_COMPLETED));
          break;
        case 'C':
        case 48+vishnu::STATE_CANCELLED:
          vec.push_back("job.status="+vishnu::convertToString(vishnu::STATE_CANCELLED));
          break;
        case 'D':
        case 48+vishnu::STATE_DOWNLOADED:
          vec.push_back("job.status="+vishnu::convertToString(vishnu::STATE_DOWNLOADED));
          break;
        case 'F':
        case 48+vishnu::STATE_FAILED:
          vec.push_back("job.status="+vishnu::convertToString(vishnu::STATE_FAILED));
          break;
        default:
          throw UserException(ERRCODE_INVALID_PARAM,
                              (boost::format("Unknown job state: %1%")%*iter).str());
          break;
        }
      }
      std::vector<std::string>::iterator vec_iter;
      if (!vec.empty()) {
        sqlRequest.append(" and ("+*vec.begin());
        for (vec_iter=vec.begin()+1; vec_iter!=vec.end(); ++vec_iter) {
          sqlRequest.append(" or "+*vec_iter);
        }
        sqlRequest.append(")");
      }
    }
    //To check the job priority
    if (options->getPriority() != -1) {
      //To check the job priority options
      vishnu::checkJobPriority(options->getPriority());
      //To add the number of the cpu to the request
      addOptionRequest("jobPrio", vishnu::convertToString(options->getPriority()), sqlRequest);
    }

    if (options->getOwner().size() != 0) {
      addOptionRequest("owner", options->getOwner(), sqlRequest);
    }

    //To check if the queue is defined
    if (options->getQueue().size() != 0) {
      BatchFactory factory;
      BatchType batchType  = ServerTMS::getInstance()->getBatchType();
      std::string batchVersion  = ServerTMS::getInstance()->getBatchVersion();
      boost::scoped_ptr<BatchServer> batchServer(factory.getBatchServerInstance(batchType, batchVersion));
      batchServer->listQueues(options->getQueue()); //raise an exception if options->getQueue does not exist

      addOptionRequest("jobQueue", options->getQueue(), sqlRequest);
    }
    if(options->getWorkId() >= 0 ) {
      long long int wid = options->getWorkId()  ;
      addIntegerOptionRequest("workId", wid, sqlRequest);
    }
  }

  /**
   * \brief Function to list sessions information
   * \return The pointer to the UMS_Data::ListSessions containing sessions information
   * \return raises an exception on error
   */
  TMS_Data::ListJobs*
  list(TMS_Data::ListJobsOptions_ptr options) {
    std::string sqlQuery =
        "SELECT vsessionid, submitMachineId, submitMachineName, jobId, jobName, workId, jobPath,"
        " outputPath, errorPath, jobPrio, nbCpus, jobWorkingDir, job.status, submitDate, endDate, owner, jobQueue,"
        " wallClockLimit, groupName, jobDescription, memLimit, nbNodes, nbNodesAndCpuPerNode, batchJobId, userid "
        "FROM job, vsession, users "
        "WHERE vsession.numsessionid=job.vsession_numsessionid"
        " AND vsession.users_numuserid=users.numuserid"
        " AND job.status > 0 ";

    if(mmachineId.compare(ALL_KEYWORD)!=0) {
      sqlQuery.append(" and job.submitMachineId='"+mdatabaseInstance->escapeData(mmachineId)+"'");
    }

    bool allOptionsAreNotSet = (options->getNbCpu()<=0);
    allOptionsAreNotSet = allOptionsAreNotSet && (options->getFromSubmitDate()==-1);
    allOptionsAreNotSet = allOptionsAreNotSet && (options->getToSubmitDate()==-1);
    allOptionsAreNotSet = allOptionsAreNotSet && (options->getStatus()==-1);
    allOptionsAreNotSet = allOptionsAreNotSet && (options->getMultipleStatus().empty());
    allOptionsAreNotSet = allOptionsAreNotSet && (options->getPriority()==-1);
    allOptionsAreNotSet = allOptionsAreNotSet && (options->getOwner().empty());
    allOptionsAreNotSet = allOptionsAreNotSet && (options->getQueue().empty());

    if (options->isBatchJob() && !allOptionsAreNotSet) {
      throw UserException(ERRCODE_INVALID_PARAM, "Conflict: the batchJob option is incompatible with other options excepted jobId option.");
    }

    if (options->isBatchJob() && mmachineId.compare(ALL_KEYWORD)==0) {
      throw UserException(ERRCODE_INVALID_PARAM, "Conflict: the batchJob option is incompatible with machine id equal to all.");
    }

    std::vector<std::string>::iterator ii;
    std::vector<std::string> results;

    TMS_Data::TMS_DataFactory_ptr ecoreFactory = TMS_Data::TMS_DataFactory::_instance();
    mlistObject = ecoreFactory->createListJobs();

    processOptions(options, sqlQuery);
    sqlQuery.append(" order by submitDate");

    boost::scoped_ptr<DatabaseResult> ListOfJobs (mdatabaseInstance->getResult(sqlQuery));
    long nbRunningJobs = 0;
    long nbWaitingJobs = 0;
    std::string batchJobId;
    time_t submitDate;
    time_t endDate;
    std::vector<std::string> ignoredIds;

    if (ListOfJobs->getNbTuples() != 0) {
      int jobStatus;

      for (size_t i = 0; i < ListOfJobs->getNbTuples(); ++i) {
        results.clear();
        results = ListOfJobs->get(i);
        ii = results.begin();

        TMS_Data::Job_ptr job = ecoreFactory->createJob();

        job->setSessionId(*ii);
        job->setSubmitMachineId(*(++ii));
        job->setSubmitMachineName(*(++ii));
        job->setJobId(*(++ii));
        job->setJobName(*(++ii));
        job->setWorkId(vishnu::convertToLong(*(++ii)));
        job->setJobPath(*(++ii));
        job->setOutputPath(*(++ii));
        job->setErrorPath(*(++ii));
        job->setJobPrio(vishnu::convertToInt(*(++ii)));
        job->setNbCpus(vishnu::convertToInt(*(++ii)));
        job->setJobWorkingDir(*(++ii));
        jobStatus = vishnu::convertToInt(*(++ii));

        if (jobStatus == vishnu::STATE_RUNNING) {
          nbRunningJobs++;
        } else if(jobStatus >= vishnu::STATE_SUBMITTED && jobStatus <= vishnu::STATE_WAITING) {
          nbWaitingJobs++;
        }

        job->setStatus(jobStatus);
        //convert the endDate into UTC date
        submitDate = vishnu::convertLocaltimeINUTCtime(vishnu::convertToTimeType(*(++ii)));
        job->setSubmitDate(submitDate);
        //convert the endDate into UTC date
        endDate = vishnu::convertLocaltimeINUTCtime(vishnu::convertToTimeType(*(++ii)));
        job->setEndDate(endDate);
        job->setOwner(*(++ii));
        job->setJobQueue(*(++ii));
        job->setWallClockLimit(vishnu::convertToInt(*(++ii)));
        job->setGroupName(*(++ii));
        job->setJobDescription(*(++ii));
        job->setMemLimit(vishnu::convertToInt(*(++ii)));
        job->setNbNodes(vishnu::convertToInt(*(++ii)));
        job->setNbNodesAndCpuPerNode(*(++ii));

        batchJobId = *(++ii);
        job->setBatchJobId(batchJobId);
        ignoredIds.push_back(batchJobId);
        job->setUserId(*(++ii));
        mlistObject->getJobs().push_back(job);
      }
      mlistObject->setNbJobs(mlistObject->getJobs().size());
      mlistObject->setNbRunningJobs(nbRunningJobs);
      mlistObject->setNbWaitingJobs(nbWaitingJobs);
    }

    if (options->isBatchJob()
        && !options->getJobId().empty()
        && mmachineId.compare(ALL_KEYWORD) !=0 ){
      BatchFactory factory;
      BatchType batchType  = ServerTMS::getInstance()->getBatchType();
      std::string batchVersion  = ServerTMS::getInstance()->getBatchVersion();
      boost::scoped_ptr<BatchServer> batchServer(factory.getBatchServerInstance(batchType, batchVersion));

      if (mlistObject != NULL) {
        std::vector<std::string>::const_iterator iter = ignoredIds.begin();
        for (unsigned int i = 0; i < mlistObject->getJobs().size(); i++) {
          if (iter != ignoredIds.end()){
            (mlistObject->getJobs().get(i))->setJobId(*iter);
            int state = batchServer->getJobState(*iter);
            ++iter;
            if (state != vishnu::STATE_UNDEFINED &&
                (mlistObject->getJobs().get(i))->getStatus() != vishnu::STATE_COMPLETED &&
                (mlistObject->getJobs().get(i))->getStatus() != vishnu::STATE_CANCELLED &&
                (mlistObject->getJobs().get(i))->getStatus() != vishnu::STATE_DOWNLOADED) {
              (mlistObject->getJobs().get(i))->setStatus(state);
            }
          }
        }
      }
      return mlistObject;
    }

    if(options->isBatchJob() && mmachineId.compare(ALL_KEYWORD)!=0 && allOptionsAreNotSet){
      BatchFactory factory;
      BatchType batchType  = ServerTMS::getInstance()->getBatchType();
      std::string batchVersion  = ServerTMS::getInstance()->getBatchVersion();
      boost::scoped_ptr<BatchServer> batchServer(factory.getBatchServerInstance(batchType, batchVersion));

      batchServer->fillListOfJobs(mlistObject, ignoredIds);
    }

    return mlistObject;
  }


  /**
   * \brief Function to get the name of the ListJobServer command line
   * \return The the name of the ListJobServer command line
   */
  std::string getCommandName()
  {
    return mcommandName;
  }

  /**
   * \brief Destructor, raises an exception on error
   */
  ~ListJobServer()
  {
  }

private:

  /////////////////////////////////
  // Attributes
  /////////////////////////////////

  /**
   * \brief The name of the ListJobServer command line
   */
  std::string mcommandName;
  /**
   * \brief The name of the machine in which the jobs whill be listed
   */
  std::string mmachineId;
};

#endif
