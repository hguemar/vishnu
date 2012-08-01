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
 * \file delete_machine.cpp
 * This file defines the VISHNU delete_machine command 
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

struct DeleteMachineFunc {

  std::string mmachineId;

  DeleteMachineFunc(std::string machineId):
    mmachineId(machineId)
  {};

  int operator()(std::string sessionKey) {
    int res = deleteMachine(sessionKey,mmachineId);
    return res;
  }
};


int main (int ac, char* av[]){

  /******* Parsed value containers ****************/

  string dietConfig;

  std::string machineId;

  /**************** Describe options *************/
  boost::shared_ptr<Options> opt(new Options(av[0]));

  opt->add("dietConfig,c",
      "The diet config file",
      ENV,
      dietConfig);

  opt->add("machineId",
          "The identifier of the machine",
          HIDDEN,
          machineId,1);

  opt->setPosition("machineId",-1);

  CLICmd cmd = CLICmd (ac, av, opt);

  // Parse the cli and setting the options found
  int ret = cmd.parse(env_name_mapper());

  if (ret != CLI_SUCCESS){
    helpUsage(*opt,"machineId");
    return ret;
  }

  // PreProcess (adapt some parameters if necessary)
  checkVishnuConfig(*opt);
  if ( opt->count("help")){
    helpUsage(*opt,"machineId");
    return 0;
  }

  DeleteMachineFunc delFunc(machineId);
  return GenericCli().run(delFunc, dietConfig, ac, av); 

}// end of main


