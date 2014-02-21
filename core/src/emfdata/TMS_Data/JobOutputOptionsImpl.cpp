// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * TMS_Data/JobOutputOptionsImpl.cpp
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

#include "JobOutputOptions.hpp"
#include <TMS_Data/TMS_DataPackage.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::TMS_Data;

/*PROTECTED REGION ID(JobOutputOptionsImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void JobOutputOptions::_initialize()
{
    // Supertypes

    // Rerefences

    /*PROTECTED REGION ID(JobOutputOptionsImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject JobOutputOptions::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean _resolve)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::TMS_Data::TMS_DataPackage::JOBOUTPUTOPTIONS__MACHINEID:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any,
                m_machineId);
    }
        return _any;
    case ::TMS_Data::TMS_DataPackage::JOBOUTPUTOPTIONS__OUTPUTDIR:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any,
                m_outputDir);
    }
        return _any;
    case ::TMS_Data::TMS_DataPackage::JOBOUTPUTOPTIONS__DAYS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any, m_days);
    }
        return _any;

    }
    throw "Error";
}

void JobOutputOptions::eSet(::ecore::EInt _featureID,
        ::ecore::EJavaObject const& _newValue)
{
    switch (_featureID)
    {
    case ::TMS_Data::TMS_DataPackage::JOBOUTPUTOPTIONS__MACHINEID:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_machineId);
    }
        return;
    case ::TMS_Data::TMS_DataPackage::JOBOUTPUTOPTIONS__OUTPUTDIR:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_outputDir);
    }
        return;
    case ::TMS_Data::TMS_DataPackage::JOBOUTPUTOPTIONS__DAYS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_days);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean JobOutputOptions::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::TMS_Data::TMS_DataPackage::JOBOUTPUTOPTIONS__MACHINEID:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_machineId);
    case ::TMS_Data::TMS_DataPackage::JOBOUTPUTOPTIONS__OUTPUTDIR:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_outputDir);
    case ::TMS_Data::TMS_DataPackage::JOBOUTPUTOPTIONS__DAYS:
        return m_days != -1;

    }
    throw "Error";
}

void JobOutputOptions::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr JobOutputOptions::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::TMS_Data::TMS_DataPackage_ptr > (::TMS_Data::TMS_DataPackage::_instance())->getJobOutputOptions();
    return _eclass;
}

