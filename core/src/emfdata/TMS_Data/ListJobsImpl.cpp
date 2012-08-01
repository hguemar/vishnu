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
 * TMS_Data/ListJobsImpl.cpp
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

#include "ListJobs.hpp"
#include <TMS_Data/TMS_DataPackage.hpp>
#include <TMS_Data/Job.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::TMS_Data;

/*PROTECTED REGION ID(ListJobsImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void ListJobs::_initialize()
{
    // Supertypes

    // Rerefences
    for (size_t i = 0; i < m_jobs->size(); i++)
    {
        (*m_jobs)[i]->_initialize();
        (*m_jobs)[i]->_setEContainer(this,
                ::TMS_Data::TMS_DataPackage::_instance()->getListJobs__jobs());
    }

    /*PROTECTED REGION ID(ListJobsImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject ListJobs::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean _resolve)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::TMS_Data::TMS_DataPackage::LISTJOBS__NBJOBS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::ELong >::toAny(_any, m_nbJobs);
    }
        return _any;
    case ::TMS_Data::TMS_DataPackage::LISTJOBS__NBRUNNINGJOBS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::ELong >::toAny(_any,
                m_nbRunningJobs);
    }
        return _any;
    case ::TMS_Data::TMS_DataPackage::LISTJOBS__NBWAITINGJOBS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::ELong >::toAny(_any,
                m_nbWaitingJobs);
    }
        return _any;
    case ::TMS_Data::TMS_DataPackage::LISTJOBS__JOBS:
    {
        _any = m_jobs->asEListOf< ::ecore::EObject > ();
    }
        return _any;

    }
    throw "Error";
}

void ListJobs::eSet(::ecore::EInt _featureID,
        ::ecore::EJavaObject const& _newValue)
{
    switch (_featureID)
    {
    case ::TMS_Data::TMS_DataPackage::LISTJOBS__NBJOBS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::ELong >::fromAny(_newValue,
                m_nbJobs);
    }
        return;
    case ::TMS_Data::TMS_DataPackage::LISTJOBS__NBRUNNINGJOBS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::ELong >::fromAny(_newValue,
                m_nbRunningJobs);
    }
        return;
    case ::TMS_Data::TMS_DataPackage::LISTJOBS__NBWAITINGJOBS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::ELong >::fromAny(_newValue,
                m_nbWaitingJobs);
    }
        return;
    case ::TMS_Data::TMS_DataPackage::LISTJOBS__JOBS:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::TMS_Data::ListJobs::getJobs().clear();
        ::TMS_Data::ListJobs::getJobs().insert_all(*_t0);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean ListJobs::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::TMS_Data::TMS_DataPackage::LISTJOBS__NBJOBS:
        return m_nbJobs != 0;
    case ::TMS_Data::TMS_DataPackage::LISTJOBS__NBRUNNINGJOBS:
        return m_nbRunningJobs != 0;
    case ::TMS_Data::TMS_DataPackage::LISTJOBS__NBWAITINGJOBS:
        return m_nbWaitingJobs != 0;
    case ::TMS_Data::TMS_DataPackage::LISTJOBS__JOBS:
        return m_jobs && m_jobs->size();

    }
    throw "Error";
}

void ListJobs::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr ListJobs::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::TMS_Data::TMS_DataPackage_ptr > (::TMS_Data::TMS_DataPackage::_instance())->getListJobs();
    return _eclass;
}

