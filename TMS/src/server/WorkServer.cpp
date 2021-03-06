/**
* \file WorkServer.cpp
* \brief This file implements the Class which manipulates VISHNU work data on server side.
* \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
* \date 31/01/2011
*/

#include "WorkServer.hpp"
#include "DbFactory.hpp"
#include "utilVishnu.hpp"
#include "utilServer.hpp"
#include "SystemException.hpp"
#include "boost/scoped_ptr.hpp"

/**
* \brief Constructor
* \param sessionKey The session key
* \param machineId The machine id
* \param work The work data structure
*/
WorkServer::WorkServer(const std::string& sessionKey,
                       const std::string& machineId,
                       TMS_Data::Work* work)
  : msessionKey(sessionKey), mmachineId(machineId), mwork(work), mworkop(NULL) {
  DbFactory factory;
  mdatabaseInstance = factory.getDatabaseInstance();

  vishnu::validateAuthKey(msessionKey, machineId, mdatabaseInstance, muserSessionInfo);
}

/**
* \brief Function to add a new VISHNU work
* \param vishnuId The identifier of the vishnu instance
* \return raises an exception on error
*/
int
WorkServer::add(int vishnuId, TMS_Data::AddWorkOptions*& mworkop) {

  std::string sqlUpdate = "update work set ";
  std::string idWorkGenerated;

  mwork->setApplicationId(mworkop->getApplicationId());
  mwork->setSubject(mworkop->getSubject());
  mwork->setOwner(mworkop->getOwner());
  mwork->setDescription(mworkop->getDescription());
  mwork->setProjectId(mworkop->getProjectId());
  mwork->setNbCPU(mworkop->getNbCPU());

  std::string timestamp = "CURRENT_TIMESTAMP";
  std::string owner = vishnu::convertToString(muserSessionInfo.num_user);
  std::string nummachine =   muserSessionInfo.num_machine;

  //if the user is an admin
  if (muserSessionInfo.user_privilege == vishnu::PRIVILEGE_ADMIN) {

    //Generation of workid
    idWorkGenerated = vishnu::getObjectId(vishnuId,
                                          "formatidwork",
                                          vishnu::WORK,
                                          mwork->getSubject());

    //if the work id is generated
    if (idWorkGenerated.size() != 0) {
      mwork->setWorkId(idWorkGenerated);
      //if the workId does not exist
      if (getAttribut("where identifier='"+mdatabaseInstance->escapeData(mwork->getWorkId())+"'","count(*)") == "1") {
        //To inactive the work status
        //          mwork->setStatus(INACTIVE_STATUS);
        // TODO
        mwork->setStatus(0);
        //FIXME : set ApplicationId of mwork currently null
        //sqlUpdate+="application_id="+convertToString(mwork->getApplicationId())+", ";
        sqlUpdate+="date_created="+timestamp+", ";
        sqlUpdate+="done_ratio="+vishnu::convertToString(mwork->getDoneRatio())+", ";
        sqlUpdate+="machine_id="+nummachine+", ";
        sqlUpdate+="nbcpus="+vishnu::convertToString(mwork->getNbCPU())+", ";
        sqlUpdate+="owner_id='"+owner+"', ";
        sqlUpdate+="status="+vishnu::convertToString(mwork->getStatus())+", ";
        sqlUpdate+="subject='"+mdatabaseInstance->escapeData(mwork->getSubject())+"' ";
        sqlUpdate+="WHERE identifier='"+mdatabaseInstance->escapeData(mwork->getWorkId())+"';";

        mdatabaseInstance->process(sqlUpdate);

      } else { //if the machine id is generated
        throw SystemException (ERRCODE_SYSTEM, "There is a problem to parse the formatidwork");
      }
    } else { //END if the formatidmachine is defined
      SystemException e (ERRCODE_SYSTEM, "The formatidwork is not defined");
      throw e;
    }
  } else { //End if the user is an admin
    throw TMSVishnuException (ERRCODE_PERMISSION_DENIED, "No sufficient permission");
  }
  return 0;
}

/**
* \brief Destructor
*/
WorkServer::~WorkServer() {
}

/**
* \brief Function to get work information
* \return  The user data structure
*/
TMS_Data::Work*
WorkServer::getData() {
  return mwork;
}

/**
* \brief Function to get work information from the database vishnu
* \param condition The condition of the select request
* \param attrname the name of the attribut to get
* \return the value of the attribut or empty string if no results
*/

std::string
WorkServer::getAttribut(std::string condition, std::string attrname) {

  std::string sqlCommand("SELECT "+attrname+" FROM work "+condition);
  boost::scoped_ptr<DatabaseResult> result(mdatabaseInstance->getResult(sqlCommand.c_str()));
  return result->getFirstElement();
}

/**
* \brief Function to get the work
* \return The name of the work
*/
std::string
WorkServer::getWorkName() {

  std::string  workName = getAttribut("where identifier='"+mdatabaseInstance->escapeData(getData()->getWorkId())+"'", "subject");

  return workName;
}

/**
* \brief Function to check the workId
* \return raises an exception
*/
void WorkServer::checkWork() {

  if(getAttribut("where identifier='"+mdatabaseInstance->escapeData(mwork->getWorkId())+"'").size()==0){
    throw TMSVishnuException(ERRCODE_UNKNOWN_WORKID, mwork->getWorkId()+" does not exist among the defined"
                             " work by VISHNU System");
  }
}
