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
 * \file list_users.cpp
 * This file defines the VISHNU list user command 
 * \author Ibrahima Cisse (ibrahima.cisse@sysfera.com)
 */


#include "common.hpp"
#include "cliUtil.hpp"
#include "utils.hpp"
#include "sessionUtils.hpp"
#include "utilVishnu.hpp"

#include "GenericCli.hpp"

namespace po = boost::program_options;

using namespace std;
using namespace vishnu;

struct ListUserFunc {

  UMS_Data_Proto::ListUsers mlsUsers;
  std::string muserIdOption;
  bool mfull;

  ListUserFunc(UMS_Data_Proto::ListUsers lsUsers, std::string userIdOption, bool full):
    mlsUsers(lsUsers), muserIdOption(userIdOption), mfull(full)
  {};

  int operator()(std::string sessionKey) {

    int res = listUsers(sessionKey, mlsUsers, muserIdOption);
    // Display the list
    if(mfull) {
      cout << mlsUsers << endl;
    }
    else {
      for(unsigned int i = 0; i < mlsUsers.users_size(); i++) {
        cout << mlsUsers.users(i) << endl;
      }
    }

    return res;
  }
};

int main (int ac, char* av[]){


  /******* Parsed value containers ****************/

  string dietConfig;

  std::string userIdOption;

  /********** EMF data ************/

  UMS_Data_Proto::ListUsers lsUsers;

  /**************** Describe options *************/
  boost::shared_ptr<Options> opt(new Options(av[0]));

  opt->add("dietConfig,c",
          "The diet config file",
          ENV,
          dietConfig);

  opt->add("userIdOption,i",
          "An option for listing all default option values\n"
          "defined by VISHNU administrator",
          CONFIG,
          userIdOption);

  bool isEmpty;
  //To process list options
  GenericCli().processListOpt(opt, isEmpty, ac, av);

  /********  Process **************************/

  bool full = false;
  // Display the list
  if(isEmpty) {
    full = true;
  }

  ListUserFunc listFunc(lsUsers, userIdOption, full);
  return GenericCli().run(listFunc, dietConfig, ac, av);

}// end of main


