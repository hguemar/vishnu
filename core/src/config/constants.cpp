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

#include "constants.hpp"

namespace vishnu {

//{{RELAX<MISRA_0_1_3> Because this table is used in other files
// !!! None of these keywords can be a prefix for another !!!
  param_t params[] =
  {
    {DIETCONFIGFILE, "dietConfigFile", STRING_PARAMETER},
    /* [1]  */ {VISHNUID, "vishnuId", INT_PARAMETER},
    /* [2]  */ {DBTYPE, "databaseType", STRING_PARAMETER},
    /* [3]  */ {DBHOST, "databaseHost", STRING_PARAMETER},
    /* [4]  */ {DBPORT, "databasePort", INT_PARAMETER},
    /* [5]  */ {DBNAME, "databaseName", STRING_PARAMETER},
    /* [6]  */ {DBUSERNAME, "databaseUserName", STRING_PARAMETER},
    /* [7]  */ {DBPASSWORD, "databaseUserPassword", STRING_PARAMETER},
    /* [8]  */ {SENDMAILSCRIPT, "sendmailScriptPath", STRING_PARAMETER},
    /* [9]  */ {BATCHTYPE, "batchSchedulerType", STRING_PARAMETER},
    /* [10] */ {MACHINEID, "vishnuMachineId", STRING_PARAMETER},
    /* [11] */ {REMOTEBINDIR, "vishnuRemoteBinDirectory", STRING_PARAMETER},
    /* [12] */ {INTERVALMONITOR, "intervalMonitor", INT_PARAMETER},
    /* [13] */ {DBPOOLSIZE, "databaseConnectionsNb", INT_PARAMETER}
  };
//}}RELAX<MISRA_0_1_3>
}

