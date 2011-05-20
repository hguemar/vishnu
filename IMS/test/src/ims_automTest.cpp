/**
 * \file ims_automTest
 * \brief Contains IMS API test implementation
 * References: VISHNU_D5_1b_IMS-PlanTests
 */

//UMS forward Headers
#include "UMS_Data_forward.hpp"
//IMS forward Headers
#include "IMS_Data_forward.hpp"

#include "IMS_fixtures.hpp"
#include "imsTestUtils.hpp"
#include "IMS_testconfig.h"

#include "TMS_Data.hpp"
using namespace TMS_Data;

// C++ Headers
#include <iostream>
#include <sstream>
#include <cmath>

// Boost Headers
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>

// namespaces declaration and  aliases
using namespace std;
using namespace UMS_Data;
using namespace IMS_Data;
using namespace vishnu;
namespace bpt= boost::posix_time;
namespace bfs= boost::filesystem;


// The database, UMS and IMS SeD are launched by IMSSedFixture.


BOOST_GLOBAL_FIXTURE(IMSSeDFixture)

BOOST_AUTO_TEST_SUITE(Information_Managment_System_test)
  //Test category 4
  // I2 - B : I2 – B: Get metric data normal
  // Get metric data : normal call

  BOOST_AUTO_TEST_CASE( get_metric_data_normal_call) {

    string sqlPath = IMSSQLPATH;

    BOOST_TEST_MESSAGE("Use case I2 – B: Get metric  data");
    int nbResMetric = 2;
    VishnuConnexion vc("root","vishnu_user");
    // get the session key and the machine identifier
    string sessionKey=vc.getConnexion();
    string machineId="machine_1";
    IMS_Data::ListMetric list;
    IMS_Data::MetricHistOp op;
    //Set FREEMOMORY metric
    op.setType(5);

    try {
      //Set the update frequency to 10 and clean the table state
      if (restore(sqlPath + "/IMSTestGetMetric.sql") != 0) {
        BOOST_TEST_MESSAGE("Database update failed for restore(sqlPath + /IMSTestGetMetric.sql)");
      }
      sleep (5);
      //Wait for metric recording in database
      //10 represents the update frequency
      sleep (nbResMetric*10);

      BOOST_CHECK_EQUAL(getMetricHistory(sessionKey, machineId, list, op),0  );
      //BOOST_TEST_MESSAGE( "list.getMetric().size()" << list.getMetric().size() << "\n");;
      BOOST_REQUIRE(list.getMetric().size() == nbResMetric);
    }
    catch (VishnuException& e) {
      BOOST_MESSAGE("FAILED\n");
      BOOST_MESSAGE(e.what());
      BOOST_CHECK(false);
    }
  }

  // I2 – E1: Get metric data with bad machine identifier
  // Get metric data : bad machine Id

  BOOST_AUTO_TEST_CASE( get_metric_data_bad_machine_Id_call) {

    BOOST_TEST_MESSAGE("Use case I2 – E1: Get metric data with bad machine Id");
    VishnuConnexion vc("root","vishnu_user");
    // get the session key and the machine identifier
    string sessionKey=vc.getConnexion();
    string machineId="unknown_name";

    IMS_Data::ListMetric list;
    IMS_Data::MetricHistOp op;

    BOOST_CHECK_THROW(getMetricHistory(sessionKey, machineId, list, op), VishnuException);
    //BOOST_TEST_MESSAGE("Testing Use case I2 – E1: Get metric data with bad machine Id" << "\n");
  }

  // I2 – E2: Get metric data with bad machine identifier
  // Get metric data : bad metric type

  BOOST_AUTO_TEST_CASE( get_metric_data_bad_metric_type) {

    BOOST_TEST_MESSAGE("Use case I2 – E2: Get metric data with bad metric type");
    VishnuConnexion vc("root","vishnu_user");
    // get the session key and the machine identifier
    string sessionKey=vc.getConnexion();
    string machineId="unknown_name";

    IMS_Data::ListMetric list;
    IMS_Data::MetricHistOp op;
    //Set unknown metric type
    op.setType(15);

    BOOST_CHECK_THROW(getMetricHistory(sessionKey, machineId, list, op), VishnuException);
  }



  // I4 – B: Get data on the infrastructure
  // Get metric data : normal call

  BOOST_AUTO_TEST_CASE(get_metric_current_value) {

    BOOST_TEST_MESSAGE("Use case I4 – B: Get data on the infrastructure");
    VishnuConnexion vc("root","vishnu_user");
    // get the session key and the machine identifier
    string sessionKey=vc.getConnexion();
    string machineId="machine_1";
    IMS_Data::ListMetric list;
    IMS_Data::CurMetricOp op;
    op.setMetricType(3);

    try {
      BOOST_CHECK_EQUAL(getMetricCurrentValue(sessionKey, machineId, list, op),0 );
      BOOST_REQUIRE(list.getMetric().size() != 0);
    }
    catch (VishnuException& e) {
      BOOST_MESSAGE("FAILED\n");
      BOOST_MESSAGE(e.what());
      BOOST_CHECK(false);
    }
  }


  // IA2.1 – B : Get a system load threshold
  // Get a system load threshold : normal call

  BOOST_AUTO_TEST_CASE(get_system_load_threshold) {

    BOOST_TEST_MESSAGE("Use case IA2.1 – B: Get a system load threshold");
    VishnuConnexion vc("root","vishnu_user");

    string sqlPath = IMSSQLPATH;
    // get the session key and the machine identifier
    string sessionKey=vc.getConnexion();
    string machineId="machine_1";

    IMS_Data::ListThreshold list;
    IMS_Data::ThresholdOp op;
    op.setMachineId(machineId);
    //Set FreeDiskSpace Metric
    op.setMetricType(3);

    try {
      BOOST_CHECK_EQUAL(getSystemThreshold(sessionKey, list, op),0 );
      //To check if the list is not empty
      BOOST_REQUIRE(list.getThreshold().size() != 0);
      //To check if the threshold is equal to 2000000
      BOOST_REQUIRE(list.getThreshold().get(0)->getValue() == 2000000);
      //Set the Threshold to 1000000
      if (restore(sqlPath + "/IMSTestThreshold.sql") != 0) {
        BOOST_TEST_MESSAGE("Database update failed for restore(sqlPath + /IMSTestThreshold.sql)");
      }

      list.getThreshold().clear();

      BOOST_CHECK_EQUAL(getSystemThreshold(sessionKey, list, op),0 );
      //To check if the list is not empty
      BOOST_REQUIRE(list.getThreshold().size() != 0);
      //To check if the threshold is equal to 1000000
      BOOST_TEST_MESSAGE("list.getThreshold().get(0)->getValue()" << list.getThreshold().get(0)->getValue());
      BOOST_REQUIRE(list.getThreshold().get(0)->getValue() == 1000000);
    }
    catch (VishnuException& e) {
      BOOST_MESSAGE("FAILED\n");
      BOOST_MESSAGE(e.what());
      BOOST_CHECK(false);
    }
  }

  // IA2.1 – E1 : Get a system load threshold with bad machine Id
  // Get a system load threshold : with bad machine Id

  BOOST_AUTO_TEST_CASE(get_system_load_threshold_bad_machine_Id) {

    BOOST_TEST_MESSAGE("Use case IA2.1 – E1: Get a system load threshold with bad machine Id");
    VishnuConnexion vc("root","vishnu_user");

    string sqlPath = IMSSQLPATH;
    // get the session key and the machine identifier
    string sessionKey=vc.getConnexion();
    string machineId="unknown_name";

    IMS_Data::ListThreshold list;
    IMS_Data::ThresholdOp op;
    op.setMachineId(machineId);

    BOOST_CHECK_THROW(getSystemThreshold(sessionKey, list, op), VishnuException);
  }

  // IA2.1 – E2 : Get a system load threshold with bad metric
  // Get a system load threshold : with bad metric

  BOOST_AUTO_TEST_CASE(get_system_load_threshold_bad_metric) {

    BOOST_TEST_MESSAGE("Use case IA2.1 – E2: Get a system load threshold with bad metric");
    VishnuConnexion vc("root","vishnu_user");

    string sqlPath = IMSSQLPATH;
    // get the session key and the machine identifier
    string sessionKey=vc.getConnexion();
    string machineId="machine_1";

    IMS_Data::ListThreshold list;
    IMS_Data::ThresholdOp op;
    op.setMachineId(machineId);
    op.setMetricType(15);

    BOOST_CHECK_THROW(getSystemThreshold(sessionKey, list, op), VishnuException);
  }

  // IA2.1 – E3 : Get a system load threshold for no admin user
  // Get a system load threshold : for no admin user

  BOOST_AUTO_TEST_CASE(get_system_load_threshold_for_no_admin_user) {

    BOOST_TEST_MESSAGE("Use case IA2.1 – E2: Get a system load threshold with no admin user");
    VishnuConnexion vc("user_1","toto");

    string sqlPath = IMSSQLPATH;
    // get the session key and the machine identifier
    string sessionKey=vc.getConnexion();
    string machineId="machine_1";

    IMS_Data::ListThreshold list;
    IMS_Data::ThresholdOp op;
    op.setMachineId(machineId);

    BOOST_CHECK_THROW(getSystemThreshold(sessionKey, list, op), VishnuException);
  }


  // IA2 – B1 : Define a system load threshold for CPUUSE Metric
  // Define a system load threshold : normal call

  /*BOOST_AUTO_TEST_CASE(define_system_load_threshold_normal_call_metric_CPU_USE) {

    BOOST_TEST_MESSAGE("Use case IA2 – B1: Define a system load threshold for CPUUSE metric");
    VishnuConnexion vc("root","vishnu_user");

    string sqlPath = IMSSQLPATH;
    // get the session key and the machine identifier
    string sessionKey=vc.getConnexion();
    string machineId="machine_1";
    int currentThreshold;

    IMS_Data::ListThreshold list;
    IMS_Data::ThresholdOp op;
    IMS_Data::Threshold systemThreshold;

    op.setMachineId(machineId);
    //Set CPUUSE Metric
    op.setMetricType(1);

    //Set handler
    systemThreshold.setHandler("root");
    systemThreshold.setMachineId(machineId);
    //Set CPUUSE Metric
    systemThreshold.setType(1);

    try {

      //To get the current value of the CPUUSE metric
      BOOST_CHECK_EQUAL(getSystemThreshold(sessionKey, list, op),0 );
      //To check if the list is not empty
      BOOST_REQUIRE(list.getThreshold().size() != 0);
      //To get thr value of the current threshold value
      currentThreshold = list.getThreshold().get(0)->getValue();
      //To clean the list
      list.getThreshold().clear();

      //To change the value of the currentThreshold
      int newThreshold = currentThreshold + 10;
      //To set a new value for the CPUUSE Metric
      systemThreshold.setValue(newThreshold);
      BOOST_CHECK_EQUAL(setSystemThreshold(sessionKey, systemThreshold),0 );

      //To get the current value of the CPUUSE metric
      BOOST_CHECK_EQUAL(getSystemThreshold(sessionKey, list, op),0 );
      //To check if the list is not empty
      BOOST_REQUIRE(list.getThreshold().size() != 0);
      //To check if the new value for the metric is ok
      BOOST_REQUIRE(list.getThreshold().get(0)->getValue() == newThreshold);
    }
    catch (VishnuException& e) {
      BOOST_MESSAGE("FAILED\n");
      BOOST_MESSAGE(e.what());
      BOOST_CHECK(false);
    }
  }

  // IA2 – B2 : Define a system load threshold for FREEDISKSPACE Metric
  // Define a system load threshold : normal call

  BOOST_AUTO_TEST_CASE(define_system_load_threshold_normal_call_metric_FREE_DISK_SPACE) {

    BOOST_TEST_MESSAGE("Use case IA2 – B2: Define a system load threshold for FREE DISK SPACE Metric");
    VishnuConnexion vc("root","vishnu_user");

    string sqlPath = IMSSQLPATH;
    // get the session key and the machine identifier
    string sessionKey=vc.getConnexion();
    string machineId="machine_1";
    int currentThreshold;

    IMS_Data::ListThreshold list;
    IMS_Data::ThresholdOp op;
    IMS_Data::Threshold systemThreshold;

    //Set FREEDISKSPACE Metric
    op.setMetricType(3);
    op.setMachineId(machineId);
    //Set handler
    systemThreshold.setHandler("root");
    systemThreshold.setMachineId(machineId);
    //Set FREEDISKSPACE Metric
    systemThreshold.setType(3);

    try {

      //To get the current value of the FREEDISKSPACE metric
      BOOST_CHECK_EQUAL(getSystemThreshold(sessionKey, list, op),0 );
      //To check if the list is not empty
      BOOST_REQUIRE(list.getThreshold().size() != 0);
      //To get thr value of the current threshold value
      currentThreshold = list.getThreshold().get(0)->getValue();
      //To clean the list
      list.getThreshold().clear();

      //To change the value of the currentThreshold
      int newThreshold = currentThreshold + 1000000;
      //To set a new value for the FREEDISKSPACE Metric
      systemThreshold.setValue(newThreshold);
      BOOST_CHECK_EQUAL(setSystemThreshold(sessionKey, systemThreshold),0 );

      BOOST_CHECK_EQUAL(getSystemThreshold(sessionKey, list, op),0 );
      //To check if the list is not empty
      BOOST_REQUIRE(list.getThreshold().size() != 0);
      //To check if the new value for the metric FREEDISKSPACE is ok
      BOOST_REQUIRE(list.getThreshold().get(0)->getValue() == newThreshold);

    }
    catch (VishnuException& e) {
      BOOST_MESSAGE("FAILED\n");
      BOOST_MESSAGE(e.what());
      BOOST_CHECK(false);
    }
  }

  // IA2 – B3 : Define a system load threshold for FREEMEMORY Metric
  // Define a system load threshold : normal call

  BOOST_AUTO_TEST_CASE(define_system_load_threshold_normal_call_metric_FREE_MEMORY) {

    BOOST_TEST_MESSAGE("Use case IA2 – B3: Define a system load threshold for FREE MEMORY Metric");
    VishnuConnexion vc("root","vishnu_user");

    string sqlPath = IMSSQLPATH;
    // get the session key and the machine identifier
    string sessionKey=vc.getConnexion();
    string machineId="machine_1";
    int currentThreshold;

    IMS_Data::ListThreshold list;
    IMS_Data::ThresholdOp op;
    IMS_Data::Threshold systemThreshold;

    //Set FREEMEMORY Metric
    op.setMetricType(5);
    op.setMachineId(machineId);

    //Set handler
    systemThreshold.setHandler("root");
    systemThreshold.setMachineId(machineId);
    //Set FREEMEMORY Metric
    systemThreshold.setType(5);

    try {

      //To get the current value of the FREEMEMORY metric
      BOOST_CHECK_EQUAL(getSystemThreshold(sessionKey, list, op),0 );
      //To check if the list is not empty
      BOOST_REQUIRE(list.getThreshold().size() != 0);
      //To get thr value of the current threshold value
      currentThreshold = list.getThreshold().get(0)->getValue();
      //To clean the list
      list.getThreshold().clear();

      //To change the value of the currentThreshold
      int newThreshold = currentThreshold + 10;

      //To set a new value for the FREEDISKSPACE Metric
      systemThreshold.setValue(newThreshold);
      BOOST_CHECK_EQUAL(setSystemThreshold(sessionKey, systemThreshold),0 );

      //To check the new value
      BOOST_CHECK_EQUAL(getSystemThreshold(sessionKey, list, op),0 );
      //To check if the list is not empty
      BOOST_REQUIRE(list.getThreshold().size() != 0);
      //To check if the value for the metric is ok
      BOOST_REQUIRE(list.getThreshold().get(0)->getValue() == newThreshold);
    }
    catch (VishnuException& e) {
      BOOST_MESSAGE("FAILED\n");
      BOOST_MESSAGE(e.what());
      BOOST_CHECK(false);
    }
  }

  // IA2 – E1 : Define a system load threshold with bad machine Id
  // Define a system load threshold : bad machine Id

  BOOST_AUTO_TEST_CASE(define_system_load_threshold_bad_machine_Id_call) {

    BOOST_TEST_MESSAGE("Use case IA2 – E1: Define a system load threshold with bad machine Id");
    VishnuConnexion vc("root","vishnu_user");

    // get the session key and the machine identifier
    string sessionKey=vc.getConnexion();
    string machineId="unknown_name";

    IMS_Data::ListThreshold list;
    IMS_Data::Threshold systemThreshold;
    //Set handler
    systemThreshold.setHandler("root");
    systemThreshold.setMachineId(machineId);
    //Set FREEMEMORY Metric
    systemThreshold.setType(5);

    BOOST_CHECK_THROW(setSystemThreshold(sessionKey, systemThreshold), VishnuException);
  }

  // IA2 – E2 : Define a system load threshold with bad machine Id
  // Define a system load threshold : bad machine Id

  BOOST_AUTO_TEST_CASE(define_system_load_threshold_bad_metric_call) {

    BOOST_TEST_MESSAGE("Use case IA2 – E2: Define a system load threshold with bad metric");
    VishnuConnexion vc("root","vishnu_user");

    string sqlPath = IMSSQLPATH;
    // get the session key and the machine identifier
    string sessionKey=vc.getConnexion();
    string machineId="machine_1";

    IMS_Data::ListThreshold list;
    IMS_Data::Threshold systemThreshold;
    //Set handler
    systemThreshold.setHandler("root");
    systemThreshold.setMachineId(machineId);
    //Set unknown metric
    systemThreshold.setType(15);

    BOOST_CHECK_THROW(setSystemThreshold(sessionKey, systemThreshold), VishnuException);
  }

  // IA2 – E3 : Define a system load threshold for no admin user
  // Define a system load threshold : for no admin user

  BOOST_AUTO_TEST_CASE(define_system_load_threshold_no_admin_call) {

    BOOST_TEST_MESSAGE("Use case IA2 – E3: Define a system load threshold for no admin user");
    VishnuConnexion vc("user_1","toto");

    string sqlPath = IMSSQLPATH;
    // get the session key and the machine identifier
    string sessionKey=vc.getConnexion();
    string machineId="machine_1";

    IMS_Data::ListThreshold list;
    IMS_Data::Threshold systemThreshold;
    //Set handler
    systemThreshold.setHandler("root");
    systemThreshold.setMachineId(machineId);
    //Set FREEMEMORY Metric
    systemThreshold.setType(5);

    BOOST_CHECK_THROW(setSystemThreshold(sessionKey, systemThreshold), VishnuException);
  }
  */

  // I1 – B: Get the update frequency normal call
  // Get the update frequency : normal call

  BOOST_AUTO_TEST_CASE( get_update_frequency_normal_call) {

    BOOST_TEST_MESSAGE("Use case I1 – B: Get the update frequency");
    string sqlPath = IMSSQLPATH;
    VishnuConnexion vc("root","vishnu_user");
    // get the session key and the machine identifier
    string sessionKey=vc.getConnexion();
    string machineId="machine_1";
    int frequency;

    try {
      //Set the update frequency to 10 and clean the table state
      if (restore(sqlPath + "/IMSTestGetMetric.sql") != 0) {
        BOOST_TEST_MESSAGE("Database update failed for restore(sqlPath + /IMSTestGetMetric.sql)");
      }
      BOOST_CHECK_EQUAL(getUpdateFrequency(sessionKey, frequency),0 );
      //Check if the frequency is equal to 10
      BOOST_REQUIRE(frequency == 10);
    }
    catch (VishnuException& e) {
      BOOST_MESSAGE("FAILED\n");
      BOOST_MESSAGE(e.what());
      BOOST_CHECK(false);
    }
  }

  // IA6 – B: Set the update frequency normal call
  // Get the update frequency : normal call

  BOOST_AUTO_TEST_CASE( set_update_frequency_normal_call) {

    BOOST_TEST_MESSAGE("Use case IA6 – B: Set the update frequency");
    string sqlPath = IMSSQLPATH;
    VishnuConnexion vc("root","vishnu_user");
    // get the session key and the machine identifier
    string sessionKey=vc.getConnexion();
    string machineId="machine_1";
    int frequency;
    int newFrequence;

    try {
      BOOST_CHECK_EQUAL(getUpdateFrequency(sessionKey, frequency),0 );
      //To check if the frequency is positive
      BOOST_REQUIRE(frequency >= 0);
      //To add 10 to the current frequency value
      newFrequence = frequency + 10;
      //To set the new frequency value
      BOOST_CHECK_EQUAL(setUpdateFrequency(sessionKey, newFrequence),0 );
      //To re-initialize the frequency value
      frequency = 0;
      //To get the frequency value
      BOOST_CHECK_EQUAL(getUpdateFrequency(sessionKey, frequency),0 );
      //Check if the frequency is equal to the value of the new frequency
      BOOST_REQUIRE(frequency == newFrequence);
    }
    catch (VishnuException& e) {
      BOOST_MESSAGE("FAILED\n");
      BOOST_MESSAGE(e.what());
      BOOST_CHECK(false);
    }
  }

  // IA6 – E1: Set the update frequency with frequency value equal to zero
  // Set the update frequency : frequency equal to zero
  BOOST_AUTO_TEST_CASE(set_update_frequency_zero_call) {

    BOOST_TEST_MESSAGE("Use case IA6 – E1: Set the update frequency with frequency equal to zero");
    VishnuConnexion vc("root","vishnu_user");
    // get the session key and the machine identifier
    string sessionKey=vc.getConnexion();
    string machineId="machine_1";
    int frequency = 0;

    BOOST_CHECK_THROW(setUpdateFrequency(sessionKey, frequency), VishnuException);
  }

  // IA6 – E2: Set the update frequency with negative frequency
  // Get the update frequency : negative frequency
  BOOST_AUTO_TEST_CASE(set_update_frequency_negative_call) {

    BOOST_TEST_MESSAGE("Use case IA6 – E2: Set the update frequency with negative value");
   VishnuConnexion vc("root","vishnu_user");
    // get the session key and the machine identifier
    string sessionKey=vc.getConnexion();
    string machineId="machine_1";
    int frequency = -15;

    BOOST_CHECK_THROW(setUpdateFrequency(sessionKey, frequency), VishnuException);
  }

  // IA6 – E3: Set the update frequency for no admin user
  // Get the update frequency : no admin user
  BOOST_AUTO_TEST_CASE(set_update_frequency_no_admin_call) {

    BOOST_TEST_MESSAGE("Use case IA6 – E3: Set the update frequency");
    VishnuConnexion vc("user_1","toto");
    // get the session key and the machine identifier
    string sessionKey=vc.getConnexion();
    string machineId="machine_1";

    BOOST_CHECK_THROW(setUpdateFrequency(sessionKey, 15), VishnuException);
  }

  //IA3-B: Define the identifier normal call
  //Define User/Machine/Job/FileTransfer identifier: normal call
   BOOST_AUTO_TEST_CASE( define_identifier_normal_call) {

    BOOST_TEST_MESSAGE("Use case IA3 – B: Define the identifier");
    string sqlPath = IMSSQLPATH;
    VishnuConnexion vc("root","vishnu_user");
    // get the session key and the machine identifier
    string sessionKey=vc.getConnexion();
    string machineId="machine_1";
    string formatUser = "UTEST_$CPT";
    string formatMachine = "MTEST_$CPT";
    string formatJob = "JTEST_$CPT";
    string formatFileTransfer = "FTTEST_$CPT";

    // CREATE DATA MODEL
    UMS_DataFactory_ptr ecoreUMSFactory = UMS_DataFactory::_instance();

    try {
      //To define the user format
      BOOST_CHECK_EQUAL(defineUserIdentifier(sessionKey, formatUser),0 );
      //To define the machine format
      BOOST_CHECK_EQUAL(defineMachineIdentifier(sessionKey, formatMachine),0 );
      //To define the job format
      BOOST_CHECK_EQUAL(defineJobIdentifier(sessionKey, formatJob),0 );
      //To define the file transfer format
      BOOST_CHECK_EQUAL(defineTransferIdentifier(sessionKey, formatFileTransfer),0 );

      //user
      User_ptr user  = ecoreUMSFactory->createUser();
      user->setFirstname("TestFirstname");
      user->setLastname ("TestLastname");
      user->setPrivilege(0) ;
      user->setEmail    ("Test@test.com");
      BOOST_CHECK_EQUAL(addUser(sessionKey, *user), 0);
      //To check if the userId format is correct
      BOOST_REQUIRE(user->getUserId().compare("UTEST_1") == 0);

      //machine
      Machine_ptr ma  = ecoreUMSFactory->createMachine();
      ma->setName              ("mana");
      ma->setSite              ("site");
      ma->setMachineDescription("desc");
      ma->setLanguage          ("lang");
      ma->setSshPublicKey      ("/id_rsa.pub");

      BOOST_CHECK_EQUAL(addMachine(sessionKey, *ma), 0);
      //To check if the machineId format is correct
      BOOST_REQUIRE(ma->getMachineId().compare("MTEST_1") == 0);

      //Job
      const std::string scriptFilePath= TMSSCRIPTSPATH "/torque_script";
      Job jobInfo;
      SubmitOptions subOptions;

      BOOST_CHECK_EQUAL(submitJob(sessionKey, machineId, scriptFilePath, jobInfo,subOptions),0 );
      //To check if the jobId format is correct
      BOOST_REQUIRE(jobInfo.getJobId().compare("JTEST_1") == 0);

    }
    catch (VishnuException& e) {
      BOOST_MESSAGE("FAILED\n");
      BOOST_MESSAGE(e.what());
      BOOST_CHECK(false);
    }
  }


BOOST_AUTO_TEST_SUITE_END()
// THE END

