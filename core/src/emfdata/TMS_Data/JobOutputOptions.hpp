// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * TMS_Data/JobOutputOptions.hpp
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

/**
 * \file JobOutputOptions.hpp
 * \brief The JobOutputOptions class
 * \author Generated file
 * \date 31/03/2011
 */

#ifndef TMS_DATA_JOBOUTPUTOPTIONS_HPP
#define TMS_DATA_JOBOUTPUTOPTIONS_HPP

#include <TMS_Data_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>

#include <ecore/EObject.hpp>

/*PROTECTED REGION ID(JobOutputOptions_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace TMS_Data
{

    /**
     * \class JobOutputOptions
     * \brief Implementation of the JobOutputOptions class
     */
    class JobOutputOptions: public virtual ::ecore::EObject

    {
    public:
        /**
         * \brief The default constructor for JobOutputOptions
         */
        JobOutputOptions();
        /**
         * \brief The destructor for JobOutputOptions
         */
        virtual ~JobOutputOptions();

        /**
         * \brief Internal method
         */
        virtual void _initialize();

        // Operations


        // Attributes
        /**
         * \brief To get the machineId
         * \return The machineId attribute value
         **/
        ::ecore::EString const& getMachineId() const;
        /**
         * \brief To set the machineId
         * \param _machineId The machineId value
         **/
        void setMachineId(::ecore::EString const& _machineId);

        /**
         * \brief To get the outputDir
         * \return The outputDir attribute value
         **/
        ::ecore::EString const& getOutputDir() const;
        /**
         * \brief To set the outputDir
         * \param _outputDir The outputDir value
         **/
        void setOutputDir(::ecore::EString const& _outputDir);

        /**
         * \brief To get the days
         * \return The days attribute value
         **/
        ::ecore::EInt getDays() const;
        /**
         * \brief To set the days
         * \param _days The days value
         **/
        void setDays(::ecore::EInt _days);

        // References


        /*PROTECTED REGION ID(JobOutputOptions) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

        // EObjectImpl
        virtual ::ecore::EJavaObject eGet(::ecore::EInt _featureID,
                ::ecore::EBoolean _resolve);
        virtual void eSet(::ecore::EInt _featureID,
                ::ecore::EJavaObject const& _newValue);
        virtual ::ecore::EBoolean eIsSet(::ecore::EInt _featureID);
        virtual void eUnset(::ecore::EInt _featureID);
        virtual ::ecore::EClass_ptr _eClass();

        /*PROTECTED REGION ID(JobOutputOptionsImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EString m_machineId;

        ::ecore::EString m_outputDir;

        ::ecore::EInt m_days;

        // References

    };

} // TMS_Data

#endif // TMS_DATA_JOBOUTPUTOPTIONS_HPP
