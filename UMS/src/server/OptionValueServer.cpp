/**
* \file OptionValueServer.cpp
* \brief This file implements the Class which manipulates VISHNU options on server side.
* \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
* \date 31/01/2011
*/
#include "OptionValueServer.hpp"
#include "UserServer.hpp"
#include "SessionServer.hpp"
/**
* \brief Constructor
* \fn OptionValueServer()
*/

OptionValueServer::OptionValueServer() {
  DbFactory factory;
  mdatabaseVishnu = factory.getDatabaseInstance();
  moptionValue = NULL;
  msessionServer = NULL;
}
/**
* \brief Constructor
* \fn OptionValueServer(UMS_Data::OptionValue optionvalue)
* \param optionvalue the option data structure
* \param sessionServer The object to manipulate session
*/
OptionValueServer::OptionValueServer(UMS_Data::OptionValue*& optionvalue, SessionServer session):
moptionValue(optionvalue) , msessionServer(&session) {
  DbFactory factory;
  mdatabaseVishnu = factory.getDatabaseInstance();
}
/**
* \brief Function to configure options on the database
* \fn    int configureOption()
* \param defaultOptions the flag to get data from defauts options table
* \return  raises an exception on error
*/
int
OptionValueServer::configureOption(bool defaultOptions) {
  std::string sqlCommand;
  std::string numoptionid;
  std::string optionu_numoptionid;
  std::string numuserid;

  try {
    UserServer userServer = UserServer(SessionServer(msessionServer->getData().getSessionKey()));
    userServer.init();
    //if the user exists
    if (userServer.exist()) {

      //if the option exists
      if (getAttribut("where description='"+moptionValue->getOptionName()+"'", "numoptionid", true).size() != 0) {
        //if the default table is used
        if (defaultOptions) {
          //if the user is an admin
          if (userServer.isAdmin()){
            sqlCommand = "UPDATE optionu set defaultvalue="+moptionValue->getValue()+"\
            where description='"+moptionValue->getOptionName()+"'";
            std::cout <<"SQL COMMAND:"<<sqlCommand;
            mdatabaseVishnu->process(sqlCommand.c_str());
          } //END if the user is an admin
          else {
            UMSVishnuException e (ERRCODE_NO_ADMIN);
            throw e;
          }
        } //END if the default table is used
        else {

          //To get the database number of the userid
          numuserid = userServer.getAttribut("where\
          userid='"+userServer.getData().getUserId()+"'and pwd='"+userServer.getData().getPassword()+"'");

          //To get the database number of the default option
          numoptionid = getAttribut("where \
          description='"+moptionValue->getOptionName()+"'", "numoptionid", true);

          //To check if this option is already defined for the user
          optionu_numoptionid = getAttribut("where \
          users_numuserid="+numuserid+" and optionu_numoptionid="+numoptionid);

          //if the option has not already defined for the user
          if (optionu_numoptionid.size() == 0) {
            sqlCommand = "insert into optionvalue (users_numuserid, optionu_numoptionid, value) values\
            ("+numuserid+",'"+
            getAttribut("where description='"+moptionValue->getOptionName()+"'", "numoptionid", true)
            +"','"+moptionValue->getValue()+"')";
          } //End if the option has not already defined for the user
          else {
            sqlCommand = "UPDATE optionvalue set value="+moptionValue->getValue()+" \
            where optionu_numoptionid="+numoptionid+" and users_numuserid="+numuserid;
          }
          std::cout <<"SQL COMMAND:"<<sqlCommand;
          mdatabaseVishnu->process(sqlCommand.c_str());
        }
      } //END if the option exists
      else {
        UMSVishnuException e (ERRCODE_UNKNOWN_OPTION);
        throw e;
      }
    }//END if the user exists
    else {
      UMSVishnuException e (ERRCODE_UNKNOWN_USER);
      throw e;
    }
  }
  catch (VishnuException& e) {
    throw;
  }

  return 0;
}
/**
* \brief Destructor
* \fn  ~OptionValueServer()
*/
OptionValueServer::~OptionValueServer() {
  if (moptionValue != NULL) {
    delete moptionValue;
  }
}
/**
* \brief Function to get option data structure
* \fn UMS_Data::OptionValue getData()
* \return  The user data structure
*/
UMS_Data::OptionValue*
OptionValueServer::getData() {
  return moptionValue;
}
/**
* \brief Function to get option information from the database vishnu
* \fn getAttribut(std::string condition, std::string attrname, defaultOptions);
* \param condition The condition of the select request
* \param attrname the name of the attribut to get
* \param defaultOptions the flag to get data from defauts options table
* \return the value of the attribut or empty string if no results
*/
std::string
OptionValueServer::getAttribut(std::string condition, std::string attrname, bool defaultOptions) {

  DatabaseResult* result;
  std::vector<std::string>::iterator ii;
  std::string sqlCommand;

  if (defaultOptions) {
    sqlCommand = "SELECT "+attrname+" FROM optionu "+condition;
  }
  else {
    sqlCommand = "SELECT "+attrname+" FROM optionvalue "+condition;
  }

  std::cout <<"SQL COMMAND:"<<sqlCommand;

  try {
    result = mdatabaseVishnu->getResult(sqlCommand.c_str());
    return result->getFirstElement();
  }
  catch (VishnuException& e) {
    throw;
  }
}
/**
* \brief Function to get closure information from the database vishnu
* \fn getAttribut(std::string condition, std::string attrname, defaultOptions);
* \param numuserId The database number id of the user who wants to get closure information
* \param nameInfo the name of the closure information
*/
int
OptionValueServer::getClosureInfo(std::string numuserId, std::string nameInfo) {

  std::string userCloseInfo;
  try {
    //To get the closure information of the user identified by the numuserId
    userCloseInfo = getAttribut ("where users_numuserid='"+numuserId+"' and optionu_numoptionid="+
    getAttribut("where description='"+nameInfo+"'", "numoptionid", true));
    //If the closure information is not defined for the user
    if (userCloseInfo.size() == 0) {
      //To get the closure information from the table with the default options values
      userCloseInfo = getAttribut("where description='"+nameInfo+"'", "defaultvalue", true);
      return convertToInt(userCloseInfo);
    } //END If the closure information is not defined for the user
    else {
      return convertToInt(userCloseInfo);
    }
  }
  catch (VishnuException& e) {
  throw;
  }
}
