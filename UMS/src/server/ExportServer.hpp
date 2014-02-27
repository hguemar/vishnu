/**
 * \file ExportServer.hpp
 * \brief This file defines the processes interaction with the database
 * \author Kevin Coulomb (kevin.coulomb@sysfera.com)
 * \date 19/04/11
 */

#ifndef __EXPORTSERVER__HH__
#define __EXPORTSERVER__HH__

#include <string>
#include <ecore.hpp> // Ecore metamodel
#include <ecorecpp.hpp> // EMF4CPP utils
#include "Database.hpp"
#include "UserServer.hpp"


/**
 * \class ExportServer
 * \brief Superclass to export in various formats
 */
class ExportServer{
public:
  /**
   * \brief Constructor
   * \param u: The user server
   */
  ExportServer(UserServer u);
  /**
   * \brief Destructor
   */
  ~ExportServer();
  /**
   * \brief To export the commands made in the oldSession in the file filename with the options op
   * \param oldSession: Session id of the old session to export
   * \param content: The content of the export (OUT)
   * \return Return if the export was a SUCCESS
   */
  virtual int
  exporte(std::string oldSession, std::string &content) = 0;
protected:
  /**
   * \brief To get the name of the mapper for the shell
   */
  virtual std::string
  getMapperName(int type) = 0;
  /**
   * \brief The user
   */
  UserServer muser;
  /**
   *  \brief The datase
   */
  Database* mdatabase;
private:
};


#endif
