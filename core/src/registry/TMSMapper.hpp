/**
 * \file TMSMapper.hpp
 * \brief Mapper for the TMS module
 * \author Kevin Coulomb (kevin.coulomb@sysfera.com)
 * \date 10/02/11
 */

#ifndef __TMSMAPPER__HH__
#define __TMSMAPPER__HH__

#include <map>

#include "Mapper.hpp"
#include "MapperRegistry.hpp"


using namespace std;

/**
 * \class TMSMapper
 * \brief Mapper implementation for the TMS module
 */
class TMSMapper : Mapper{
public :
  TMSMapper(MapperRegistry* reg, string name);
  TMSMapper();
  /**
   * \brief To register a mapper in the list of active mapper
   * \fn virtual int registerMapper()
   * \return 0 on success, an error code otherwise
   */
  virtual int
  registerMapper();

  /**
   * \brief To unregister a mapper in the list of active mapper
   * \fn virtual int unregisterMapper()
   * \return 0 on success, an error code otherwise
   */
  virtual int 
  unregisterMapper();

  /**
   * \brief To get the command corresponding to a key
   * \fn virtual int getCommand()
   * \return 0 on success, an error code otherwise
   */
  virtual int
  getCommand(const string& key,string& command);

  /**
   * \brief To get the key corresponding to a command
   * \fn virtual int getKey()
   * \return 0 on success, an error code otherwise
   */
  virtual int
  getKey(const string& command, string& key);

protected:
private:
};


#endif
