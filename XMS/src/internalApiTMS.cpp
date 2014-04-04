/**
 * \file TMS/src/sed/internalApi.cpp
 * \brief This file contains the VISHNU internal TMS API function.
 * \author Daouda Traore (daouda.traore@sysfera.com)
 * \date April 2011
 */


#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/format.hpp>
#include <boost/filesystem/path.hpp>


//EMF
#include <ecore.hpp> // Ecore metamodel
#include <ecorecpp.hpp> // EMF4CPP utils
#include "TMS_Data.hpp"
#include "DIET_client.h"

#include "utilServer.hpp"
#include "BatchServer.hpp"
#include "ServerXMS.hpp"
#include "JobServer.hpp"
#include "WorkServer.hpp"
#include "ListJobServer.hpp"
#include "ListQueuesServer.hpp"
#include "ListProgressServer.hpp"
#include "JobOutputServer.hpp"
#include "WorkServer.hpp"
#include "internalApiTMS.hpp"
#include "MapperRegistry.hpp"


namespace bfs=boost::filesystem; // an alias for boost filesystem namespace

#ifdef TMS_STANDALONE
#define FINISH_COMMAND(sessionKey, arg1, arg2, arg3, arg4)  SessionServer sessionServer(authKey); \
  sessionServer.finish(arg1, arg2, arg3, arg4)
#else
#define FINISH_COMMAND(sessionKey, arg1, arg2, arg3, arg4) (boost::format("Command completed: %1%. status: %2%.")% arg1 % arg2).str()
#endif

/**
 * \brief Function to solve the jobSubmit service
 * \param pb is a structure which corresponds to the descriptor of a profile
 * \return raises an exception on error
 */
int
solveSubmitJob(diet_profile_t* pb) {

  std::string scriptContent;
  std::string machineId;
  std::string jsonEncodedOptions;
  std::string authKey;

  // get profile parameters
  diet_string_get(pb,0, authKey);
  diet_string_get(pb,1, machineId);
  diet_string_get(pb,2, scriptContent);
  diet_string_get(pb,3, jsonEncodedOptions);

  // reset the profile to send back result
  diet_profile_reset(pb, 2);

  try {
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(vishnu::TMSMAPPERNAME);
    int mapperkey = mapper->code("vishnu_submit_job");
    mapper->code(machineId, mapperkey);
    mapper->code(jsonEncodedOptions, mapperkey);
    std::string cmd = mapper->finalize(mapperkey);

    //FIXME: decode job and options
    ServerXMS* server = ServerXMS::getInstance();

    JobServer jobServer(authKey, machineId, server->getSedConfig());
    jobServer.setDebugLevel(server->getDebugLevel()); // Set the debug level

    JsonObject options(jsonEncodedOptions);

    std::string jobId = jobServer.submitJob(scriptContent,
                                            &options,
                                            server->getVishnuId(),
                                            server->getDefaultBatchOption());

    diet_string_set(pb,0, "success");
    diet_string_set(pb,1, JsonObject::serialize(jobServer.getJobInfo(jobId)));

    FINISH_COMMAND(authKey, cmd, vishnu::TMS, vishnu::CMDSUCCESS, jobId);

  } catch (VishnuException& ex) {
    try {
      FINISH_COMMAND(authKey, "", vishnu::TMS, vishnu::CMDFAILED, "");
    } catch (VishnuException& fe) {
      ex.appendMsgComp(fe.what());
    }
    diet_string_set(pb,0, "error");
    diet_string_set(pb,1, ex.what());
  }

  return 0;
}

/**
 * \brief Function to solve the jobCancel service
 * \param pb is a structure which corresponds to the descriptor of a profile
 * \return raises an exception on error
 */
int
solveCancelJob(diet_profile_t* pb) {

  std::string authKey;
  std::string machineId;
  std::string optionSerialized;

  diet_string_get(pb,0, authKey);
  diet_string_get(pb,1, machineId);
  diet_string_get(pb,2, optionSerialized);

  // reset the profile to send back result
  diet_profile_reset(pb, 2);


  try {
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(vishnu::TMSMAPPERNAME);
    int mapperkey = mapper->code("vishnu_cancel_job");
    mapper->code(machineId, mapperkey);
    mapper->code(optionSerialized, mapperkey);
    std::string cmd = mapper->finalize(mapperkey);

    ServerXMS* server = ServerXMS::getInstance();
    JobServer jobServer(authKey, machineId, server->getSedConfig());

    JsonObject options(optionSerialized);
    jobServer.cancelJob(&options);

    diet_string_set(pb,0, "success");
    diet_string_set(pb,1, "");

    FINISH_COMMAND(authKey, cmd, vishnu::TMS, vishnu::CMDSUCCESS, "");
  } catch (VishnuException& ex) {
    try {
      FINISH_COMMAND(authKey, "", vishnu::TMS, vishnu::CMDFAILED, "");
    } catch (VishnuException& fe) {
      ex.appendMsgComp(fe.what());
    }
    diet_string_set(pb,0, "error");
    diet_string_set(pb,1, ex.what());
  }
  return 0;
}

/**
 * \brief Function to solve the jobInfo service
 * \param pb is a structure which corresponds to the descriptor of a profile
 * \return raises an exception on error
 */
int
solveJobInfo(diet_profile_t* pb) {

  std::string authKey;
  std::string machineId;
  std::string jobId;

  //IN Parameters
  diet_string_get(pb, 0, authKey);
  diet_string_get(pb, 1, machineId);
  diet_string_get(pb, 2, jobId);

  // reset the profile to send back result
  diet_profile_reset(pb, 2);

  try{
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(vishnu::TMSMAPPERNAME);
    int mapperkey = mapper->code("vishnu_get_job_info");
    mapper->code(machineId, mapperkey);
    mapper->code(jobId, mapperkey);
    std::string cmd = mapper->finalize(mapperkey);

    JobServer jobServer(authKey, machineId, ServerXMS::getInstance()->getSedConfig());
    std::string jobSerialized = JsonObject::serialize(jobServer.getJobInfo(jobId));

    diet_string_set(pb,1, jobSerialized);
    diet_string_set(pb,0, "success");

    FINISH_COMMAND(authKey, cmd, vishnu::TMS, vishnu::CMDSUCCESS, "");
  } catch (VishnuException& e) {
    try {
      FINISH_COMMAND(authKey, "", vishnu::TMS, vishnu::CMDFAILED, "");
    } catch (VishnuException& fe) {
      e.appendMsgComp(fe.what());
    }
    diet_string_set(pb,0, "error");
    diet_string_set(pb,1, e.what());
  }

  return 0;
}

/**
 * \brief Function to solve the getListOfQueues service
 * \param pb is a structure which corresponds to the descriptor of a profile
 * \return raises an exception on error
 */
int
solveListOfQueues(diet_profile_t* pb) {

  std::string authKey;
  std::string machineId;
  std::string optionSerialized;
  std::string listQueuesSerialized;

  diet_string_get(pb,0, authKey);
  diet_string_get(pb,1, machineId);
  diet_string_get(pb,2, optionSerialized);

  // reset profile to handle result
  diet_profile_reset(pb, 2);

  TMS_Data::ListQueues_ptr listQueues = NULL;


  ListQueuesServer queryQueues(ServerXMS::getInstance()->getBatchType(),
                               ServerXMS::getInstance()->getBatchVersion(),
                               optionSerialized);

  try {
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(vishnu::TMSMAPPERNAME);
    int mapperkey = mapper->code("vishnu_list_queues");
    mapper->code(machineId, mapperkey);
    mapper->code(optionSerialized, mapperkey);
    std::string cmd = mapper->finalize(mapperkey);

    listQueues = queryQueues.list();

    ::ecorecpp::serializer::serializer _ser;
    listQueuesSerialized =  _ser.serialize_str(listQueues);


    diet_string_set(pb,0, "success");
    diet_string_set(pb,1, listQueuesSerialized);
    FINISH_COMMAND(authKey, cmd, vishnu::TMS, vishnu::CMDSUCCESS, "");
  } catch (VishnuException& ex) {
    try {
      FINISH_COMMAND(authKey, "", vishnu::TMS, vishnu::CMDFAILED, "");
    } catch (VishnuException& fe) {
      ex.appendMsgComp(fe.what());
    }
    diet_string_set(pb,0, "error");
    diet_string_set(pb,1, ex.what());
  }

  return 0;
}

/**
 * \brief Function to solve the jobOutPutGetResult service
 * \param pb is a structure which corresponds to the descriptor of a profile
 * \return raises an exception on error
 */
int
solveJobOutPutGetResult(diet_profile_t* pb) {

  std::string authKey;
  std::string machineId;
  std::string optionsSerialized;
  std::string jobid;

  //IN Parameters
  diet_string_get(pb,0, authKey);
  diet_string_get(pb,1, machineId);
  diet_string_get(pb,2, optionsSerialized);
  diet_string_get(pb,3, jobid);

  // reset profile to handle result
  diet_profile_reset(pb, 2);

  try {
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(vishnu::TMSMAPPERNAME);
    int mapperkey = mapper->code("vishnu_get_job_output");
    mapper->code(machineId, mapperkey);
    mapper->code(optionsSerialized, mapperkey);
    mapper->code(jobid, mapperkey);
    std::string cmd = mapper->finalize(mapperkey);

    //Start dealing with output
    JobOutputServer jobOutputServer(authKey, machineId);
    JsonObject options(optionsSerialized);
    TMS_Data::JobResult result = jobOutputServer.getJobOutput(&options, jobid);
    std::string jobFiles = vishnu::getResultFiles(result, false) ;
    std::string outputInfo = bfs::unique_path(boost::str(boost::format("%1%/vishnu-%2%-outdescr%3%")
                                                         % boost::filesystem::temp_directory_path().string()
                                                         % jobid
                                                         % "%%%%%%%")).string();
    vishnu::saveInFile(outputInfo, jobFiles);

    diet_string_set(pb,0, "success");
    diet_string_set(pb,1, outputInfo);

    FINISH_COMMAND(authKey, cmd, vishnu::TMS, vishnu::CMDSUCCESS, "");
  } catch (VishnuException& e) {
    try {
      FINISH_COMMAND(authKey, "", vishnu::TMS, vishnu::CMDFAILED, "");
    } catch (VishnuException& fe) {
      e.appendMsgComp(fe.what());
    }

    diet_string_set(pb,0, "error");
    diet_string_set(pb,1, e.what());
  }
  return 0;
}

/**
 * \brief Function to solve the generic query service
 * \param pb is a structure which corresponds to the descriptor of a profile
 * \return raises an exception on error
 */
template <class QueryParameters, class List, class QueryType>
int
solveGenerique(diet_profile_t* pb) {

  std::string authKey;
  std::string machineId;
  std::string optionValueSerialized;
  std::string listSerialized = "";

  //IN Parameters
  diet_string_get(pb,0, authKey);
  diet_string_get(pb,1, machineId);
  diet_string_get(pb,2, optionValueSerialized);

  // reset profile to handle result
  diet_profile_reset(pb, 2);

  QueryParameters* options = NULL;
  List* list = NULL;

  try {

    //To parse the object serialized
    if (! vishnu::parseEmfObject(optionValueSerialized, options)) {
      throw TMSVishnuException(ERRCODE_INVALID_PARAM);
    }
    QueryType query(authKey);

    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(vishnu::TMSMAPPERNAME);
    int mapperkey = mapper->code(query.getCommandName());
    mapper->code(machineId, mapperkey);
    mapper->code(optionValueSerialized, mapperkey);
    std::string cmd = mapper->finalize(mapperkey);

    list = query.list(options);

    ::ecorecpp::serializer::serializer _ser;
    listSerialized =  _ser.serialize_str(list);

    //OUT Parameter
    diet_string_set(pb,0, "success");
    diet_string_set(pb,1, listSerialized);

    FINISH_COMMAND(authKey, cmd, vishnu::TMS, vishnu::CMDSUCCESS, "");

  } catch (VishnuException& ex) {
    try {
      FINISH_COMMAND(authKey, "", vishnu::TMS, vishnu::CMDFAILED, "");
    } catch (VishnuException& fe) {
      ex.appendMsgComp(fe.what());
    }
    diet_string_set(pb,0, "error");
    diet_string_set(pb,1,  ex.what());
  }
  delete options;
  delete list;
  return 0;
}

/**
 * \brief Function to solve the getListOfJobs service
 * \param pb is a structure which corresponds to the descriptor of a profile
 * \return raises an exception on error
 */
int
solveGetListOfJobs(diet_profile_t* pb) {
  return solveGenerique<TMS_Data::ListJobsOptions, TMS_Data::ListJobs, ListJobServer >(pb);
}

/**
 * \brief Function to solve the getJobsProgression service
 * \param pb is a structure which corresponds to the descriptor of a profile
 * \return raises an exception on error
 */
int
solveGetListOfJobsProgression(diet_profile_t* pb) {
  return solveGenerique<TMS_Data::ProgressOptions, TMS_Data::ListProgression, ListProgressServer >(pb);
}

/**
 * \brief Function to solve the jobOutputGetCompletedJobs service
 * \param pb is a structure which corresponds to the descriptor of a profile
 * \return raises an exception on error
 */
int
solveJobOutPutGetCompletedJobs(diet_profile_t* pb) {
  std::string authKey;
  std::string machineId;
  std::string serializedOptions;
  std::string jobListsSerialized;
  int mapperkey;
  std::string cmd;

  diet_string_get(pb, 0, authKey);
  diet_string_get(pb, 1, machineId);
  diet_string_get(pb, 2, serializedOptions);

  // reset profile to handle result
  diet_profile_reset(pb, 2);

  try {
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(vishnu::TMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_get_completed_jobs_output");
    mapper->code(machineId, mapperkey);
    mapper->code(serializedOptions, mapperkey);
    cmd = mapper->finalize(mapperkey);

    JsonObject options(serializedOptions);
    JobOutputServer jobOutputServer(authKey, machineId);
    TMS_Data::ListJobResults_ptr jobResults = jobOutputServer.getCompletedJobsOutput(&options);

    ::ecorecpp::serializer::serializer _ser;
    jobListsSerialized = _ser.serialize_str(jobResults);

    std::ostringstream ossFileName ;
    int nbResult = jobResults->getResults().size() ;
    for(size_t i = 0; i < nbResult; i++) {
      std::ostringstream missingFiles;
      missingFiles.clear() ;
      ossFileName << vishnu::getResultFiles(*jobResults->getResults().get(i), true);
    }
    std::string outputInfo = bfs::unique_path(boost::filesystem::temp_directory_path().string()+"/vishnu-outdescr%%%%%%%").string();
    vishnu::saveInFile(outputInfo, ossFileName.str());

    JsonObject data;
    data.setProperty("infofile", outputInfo);
    data.setProperty("joblist", jobListsSerialized);

    // set result
    diet_string_set(pb, 0, "success");
    diet_string_set(pb, 1, data.encode());

    FINISH_COMMAND(authKey, cmd, vishnu::TMS, vishnu::CMDSUCCESS, "");
  } catch (VishnuException& e) {
    try {
      FINISH_COMMAND(authKey, cmd, vishnu::TMS, vishnu::CMDFAILED, "");
    } catch (VishnuException& fe) {
      e.appendMsgComp(fe.what());
    }
    // set result
    diet_string_set(pb, 0, "error");
    diet_string_set(pb, 1, e.what());
  }
  return 0;
}


/**
 * \brief Function to solve the service solveAddWork
 * \param pb is a structure which corresponds to the descriptor of a profile
 * \return raises an exception on error
 */
int
solveAddWork(diet_profile_t* pb) {
  std::string authKey;
  std::string workSerialized;
  std::string opSerialized;

  //IN Parameters
  diet_string_get(pb,0, authKey);
  diet_string_get(pb,1, workSerialized);
  diet_string_get(pb,2, opSerialized);

  // reset profile to handle result
  diet_profile_reset(pb, 2);

  //FIXME: SessionServer sessionServer = SessionServer(authKey);

  TMS_Data::AddWorkOptions_ptr workop = NULL;
  TMS_Data::Work_ptr work = NULL;

  try {
    std::string msgComp = "";

    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(vishnu::TMSMAPPERNAME);
    int mapperkey = mapper->code("vishnu_add_work");
    mapper->code(workSerialized, mapperkey);
    mapper->code(opSerialized, mapperkey);
    std::string cmd = mapper->finalize(mapperkey);

    //To parse the object serialized
    if (! vishnu::parseEmfObject(workSerialized, work)) {
      throw TMSVishnuException(ERRCODE_INVALID_PARAM, msgComp);
    }
    //To parse the object serialized
    if (! vishnu::parseEmfObject(opSerialized, workop)) {
      throw TMSVishnuException(ERRCODE_INVALID_PARAM, msgComp);
    }

    //FIXME: WorkServer workServer = WorkServer(work, sessionServer);
    //FIXME: workServer.add(ServerXMS::getInstance()->getVishnuId(), workop);

    //To serialize the user object
    ::ecorecpp::serializer::serializer _ser;
    std::string workSerializedUpdate = _ser.serialize_str(work);

    // set result
    diet_string_set(pb,0, "success");
    diet_string_set(pb,1, workSerializedUpdate);

    FINISH_COMMAND(authKey, cmd, vishnu::TMS, vishnu::CMDFAILED, work->getWorkId());
  } catch (VishnuException& e) {
    try {
      FINISH_COMMAND(authKey, "", vishnu::TMS, vishnu::CMDFAILED, "");
    } catch (VishnuException& fe) {
      e.appendMsgComp(fe.what());
    }

    // set result
    diet_string_set(pb,0, "error");
    diet_string_set(pb,1, e.what());
  }
  delete work;
  return 0;
}
