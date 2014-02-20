/**
 * \file ListAuthSystemsServer.hpp
 * \brief This file contains the VISHNU QueryServer class.
 * \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
 * \date February 2012
 */
#ifndef _LIST_AUTH_SYSTEMS_SERVER_
#define _LIST_AUTH_SYSTEMS_SERVER_

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "boost/date_time/posix_time/posix_time.hpp"

#include "SessionServer.hpp"
#include "QueryServer.hpp"

#include "ListAuthSystems.hpp"
#include "ListAuthSysOptions.hpp"

/**
 * \class ListAuthSystemsServer
 * \brief ListAuthSystemsServer class implementation
 */
class ListAuthSystemsServer: public QueryServer<UMS_Data::ListAuthSysOptions, UMS_Data::ListAuthSystems>
{

public:

  /**
   * \param session The object which encapsulates the session information (ex: identifier of the session)
   * \brief Constructor, raises an exception on error
   */
  ListAuthSystemsServer(const SessionServer& session)
    : QueryServer<UMS_Data::ListAuthSysOptions, UMS_Data::ListAuthSystems>(),
      mcommandName("vishnu_list_auth_systems"),
      msessionServer(session)
  {

  }

  /**
   * \brief Function to treat the ListAuthSystemsServer options
   * \param userServer the object which encapsulates user information
   * \param options The object which encapsulates the information of ListAuthSystemsServer  options
   * \param sqlRequest the sql data base request
   * \return raises an exception on error
   */
  void
  processOptions(UserServer userServer, const UMS_Data::ListAuthSysOptions_ptr& options, std::string& sqlRequest) {


    mfullInfo = options->isListFullInfo();
    //If the full option is defined, the user must be an admin
    if (mfullInfo) {
      if(!userServer.isAdmin()) {
        UMSVishnuException e (ERRCODE_NO_ADMIN);
        throw e;
      }
    }

    if (options != NULL) {
      std::string  userId = options->getUserId();
      if(userId.size()!=0) {
        //If the user is an admin
        if(userServer.isAdmin()) {
          checkUserId(userId);
          sqlRequest.append(" and authsystemid IN (SELECT authsystemid from authsystem, users,"
                            "authaccount where userid='"+mdatabaseInstance->escapeData(userId)+"'"
                            "and authaccount.authsystem_authsystemid=authsystem.numauthsystemid and authaccount.users_numuserid=users.numuserid)"
                            );
        }//End If the user is an admin
        else {
          UMSVishnuException e (ERRCODE_NO_ADMIN);
          throw e;
        }
      }

      std::string  authSystemId = options->getAuthSystemId();
      if(authSystemId.size()!=0) {
        //To check if the authSystem identifier is correct
        checkAuthSystemId(authSystemId);
        addOptionRequest("authsystemid", authSystemId, sqlRequest);
      }

      //If the option for listing all authSystem has not defined
      if (!options->isListAllAuthSystems()) {
        //If the option userId has not
        if ((userId.size() == 0) && (authSystemId.size() == 0)) {
          sqlRequest.append(" and authsystemid IN (SELECT authsystemid from authsystem, users,"
                            "authaccount where userid='"+mdatabaseInstance->escapeData(userServer.getData().getUserId())+"'"
                            "and authaccount.authsystem_authsystemid=authsystem.numauthsystemid and authaccount.users_numuserid=users.numuserid)"
                            );
        }
      }
    }
    else {
      sqlRequest.append(" and authsystemid IN (SELECT authsystemid from authsystem, users, "
                        "authaccount where userid='"+mdatabaseInstance->escapeData(userServer.getData().getUserId())+"'"
                        "and authaccount.authsystem_authsystemid=authsystem.numauthsystemid and authaccount.users_numuserid=users.numuserid)"
                        );
    }
  }

  /**
  * \brief Function to list machines information
  * \return The pointer to the UMS_Data::ListAuthSystems containing users information
  * \return raises an exception on error
  */
  UMS_Data::ListAuthSystems* list(UMS_Data::ListAuthSysOptions_ptr option) {

    std::string sql = (boost::format("SELECT authsystemid, name, uri, authlogin, authpassword,"
                                     "       userpwdencryption, authtype, authsystem.status, ldapbase "
                                     " FROM  authsystem, ldapauthsystem"
                                     " WHERE ldapauthsystem.authsystem_authsystemid = authsystem.numauthsystemid"
                                     "  AND authsystem.status!=%1%")%vishnu::STATUS_DELETED).str();
    std::vector<std::string>::iterator ii;
    std::vector<std::string> results;
    UMS_Data::UMS_DataFactory_ptr ecoreFactory = UMS_Data::UMS_DataFactory::_instance();
    mlistObject = ecoreFactory->createListAuthSystems();

    //Creation of the object user
    UserServer userServer = UserServer(msessionServer);
    userServer.init();
    //if the user exists
    if (userServer.exist()) {

      processOptions(userServer, option, sql);
      sql.append(" order by authsystemid");
      //To get the list of authSystems from the database
      boost::scoped_ptr<DatabaseResult> ListofAuthSystems (mdatabaseInstance->getResult(sql.c_str()));
      if (ListofAuthSystems->getNbTuples() != 0){
        for (size_t i = 0; i < ListofAuthSystems->getNbTuples(); ++i) {
          results.clear();
          results = ListofAuthSystems->get(i);
          ii = results.begin();
          UMS_Data::AuthSystem_ptr authSystem = ecoreFactory->createAuthSystem();
          authSystem->setAuthSystemId(*ii);
          authSystem->setName(*(++ii));
          authSystem->setURI(*(++ii));
          std::string authLogin(*(++ii));
          std::string authPassword(*(++ii));
          int userPasswordEncryption(vishnu::convertToInt(*(++ii)));
          int type(vishnu::convertToInt(*(++ii)));
          if (mfullInfo) {
            authSystem->setAuthLogin(authLogin);
            authSystem->setAuthPassword(authPassword);
            authSystem->setUserPasswordEncryption(userPasswordEncryption);
            authSystem->setType(type);
          }
          authSystem->setStatus(vishnu::convertToInt(*(++ii)));
          authSystem->setLdapBase(*(++ii));
          mlistObject->getAuthSystems().push_back(authSystem);
        }
      }
    }
    else {
      UMSVishnuException e (ERRCODE_UNKNOWN_USER);
      throw e;
    }
    return mlistObject;


  }

  /**
   * \brief Function to get the name of the ListAuthSystemsServer command line
   * \return The the name of the ListAuthSystemsServer command line
   */
  std::string
  getCommandName()
  {
    return mcommandName;
  }

  /**
   * \brief Destructor, raises an exception on error
   */
  ~ListAuthSystemsServer() { }

private:

  /////////////////////////////////
  // Attributes
  /////////////////////////////////

  /**
  * \brief The name of the ListMachinesServer command line
  */
  std::string mcommandName;
  /**
  * \brief An option to have full information
  */
  bool mfullInfo;

  /**
  * \brief The SessionServer object containing the encrypted identifier of the session
  *  generated by VISHNU
  */
  SessionServer msessionServer;
};

#endif
