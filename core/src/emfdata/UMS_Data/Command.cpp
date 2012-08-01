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

// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * UMS_Data/Command.cpp
 * Copyright (C) Cátedra SAES-UMU 2010 <andres.senac@um.es>
 *
 * EMF4CPP is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EMF4CPP is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Command.hpp"
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "UMS_Data/UMS_DataPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::UMS_Data;

// Default constructor
Command::Command() :
    m_commandId(""), m_sessionId(""), m_machineId(""), m_cmdStartTime(-1),
            m_cmdEndTime(-1), m_status(0)
{

    /*PROTECTED REGION ID(CommandImpl__CommandImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

Command::~Command()
{
}

/*PROTECTED REGION ID(Command.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EString const& Command::getCommandId() const
{
    return m_commandId;
}

void Command::setCommandId(::ecore::EString const& _commandId)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_commandId = m_commandId;
#endif
    m_commandId = _commandId;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::UMS_Data::UMS_DataPackage::_instance()->getCommand__commandId(),
                _old_commandId,
                m_commandId
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Command::getSessionId() const
{
    return m_sessionId;
}

void Command::setSessionId(::ecore::EString const& _sessionId)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_sessionId = m_sessionId;
#endif
    m_sessionId = _sessionId;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::UMS_Data::UMS_DataPackage::_instance()->getCommand__sessionId(),
                _old_sessionId,
                m_sessionId
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Command::getMachineId() const
{
    return m_machineId;
}

void Command::setMachineId(::ecore::EString const& _machineId)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_machineId = m_machineId;
#endif
    m_machineId = _machineId;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::UMS_Data::UMS_DataPackage::_instance()->getCommand__machineId(),
                _old_machineId,
                m_machineId
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Command::getCmdDescription() const
{
    return m_cmdDescription;
}

void Command::setCmdDescription(::ecore::EString const& _cmdDescription)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_cmdDescription = m_cmdDescription;
#endif
    m_cmdDescription = _cmdDescription;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::UMS_Data::UMS_DataPackage::_instance()->getCommand__cmdDescription(),
                _old_cmdDescription,
                m_cmdDescription
        );
        eNotify(&notification);
    }
#endif
}

::ecore::ELong Command::getCmdStartTime() const
{
    return m_cmdStartTime;
}

void Command::setCmdStartTime(::ecore::ELong _cmdStartTime)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::ELong _old_cmdStartTime = m_cmdStartTime;
#endif
    m_cmdStartTime = _cmdStartTime;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::UMS_Data::UMS_DataPackage::_instance()->getCommand__cmdStartTime(),
                _old_cmdStartTime,
                m_cmdStartTime
        );
        eNotify(&notification);
    }
#endif
}

::ecore::ELong Command::getCmdEndTime() const
{
    return m_cmdEndTime;
}

void Command::setCmdEndTime(::ecore::ELong _cmdEndTime)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::ELong _old_cmdEndTime = m_cmdEndTime;
#endif
    m_cmdEndTime = _cmdEndTime;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::UMS_Data::UMS_DataPackage::_instance()->getCommand__cmdEndTime(),
                _old_cmdEndTime,
                m_cmdEndTime
        );
        eNotify(&notification);
    }
#endif
}

::UMS_Data::CommandStatusType Command::getStatus() const
{
    return m_status;
}

void Command::setStatus(::UMS_Data::CommandStatusType _status)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::UMS_Data::CommandStatusType _old_status = m_status;
#endif
    m_status = _status;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::UMS_Data::UMS_DataPackage::_instance()->getCommand__status(),
                _old_status,
                m_status
        );
        eNotify(&notification);
    }
#endif
}

// References

