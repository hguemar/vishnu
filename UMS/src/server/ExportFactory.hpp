/**
 * \file ExportFactory.hpp
 * \brief This file defines the export factory
 * \author Kevin Coulomb (kevin.coulomb@sysfera.com)
 * \date 23/05/10
 */

#ifndef _EXPORTFACTORY_H_
#define _EXPORTFACTORY_H_

#include "ExportServer.hpp"
#include "UserServer.hpp"
#include <ecore.hpp> // Ecore metamodel
#include <ecorecpp.hpp> // EMF4CPP utils


/**
 * \class ExportFactory
 * \brief Export factory
 */
class ExportFactory{
public:
  /**
   * \brief Constructor
   */
  ExportFactory();
  /**
   * \brief Destructor
   */
  ~ExportFactory();
  /**
   * \brief To get an export server
   */
  static ExportServer*
  getExporter(UserServer u);

protected:
private:

};

#endif
