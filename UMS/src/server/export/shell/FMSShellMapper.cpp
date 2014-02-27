/**
 * \file FMSMapper.ccp
 * \brief Implementation of the FMS mapper
 * \author Kevin Coulomb (kevin.coulomb@sysfera.com)
 * \date 10/02/11
 */

#include "FMSShellMapper.hpp"

#include <string>

#include "FMS_Data.hpp"
#include "FMS_Data_forward.hpp"
#include "UserServer.hpp"
#include "SessionServer.hpp"
#include "MachineServer.hpp"
#include "LocalAccountServer.hpp"
#include "QueryServer.hpp"
#include "CommandServer.hpp"
#include "utilServer.hpp"

using namespace vishnu;

FMSShellMapper::FMSShellMapper(){
};

FMSShellMapper::~FMSShellMapper(){
};

FMSShellMapper::FMSShellMapper(MapperRegistry* reg, std::string na):FMSMapper(reg, na) {
}
