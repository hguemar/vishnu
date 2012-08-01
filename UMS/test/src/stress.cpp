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

#include "UMS_Data.hpp"
#include "UMS_Data_forward.hpp"
#include <iostream>
#include "api_ums.hpp"

using namespace std;
using namespace UMS_Data;
using namespace vishnu;

void stress(){
  int i;
  string             	  key  = ""       ;
  string 	     	  pwd  = "admin"  ;
  string 	     	  uid  = "admin_1";
  ConnectOptions 	  cop  ;//= ecoreFactory->createConnectOptions();
  Session                 sess ;

  // Setting value
  vishnuInitialize(getenv("VISHNU_CONFIG_FILE"), 0, NULL);

  for (i=0;i<5;i++){
    cout << " In loop : " <<  i << endl;
    connect    (uid, pwd, sess, cop );
    close(sess.getSessionKey());
  }
  vishnuFinalize();
}


void forker(int cpt){
  cpt--;
  switch(fork()){
  case 0 :
    stress();
    break;
  case -1 :
    cout << " Fork number " << cpt << " failed " << endl;
    break;
  default :
    if(cpt>0)
      forker(cpt);
    break;
  }
  return;
}


int main(int argc, char** argv){
  int cpt;
  if (argc>1){
    cpt = atoi (argv[1]);
  }
  else{
    cpt = 5;
  }
  forker(cpt);
  return 0;
}


