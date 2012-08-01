/* This file is a part of VISHNU.

* Copyright SysFera SAS (2011) 

* contact@sysfera.com

* This software is a computer program whose purpose is to provide 
* access to distributed computing resources.
*
* This software is governed by the CeCILL  license under French law and
* abiding by the rules of distribution of free software.  You can  use, 
* modify and/ or redistribute the software under the terms of the CeCILL
* license as circulated by CEA, CNRS and INRIA at the following URL
* "http://www.cecill.info". 

* As a counterpart to the access to the source code and  rights to copy,
* modify and redistribute granted by the license, users are provided only
* with a limited warranty  and the software's author,  the holder of the
* economic rights,  and the successive licensors  have only  limited
* liability. 
*
* In this respect, the user's attention is drawn to the risks associated
* with loading,  using,  modifying and/or developing or reproducing the
* software by the user in light of its specific status of free software,
* that may mean  that it is complicated to manipulate,  and  that  also
* therefore means  that it is reserved for developers  and  experienced
* professionals having in-depth computer knowledge. Users are therefore
* encouraged to load and test the software's suitability as regards their
* requirements in conditions enabling the security of their systems and/or 
* data to be ensured and,  more generally, to use and operate it in the 
* same conditions as regards security. 
*
* The fact that you are presently reading this means that you have had
* knowledge of the CeCILL license and that you accept its terms.
*/

/**
 * \file ListOptionsValuesServer.hpp
 * \brief This file contains the VISHNU QueryServer class.
 * \author Daouda Traore (daouda.traore@sysfera.com) and
 *   Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
 * \date February 2011
 */
#ifndef _LIST_OPTIONS_VALUES_SERVER_
#define _LIST_OPTIONS_VALUES_SERVER_

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "boost/date_time/posix_time/posix_time.hpp"

#include "SessionServer.hpp"
#include "ListOptionsValues.hpp"
#include "ListOptOptions.hpp"

/**
 * \class ListOptionsValuesServer
 * \brief ListOptionsValuesServer class implementation
 */
class ListOptionsValuesServer: public QueryServer<UMS_Data::ListOptOptions, UMS_Data::ListOptionsValues>
{

public:

  /**
   * \fn ListOptionsValuesServer(const SessionServer session)
   * \param session The object which encapsulates the session information (ex: identifier of the session)
   * \brief Constructor, raises an exception on error
   */
  ListOptionsValuesServer(const SessionServer session):
    QueryServer<UMS_Data::ListOptOptions, UMS_Data::ListOptionsValues>(session)
  {
    mcommandName = "vishnu_list_options";
  }
  /**
   * \fn ListOptionsValuesServer(UMS_Data::ListOptOptions_ptr params,
   *                             const SessionServer& session)
   * \param params The object which encapsulates the information of ListOptionsValuesServer options
   * \param session The object which encapsulates the session information (ex: identifier of the session)
   * \brief Constructor, raises an exception on error
   */
  ListOptionsValuesServer(UMS_Data::ListOptOptions_ptr params, const SessionServer& session):
    QueryServer<UMS_Data::ListOptOptions, UMS_Data::ListOptionsValues>(params, session)
  {
    mcommandName = "vishnu_list_options";
  }

  /**
   * \brief Function to treat the ListOptionsValuesServer options
   * \fn void processOptions(UserServer userServer,
   *                         const UMS_Data::ListOptOptions_ptr& options,
   *                         std::string& sqlRequest)
   * \param userServer the object which encapsulates user information
   * \param options the object which contains the ListOptionsValuesServer options values
   * \param sqlRequest the sql data base request
   * \return raises an exception on error
   */
  void processOptions(UserServer userServer, const UMS_Data::ListOptOptions_ptr& options, std::string& sqlRequest)
  {
      std::string sqlListofOptionValues = "SELECT description, value, userid from optionu, optionvalue, users"
                                     " where optionu.numoptionid=optionvalue.optionu_numoptionid and"
                                     " optionvalue.users_numuserid=users.numuserid";

     size_t userIdSize = options->getUserId().size();
     size_t nameSize = options->getOptionName().size();
     bool listAllDefault = options->isListAllDeftValue();

     if ((!userServer.isAdmin()) && (userIdSize!=0)) {
        UMSVishnuException e (ERRCODE_NO_ADMIN);
        throw e;
     }

     if(!listAllDefault) {

       if(userIdSize==0) {
          sqlRequest = sqlListofOptionValues;
          addOptionRequest("userid", userServer.getData().getUserId(), sqlRequest);
       } else {
          //To check if the user id is correct
          checkUserId(options->getUserId());

          sqlRequest = sqlListofOptionValues;
          addOptionRequest("userid", options->getUserId(), sqlRequest);
       }

       if(nameSize!=0) {
          //To check if the option name is correct
          checkOptionName(options->getOptionName());

          addOptionRequest("description", options->getOptionName(), sqlRequest);
       }
    }

  }

  /**
   * \brief Function to list options values information
   * \fn UMS_Data::ListOptionsValues* list()
   * \return The pointer to the UMS_Data::ListOptionsValues containing options values information
   * \return raises an exception on error
   */
  UMS_Data::ListOptionsValues* list() {
    std::string sqlListofOptions = "SELECT description, defaultvalue from optionu";

    std::vector<std::string>::iterator ii;
    std::vector<std::string> results;
    UMS_Data::UMS_DataFactory_ptr ecoreFactory = UMS_Data::UMS_DataFactory::_instance();
    mlistObject = ecoreFactory->createListOptionsValues();


      //Creation of the object user
      UserServer userServer = UserServer(msessionServer);
      userServer.init();
      //if the user exists
      if (userServer.exist()) {
        //To process options
        processOptions(userServer, mparameters, sqlListofOptions);

        //To get the list of options values from the database
        boost::scoped_ptr<DatabaseResult> ListofOptions (mdatabaseVishnu->getResult(sqlListofOptions.c_str()));

        if (ListofOptions->getNbTuples() != 0){
          for (size_t i = 0; i < ListofOptions->getNbTuples(); ++i) {
            results.clear();
            results = ListofOptions->get(i);
            ii = results.begin();

            UMS_Data::OptionValue_ptr optionValue = ecoreFactory->createOptionValue();;
            optionValue->setOptionName(*ii);
            optionValue->setValue(*(++ii));
            mlistObject->getOptionValues().push_back(optionValue);
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
   * \brief Function to get the name of the ListOptionsValuesServer command line
   * \fn std::string getCommandName()
   * \return The the name of the ListOptionsValuesServer command line
   */
  std::string getCommandName()
  {
    return mcommandName;
  }

  /**
   * \fn ~ListOptionsValuesServer()
   * \brief Destructor, raises an exception on error
   */
  ~ListOptionsValuesServer()
  {
  }

  private:

  /////////////////////////////////
  // Attributes
  /////////////////////////////////


 /**
  * \brief The name of the ListOptionsValuesServer command line
  */
  std::string mcommandName;
};

#endif
