/**s
* \file CommandServer.hpp
* \brief This file presents the Class which manipulates Commands on server side.
* \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
* \date 31/01/2011
*/

#ifndef COMMAND_SERVER_H
#define COMMAND_SERVER_H

#include <string>
#include <iostream>
#include "SessionServer.hpp"

/**
* \class CommandServer
* \brief CommandServer class implementation
*/
class CommandServer {
public:
  /**
  * \brief Constructor
  * \param session The object which encapsulates session data
  */
  CommandServer(SessionServer session);
  /**
  * \brief Constructor
  * \param cmd The cmd launched by the user
  * \param session The object which encapsulates session data
  */
	CommandServer(std::string cmd, SessionServer session);
  /**
  * \brief Function to get the command description
  * \return the current command
  */
  std::string
  getCommand();
  /**
  * \brief Function to record the command on the database
  * \param cmdType The type of the command (UMS, TMS, FMS)
  * \param cmdStatus The status of the command
  * \param newVishnuObjectID the new vishnu object Id
  * \param startTime The start time of command
  * \param endTime The end time of command
  * \return raises an exception on error
  */
  int
  record(vishnu::CmdType cmdType,
         vishnu::CmdStatus cmdStatus,
         std::string newVishnuObjectID = " ",
         std::string startTime = "CURRENT_TIMESTAMP",
         std::string endTime = "CURRENT_TIMESTAMP");
  /**
  * \brief Function to check if commands are running
  * \return true if commands are running else false
  */
  bool
  isRunning();
  /**
  * \brief Destructor
  */
	~CommandServer();

  private:
  /**
  * \brief An instance of vishnu database
  */
  Database *mdatabaseVishnu;
  /**
  * \brief An object which encapsulates session data
  */
  SessionServer msessionServer;
  /**
  * \brief The command launched by the user
  */
  std::string mcommand;
};
#endif
