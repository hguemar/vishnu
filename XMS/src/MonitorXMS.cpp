#include "MonitorXMS.hpp"
#include <csignal>
#include "AuthenticatorConfiguration.hpp"
#include "AuthenticatorFactory.hpp"
#include "Authenticator.hpp"
#include "BatchServer.hpp"
#include "BatchFactory.hpp"
#include "ServerXMS.hpp"


MonitorXMS::MonitorXMS(int interval) :
  minterval(interval),
  mdatabaseVishnu(NULL),
  mauthenticator(NULL) {}

MonitorXMS::~MonitorXMS() {
  delete mdatabaseVishnu;
}

void
MonitorXMS::init(const SedConfig& cfg) {
  using boost::format;
  using boost::str;

  int vishnuId = cfg.vishnuId;
  DbConfiguration dbConfig = cfg.dbConfig;
  AuthenticatorConfiguration authenticatorConfig = cfg.authenticatorConfig;
  mhasUMS = cfg.hasUMS;
  mhasTMS = cfg.hasTMS;
  mhasFMS = cfg.hasFMS;


  DbFactory factory;
  mdatabaseVishnu = factory.createDatabaseInstance(dbConfig);
  mmachineId = cfg.mid;
  mbatchType = cfg.batchType;
  mbatchVersion = cfg.batchVersion;

  AuthenticatorFactory authfactory;
  mauthenticator = authfactory.createAuthenticatorInstance(authenticatorConfig);

  std::string sqlCommand =
   str(format("SELECT * FROM vishnu where vishnuid=%1%")
     % vishnu::convertToString(vishnuId));

  try {
    /*connection to the database*/
    mdatabaseVishnu->connect();

    /* Checking of vishnuid on the database */
    boost::scoped_ptr<DatabaseResult> result(mdatabaseVishnu->getResult(sqlCommand.c_str()));
    if (result->getResults().size() == 0) {
      throw SystemException(ERRCODE_DBERR, "The vishnuid is unrecognized");
    }
  } catch (VishnuException& e) {
    exit(0);
  }
}

void
MonitorXMS::checkJobs(int batchtype){
  std::string sqlRequest = boost::str(boost::format(
    "SELECT jobId, batchJobId, vmIp, vmId "
    " FROM job, vsession "
    " WHERE vsession.numsessionid=job.vsession_numsessionid "
    " AND submitMachineId='%1%' "
    " AND batchType=%2% "
    " AND status >= %3% "
    " AND status < %4% ")
      % mmachineId
      % vishnu::convertToString(batchtype)
      % vishnu::STATE_UNDEFINED
      % vishnu::STATE_COMPLETED);
  BatchFactory factory;
  boost::scoped_ptr<BatchServer> batchServer(factory.getBatchServerInstance(batchtype, mbatchVersion));

  try {
    std::cout << "request : " << sqlRequest << " results \n";
    boost::scoped_ptr<DatabaseResult> result(mdatabaseVishnu->getResult(sqlRequest.c_str()));

    std::vector<std::string> buffer;
    std::vector<std::string>::iterator item;
    std::cout << "found : " << result->getNbTuples() << " results \n";
    for (size_t i = 0; i < result->getNbTuples(); ++i) {
      buffer.clear();
      buffer = result->get(i);
      item = buffer.begin();
      TMS_Data::Job job;
      job.setJobId( *item++ );
      job.setBatchJobId( *item++ );
      job.setVmIp( *item++ );
      job.setVmId( *item++ );
      job.setOwner( *item );

      try {
        int state;
        switch (batchtype) {
        case DELTACLOUD:
        case OPENNEBULA:
          state = batchServer->getJobState( JsonObject::serialize(job) );
          break;
        default:
          std::cout << "LF states : " << " results \n";
          state = batchServer->getJobState(job.getBatchJobId());
          std::cout << "found state : " << state << " results \n";
          break;
        }
        std::string query = boost::str(boost::format("UPDATE job SET status=%1%"
                                                     " WHERE jobId='%2%';")
                                       % vishnu::convertToString(state) % job.getJobId());
        if (state == vishnu::STATE_COMPLETED) {
          query.append(boost::str(boost::format("UPDATE job SET endDate=CURRENT_TIMESTAMP"
                                                " WHERE jobId='%1%';") % job.getJobId()));
        }
        mdatabaseVishnu->process(query.c_str());
      } catch (VishnuException& ex) {
        std::clog << boost::format("[TMSMONITOR][ERROR] %1%\n")%ex.what();
      }
    }
  } catch (VishnuException& ex) {
    std::clog << boost::format("[TMSMONITOR][ERROR] %1%\n")%ex.what();
  }
}


void
MonitorXMS::checkSession(){
  SessionServer closer;
  std::vector<std::string> tmp;
  std::vector<std::string>::iterator ii;
  try {
    boost::scoped_ptr<DatabaseResult> result(closer.getSessionToclosebyTimeout());

    if (result->getNbTuples() != 0) {
      for (size_t i = 0; i < result->getNbTuples(); ++i) {
        tmp.clear();
        tmp = result->get(i);

        ii = tmp.begin();
        SessionServer sessionServer (*ii);

        try {
          //closure of the session
          sessionServer.close();
        }
        catch (VishnuException& e) {
          std::string errorInfo =  e.buildExceptionString();
          std::cerr << errorInfo << "\n";
          if (e.getMsgI() == ERRCODE_AUTHENTERR) {
            //FIXME: Do something for the sed UMS when the monitor goes out
            std::cerr << errorInfo << "\n";
            exit(1);
          }
        }
      }
    }

  } catch (VishnuException& e) {
    std::string errorInfo =  e.buildExceptionString();

    if ((e.getMsgI() == ERRCODE_DBERR) || (e.getMsgI() == ERRCODE_AUTHENTERR)) {
      std::cerr << errorInfo << "\n";
      exit(1);
    }
  }
}

void
MonitorXMS::checkFile(){
  std::vector<std::string>::iterator iter;
  std::vector<std::string> tmp;
  std::string pid,transferId;
  std::string sqlUpdatedRequest;
  std::string sqlRequest = "SELECT transferid,processid "
                           " FROM filetransfer,vsession"
                           " WHERE vsession.numsessionid=filetransfer.vsession_numsessionid "
                           " AND filetransfer.status=0";
  try {
    boost::scoped_ptr<DatabaseResult> result(mdatabaseVishnu->getResult(sqlRequest));
    if (result->getNbTuples() != 0) {
      for (size_t i = 0; i < result->getNbTuples(); ++i) {
        tmp.clear();
        tmp = result->get(i);
        iter = tmp.begin();
        transferId=*iter;
        ++iter;
        pid = *iter;
        ++iter;
        try {
          if(false==vishnu::process_exists(vishnu::convertToString(pid))) {
            sqlUpdatedRequest = "UPDATE filetransfer SET status=3 where transferid='"+transferId+"'";
            mdatabaseVishnu->process(sqlUpdatedRequest);
          }
        } catch (VishnuException& ex) {
          std::clog << boost::format("[FMSMONITOR][ERROR] %1%\n")%ex.what();
        }
      }
    }
  } catch (VishnuException& ex) {
    std::clog << boost::format("[FMSMONITOR][ERROR] %1%\n")%ex.what();
  }
}



int
MonitorXMS::run() {
  std::cout << "running monitor \n";
  if (mhasUMS)
    checkSession();
  if (mhasTMS) {
    std::cout << "running monitor TMS" << mbatchType << "\n";
    checkJobs(mbatchType);
    if (mbatchType != POSIX){
      std::cout << "running monitor TMS" << POSIX << "\n";
      checkJobs(POSIX);
    }
  }
  if (mhasFMS)
    checkFile();

// KEPT Waiting to know wtf is this
//  std::string vmUser = "root";
//  if (mbatchType == DELTACLOUD) {
//    vmUser = vishnu::getVar(vishnu::CLOUD_ENV_VARS[vishnu::CLOUD_VM_USER], true, "root");
//  }
  sleep(minterval);

  return 0;
}
