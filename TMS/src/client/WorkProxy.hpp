/**
 * \file WorkProxy.hpp
 * \brief This file contains the VISHNU WorkProxy class.
 * \author Coulomb Kevin (kevin.coulomb@sysfera.com)
 * \date June 2012
 */
#ifndef _WORK_PROXY_H_
#define _WORK_PROXY_H_

#include <string>
#include <iostream>

#include "SessionProxy.hpp"
#include "Work.hpp"

/**
 * \class MachineProxy
 * \brief MachineProxy class implementation
 */
class WorkProxy
{

  public:

    /**
     * \param session The object which encapsulates the session information (ex: identifier of the session)
     * \brief Constructor, raises an exception on error
     */
    WorkProxy(const SessionProxy& session);
    /**
     * \brief Function to add a new machine
     * \param work The object which encapsulates the work information
     * \return raises an exception on error
     */
    int add(TMS_Data::Work& work);
    /**
     * \brief Function to update machine description
     * \return raises an exception on error
     */
    int update();
    /**
     * \brief Function to remove a machine
     * \return raises an exception on error
     */
    int deleteWork();
    /**
     * \brief Function get SessionProxy object which contains the VISHNU session identifier
     * \return a SessionProy object which contains the VISHNU session information
     * \return raises an exception on error
     */
    SessionProxy getSessionProxy();
    /**
     * \brief Function get machine information
     * \return Work object encapsulates the information of the machine
     * \return raises an exception on error
     */
    TMS_Data::Work getData();
    /**
     * \brief Destructor, raises an exception on error
     */
    ~WorkProxy();

  private:

    /////////////////////////////////
    // Attributes
    /////////////////////////////////

    /**
     * \brief The object which encapsulates the work
     */
    TMS_Data::Work mwork;
    /**
     * \brief The SessionProxy object containing the encrypted identifier of the session
     *  generated by VISHNU
     */
    SessionProxy msessionProxy;

};
#endif
