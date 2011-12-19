/**
 * \file fms_automTest
 * \brief Contains FMS API test implementation
 * References: VISHNU_D3_1b_FMS-PlanTests
 */
// Prerequisites for this test suite to work correctly:
// 1/ check the cmake parameters TEST_*
// 2/ setup a 'test' unix group on host TEST_FMS_HOST1
//    and add the user TEST_USER_LOGIN to this group
// 3/ check that the /root directory is not accessible for
//    the user that runs the tests (on TEST_FMS_HOST1)

#include "FMS_test_utils.hpp"

// namespaces declaration and  aliases
using namespace std;
using namespace UMS_Data;
using namespace FMS_Data;
using namespace vishnu;
namespace ba = boost::assign;
namespace bpt= boost::posix_time;
namespace bfs= boost::filesystem;

// The database, UMS and FMS SeD are launched by FMSSedFixture.
BOOST_FIXTURE_TEST_SUITE(CreateDir, FMSSeDFixture)

/*****************************************************************************/
/************************  D I R E C T O R I E S *****************************/
/*****************************************************************************/



// All tests of category 1,2,3 for DIRECTORIES only

BOOST_AUTO_TEST_CASE(CreateDir_Base)
{
  BOOST_TEST_MESSAGE("Testing directory creation UC F1.CR2-B");
  VishnuConnection vc(userId, userPwd);
  string sessionKey=vc.getSessionKey();

  try {
    BOOST_REQUIRE( createDir(sessionKey, dirFullPath1) == 0);
    // Check 1: list content of parent directory
    bool isNewDirFound = isFoundInDir(sessionKey, baseDirFullPath1, newDirName);
    BOOST_REQUIRE(isNewDirFound);
    // Check 2: create new file in new directory
    string fileFullPath = dirFullPath1 + slash + newFileName;
    BOOST_REQUIRE( createFile(sessionKey, fileFullPath) == 0 );
    // Cleanup
    BOOST_CHECK( removeFile(sessionKey, fileFullPath) == 0);
    BOOST_CHECK( removeDir(sessionKey, dirFullPath1) == 0);

  } catch (VishnuException& e) {
    BOOST_MESSAGE(e.what());
    BOOST_CHECK(false);
  }
}

BOOST_AUTO_TEST_CASE(CreateDir_Exceptions)
{
  BOOST_TEST_MESSAGE("Testing directory creation errors UC F1.CR2-E");
  VishnuConnection vc(userId, userPwd);
  string sessionKey=vc.getSessionKey();

  try {
    // E1 case
    string invalidDir = "rkvh";
    string invalidFullPath = baseDirFullPath1 + slash + invalidDir + slash + newDirName;
    BOOST_CHECK_THROW( createDir(sessionKey, invalidFullPath), VishnuException);
    // E2 case
    string noAccessLocalPath = "/root/abc";
    string noAccessFullPath = machineId1 + sep + noAccessLocalPath;
    BOOST_CHECK_THROW( createDir(sessionKey, noAccessFullPath), VishnuException);
    // E3 case
    string invalidMachineId = "tt";
    string invalidMachineFullPath = invalidMachineId + sep + remoteBaseDir1;
    BOOST_CHECK_THROW( createDir(sessionKey, invalidMachineFullPath), VishnuException);

  } catch (VishnuException& e) {
    BOOST_MESSAGE(e.what());
    BOOST_CHECK(false);
  }
}


BOOST_AUTO_TEST_SUITE_END()
// THE END
