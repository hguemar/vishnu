// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * TMS_Data/TMS_DataPackageImpl.cpp
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

#include <TMS_Data/TMS_DataPackage.hpp>
#include <TMS_Data/TMS_DataFactory.hpp>
#include <ecore.hpp>
#include <ecore/EcorePackage.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EAttribute.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EOperation.hpp>
#include <ecore/EParameter.hpp>
#include <ecore/EEnum.hpp>
#include <ecore/EEnumLiteral.hpp>
#include <ecore/EDataType.hpp>
#include <ecore/EGenericType.hpp>
#include <ecore/ETypeParameter.hpp>
#include <ecore/EcorePackage.hpp>
#include <ecore/EcorePackage.hpp>

using namespace ::TMS_Data;

TMS_DataPackage::TMS_DataPackage()
{

    s_instance.reset(this);

    // Factory
    ::ecore::EFactory_ptr _fa = TMS_DataFactory::_instance();
    setEFactoryInstance(_fa);
    _fa->setEPackage(this);

    // Create classes and their features

    // Job
    m_JobEClass = new ::ecore::EClass();
    m_JobEClass->setClassifierID(JOB);
    m_JobEClass->setEPackage(this);
    getEClassifiers().push_back(m_JobEClass);
    m_Job__sessionId = new ::ecore::EAttribute();
    m_Job__sessionId->setFeatureID(::TMS_Data::TMS_DataPackage::JOB__SESSIONID);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__sessionId);
    m_Job__submitMachineId = new ::ecore::EAttribute();
    m_Job__submitMachineId->setFeatureID(
            ::TMS_Data::TMS_DataPackage::JOB__SUBMITMACHINEID);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__submitMachineId);
    m_Job__submitMachineName = new ::ecore::EAttribute();
    m_Job__submitMachineName->setFeatureID(
            ::TMS_Data::TMS_DataPackage::JOB__SUBMITMACHINENAME);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__submitMachineName);
    m_Job__jobId = new ::ecore::EAttribute();
    m_Job__jobId->setFeatureID(::TMS_Data::TMS_DataPackage::JOB__JOBID);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__jobId);
    m_Job__jobName = new ::ecore::EAttribute();
    m_Job__jobName->setFeatureID(::TMS_Data::TMS_DataPackage::JOB__JOBNAME);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__jobName);
    m_Job__jobPath = new ::ecore::EAttribute();
    m_Job__jobPath->setFeatureID(::TMS_Data::TMS_DataPackage::JOB__JOBPATH);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__jobPath);
    m_Job__outputPath = new ::ecore::EAttribute();
    m_Job__outputPath->setFeatureID(
            ::TMS_Data::TMS_DataPackage::JOB__OUTPUTPATH);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__outputPath);
    m_Job__errorPath = new ::ecore::EAttribute();
    m_Job__errorPath->setFeatureID(::TMS_Data::TMS_DataPackage::JOB__ERRORPATH);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__errorPath);
    m_Job__jobPrio = new ::ecore::EAttribute();
    m_Job__jobPrio->setFeatureID(::TMS_Data::TMS_DataPackage::JOB__JOBPRIO);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__jobPrio);
    m_Job__nbCpus = new ::ecore::EAttribute();
    m_Job__nbCpus->setFeatureID(::TMS_Data::TMS_DataPackage::JOB__NBCPUS);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__nbCpus);
    m_Job__jobWorkingDir = new ::ecore::EAttribute();
    m_Job__jobWorkingDir->setFeatureID(
            ::TMS_Data::TMS_DataPackage::JOB__JOBWORKINGDIR);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__jobWorkingDir);
    m_Job__status = new ::ecore::EAttribute();
    m_Job__status->setFeatureID(::TMS_Data::TMS_DataPackage::JOB__STATUS);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__status);
    m_Job__submitDate = new ::ecore::EAttribute();
    m_Job__submitDate->setFeatureID(
            ::TMS_Data::TMS_DataPackage::JOB__SUBMITDATE);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__submitDate);
    m_Job__endDate = new ::ecore::EAttribute();
    m_Job__endDate->setFeatureID(::TMS_Data::TMS_DataPackage::JOB__ENDDATE);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__endDate);
    m_Job__owner = new ::ecore::EAttribute();
    m_Job__owner->setFeatureID(::TMS_Data::TMS_DataPackage::JOB__OWNER);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__owner);
    m_Job__jobQueue = new ::ecore::EAttribute();
    m_Job__jobQueue->setFeatureID(::TMS_Data::TMS_DataPackage::JOB__JOBQUEUE);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__jobQueue);
    m_Job__wallClockLimit = new ::ecore::EAttribute();
    m_Job__wallClockLimit->setFeatureID(
            ::TMS_Data::TMS_DataPackage::JOB__WALLCLOCKLIMIT);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__wallClockLimit);
    m_Job__groupName = new ::ecore::EAttribute();
    m_Job__groupName->setFeatureID(::TMS_Data::TMS_DataPackage::JOB__GROUPNAME);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__groupName);
    m_Job__jobDescription = new ::ecore::EAttribute();
    m_Job__jobDescription->setFeatureID(
            ::TMS_Data::TMS_DataPackage::JOB__JOBDESCRIPTION);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__jobDescription);
    m_Job__memLimit = new ::ecore::EAttribute();
    m_Job__memLimit->setFeatureID(::TMS_Data::TMS_DataPackage::JOB__MEMLIMIT);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__memLimit);
    m_Job__nbNodes = new ::ecore::EAttribute();
    m_Job__nbNodes->setFeatureID(::TMS_Data::TMS_DataPackage::JOB__NBNODES);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__nbNodes);
    m_Job__nbNodesAndCpuPerNode = new ::ecore::EAttribute();
    m_Job__nbNodesAndCpuPerNode->setFeatureID(
            ::TMS_Data::TMS_DataPackage::JOB__NBNODESANDCPUPERNODE);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__nbNodesAndCpuPerNode);
    m_Job__batchJobId = new ::ecore::EAttribute();
    m_Job__batchJobId->setFeatureID(
            ::TMS_Data::TMS_DataPackage::JOB__BATCHJOBID);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__batchJobId);
    m_Job__outputDir = new ::ecore::EAttribute();
    m_Job__outputDir->setFeatureID(::TMS_Data::TMS_DataPackage::JOB__OUTPUTDIR);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__outputDir);
    m_Job__workId = new ::ecore::EAttribute();
    m_Job__workId->setFeatureID(::TMS_Data::TMS_DataPackage::JOB__WORKID);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__workId);
    m_Job__userId = new ::ecore::EAttribute();
    m_Job__userId->setFeatureID(::TMS_Data::TMS_DataPackage::JOB__USERID);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__userId);
    m_Job__vmId = new ::ecore::EAttribute();
    m_Job__vmId->setFeatureID(::TMS_Data::TMS_DataPackage::JOB__VMID);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__vmId);
    m_Job__vmIp = new ::ecore::EAttribute();
    m_Job__vmIp->setFeatureID(::TMS_Data::TMS_DataPackage::JOB__VMIP);
    m_JobEClass->getEStructuralFeatures().push_back(m_Job__vmIp);

    // ListJobs
    m_ListJobsEClass = new ::ecore::EClass();
    m_ListJobsEClass->setClassifierID(LISTJOBS);
    m_ListJobsEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListJobsEClass);
    m_ListJobs__nbJobs = new ::ecore::EAttribute();
    m_ListJobs__nbJobs->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTJOBS__NBJOBS);
    m_ListJobsEClass->getEStructuralFeatures().push_back(m_ListJobs__nbJobs);
    m_ListJobs__nbRunningJobs = new ::ecore::EAttribute();
    m_ListJobs__nbRunningJobs->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTJOBS__NBRUNNINGJOBS);
    m_ListJobsEClass->getEStructuralFeatures().push_back(
            m_ListJobs__nbRunningJobs);
    m_ListJobs__nbWaitingJobs = new ::ecore::EAttribute();
    m_ListJobs__nbWaitingJobs->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTJOBS__NBWAITINGJOBS);
    m_ListJobsEClass->getEStructuralFeatures().push_back(
            m_ListJobs__nbWaitingJobs);
    m_ListJobs__jobs = new ::ecore::EReference();
    m_ListJobs__jobs->setFeatureID(::TMS_Data::TMS_DataPackage::LISTJOBS__JOBS);
    m_ListJobsEClass->getEStructuralFeatures().push_back(m_ListJobs__jobs);

    // SubmitOptions
    m_SubmitOptionsEClass = new ::ecore::EClass();
    m_SubmitOptionsEClass->setClassifierID(SUBMITOPTIONS);
    m_SubmitOptionsEClass->setEPackage(this);
    getEClassifiers().push_back(m_SubmitOptionsEClass);
    m_SubmitOptions__name = new ::ecore::EAttribute();
    m_SubmitOptions__name->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__NAME);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__name);
    m_SubmitOptions__queue = new ::ecore::EAttribute();
    m_SubmitOptions__queue->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__QUEUE);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__queue);
    m_SubmitOptions__wallTime = new ::ecore::EAttribute();
    m_SubmitOptions__wallTime->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__WALLTIME);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__wallTime);
    m_SubmitOptions__memory = new ::ecore::EAttribute();
    m_SubmitOptions__memory->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__MEMORY);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__memory);
    m_SubmitOptions__nbCpu = new ::ecore::EAttribute();
    m_SubmitOptions__nbCpu->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__NBCPU);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__nbCpu);
    m_SubmitOptions__nbNodesAndCpuPerNode = new ::ecore::EAttribute();
    m_SubmitOptions__nbNodesAndCpuPerNode->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__NBNODESANDCPUPERNODE);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__nbNodesAndCpuPerNode);
    m_SubmitOptions__outputPath = new ::ecore::EAttribute();
    m_SubmitOptions__outputPath->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__OUTPUTPATH);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__outputPath);
    m_SubmitOptions__errorPath = new ::ecore::EAttribute();
    m_SubmitOptions__errorPath->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__ERRORPATH);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__errorPath);
    m_SubmitOptions__mailNotification = new ::ecore::EAttribute();
    m_SubmitOptions__mailNotification->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__MAILNOTIFICATION);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__mailNotification);
    m_SubmitOptions__mailNotifyUser = new ::ecore::EAttribute();
    m_SubmitOptions__mailNotifyUser->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__MAILNOTIFYUSER);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__mailNotifyUser);
    m_SubmitOptions__group = new ::ecore::EAttribute();
    m_SubmitOptions__group->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__GROUP);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__group);
    m_SubmitOptions__workingDir = new ::ecore::EAttribute();
    m_SubmitOptions__workingDir->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__WORKINGDIR);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__workingDir);
    m_SubmitOptions__cpuTime = new ::ecore::EAttribute();
    m_SubmitOptions__cpuTime->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__CPUTIME);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__cpuTime);
    m_SubmitOptions__selectQueueAutom = new ::ecore::EAttribute();
    m_SubmitOptions__selectQueueAutom->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__SELECTQUEUEAUTOM);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__selectQueueAutom);
    m_SubmitOptions__fileParams = new ::ecore::EAttribute();
    m_SubmitOptions__fileParams->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__FILEPARAMS);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__fileParams);
    m_SubmitOptions__textParams = new ::ecore::EAttribute();
    m_SubmitOptions__textParams->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__TEXTPARAMS);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__textParams);
    m_SubmitOptions__workId = new ::ecore::EAttribute();
    m_SubmitOptions__workId->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__WORKID);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__workId);
    m_SubmitOptions__specificParams = new ::ecore::EAttribute();
    m_SubmitOptions__specificParams->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__SPECIFICPARAMS);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__specificParams);
    m_SubmitOptions__posix = new ::ecore::EAttribute();
    m_SubmitOptions__posix->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__POSIX);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__posix);
    m_SubmitOptions__machine = new ::ecore::EAttribute();
    m_SubmitOptions__machine->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__MACHINE);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__machine);
    m_SubmitOptions__criterion = new ::ecore::EReference();
    m_SubmitOptions__criterion->setFeatureID(
            ::TMS_Data::TMS_DataPackage::SUBMITOPTIONS__CRITERION);
    m_SubmitOptionsEClass->getEStructuralFeatures().push_back(
            m_SubmitOptions__criterion);

    // ListJobsOptions
    m_ListJobsOptionsEClass = new ::ecore::EClass();
    m_ListJobsOptionsEClass->setClassifierID(LISTJOBSOPTIONS);
    m_ListJobsOptionsEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListJobsOptionsEClass);
    m_ListJobsOptions__jobId = new ::ecore::EAttribute();
    m_ListJobsOptions__jobId->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTJOBSOPTIONS__JOBID);
    m_ListJobsOptionsEClass->getEStructuralFeatures().push_back(
            m_ListJobsOptions__jobId);
    m_ListJobsOptions__nbCpu = new ::ecore::EAttribute();
    m_ListJobsOptions__nbCpu->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTJOBSOPTIONS__NBCPU);
    m_ListJobsOptionsEClass->getEStructuralFeatures().push_back(
            m_ListJobsOptions__nbCpu);
    m_ListJobsOptions__fromSubmitDate = new ::ecore::EAttribute();
    m_ListJobsOptions__fromSubmitDate->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTJOBSOPTIONS__FROMSUBMITDATE);
    m_ListJobsOptionsEClass->getEStructuralFeatures().push_back(
            m_ListJobsOptions__fromSubmitDate);
    m_ListJobsOptions__toSubmitDate = new ::ecore::EAttribute();
    m_ListJobsOptions__toSubmitDate->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTJOBSOPTIONS__TOSUBMITDATE);
    m_ListJobsOptionsEClass->getEStructuralFeatures().push_back(
            m_ListJobsOptions__toSubmitDate);
    m_ListJobsOptions__owner = new ::ecore::EAttribute();
    m_ListJobsOptions__owner->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTJOBSOPTIONS__OWNER);
    m_ListJobsOptionsEClass->getEStructuralFeatures().push_back(
            m_ListJobsOptions__owner);
    m_ListJobsOptions__status = new ::ecore::EAttribute();
    m_ListJobsOptions__status->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTJOBSOPTIONS__STATUS);
    m_ListJobsOptionsEClass->getEStructuralFeatures().push_back(
            m_ListJobsOptions__status);
    m_ListJobsOptions__priority = new ::ecore::EAttribute();
    m_ListJobsOptions__priority->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTJOBSOPTIONS__PRIORITY);
    m_ListJobsOptionsEClass->getEStructuralFeatures().push_back(
            m_ListJobsOptions__priority);
    m_ListJobsOptions__queue = new ::ecore::EAttribute();
    m_ListJobsOptions__queue->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTJOBSOPTIONS__QUEUE);
    m_ListJobsOptionsEClass->getEStructuralFeatures().push_back(
            m_ListJobsOptions__queue);
    m_ListJobsOptions__multipleStatus = new ::ecore::EAttribute();
    m_ListJobsOptions__multipleStatus->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTJOBSOPTIONS__MULTIPLESTATUS);
    m_ListJobsOptionsEClass->getEStructuralFeatures().push_back(
            m_ListJobsOptions__multipleStatus);
    m_ListJobsOptions__batchJob = new ::ecore::EAttribute();
    m_ListJobsOptions__batchJob->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTJOBSOPTIONS__BATCHJOB);
    m_ListJobsOptionsEClass->getEStructuralFeatures().push_back(
            m_ListJobsOptions__batchJob);
    m_ListJobsOptions__workId = new ::ecore::EAttribute();
    m_ListJobsOptions__workId->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTJOBSOPTIONS__WORKID);
    m_ListJobsOptionsEClass->getEStructuralFeatures().push_back(
            m_ListJobsOptions__workId);
    m_ListJobsOptions__listAll = new ::ecore::EAttribute();
    m_ListJobsOptions__listAll->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTJOBSOPTIONS__LISTALL);
    m_ListJobsOptionsEClass->getEStructuralFeatures().push_back(
            m_ListJobsOptions__listAll);
    m_ListJobsOptions__machineId = new ::ecore::EAttribute();
    m_ListJobsOptions__machineId->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTJOBSOPTIONS__MACHINEID);
    m_ListJobsOptionsEClass->getEStructuralFeatures().push_back(
            m_ListJobsOptions__machineId);

    // ProgressOptions
    m_ProgressOptionsEClass = new ::ecore::EClass();
    m_ProgressOptionsEClass->setClassifierID(PROGRESSOPTIONS);
    m_ProgressOptionsEClass->setEPackage(this);
    getEClassifiers().push_back(m_ProgressOptionsEClass);
    m_ProgressOptions__jobId = new ::ecore::EAttribute();
    m_ProgressOptions__jobId->setFeatureID(
            ::TMS_Data::TMS_DataPackage::PROGRESSOPTIONS__JOBID);
    m_ProgressOptionsEClass->getEStructuralFeatures().push_back(
            m_ProgressOptions__jobId);
    m_ProgressOptions__user = new ::ecore::EAttribute();
    m_ProgressOptions__user->setFeatureID(
            ::TMS_Data::TMS_DataPackage::PROGRESSOPTIONS__USER);
    m_ProgressOptionsEClass->getEStructuralFeatures().push_back(
            m_ProgressOptions__user);
    m_ProgressOptions__machineId = new ::ecore::EAttribute();
    m_ProgressOptions__machineId->setFeatureID(
            ::TMS_Data::TMS_DataPackage::PROGRESSOPTIONS__MACHINEID);
    m_ProgressOptionsEClass->getEStructuralFeatures().push_back(
            m_ProgressOptions__machineId);

    // ListProgression
    m_ListProgressionEClass = new ::ecore::EClass();
    m_ListProgressionEClass->setClassifierID(LISTPROGRESSION);
    m_ListProgressionEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListProgressionEClass);
    m_ListProgression__nbJobs = new ::ecore::EAttribute();
    m_ListProgression__nbJobs->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTPROGRESSION__NBJOBS);
    m_ListProgressionEClass->getEStructuralFeatures().push_back(
            m_ListProgression__nbJobs);
    m_ListProgression__progress = new ::ecore::EReference();
    m_ListProgression__progress->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTPROGRESSION__PROGRESS);
    m_ListProgressionEClass->getEStructuralFeatures().push_back(
            m_ListProgression__progress);

    // Progression
    m_ProgressionEClass = new ::ecore::EClass();
    m_ProgressionEClass->setClassifierID(PROGRESSION);
    m_ProgressionEClass->setEPackage(this);
    getEClassifiers().push_back(m_ProgressionEClass);
    m_Progression__jobId = new ::ecore::EAttribute();
    m_Progression__jobId->setFeatureID(
            ::TMS_Data::TMS_DataPackage::PROGRESSION__JOBID);
    m_ProgressionEClass->getEStructuralFeatures().push_back(
            m_Progression__jobId);
    m_Progression__jobName = new ::ecore::EAttribute();
    m_Progression__jobName->setFeatureID(
            ::TMS_Data::TMS_DataPackage::PROGRESSION__JOBNAME);
    m_ProgressionEClass->getEStructuralFeatures().push_back(
            m_Progression__jobName);
    m_Progression__wallTime = new ::ecore::EAttribute();
    m_Progression__wallTime->setFeatureID(
            ::TMS_Data::TMS_DataPackage::PROGRESSION__WALLTIME);
    m_ProgressionEClass->getEStructuralFeatures().push_back(
            m_Progression__wallTime);
    m_Progression__startTime = new ::ecore::EAttribute();
    m_Progression__startTime->setFeatureID(
            ::TMS_Data::TMS_DataPackage::PROGRESSION__STARTTIME);
    m_ProgressionEClass->getEStructuralFeatures().push_back(
            m_Progression__startTime);
    m_Progression__endTime = new ::ecore::EAttribute();
    m_Progression__endTime->setFeatureID(
            ::TMS_Data::TMS_DataPackage::PROGRESSION__ENDTIME);
    m_ProgressionEClass->getEStructuralFeatures().push_back(
            m_Progression__endTime);
    m_Progression__percent = new ::ecore::EAttribute();
    m_Progression__percent->setFeatureID(
            ::TMS_Data::TMS_DataPackage::PROGRESSION__PERCENT);
    m_ProgressionEClass->getEStructuralFeatures().push_back(
            m_Progression__percent);
    m_Progression__status = new ::ecore::EAttribute();
    m_Progression__status->setFeatureID(
            ::TMS_Data::TMS_DataPackage::PROGRESSION__STATUS);
    m_ProgressionEClass->getEStructuralFeatures().push_back(
            m_Progression__status);

    // ListQueues
    m_ListQueuesEClass = new ::ecore::EClass();
    m_ListQueuesEClass->setClassifierID(LISTQUEUES);
    m_ListQueuesEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListQueuesEClass);
    m_ListQueues__nbQueues = new ::ecore::EAttribute();
    m_ListQueues__nbQueues->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTQUEUES__NBQUEUES);
    m_ListQueuesEClass->getEStructuralFeatures().push_back(
            m_ListQueues__nbQueues);
    m_ListQueues__queues = new ::ecore::EReference();
    m_ListQueues__queues->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTQUEUES__QUEUES);
    m_ListQueuesEClass->getEStructuralFeatures().push_back(m_ListQueues__queues);

    // Queue
    m_QueueEClass = new ::ecore::EClass();
    m_QueueEClass->setClassifierID(QUEUE);
    m_QueueEClass->setEPackage(this);
    getEClassifiers().push_back(m_QueueEClass);
    m_Queue__name = new ::ecore::EAttribute();
    m_Queue__name->setFeatureID(::TMS_Data::TMS_DataPackage::QUEUE__NAME);
    m_QueueEClass->getEStructuralFeatures().push_back(m_Queue__name);
    m_Queue__maxJobCpu = new ::ecore::EAttribute();
    m_Queue__maxJobCpu->setFeatureID(
            ::TMS_Data::TMS_DataPackage::QUEUE__MAXJOBCPU);
    m_QueueEClass->getEStructuralFeatures().push_back(m_Queue__maxJobCpu);
    m_Queue__maxProcCpu = new ::ecore::EAttribute();
    m_Queue__maxProcCpu->setFeatureID(
            ::TMS_Data::TMS_DataPackage::QUEUE__MAXPROCCPU);
    m_QueueEClass->getEStructuralFeatures().push_back(m_Queue__maxProcCpu);
    m_Queue__memory = new ::ecore::EAttribute();
    m_Queue__memory->setFeatureID(::TMS_Data::TMS_DataPackage::QUEUE__MEMORY);
    m_QueueEClass->getEStructuralFeatures().push_back(m_Queue__memory);
    m_Queue__wallTime = new ::ecore::EAttribute();
    m_Queue__wallTime->setFeatureID(
            ::TMS_Data::TMS_DataPackage::QUEUE__WALLTIME);
    m_QueueEClass->getEStructuralFeatures().push_back(m_Queue__wallTime);
    m_Queue__node = new ::ecore::EAttribute();
    m_Queue__node->setFeatureID(::TMS_Data::TMS_DataPackage::QUEUE__NODE);
    m_QueueEClass->getEStructuralFeatures().push_back(m_Queue__node);
    m_Queue__nbRunningJobs = new ::ecore::EAttribute();
    m_Queue__nbRunningJobs->setFeatureID(
            ::TMS_Data::TMS_DataPackage::QUEUE__NBRUNNINGJOBS);
    m_QueueEClass->getEStructuralFeatures().push_back(m_Queue__nbRunningJobs);
    m_Queue__nbJobsInQueue = new ::ecore::EAttribute();
    m_Queue__nbJobsInQueue->setFeatureID(
            ::TMS_Data::TMS_DataPackage::QUEUE__NBJOBSINQUEUE);
    m_QueueEClass->getEStructuralFeatures().push_back(m_Queue__nbJobsInQueue);
    m_Queue__state = new ::ecore::EAttribute();
    m_Queue__state->setFeatureID(::TMS_Data::TMS_DataPackage::QUEUE__STATE);
    m_QueueEClass->getEStructuralFeatures().push_back(m_Queue__state);
    m_Queue__priority = new ::ecore::EAttribute();
    m_Queue__priority->setFeatureID(
            ::TMS_Data::TMS_DataPackage::QUEUE__PRIORITY);
    m_QueueEClass->getEStructuralFeatures().push_back(m_Queue__priority);
    m_Queue__description = new ::ecore::EAttribute();
    m_Queue__description->setFeatureID(
            ::TMS_Data::TMS_DataPackage::QUEUE__DESCRIPTION);
    m_QueueEClass->getEStructuralFeatures().push_back(m_Queue__description);

    // JobResult
    m_JobResultEClass = new ::ecore::EClass();
    m_JobResultEClass->setClassifierID(JOBRESULT);
    m_JobResultEClass->setEPackage(this);
    getEClassifiers().push_back(m_JobResultEClass);
    m_JobResult__jobId = new ::ecore::EAttribute();
    m_JobResult__jobId->setFeatureID(
            ::TMS_Data::TMS_DataPackage::JOBRESULT__JOBID);
    m_JobResultEClass->getEStructuralFeatures().push_back(m_JobResult__jobId);
    m_JobResult__outputPath = new ::ecore::EAttribute();
    m_JobResult__outputPath->setFeatureID(
            ::TMS_Data::TMS_DataPackage::JOBRESULT__OUTPUTPATH);
    m_JobResultEClass->getEStructuralFeatures().push_back(
            m_JobResult__outputPath);
    m_JobResult__errorPath = new ::ecore::EAttribute();
    m_JobResult__errorPath->setFeatureID(
            ::TMS_Data::TMS_DataPackage::JOBRESULT__ERRORPATH);
    m_JobResultEClass->getEStructuralFeatures().push_back(
            m_JobResult__errorPath);
    m_JobResult__outputDir = new ::ecore::EAttribute();
    m_JobResult__outputDir->setFeatureID(
            ::TMS_Data::TMS_DataPackage::JOBRESULT__OUTPUTDIR);
    m_JobResultEClass->getEStructuralFeatures().push_back(
            m_JobResult__outputDir);

    // ListJobResults
    m_ListJobResultsEClass = new ::ecore::EClass();
    m_ListJobResultsEClass->setClassifierID(LISTJOBRESULTS);
    m_ListJobResultsEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListJobResultsEClass);
    m_ListJobResults__nbJobs = new ::ecore::EAttribute();
    m_ListJobResults__nbJobs->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTJOBRESULTS__NBJOBS);
    m_ListJobResultsEClass->getEStructuralFeatures().push_back(
            m_ListJobResults__nbJobs);
    m_ListJobResults__Results = new ::ecore::EReference();
    m_ListJobResults__Results->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LISTJOBRESULTS__RESULTS);
    m_ListJobResultsEClass->getEStructuralFeatures().push_back(
            m_ListJobResults__Results);

    // LoadCriterion
    m_LoadCriterionEClass = new ::ecore::EClass();
    m_LoadCriterionEClass->setClassifierID(LOADCRITERION);
    m_LoadCriterionEClass->setEPackage(this);
    getEClassifiers().push_back(m_LoadCriterionEClass);
    m_LoadCriterion__loadType = new ::ecore::EAttribute();
    m_LoadCriterion__loadType->setFeatureID(
            ::TMS_Data::TMS_DataPackage::LOADCRITERION__LOADTYPE);
    m_LoadCriterionEClass->getEStructuralFeatures().push_back(
            m_LoadCriterion__loadType);

    // Work
    m_WorkEClass = new ::ecore::EClass();
    m_WorkEClass->setClassifierID(WORK);
    m_WorkEClass->setEPackage(this);
    getEClassifiers().push_back(m_WorkEClass);
    m_Work__sessionId = new ::ecore::EAttribute();
    m_Work__sessionId->setFeatureID(
            ::TMS_Data::TMS_DataPackage::WORK__SESSIONID);
    m_WorkEClass->getEStructuralFeatures().push_back(m_Work__sessionId);
    m_Work__applicationId = new ::ecore::EAttribute();
    m_Work__applicationId->setFeatureID(
            ::TMS_Data::TMS_DataPackage::WORK__APPLICATIONID);
    m_WorkEClass->getEStructuralFeatures().push_back(m_Work__applicationId);
    m_Work__subject = new ::ecore::EAttribute();
    m_Work__subject->setFeatureID(::TMS_Data::TMS_DataPackage::WORK__SUBJECT);
    m_WorkEClass->getEStructuralFeatures().push_back(m_Work__subject);
    m_Work__priority = new ::ecore::EAttribute();
    m_Work__priority->setFeatureID(::TMS_Data::TMS_DataPackage::WORK__PRIORITY);
    m_WorkEClass->getEStructuralFeatures().push_back(m_Work__priority);
    m_Work__status = new ::ecore::EAttribute();
    m_Work__status->setFeatureID(::TMS_Data::TMS_DataPackage::WORK__STATUS);
    m_WorkEClass->getEStructuralFeatures().push_back(m_Work__status);
    m_Work__endDate = new ::ecore::EAttribute();
    m_Work__endDate->setFeatureID(::TMS_Data::TMS_DataPackage::WORK__ENDDATE);
    m_WorkEClass->getEStructuralFeatures().push_back(m_Work__endDate);
    m_Work__owner = new ::ecore::EAttribute();
    m_Work__owner->setFeatureID(::TMS_Data::TMS_DataPackage::WORK__OWNER);
    m_WorkEClass->getEStructuralFeatures().push_back(m_Work__owner);
    m_Work__estimatedHour = new ::ecore::EAttribute();
    m_Work__estimatedHour->setFeatureID(
            ::TMS_Data::TMS_DataPackage::WORK__ESTIMATEDHOUR);
    m_WorkEClass->getEStructuralFeatures().push_back(m_Work__estimatedHour);
    m_Work__doneRatio = new ::ecore::EAttribute();
    m_Work__doneRatio->setFeatureID(
            ::TMS_Data::TMS_DataPackage::WORK__DONERATIO);
    m_WorkEClass->getEStructuralFeatures().push_back(m_Work__doneRatio);
    m_Work__description = new ::ecore::EAttribute();
    m_Work__description->setFeatureID(
            ::TMS_Data::TMS_DataPackage::WORK__DESCRIPTION);
    m_WorkEClass->getEStructuralFeatures().push_back(m_Work__description);
    m_Work__dateCreated = new ::ecore::EAttribute();
    m_Work__dateCreated->setFeatureID(
            ::TMS_Data::TMS_DataPackage::WORK__DATECREATED);
    m_WorkEClass->getEStructuralFeatures().push_back(m_Work__dateCreated);
    m_Work__dateEnded = new ::ecore::EAttribute();
    m_Work__dateEnded->setFeatureID(
            ::TMS_Data::TMS_DataPackage::WORK__DATEENDED);
    m_WorkEClass->getEStructuralFeatures().push_back(m_Work__dateEnded);
    m_Work__dateStarted = new ::ecore::EAttribute();
    m_Work__dateStarted->setFeatureID(
            ::TMS_Data::TMS_DataPackage::WORK__DATESTARTED);
    m_WorkEClass->getEStructuralFeatures().push_back(m_Work__dateStarted);
    m_Work__lastUpdated = new ::ecore::EAttribute();
    m_Work__lastUpdated->setFeatureID(
            ::TMS_Data::TMS_DataPackage::WORK__LASTUPDATED);
    m_WorkEClass->getEStructuralFeatures().push_back(m_Work__lastUpdated);
    m_Work__workId = new ::ecore::EAttribute();
    m_Work__workId->setFeatureID(::TMS_Data::TMS_DataPackage::WORK__WORKID);
    m_WorkEClass->getEStructuralFeatures().push_back(m_Work__workId);
    m_Work__projectId = new ::ecore::EAttribute();
    m_Work__projectId->setFeatureID(
            ::TMS_Data::TMS_DataPackage::WORK__PROJECTID);
    m_WorkEClass->getEStructuralFeatures().push_back(m_Work__projectId);
    m_Work__submitDate = new ::ecore::EAttribute();
    m_Work__submitDate->setFeatureID(
            ::TMS_Data::TMS_DataPackage::WORK__SUBMITDATE);
    m_WorkEClass->getEStructuralFeatures().push_back(m_Work__submitDate);
    m_Work__machineId = new ::ecore::EAttribute();
    m_Work__machineId->setFeatureID(
            ::TMS_Data::TMS_DataPackage::WORK__MACHINEID);
    m_WorkEClass->getEStructuralFeatures().push_back(m_Work__machineId);
    m_Work__nbCPU = new ::ecore::EAttribute();
    m_Work__nbCPU->setFeatureID(::TMS_Data::TMS_DataPackage::WORK__NBCPU);
    m_WorkEClass->getEStructuralFeatures().push_back(m_Work__nbCPU);
    m_Work__dueDate = new ::ecore::EAttribute();
    m_Work__dueDate->setFeatureID(::TMS_Data::TMS_DataPackage::WORK__DUEDATE);
    m_WorkEClass->getEStructuralFeatures().push_back(m_Work__dueDate);

    // AddWorkOptions
    m_AddWorkOptionsEClass = new ::ecore::EClass();
    m_AddWorkOptionsEClass->setClassifierID(ADDWORKOPTIONS);
    m_AddWorkOptionsEClass->setEPackage(this);
    getEClassifiers().push_back(m_AddWorkOptionsEClass);
    m_AddWorkOptions__applicationId = new ::ecore::EAttribute();
    m_AddWorkOptions__applicationId->setFeatureID(
            ::TMS_Data::TMS_DataPackage::ADDWORKOPTIONS__APPLICATIONID);
    m_AddWorkOptionsEClass->getEStructuralFeatures().push_back(
            m_AddWorkOptions__applicationId);
    m_AddWorkOptions__subject = new ::ecore::EAttribute();
    m_AddWorkOptions__subject->setFeatureID(
            ::TMS_Data::TMS_DataPackage::ADDWORKOPTIONS__SUBJECT);
    m_AddWorkOptionsEClass->getEStructuralFeatures().push_back(
            m_AddWorkOptions__subject);
    m_AddWorkOptions__priority = new ::ecore::EAttribute();
    m_AddWorkOptions__priority->setFeatureID(
            ::TMS_Data::TMS_DataPackage::ADDWORKOPTIONS__PRIORITY);
    m_AddWorkOptionsEClass->getEStructuralFeatures().push_back(
            m_AddWorkOptions__priority);
    m_AddWorkOptions__owner = new ::ecore::EAttribute();
    m_AddWorkOptions__owner->setFeatureID(
            ::TMS_Data::TMS_DataPackage::ADDWORKOPTIONS__OWNER);
    m_AddWorkOptionsEClass->getEStructuralFeatures().push_back(
            m_AddWorkOptions__owner);
    m_AddWorkOptions__estimatedHour = new ::ecore::EAttribute();
    m_AddWorkOptions__estimatedHour->setFeatureID(
            ::TMS_Data::TMS_DataPackage::ADDWORKOPTIONS__ESTIMATEDHOUR);
    m_AddWorkOptionsEClass->getEStructuralFeatures().push_back(
            m_AddWorkOptions__estimatedHour);
    m_AddWorkOptions__description = new ::ecore::EAttribute();
    m_AddWorkOptions__description->setFeatureID(
            ::TMS_Data::TMS_DataPackage::ADDWORKOPTIONS__DESCRIPTION);
    m_AddWorkOptionsEClass->getEStructuralFeatures().push_back(
            m_AddWorkOptions__description);
    m_AddWorkOptions__projectId = new ::ecore::EAttribute();
    m_AddWorkOptions__projectId->setFeatureID(
            ::TMS_Data::TMS_DataPackage::ADDWORKOPTIONS__PROJECTID);
    m_AddWorkOptionsEClass->getEStructuralFeatures().push_back(
            m_AddWorkOptions__projectId);
    m_AddWorkOptions__machineId = new ::ecore::EAttribute();
    m_AddWorkOptions__machineId->setFeatureID(
            ::TMS_Data::TMS_DataPackage::ADDWORKOPTIONS__MACHINEID);
    m_AddWorkOptionsEClass->getEStructuralFeatures().push_back(
            m_AddWorkOptions__machineId);
    m_AddWorkOptions__nbCPU = new ::ecore::EAttribute();
    m_AddWorkOptions__nbCPU->setFeatureID(
            ::TMS_Data::TMS_DataPackage::ADDWORKOPTIONS__NBCPU);
    m_AddWorkOptionsEClass->getEStructuralFeatures().push_back(
            m_AddWorkOptions__nbCPU);

    // CancelOptions
    m_CancelOptionsEClass = new ::ecore::EClass();
    m_CancelOptionsEClass->setClassifierID(CANCELOPTIONS);
    m_CancelOptionsEClass->setEPackage(this);
    getEClassifiers().push_back(m_CancelOptionsEClass);
    m_CancelOptions__machineId = new ::ecore::EAttribute();
    m_CancelOptions__machineId->setFeatureID(
            ::TMS_Data::TMS_DataPackage::CANCELOPTIONS__MACHINEID);
    m_CancelOptionsEClass->getEStructuralFeatures().push_back(
            m_CancelOptions__machineId);
    m_CancelOptions__user = new ::ecore::EAttribute();
    m_CancelOptions__user->setFeatureID(
            ::TMS_Data::TMS_DataPackage::CANCELOPTIONS__USER);
    m_CancelOptionsEClass->getEStructuralFeatures().push_back(
            m_CancelOptions__user);
    m_CancelOptions__jobId = new ::ecore::EAttribute();
    m_CancelOptions__jobId->setFeatureID(
            ::TMS_Data::TMS_DataPackage::CANCELOPTIONS__JOBID);
    m_CancelOptionsEClass->getEStructuralFeatures().push_back(
            m_CancelOptions__jobId);

    // JobOutputOptions
    m_JobOutputOptionsEClass = new ::ecore::EClass();
    m_JobOutputOptionsEClass->setClassifierID(JOBOUTPUTOPTIONS);
    m_JobOutputOptionsEClass->setEPackage(this);
    getEClassifiers().push_back(m_JobOutputOptionsEClass);
    m_JobOutputOptions__machineId = new ::ecore::EAttribute();
    m_JobOutputOptions__machineId->setFeatureID(
            ::TMS_Data::TMS_DataPackage::JOBOUTPUTOPTIONS__MACHINEID);
    m_JobOutputOptionsEClass->getEStructuralFeatures().push_back(
            m_JobOutputOptions__machineId);
    m_JobOutputOptions__outputDir = new ::ecore::EAttribute();
    m_JobOutputOptions__outputDir->setFeatureID(
            ::TMS_Data::TMS_DataPackage::JOBOUTPUTOPTIONS__OUTPUTDIR);
    m_JobOutputOptionsEClass->getEStructuralFeatures().push_back(
            m_JobOutputOptions__outputDir);
    m_JobOutputOptions__days = new ::ecore::EAttribute();
    m_JobOutputOptions__days->setFeatureID(
            ::TMS_Data::TMS_DataPackage::JOBOUTPUTOPTIONS__DAYS);
    m_JobOutputOptionsEClass->getEStructuralFeatures().push_back(
            m_JobOutputOptions__days);

    // Create enums

    m_JobPriorityEEnum = new ::ecore::EEnum();
    m_JobPriorityEEnum->setClassifierID(JOBPRIORITY);
    m_JobPriorityEEnum->setEPackage(this);
    getEClassifiers().push_back(m_JobPriorityEEnum);

    m_JobStatusEEnum = new ::ecore::EEnum();
    m_JobStatusEEnum->setClassifierID(JOBSTATUS);
    m_JobStatusEEnum->setEPackage(this);
    getEClassifiers().push_back(m_JobStatusEEnum);

    m_QueuePriorityEEnum = new ::ecore::EEnum();
    m_QueuePriorityEEnum->setClassifierID(QUEUEPRIORITY);
    m_QueuePriorityEEnum->setEPackage(this);
    getEClassifiers().push_back(m_QueuePriorityEEnum);

    m_QueueStatusEEnum = new ::ecore::EEnum();
    m_QueueStatusEEnum->setClassifierID(QUEUESTATUS);
    m_QueueStatusEEnum->setEPackage(this);
    getEClassifiers().push_back(m_QueueStatusEEnum);

    m_LoadTypeEEnum = new ::ecore::EEnum();
    m_LoadTypeEEnum->setClassifierID(LOADTYPE);
    m_LoadTypeEEnum->setEPackage(this);
    getEClassifiers().push_back(m_LoadTypeEEnum);

    // Create data types


    // Initialize package
    setName("TMS_Data");
    setNsPrefix("tms_data");
    setNsURI("http://www.sysfera.com/emf/tms/data");

    // TODO: bounds for type parameters

    // Add supertypes to classes

    // TODO: Initialize classes and features; add operations and parameters
    // TODO: GenericTypes
    // Job
    m_JobEClass->setName("Job");
    m_JobEClass->setAbstract(false);
    m_JobEClass->setInterface(false);
    m_Job__sessionId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Job__sessionId->setName("sessionId");
    m_Job__sessionId->setDefaultValueLiteral("");
    m_Job__sessionId->setLowerBound(0);
    m_Job__sessionId->setUpperBound(1);
    m_Job__sessionId->setTransient(false);
    m_Job__sessionId->setVolatile(false);
    m_Job__sessionId->setChangeable(true);
    m_Job__sessionId->setUnsettable(false);
    m_Job__sessionId->setID(false);
    m_Job__sessionId->setUnique(true);
    m_Job__sessionId->setDerived(false);
    m_Job__sessionId->setOrdered(true);
    m_Job__submitMachineId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Job__submitMachineId->setName("submitMachineId");
    m_Job__submitMachineId->setDefaultValueLiteral("");
    m_Job__submitMachineId->setLowerBound(0);
    m_Job__submitMachineId->setUpperBound(1);
    m_Job__submitMachineId->setTransient(false);
    m_Job__submitMachineId->setVolatile(false);
    m_Job__submitMachineId->setChangeable(true);
    m_Job__submitMachineId->setUnsettable(false);
    m_Job__submitMachineId->setID(false);
    m_Job__submitMachineId->setUnique(true);
    m_Job__submitMachineId->setDerived(false);
    m_Job__submitMachineId->setOrdered(true);
    m_Job__submitMachineName->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Job__submitMachineName->setName("submitMachineName");
    m_Job__submitMachineName->setDefaultValueLiteral("");
    m_Job__submitMachineName->setLowerBound(0);
    m_Job__submitMachineName->setUpperBound(1);
    m_Job__submitMachineName->setTransient(false);
    m_Job__submitMachineName->setVolatile(false);
    m_Job__submitMachineName->setChangeable(true);
    m_Job__submitMachineName->setUnsettable(false);
    m_Job__submitMachineName->setID(false);
    m_Job__submitMachineName->setUnique(true);
    m_Job__submitMachineName->setDerived(false);
    m_Job__submitMachineName->setOrdered(true);
    m_Job__jobId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Job__jobId->setName("jobId");
    m_Job__jobId->setDefaultValueLiteral("");
    m_Job__jobId->setLowerBound(0);
    m_Job__jobId->setUpperBound(1);
    m_Job__jobId->setTransient(false);
    m_Job__jobId->setVolatile(false);
    m_Job__jobId->setChangeable(true);
    m_Job__jobId->setUnsettable(false);
    m_Job__jobId->setID(false);
    m_Job__jobId->setUnique(true);
    m_Job__jobId->setDerived(false);
    m_Job__jobId->setOrdered(true);
    m_Job__jobName->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Job__jobName->setName("jobName");
    m_Job__jobName->setDefaultValueLiteral("");
    m_Job__jobName->setLowerBound(0);
    m_Job__jobName->setUpperBound(1);
    m_Job__jobName->setTransient(false);
    m_Job__jobName->setVolatile(false);
    m_Job__jobName->setChangeable(true);
    m_Job__jobName->setUnsettable(false);
    m_Job__jobName->setID(false);
    m_Job__jobName->setUnique(true);
    m_Job__jobName->setDerived(false);
    m_Job__jobName->setOrdered(true);
    m_Job__jobPath->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Job__jobPath->setName("jobPath");
    m_Job__jobPath->setDefaultValueLiteral("");
    m_Job__jobPath->setLowerBound(0);
    m_Job__jobPath->setUpperBound(1);
    m_Job__jobPath->setTransient(false);
    m_Job__jobPath->setVolatile(false);
    m_Job__jobPath->setChangeable(true);
    m_Job__jobPath->setUnsettable(false);
    m_Job__jobPath->setID(false);
    m_Job__jobPath->setUnique(true);
    m_Job__jobPath->setDerived(false);
    m_Job__jobPath->setOrdered(true);
    m_Job__outputPath->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Job__outputPath->setName("outputPath");
    m_Job__outputPath->setDefaultValueLiteral("");
    m_Job__outputPath->setLowerBound(0);
    m_Job__outputPath->setUpperBound(1);
    m_Job__outputPath->setTransient(false);
    m_Job__outputPath->setVolatile(false);
    m_Job__outputPath->setChangeable(true);
    m_Job__outputPath->setUnsettable(false);
    m_Job__outputPath->setID(false);
    m_Job__outputPath->setUnique(true);
    m_Job__outputPath->setDerived(false);
    m_Job__outputPath->setOrdered(true);
    m_Job__errorPath->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Job__errorPath->setName("errorPath");
    m_Job__errorPath->setDefaultValueLiteral("");
    m_Job__errorPath->setLowerBound(0);
    m_Job__errorPath->setUpperBound(1);
    m_Job__errorPath->setTransient(false);
    m_Job__errorPath->setVolatile(false);
    m_Job__errorPath->setChangeable(true);
    m_Job__errorPath->setUnsettable(false);
    m_Job__errorPath->setID(false);
    m_Job__errorPath->setUnique(true);
    m_Job__errorPath->setDerived(false);
    m_Job__errorPath->setOrdered(true);
    m_Job__jobPrio->setEType(m_JobPriorityEEnum);
    m_Job__jobPrio->setName("jobPrio");
    m_Job__jobPrio->setDefaultValueLiteral("-1");
    m_Job__jobPrio->setLowerBound(0);
    m_Job__jobPrio->setUpperBound(1);
    m_Job__jobPrio->setTransient(false);
    m_Job__jobPrio->setVolatile(false);
    m_Job__jobPrio->setChangeable(true);
    m_Job__jobPrio->setUnsettable(false);
    m_Job__jobPrio->setID(false);
    m_Job__jobPrio->setUnique(true);
    m_Job__jobPrio->setDerived(false);
    m_Job__jobPrio->setOrdered(true);
    m_Job__nbCpus->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Job__nbCpus->setName("nbCpus");
    m_Job__nbCpus->setDefaultValueLiteral("-1");
    m_Job__nbCpus->setLowerBound(0);
    m_Job__nbCpus->setUpperBound(1);
    m_Job__nbCpus->setTransient(false);
    m_Job__nbCpus->setVolatile(false);
    m_Job__nbCpus->setChangeable(true);
    m_Job__nbCpus->setUnsettable(false);
    m_Job__nbCpus->setID(false);
    m_Job__nbCpus->setUnique(true);
    m_Job__nbCpus->setDerived(false);
    m_Job__nbCpus->setOrdered(true);
    m_Job__jobWorkingDir->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Job__jobWorkingDir->setName("jobWorkingDir");
    m_Job__jobWorkingDir->setDefaultValueLiteral("");
    m_Job__jobWorkingDir->setLowerBound(0);
    m_Job__jobWorkingDir->setUpperBound(1);
    m_Job__jobWorkingDir->setTransient(false);
    m_Job__jobWorkingDir->setVolatile(false);
    m_Job__jobWorkingDir->setChangeable(true);
    m_Job__jobWorkingDir->setUnsettable(false);
    m_Job__jobWorkingDir->setID(false);
    m_Job__jobWorkingDir->setUnique(true);
    m_Job__jobWorkingDir->setDerived(false);
    m_Job__jobWorkingDir->setOrdered(true);
    m_Job__status->setEType(m_JobStatusEEnum);
    m_Job__status->setName("status");
    m_Job__status->setDefaultValueLiteral("-1");
    m_Job__status->setLowerBound(0);
    m_Job__status->setUpperBound(1);
    m_Job__status->setTransient(false);
    m_Job__status->setVolatile(false);
    m_Job__status->setChangeable(true);
    m_Job__status->setUnsettable(false);
    m_Job__status->setID(false);
    m_Job__status->setUnique(true);
    m_Job__status->setDerived(false);
    m_Job__status->setOrdered(true);
    m_Job__submitDate->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Job__submitDate->setName("submitDate");
    m_Job__submitDate->setDefaultValueLiteral("-1");
    m_Job__submitDate->setLowerBound(0);
    m_Job__submitDate->setUpperBound(1);
    m_Job__submitDate->setTransient(false);
    m_Job__submitDate->setVolatile(false);
    m_Job__submitDate->setChangeable(true);
    m_Job__submitDate->setUnsettable(false);
    m_Job__submitDate->setID(false);
    m_Job__submitDate->setUnique(true);
    m_Job__submitDate->setDerived(false);
    m_Job__submitDate->setOrdered(true);
    m_Job__endDate->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Job__endDate->setName("endDate");
    m_Job__endDate->setDefaultValueLiteral("-1");
    m_Job__endDate->setLowerBound(0);
    m_Job__endDate->setUpperBound(1);
    m_Job__endDate->setTransient(false);
    m_Job__endDate->setVolatile(false);
    m_Job__endDate->setChangeable(true);
    m_Job__endDate->setUnsettable(false);
    m_Job__endDate->setID(false);
    m_Job__endDate->setUnique(true);
    m_Job__endDate->setDerived(false);
    m_Job__endDate->setOrdered(true);
    m_Job__owner->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Job__owner->setName("owner");
    m_Job__owner->setDefaultValueLiteral("");
    m_Job__owner->setLowerBound(0);
    m_Job__owner->setUpperBound(1);
    m_Job__owner->setTransient(false);
    m_Job__owner->setVolatile(false);
    m_Job__owner->setChangeable(true);
    m_Job__owner->setUnsettable(false);
    m_Job__owner->setID(false);
    m_Job__owner->setUnique(true);
    m_Job__owner->setDerived(false);
    m_Job__owner->setOrdered(true);
    m_Job__jobQueue->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Job__jobQueue->setName("jobQueue");
    m_Job__jobQueue->setDefaultValueLiteral("");
    m_Job__jobQueue->setLowerBound(0);
    m_Job__jobQueue->setUpperBound(1);
    m_Job__jobQueue->setTransient(false);
    m_Job__jobQueue->setVolatile(false);
    m_Job__jobQueue->setChangeable(true);
    m_Job__jobQueue->setUnsettable(false);
    m_Job__jobQueue->setID(false);
    m_Job__jobQueue->setUnique(true);
    m_Job__jobQueue->setDerived(false);
    m_Job__jobQueue->setOrdered(true);
    m_Job__wallClockLimit->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Job__wallClockLimit->setName("wallClockLimit");
    m_Job__wallClockLimit->setDefaultValueLiteral("-1");
    m_Job__wallClockLimit->setLowerBound(0);
    m_Job__wallClockLimit->setUpperBound(1);
    m_Job__wallClockLimit->setTransient(false);
    m_Job__wallClockLimit->setVolatile(false);
    m_Job__wallClockLimit->setChangeable(true);
    m_Job__wallClockLimit->setUnsettable(false);
    m_Job__wallClockLimit->setID(false);
    m_Job__wallClockLimit->setUnique(true);
    m_Job__wallClockLimit->setDerived(false);
    m_Job__wallClockLimit->setOrdered(true);
    m_Job__groupName->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Job__groupName->setName("groupName");
    m_Job__groupName->setDefaultValueLiteral("");
    m_Job__groupName->setLowerBound(0);
    m_Job__groupName->setUpperBound(1);
    m_Job__groupName->setTransient(false);
    m_Job__groupName->setVolatile(false);
    m_Job__groupName->setChangeable(true);
    m_Job__groupName->setUnsettable(false);
    m_Job__groupName->setID(false);
    m_Job__groupName->setUnique(true);
    m_Job__groupName->setDerived(false);
    m_Job__groupName->setOrdered(true);
    m_Job__jobDescription->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Job__jobDescription->setName("jobDescription");
    m_Job__jobDescription->setDefaultValueLiteral("");
    m_Job__jobDescription->setLowerBound(0);
    m_Job__jobDescription->setUpperBound(1);
    m_Job__jobDescription->setTransient(false);
    m_Job__jobDescription->setVolatile(false);
    m_Job__jobDescription->setChangeable(true);
    m_Job__jobDescription->setUnsettable(false);
    m_Job__jobDescription->setID(false);
    m_Job__jobDescription->setUnique(true);
    m_Job__jobDescription->setDerived(false);
    m_Job__jobDescription->setOrdered(true);
    m_Job__memLimit->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Job__memLimit->setName("memLimit");
    m_Job__memLimit->setDefaultValueLiteral("-1");
    m_Job__memLimit->setLowerBound(0);
    m_Job__memLimit->setUpperBound(1);
    m_Job__memLimit->setTransient(false);
    m_Job__memLimit->setVolatile(false);
    m_Job__memLimit->setChangeable(true);
    m_Job__memLimit->setUnsettable(false);
    m_Job__memLimit->setID(false);
    m_Job__memLimit->setUnique(true);
    m_Job__memLimit->setDerived(false);
    m_Job__memLimit->setOrdered(true);
    m_Job__nbNodes->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Job__nbNodes->setName("nbNodes");
    m_Job__nbNodes->setDefaultValueLiteral("-1");
    m_Job__nbNodes->setLowerBound(0);
    m_Job__nbNodes->setUpperBound(1);
    m_Job__nbNodes->setTransient(false);
    m_Job__nbNodes->setVolatile(false);
    m_Job__nbNodes->setChangeable(true);
    m_Job__nbNodes->setUnsettable(false);
    m_Job__nbNodes->setID(false);
    m_Job__nbNodes->setUnique(true);
    m_Job__nbNodes->setDerived(false);
    m_Job__nbNodes->setOrdered(true);
    m_Job__nbNodesAndCpuPerNode->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Job__nbNodesAndCpuPerNode->setName("nbNodesAndCpuPerNode");
    m_Job__nbNodesAndCpuPerNode->setDefaultValueLiteral("");
    m_Job__nbNodesAndCpuPerNode->setLowerBound(0);
    m_Job__nbNodesAndCpuPerNode->setUpperBound(1);
    m_Job__nbNodesAndCpuPerNode->setTransient(false);
    m_Job__nbNodesAndCpuPerNode->setVolatile(false);
    m_Job__nbNodesAndCpuPerNode->setChangeable(true);
    m_Job__nbNodesAndCpuPerNode->setUnsettable(false);
    m_Job__nbNodesAndCpuPerNode->setID(false);
    m_Job__nbNodesAndCpuPerNode->setUnique(true);
    m_Job__nbNodesAndCpuPerNode->setDerived(false);
    m_Job__nbNodesAndCpuPerNode->setOrdered(true);
    m_Job__batchJobId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Job__batchJobId->setName("batchJobId");
    m_Job__batchJobId->setDefaultValueLiteral("" "");
    m_Job__batchJobId->setLowerBound(0);
    m_Job__batchJobId->setUpperBound(1);
    m_Job__batchJobId->setTransient(false);
    m_Job__batchJobId->setVolatile(false);
    m_Job__batchJobId->setChangeable(true);
    m_Job__batchJobId->setUnsettable(false);
    m_Job__batchJobId->setID(false);
    m_Job__batchJobId->setUnique(true);
    m_Job__batchJobId->setDerived(false);
    m_Job__batchJobId->setOrdered(true);
    m_Job__outputDir->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Job__outputDir->setName("outputDir");
    m_Job__outputDir->setDefaultValueLiteral("");
    m_Job__outputDir->setLowerBound(0);
    m_Job__outputDir->setUpperBound(1);
    m_Job__outputDir->setTransient(false);
    m_Job__outputDir->setVolatile(false);
    m_Job__outputDir->setChangeable(true);
    m_Job__outputDir->setUnsettable(false);
    m_Job__outputDir->setID(false);
    m_Job__outputDir->setUnique(true);
    m_Job__outputDir->setDerived(false);
    m_Job__outputDir->setOrdered(true);
    m_Job__workId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Job__workId->setName("workId");
    m_Job__workId->setDefaultValueLiteral("0");
    m_Job__workId->setLowerBound(0);
    m_Job__workId->setUpperBound(1);
    m_Job__workId->setTransient(false);
    m_Job__workId->setVolatile(false);
    m_Job__workId->setChangeable(true);
    m_Job__workId->setUnsettable(false);
    m_Job__workId->setID(false);
    m_Job__workId->setUnique(true);
    m_Job__workId->setDerived(false);
    m_Job__workId->setOrdered(true);
    m_Job__userId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Job__userId->setName("userId");
    m_Job__userId->setDefaultValueLiteral("" "");
    m_Job__userId->setLowerBound(0);
    m_Job__userId->setUpperBound(1);
    m_Job__userId->setTransient(false);
    m_Job__userId->setVolatile(false);
    m_Job__userId->setChangeable(true);
    m_Job__userId->setUnsettable(false);
    m_Job__userId->setID(false);
    m_Job__userId->setUnique(true);
    m_Job__userId->setDerived(false);
    m_Job__userId->setOrdered(true);
    m_Job__vmId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Job__vmId->setName("vmId");
    m_Job__vmId->setDefaultValueLiteral("" "");
    m_Job__vmId->setLowerBound(0);
    m_Job__vmId->setUpperBound(1);
    m_Job__vmId->setTransient(false);
    m_Job__vmId->setVolatile(false);
    m_Job__vmId->setChangeable(true);
    m_Job__vmId->setUnsettable(false);
    m_Job__vmId->setID(false);
    m_Job__vmId->setUnique(true);
    m_Job__vmId->setDerived(false);
    m_Job__vmId->setOrdered(true);
    m_Job__vmIp->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Job__vmIp->setName("vmIp");
    m_Job__vmIp->setDefaultValueLiteral("" "");
    m_Job__vmIp->setLowerBound(0);
    m_Job__vmIp->setUpperBound(1);
    m_Job__vmIp->setTransient(false);
    m_Job__vmIp->setVolatile(false);
    m_Job__vmIp->setChangeable(true);
    m_Job__vmIp->setUnsettable(false);
    m_Job__vmIp->setID(false);
    m_Job__vmIp->setUnique(false);
    m_Job__vmIp->setDerived(false);
    m_Job__vmIp->setOrdered(true);
    // ListJobs
    m_ListJobsEClass->setName("ListJobs");
    m_ListJobsEClass->setAbstract(false);
    m_ListJobsEClass->setInterface(false);
    m_ListJobs__nbJobs->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_ListJobs__nbJobs->setName("nbJobs");
    m_ListJobs__nbJobs->setDefaultValueLiteral("0");
    m_ListJobs__nbJobs->setLowerBound(0);
    m_ListJobs__nbJobs->setUpperBound(1);
    m_ListJobs__nbJobs->setTransient(false);
    m_ListJobs__nbJobs->setVolatile(false);
    m_ListJobs__nbJobs->setChangeable(true);
    m_ListJobs__nbJobs->setUnsettable(false);
    m_ListJobs__nbJobs->setID(false);
    m_ListJobs__nbJobs->setUnique(true);
    m_ListJobs__nbJobs->setDerived(false);
    m_ListJobs__nbJobs->setOrdered(true);
    m_ListJobs__nbRunningJobs->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_ListJobs__nbRunningJobs->setName("nbRunningJobs");
    m_ListJobs__nbRunningJobs->setDefaultValueLiteral("0");
    m_ListJobs__nbRunningJobs->setLowerBound(0);
    m_ListJobs__nbRunningJobs->setUpperBound(1);
    m_ListJobs__nbRunningJobs->setTransient(false);
    m_ListJobs__nbRunningJobs->setVolatile(false);
    m_ListJobs__nbRunningJobs->setChangeable(true);
    m_ListJobs__nbRunningJobs->setUnsettable(false);
    m_ListJobs__nbRunningJobs->setID(false);
    m_ListJobs__nbRunningJobs->setUnique(true);
    m_ListJobs__nbRunningJobs->setDerived(false);
    m_ListJobs__nbRunningJobs->setOrdered(true);
    m_ListJobs__nbWaitingJobs->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_ListJobs__nbWaitingJobs->setName("nbWaitingJobs");
    m_ListJobs__nbWaitingJobs->setDefaultValueLiteral("0");
    m_ListJobs__nbWaitingJobs->setLowerBound(0);
    m_ListJobs__nbWaitingJobs->setUpperBound(1);
    m_ListJobs__nbWaitingJobs->setTransient(false);
    m_ListJobs__nbWaitingJobs->setVolatile(false);
    m_ListJobs__nbWaitingJobs->setChangeable(true);
    m_ListJobs__nbWaitingJobs->setUnsettable(false);
    m_ListJobs__nbWaitingJobs->setID(false);
    m_ListJobs__nbWaitingJobs->setUnique(true);
    m_ListJobs__nbWaitingJobs->setDerived(false);
    m_ListJobs__nbWaitingJobs->setOrdered(true);
    m_ListJobs__jobs->setEType(m_JobEClass);
    m_ListJobs__jobs->setName("jobs");
    m_ListJobs__jobs->setDefaultValueLiteral("");
    m_ListJobs__jobs->setLowerBound(0);
    m_ListJobs__jobs->setUpperBound(-1);
    m_ListJobs__jobs->setTransient(false);
    m_ListJobs__jobs->setVolatile(false);
    m_ListJobs__jobs->setChangeable(true);
    m_ListJobs__jobs->setContainment(true);
    m_ListJobs__jobs->setResolveProxies(true);
    m_ListJobs__jobs->setUnique(true);
    m_ListJobs__jobs->setDerived(false);
    m_ListJobs__jobs->setOrdered(true);
    // SubmitOptions
    m_SubmitOptionsEClass->setName("SubmitOptions");
    m_SubmitOptionsEClass->setAbstract(false);
    m_SubmitOptionsEClass->setInterface(false);
    m_SubmitOptions__name->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_SubmitOptions__name->setName("name");
    m_SubmitOptions__name->setDefaultValueLiteral("");
    m_SubmitOptions__name->setLowerBound(0);
    m_SubmitOptions__name->setUpperBound(1);
    m_SubmitOptions__name->setTransient(false);
    m_SubmitOptions__name->setVolatile(false);
    m_SubmitOptions__name->setChangeable(true);
    m_SubmitOptions__name->setUnsettable(false);
    m_SubmitOptions__name->setID(false);
    m_SubmitOptions__name->setUnique(true);
    m_SubmitOptions__name->setDerived(false);
    m_SubmitOptions__name->setOrdered(true);
    m_SubmitOptions__queue->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_SubmitOptions__queue->setName("queue");
    m_SubmitOptions__queue->setDefaultValueLiteral("");
    m_SubmitOptions__queue->setLowerBound(0);
    m_SubmitOptions__queue->setUpperBound(1);
    m_SubmitOptions__queue->setTransient(false);
    m_SubmitOptions__queue->setVolatile(false);
    m_SubmitOptions__queue->setChangeable(true);
    m_SubmitOptions__queue->setUnsettable(false);
    m_SubmitOptions__queue->setID(false);
    m_SubmitOptions__queue->setUnique(true);
    m_SubmitOptions__queue->setDerived(false);
    m_SubmitOptions__queue->setOrdered(true);
    m_SubmitOptions__wallTime->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_SubmitOptions__wallTime->setName("wallTime");
    m_SubmitOptions__wallTime->setDefaultValueLiteral("-1");
    m_SubmitOptions__wallTime->setLowerBound(0);
    m_SubmitOptions__wallTime->setUpperBound(1);
    m_SubmitOptions__wallTime->setTransient(false);
    m_SubmitOptions__wallTime->setVolatile(false);
    m_SubmitOptions__wallTime->setChangeable(true);
    m_SubmitOptions__wallTime->setUnsettable(false);
    m_SubmitOptions__wallTime->setID(false);
    m_SubmitOptions__wallTime->setUnique(true);
    m_SubmitOptions__wallTime->setDerived(false);
    m_SubmitOptions__wallTime->setOrdered(true);
    m_SubmitOptions__memory->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_SubmitOptions__memory->setName("memory");
    m_SubmitOptions__memory->setDefaultValueLiteral("-1");
    m_SubmitOptions__memory->setLowerBound(0);
    m_SubmitOptions__memory->setUpperBound(1);
    m_SubmitOptions__memory->setTransient(false);
    m_SubmitOptions__memory->setVolatile(false);
    m_SubmitOptions__memory->setChangeable(true);
    m_SubmitOptions__memory->setUnsettable(false);
    m_SubmitOptions__memory->setID(false);
    m_SubmitOptions__memory->setUnique(true);
    m_SubmitOptions__memory->setDerived(false);
    m_SubmitOptions__memory->setOrdered(true);
    m_SubmitOptions__nbCpu->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_SubmitOptions__nbCpu->setName("nbCpu");
    m_SubmitOptions__nbCpu->setDefaultValueLiteral("-1");
    m_SubmitOptions__nbCpu->setLowerBound(0);
    m_SubmitOptions__nbCpu->setUpperBound(1);
    m_SubmitOptions__nbCpu->setTransient(false);
    m_SubmitOptions__nbCpu->setVolatile(false);
    m_SubmitOptions__nbCpu->setChangeable(true);
    m_SubmitOptions__nbCpu->setUnsettable(false);
    m_SubmitOptions__nbCpu->setID(false);
    m_SubmitOptions__nbCpu->setUnique(true);
    m_SubmitOptions__nbCpu->setDerived(false);
    m_SubmitOptions__nbCpu->setOrdered(true);
    m_SubmitOptions__nbNodesAndCpuPerNode->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_SubmitOptions__nbNodesAndCpuPerNode->setName("nbNodesAndCpuPerNode");
    m_SubmitOptions__nbNodesAndCpuPerNode->setDefaultValueLiteral("");
    m_SubmitOptions__nbNodesAndCpuPerNode->setLowerBound(0);
    m_SubmitOptions__nbNodesAndCpuPerNode->setUpperBound(1);
    m_SubmitOptions__nbNodesAndCpuPerNode->setTransient(false);
    m_SubmitOptions__nbNodesAndCpuPerNode->setVolatile(false);
    m_SubmitOptions__nbNodesAndCpuPerNode->setChangeable(true);
    m_SubmitOptions__nbNodesAndCpuPerNode->setUnsettable(false);
    m_SubmitOptions__nbNodesAndCpuPerNode->setID(false);
    m_SubmitOptions__nbNodesAndCpuPerNode->setUnique(true);
    m_SubmitOptions__nbNodesAndCpuPerNode->setDerived(false);
    m_SubmitOptions__nbNodesAndCpuPerNode->setOrdered(true);
    m_SubmitOptions__outputPath->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_SubmitOptions__outputPath->setName("outputPath");
    m_SubmitOptions__outputPath->setDefaultValueLiteral("");
    m_SubmitOptions__outputPath->setLowerBound(0);
    m_SubmitOptions__outputPath->setUpperBound(1);
    m_SubmitOptions__outputPath->setTransient(false);
    m_SubmitOptions__outputPath->setVolatile(false);
    m_SubmitOptions__outputPath->setChangeable(true);
    m_SubmitOptions__outputPath->setUnsettable(false);
    m_SubmitOptions__outputPath->setID(false);
    m_SubmitOptions__outputPath->setUnique(true);
    m_SubmitOptions__outputPath->setDerived(false);
    m_SubmitOptions__outputPath->setOrdered(true);
    m_SubmitOptions__errorPath->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_SubmitOptions__errorPath->setName("errorPath");
    m_SubmitOptions__errorPath->setDefaultValueLiteral("");
    m_SubmitOptions__errorPath->setLowerBound(0);
    m_SubmitOptions__errorPath->setUpperBound(1);
    m_SubmitOptions__errorPath->setTransient(false);
    m_SubmitOptions__errorPath->setVolatile(false);
    m_SubmitOptions__errorPath->setChangeable(true);
    m_SubmitOptions__errorPath->setUnsettable(false);
    m_SubmitOptions__errorPath->setID(false);
    m_SubmitOptions__errorPath->setUnique(true);
    m_SubmitOptions__errorPath->setDerived(false);
    m_SubmitOptions__errorPath->setOrdered(true);
    m_SubmitOptions__mailNotification->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_SubmitOptions__mailNotification->setName("mailNotification");
    m_SubmitOptions__mailNotification->setDefaultValueLiteral("");
    m_SubmitOptions__mailNotification->setLowerBound(0);
    m_SubmitOptions__mailNotification->setUpperBound(1);
    m_SubmitOptions__mailNotification->setTransient(false);
    m_SubmitOptions__mailNotification->setVolatile(false);
    m_SubmitOptions__mailNotification->setChangeable(true);
    m_SubmitOptions__mailNotification->setUnsettable(false);
    m_SubmitOptions__mailNotification->setID(false);
    m_SubmitOptions__mailNotification->setUnique(true);
    m_SubmitOptions__mailNotification->setDerived(false);
    m_SubmitOptions__mailNotification->setOrdered(true);
    m_SubmitOptions__mailNotifyUser->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_SubmitOptions__mailNotifyUser->setName("mailNotifyUser");
    m_SubmitOptions__mailNotifyUser->setDefaultValueLiteral("");
    m_SubmitOptions__mailNotifyUser->setLowerBound(0);
    m_SubmitOptions__mailNotifyUser->setUpperBound(1);
    m_SubmitOptions__mailNotifyUser->setTransient(false);
    m_SubmitOptions__mailNotifyUser->setVolatile(false);
    m_SubmitOptions__mailNotifyUser->setChangeable(true);
    m_SubmitOptions__mailNotifyUser->setUnsettable(false);
    m_SubmitOptions__mailNotifyUser->setID(false);
    m_SubmitOptions__mailNotifyUser->setUnique(true);
    m_SubmitOptions__mailNotifyUser->setDerived(false);
    m_SubmitOptions__mailNotifyUser->setOrdered(true);
    m_SubmitOptions__group->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_SubmitOptions__group->setName("group");
    m_SubmitOptions__group->setDefaultValueLiteral("");
    m_SubmitOptions__group->setLowerBound(0);
    m_SubmitOptions__group->setUpperBound(1);
    m_SubmitOptions__group->setTransient(false);
    m_SubmitOptions__group->setVolatile(false);
    m_SubmitOptions__group->setChangeable(true);
    m_SubmitOptions__group->setUnsettable(false);
    m_SubmitOptions__group->setID(false);
    m_SubmitOptions__group->setUnique(true);
    m_SubmitOptions__group->setDerived(false);
    m_SubmitOptions__group->setOrdered(true);
    m_SubmitOptions__workingDir->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_SubmitOptions__workingDir->setName("workingDir");
    m_SubmitOptions__workingDir->setDefaultValueLiteral("");
    m_SubmitOptions__workingDir->setLowerBound(0);
    m_SubmitOptions__workingDir->setUpperBound(1);
    m_SubmitOptions__workingDir->setTransient(false);
    m_SubmitOptions__workingDir->setVolatile(false);
    m_SubmitOptions__workingDir->setChangeable(true);
    m_SubmitOptions__workingDir->setUnsettable(false);
    m_SubmitOptions__workingDir->setID(false);
    m_SubmitOptions__workingDir->setUnique(true);
    m_SubmitOptions__workingDir->setDerived(false);
    m_SubmitOptions__workingDir->setOrdered(true);
    m_SubmitOptions__cpuTime->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_SubmitOptions__cpuTime->setName("cpuTime");
    m_SubmitOptions__cpuTime->setDefaultValueLiteral("");
    m_SubmitOptions__cpuTime->setLowerBound(0);
    m_SubmitOptions__cpuTime->setUpperBound(1);
    m_SubmitOptions__cpuTime->setTransient(false);
    m_SubmitOptions__cpuTime->setVolatile(false);
    m_SubmitOptions__cpuTime->setChangeable(true);
    m_SubmitOptions__cpuTime->setUnsettable(false);
    m_SubmitOptions__cpuTime->setID(false);
    m_SubmitOptions__cpuTime->setUnique(true);
    m_SubmitOptions__cpuTime->setDerived(false);
    m_SubmitOptions__cpuTime->setOrdered(true);
    m_SubmitOptions__selectQueueAutom->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_SubmitOptions__selectQueueAutom->setName("selectQueueAutom");
    m_SubmitOptions__selectQueueAutom->setDefaultValueLiteral("false");
    m_SubmitOptions__selectQueueAutom->setLowerBound(0);
    m_SubmitOptions__selectQueueAutom->setUpperBound(1);
    m_SubmitOptions__selectQueueAutom->setTransient(false);
    m_SubmitOptions__selectQueueAutom->setVolatile(false);
    m_SubmitOptions__selectQueueAutom->setChangeable(true);
    m_SubmitOptions__selectQueueAutom->setUnsettable(false);
    m_SubmitOptions__selectQueueAutom->setID(false);
    m_SubmitOptions__selectQueueAutom->setUnique(true);
    m_SubmitOptions__selectQueueAutom->setDerived(false);
    m_SubmitOptions__selectQueueAutom->setOrdered(true);
    m_SubmitOptions__fileParams->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_SubmitOptions__fileParams->setName("fileParams");
    m_SubmitOptions__fileParams->setDefaultValueLiteral("");
    m_SubmitOptions__fileParams->setLowerBound(0);
    m_SubmitOptions__fileParams->setUpperBound(1);
    m_SubmitOptions__fileParams->setTransient(false);
    m_SubmitOptions__fileParams->setVolatile(false);
    m_SubmitOptions__fileParams->setChangeable(true);
    m_SubmitOptions__fileParams->setUnsettable(false);
    m_SubmitOptions__fileParams->setID(false);
    m_SubmitOptions__fileParams->setUnique(true);
    m_SubmitOptions__fileParams->setDerived(false);
    m_SubmitOptions__fileParams->setOrdered(true);
    m_SubmitOptions__textParams->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_SubmitOptions__textParams->setName("textParams");
    m_SubmitOptions__textParams->setDefaultValueLiteral("");
    m_SubmitOptions__textParams->setLowerBound(0);
    m_SubmitOptions__textParams->setUpperBound(1);
    m_SubmitOptions__textParams->setTransient(false);
    m_SubmitOptions__textParams->setVolatile(false);
    m_SubmitOptions__textParams->setChangeable(true);
    m_SubmitOptions__textParams->setUnsettable(false);
    m_SubmitOptions__textParams->setID(false);
    m_SubmitOptions__textParams->setUnique(true);
    m_SubmitOptions__textParams->setDerived(false);
    m_SubmitOptions__textParams->setOrdered(true);
    m_SubmitOptions__workId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_SubmitOptions__workId->setName("workId");
    m_SubmitOptions__workId->setDefaultValueLiteral("0");
    m_SubmitOptions__workId->setLowerBound(0);
    m_SubmitOptions__workId->setUpperBound(1);
    m_SubmitOptions__workId->setTransient(false);
    m_SubmitOptions__workId->setVolatile(false);
    m_SubmitOptions__workId->setChangeable(true);
    m_SubmitOptions__workId->setUnsettable(false);
    m_SubmitOptions__workId->setID(false);
    m_SubmitOptions__workId->setUnique(true);
    m_SubmitOptions__workId->setDerived(false);
    m_SubmitOptions__workId->setOrdered(true);
    m_SubmitOptions__specificParams->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_SubmitOptions__specificParams->setName("specificParams");
    m_SubmitOptions__specificParams->setDefaultValueLiteral("");
    m_SubmitOptions__specificParams->setLowerBound(0);
    m_SubmitOptions__specificParams->setUpperBound(1);
    m_SubmitOptions__specificParams->setTransient(false);
    m_SubmitOptions__specificParams->setVolatile(false);
    m_SubmitOptions__specificParams->setChangeable(true);
    m_SubmitOptions__specificParams->setUnsettable(false);
    m_SubmitOptions__specificParams->setID(false);
    m_SubmitOptions__specificParams->setUnique(true);
    m_SubmitOptions__specificParams->setDerived(false);
    m_SubmitOptions__specificParams->setOrdered(true);
    m_SubmitOptions__posix->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_SubmitOptions__posix->setName("posix");
    m_SubmitOptions__posix->setDefaultValueLiteral("false");
    m_SubmitOptions__posix->setLowerBound(0);
    m_SubmitOptions__posix->setUpperBound(1);
    m_SubmitOptions__posix->setTransient(false);
    m_SubmitOptions__posix->setVolatile(false);
    m_SubmitOptions__posix->setChangeable(true);
    m_SubmitOptions__posix->setUnsettable(false);
    m_SubmitOptions__posix->setID(false);
    m_SubmitOptions__posix->setUnique(true);
    m_SubmitOptions__posix->setDerived(false);
    m_SubmitOptions__posix->setOrdered(true);
    m_SubmitOptions__machine->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_SubmitOptions__machine->setName("machine");
    m_SubmitOptions__machine->setDefaultValueLiteral("" "");
    m_SubmitOptions__machine->setLowerBound(0);
    m_SubmitOptions__machine->setUpperBound(1);
    m_SubmitOptions__machine->setTransient(false);
    m_SubmitOptions__machine->setVolatile(false);
    m_SubmitOptions__machine->setChangeable(true);
    m_SubmitOptions__machine->setUnsettable(false);
    m_SubmitOptions__machine->setID(false);
    m_SubmitOptions__machine->setUnique(true);
    m_SubmitOptions__machine->setDerived(false);
    m_SubmitOptions__machine->setOrdered(true);
    m_SubmitOptions__criterion->setEType(m_LoadCriterionEClass);
    m_SubmitOptions__criterion->setName("criterion");
    m_SubmitOptions__criterion->setDefaultValueLiteral("");
    m_SubmitOptions__criterion->setLowerBound(0);
    m_SubmitOptions__criterion->setUpperBound(1);
    m_SubmitOptions__criterion->setTransient(false);
    m_SubmitOptions__criterion->setVolatile(false);
    m_SubmitOptions__criterion->setChangeable(true);
    m_SubmitOptions__criterion->setContainment(true);
    m_SubmitOptions__criterion->setResolveProxies(true);
    m_SubmitOptions__criterion->setUnique(true);
    m_SubmitOptions__criterion->setDerived(false);
    m_SubmitOptions__criterion->setOrdered(true);
    // ListJobsOptions
    m_ListJobsOptionsEClass->setName("ListJobsOptions");
    m_ListJobsOptionsEClass->setAbstract(false);
    m_ListJobsOptionsEClass->setInterface(false);
    m_ListJobsOptions__jobId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListJobsOptions__jobId->setName("jobId");
    m_ListJobsOptions__jobId->setDefaultValueLiteral("" "");
    m_ListJobsOptions__jobId->setLowerBound(0);
    m_ListJobsOptions__jobId->setUpperBound(1);
    m_ListJobsOptions__jobId->setTransient(false);
    m_ListJobsOptions__jobId->setVolatile(false);
    m_ListJobsOptions__jobId->setChangeable(true);
    m_ListJobsOptions__jobId->setUnsettable(false);
    m_ListJobsOptions__jobId->setID(false);
    m_ListJobsOptions__jobId->setUnique(true);
    m_ListJobsOptions__jobId->setDerived(false);
    m_ListJobsOptions__jobId->setOrdered(true);
    m_ListJobsOptions__nbCpu->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_ListJobsOptions__nbCpu->setName("nbCpu");
    m_ListJobsOptions__nbCpu->setDefaultValueLiteral("-1");
    m_ListJobsOptions__nbCpu->setLowerBound(0);
    m_ListJobsOptions__nbCpu->setUpperBound(1);
    m_ListJobsOptions__nbCpu->setTransient(false);
    m_ListJobsOptions__nbCpu->setVolatile(false);
    m_ListJobsOptions__nbCpu->setChangeable(true);
    m_ListJobsOptions__nbCpu->setUnsettable(false);
    m_ListJobsOptions__nbCpu->setID(false);
    m_ListJobsOptions__nbCpu->setUnique(true);
    m_ListJobsOptions__nbCpu->setDerived(false);
    m_ListJobsOptions__nbCpu->setOrdered(true);
    m_ListJobsOptions__fromSubmitDate->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_ListJobsOptions__fromSubmitDate->setName("fromSubmitDate");
    m_ListJobsOptions__fromSubmitDate->setDefaultValueLiteral("-1");
    m_ListJobsOptions__fromSubmitDate->setLowerBound(0);
    m_ListJobsOptions__fromSubmitDate->setUpperBound(1);
    m_ListJobsOptions__fromSubmitDate->setTransient(false);
    m_ListJobsOptions__fromSubmitDate->setVolatile(false);
    m_ListJobsOptions__fromSubmitDate->setChangeable(true);
    m_ListJobsOptions__fromSubmitDate->setUnsettable(false);
    m_ListJobsOptions__fromSubmitDate->setID(false);
    m_ListJobsOptions__fromSubmitDate->setUnique(true);
    m_ListJobsOptions__fromSubmitDate->setDerived(false);
    m_ListJobsOptions__fromSubmitDate->setOrdered(true);
    m_ListJobsOptions__toSubmitDate->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_ListJobsOptions__toSubmitDate->setName("toSubmitDate");
    m_ListJobsOptions__toSubmitDate->setDefaultValueLiteral("-1");
    m_ListJobsOptions__toSubmitDate->setLowerBound(0);
    m_ListJobsOptions__toSubmitDate->setUpperBound(1);
    m_ListJobsOptions__toSubmitDate->setTransient(false);
    m_ListJobsOptions__toSubmitDate->setVolatile(false);
    m_ListJobsOptions__toSubmitDate->setChangeable(true);
    m_ListJobsOptions__toSubmitDate->setUnsettable(false);
    m_ListJobsOptions__toSubmitDate->setID(false);
    m_ListJobsOptions__toSubmitDate->setUnique(true);
    m_ListJobsOptions__toSubmitDate->setDerived(false);
    m_ListJobsOptions__toSubmitDate->setOrdered(true);
    m_ListJobsOptions__owner->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListJobsOptions__owner->setName("owner");
    m_ListJobsOptions__owner->setDefaultValueLiteral("");
    m_ListJobsOptions__owner->setLowerBound(0);
    m_ListJobsOptions__owner->setUpperBound(1);
    m_ListJobsOptions__owner->setTransient(false);
    m_ListJobsOptions__owner->setVolatile(false);
    m_ListJobsOptions__owner->setChangeable(true);
    m_ListJobsOptions__owner->setUnsettable(false);
    m_ListJobsOptions__owner->setID(false);
    m_ListJobsOptions__owner->setUnique(true);
    m_ListJobsOptions__owner->setDerived(false);
    m_ListJobsOptions__owner->setOrdered(true);
    m_ListJobsOptions__status->setEType(m_JobStatusEEnum);
    m_ListJobsOptions__status->setName("status");
    m_ListJobsOptions__status->setDefaultValueLiteral("-1");
    m_ListJobsOptions__status->setLowerBound(0);
    m_ListJobsOptions__status->setUpperBound(1);
    m_ListJobsOptions__status->setTransient(false);
    m_ListJobsOptions__status->setVolatile(false);
    m_ListJobsOptions__status->setChangeable(true);
    m_ListJobsOptions__status->setUnsettable(false);
    m_ListJobsOptions__status->setID(false);
    m_ListJobsOptions__status->setUnique(true);
    m_ListJobsOptions__status->setDerived(false);
    m_ListJobsOptions__status->setOrdered(true);
    m_ListJobsOptions__priority->setEType(m_JobPriorityEEnum);
    m_ListJobsOptions__priority->setName("priority");
    m_ListJobsOptions__priority->setDefaultValueLiteral("-1");
    m_ListJobsOptions__priority->setLowerBound(0);
    m_ListJobsOptions__priority->setUpperBound(1);
    m_ListJobsOptions__priority->setTransient(false);
    m_ListJobsOptions__priority->setVolatile(false);
    m_ListJobsOptions__priority->setChangeable(true);
    m_ListJobsOptions__priority->setUnsettable(false);
    m_ListJobsOptions__priority->setID(false);
    m_ListJobsOptions__priority->setUnique(true);
    m_ListJobsOptions__priority->setDerived(false);
    m_ListJobsOptions__priority->setOrdered(true);
    m_ListJobsOptions__queue->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListJobsOptions__queue->setName("queue");
    m_ListJobsOptions__queue->setDefaultValueLiteral("");
    m_ListJobsOptions__queue->setLowerBound(0);
    m_ListJobsOptions__queue->setUpperBound(1);
    m_ListJobsOptions__queue->setTransient(false);
    m_ListJobsOptions__queue->setVolatile(false);
    m_ListJobsOptions__queue->setChangeable(true);
    m_ListJobsOptions__queue->setUnsettable(false);
    m_ListJobsOptions__queue->setID(false);
    m_ListJobsOptions__queue->setUnique(true);
    m_ListJobsOptions__queue->setDerived(false);
    m_ListJobsOptions__queue->setOrdered(true);
    m_ListJobsOptions__multipleStatus->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListJobsOptions__multipleStatus->setName("multipleStatus");
    m_ListJobsOptions__multipleStatus->setDefaultValueLiteral("");
    m_ListJobsOptions__multipleStatus->setLowerBound(0);
    m_ListJobsOptions__multipleStatus->setUpperBound(1);
    m_ListJobsOptions__multipleStatus->setTransient(false);
    m_ListJobsOptions__multipleStatus->setVolatile(false);
    m_ListJobsOptions__multipleStatus->setChangeable(true);
    m_ListJobsOptions__multipleStatus->setUnsettable(false);
    m_ListJobsOptions__multipleStatus->setID(false);
    m_ListJobsOptions__multipleStatus->setUnique(true);
    m_ListJobsOptions__multipleStatus->setDerived(false);
    m_ListJobsOptions__multipleStatus->setOrdered(true);
    m_ListJobsOptions__batchJob->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_ListJobsOptions__batchJob->setName("batchJob");
    m_ListJobsOptions__batchJob->setDefaultValueLiteral("false");
    m_ListJobsOptions__batchJob->setLowerBound(0);
    m_ListJobsOptions__batchJob->setUpperBound(1);
    m_ListJobsOptions__batchJob->setTransient(false);
    m_ListJobsOptions__batchJob->setVolatile(false);
    m_ListJobsOptions__batchJob->setChangeable(true);
    m_ListJobsOptions__batchJob->setUnsettable(false);
    m_ListJobsOptions__batchJob->setID(false);
    m_ListJobsOptions__batchJob->setUnique(true);
    m_ListJobsOptions__batchJob->setDerived(false);
    m_ListJobsOptions__batchJob->setOrdered(true);
    m_ListJobsOptions__workId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_ListJobsOptions__workId->setName("workId");
    m_ListJobsOptions__workId->setDefaultValueLiteral("-1");
    m_ListJobsOptions__workId->setLowerBound(0);
    m_ListJobsOptions__workId->setUpperBound(1);
    m_ListJobsOptions__workId->setTransient(false);
    m_ListJobsOptions__workId->setVolatile(false);
    m_ListJobsOptions__workId->setChangeable(true);
    m_ListJobsOptions__workId->setUnsettable(false);
    m_ListJobsOptions__workId->setID(false);
    m_ListJobsOptions__workId->setUnique(true);
    m_ListJobsOptions__workId->setDerived(false);
    m_ListJobsOptions__workId->setOrdered(true);
    m_ListJobsOptions__listAll->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_ListJobsOptions__listAll->setName("listAll");
    m_ListJobsOptions__listAll->setDefaultValueLiteral("false");
    m_ListJobsOptions__listAll->setLowerBound(0);
    m_ListJobsOptions__listAll->setUpperBound(1);
    m_ListJobsOptions__listAll->setTransient(false);
    m_ListJobsOptions__listAll->setVolatile(false);
    m_ListJobsOptions__listAll->setChangeable(true);
    m_ListJobsOptions__listAll->setUnsettable(false);
    m_ListJobsOptions__listAll->setID(false);
    m_ListJobsOptions__listAll->setUnique(true);
    m_ListJobsOptions__listAll->setDerived(false);
    m_ListJobsOptions__listAll->setOrdered(true);
    m_ListJobsOptions__machineId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListJobsOptions__machineId->setName("machineId");
    m_ListJobsOptions__machineId->setDefaultValueLiteral("");
    m_ListJobsOptions__machineId->setLowerBound(0);
    m_ListJobsOptions__machineId->setUpperBound(1);
    m_ListJobsOptions__machineId->setTransient(false);
    m_ListJobsOptions__machineId->setVolatile(false);
    m_ListJobsOptions__machineId->setChangeable(true);
    m_ListJobsOptions__machineId->setUnsettable(false);
    m_ListJobsOptions__machineId->setID(false);
    m_ListJobsOptions__machineId->setUnique(true);
    m_ListJobsOptions__machineId->setDerived(false);
    m_ListJobsOptions__machineId->setOrdered(true);
    // ProgressOptions
    m_ProgressOptionsEClass->setName("ProgressOptions");
    m_ProgressOptionsEClass->setAbstract(false);
    m_ProgressOptionsEClass->setInterface(false);
    m_ProgressOptions__jobId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ProgressOptions__jobId->setName("jobId");
    m_ProgressOptions__jobId->setDefaultValueLiteral("");
    m_ProgressOptions__jobId->setLowerBound(0);
    m_ProgressOptions__jobId->setUpperBound(1);
    m_ProgressOptions__jobId->setTransient(false);
    m_ProgressOptions__jobId->setVolatile(false);
    m_ProgressOptions__jobId->setChangeable(true);
    m_ProgressOptions__jobId->setUnsettable(false);
    m_ProgressOptions__jobId->setID(false);
    m_ProgressOptions__jobId->setUnique(true);
    m_ProgressOptions__jobId->setDerived(false);
    m_ProgressOptions__jobId->setOrdered(true);
    m_ProgressOptions__user->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ProgressOptions__user->setName("user");
    m_ProgressOptions__user->setDefaultValueLiteral("");
    m_ProgressOptions__user->setLowerBound(0);
    m_ProgressOptions__user->setUpperBound(1);
    m_ProgressOptions__user->setTransient(false);
    m_ProgressOptions__user->setVolatile(false);
    m_ProgressOptions__user->setChangeable(true);
    m_ProgressOptions__user->setUnsettable(false);
    m_ProgressOptions__user->setID(false);
    m_ProgressOptions__user->setUnique(true);
    m_ProgressOptions__user->setDerived(false);
    m_ProgressOptions__user->setOrdered(true);
    m_ProgressOptions__machineId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ProgressOptions__machineId->setName("machineId");
    m_ProgressOptions__machineId->setDefaultValueLiteral("" "");
    m_ProgressOptions__machineId->setLowerBound(0);
    m_ProgressOptions__machineId->setUpperBound(1);
    m_ProgressOptions__machineId->setTransient(false);
    m_ProgressOptions__machineId->setVolatile(false);
    m_ProgressOptions__machineId->setChangeable(true);
    m_ProgressOptions__machineId->setUnsettable(false);
    m_ProgressOptions__machineId->setID(false);
    m_ProgressOptions__machineId->setUnique(true);
    m_ProgressOptions__machineId->setDerived(false);
    m_ProgressOptions__machineId->setOrdered(true);
    // ListProgression
    m_ListProgressionEClass->setName("ListProgression");
    m_ListProgressionEClass->setAbstract(false);
    m_ListProgressionEClass->setInterface(false);
    m_ListProgression__nbJobs->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_ListProgression__nbJobs->setName("nbJobs");
    m_ListProgression__nbJobs->setDefaultValueLiteral("0");
    m_ListProgression__nbJobs->setLowerBound(0);
    m_ListProgression__nbJobs->setUpperBound(1);
    m_ListProgression__nbJobs->setTransient(false);
    m_ListProgression__nbJobs->setVolatile(false);
    m_ListProgression__nbJobs->setChangeable(true);
    m_ListProgression__nbJobs->setUnsettable(false);
    m_ListProgression__nbJobs->setID(false);
    m_ListProgression__nbJobs->setUnique(true);
    m_ListProgression__nbJobs->setDerived(false);
    m_ListProgression__nbJobs->setOrdered(true);
    m_ListProgression__progress->setEType(m_ProgressionEClass);
    m_ListProgression__progress->setName("progress");
    m_ListProgression__progress->setDefaultValueLiteral("");
    m_ListProgression__progress->setLowerBound(0);
    m_ListProgression__progress->setUpperBound(-1);
    m_ListProgression__progress->setTransient(false);
    m_ListProgression__progress->setVolatile(false);
    m_ListProgression__progress->setChangeable(true);
    m_ListProgression__progress->setContainment(true);
    m_ListProgression__progress->setResolveProxies(true);
    m_ListProgression__progress->setUnique(true);
    m_ListProgression__progress->setDerived(false);
    m_ListProgression__progress->setOrdered(true);
    // Progression
    m_ProgressionEClass->setName("Progression");
    m_ProgressionEClass->setAbstract(false);
    m_ProgressionEClass->setInterface(false);
    m_Progression__jobId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Progression__jobId->setName("jobId");
    m_Progression__jobId->setDefaultValueLiteral("");
    m_Progression__jobId->setLowerBound(0);
    m_Progression__jobId->setUpperBound(1);
    m_Progression__jobId->setTransient(false);
    m_Progression__jobId->setVolatile(false);
    m_Progression__jobId->setChangeable(true);
    m_Progression__jobId->setUnsettable(false);
    m_Progression__jobId->setID(false);
    m_Progression__jobId->setUnique(true);
    m_Progression__jobId->setDerived(false);
    m_Progression__jobId->setOrdered(true);
    m_Progression__jobName->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Progression__jobName->setName("jobName");
    m_Progression__jobName->setDefaultValueLiteral("");
    m_Progression__jobName->setLowerBound(0);
    m_Progression__jobName->setUpperBound(1);
    m_Progression__jobName->setTransient(false);
    m_Progression__jobName->setVolatile(false);
    m_Progression__jobName->setChangeable(true);
    m_Progression__jobName->setUnsettable(false);
    m_Progression__jobName->setID(false);
    m_Progression__jobName->setUnique(true);
    m_Progression__jobName->setDerived(false);
    m_Progression__jobName->setOrdered(true);
    m_Progression__wallTime->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Progression__wallTime->setName("wallTime");
    m_Progression__wallTime->setDefaultValueLiteral("-1");
    m_Progression__wallTime->setLowerBound(0);
    m_Progression__wallTime->setUpperBound(1);
    m_Progression__wallTime->setTransient(false);
    m_Progression__wallTime->setVolatile(false);
    m_Progression__wallTime->setChangeable(true);
    m_Progression__wallTime->setUnsettable(false);
    m_Progression__wallTime->setID(false);
    m_Progression__wallTime->setUnique(true);
    m_Progression__wallTime->setDerived(false);
    m_Progression__wallTime->setOrdered(true);
    m_Progression__startTime->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Progression__startTime->setName("startTime");
    m_Progression__startTime->setDefaultValueLiteral("-1");
    m_Progression__startTime->setLowerBound(0);
    m_Progression__startTime->setUpperBound(1);
    m_Progression__startTime->setTransient(false);
    m_Progression__startTime->setVolatile(false);
    m_Progression__startTime->setChangeable(true);
    m_Progression__startTime->setUnsettable(false);
    m_Progression__startTime->setID(false);
    m_Progression__startTime->setUnique(true);
    m_Progression__startTime->setDerived(false);
    m_Progression__startTime->setOrdered(true);
    m_Progression__endTime->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Progression__endTime->setName("endTime");
    m_Progression__endTime->setDefaultValueLiteral("-1");
    m_Progression__endTime->setLowerBound(0);
    m_Progression__endTime->setUpperBound(1);
    m_Progression__endTime->setTransient(false);
    m_Progression__endTime->setVolatile(false);
    m_Progression__endTime->setChangeable(true);
    m_Progression__endTime->setUnsettable(false);
    m_Progression__endTime->setID(false);
    m_Progression__endTime->setUnique(true);
    m_Progression__endTime->setDerived(false);
    m_Progression__endTime->setOrdered(true);
    m_Progression__percent->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Progression__percent->setName("percent");
    m_Progression__percent->setDefaultValueLiteral("0");
    m_Progression__percent->setLowerBound(0);
    m_Progression__percent->setUpperBound(1);
    m_Progression__percent->setTransient(false);
    m_Progression__percent->setVolatile(false);
    m_Progression__percent->setChangeable(true);
    m_Progression__percent->setUnsettable(false);
    m_Progression__percent->setID(false);
    m_Progression__percent->setUnique(true);
    m_Progression__percent->setDerived(false);
    m_Progression__percent->setOrdered(true);
    m_Progression__status->setEType(m_JobStatusEEnum);
    m_Progression__status->setName("status");
    m_Progression__status->setDefaultValueLiteral("-1");
    m_Progression__status->setLowerBound(0);
    m_Progression__status->setUpperBound(1);
    m_Progression__status->setTransient(false);
    m_Progression__status->setVolatile(false);
    m_Progression__status->setChangeable(true);
    m_Progression__status->setUnsettable(false);
    m_Progression__status->setID(false);
    m_Progression__status->setUnique(true);
    m_Progression__status->setDerived(false);
    m_Progression__status->setOrdered(true);
    // ListQueues
    m_ListQueuesEClass->setName("ListQueues");
    m_ListQueuesEClass->setAbstract(false);
    m_ListQueuesEClass->setInterface(false);
    m_ListQueues__nbQueues->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_ListQueues__nbQueues->setName("nbQueues");
    m_ListQueues__nbQueues->setDefaultValueLiteral("0");
    m_ListQueues__nbQueues->setLowerBound(0);
    m_ListQueues__nbQueues->setUpperBound(1);
    m_ListQueues__nbQueues->setTransient(false);
    m_ListQueues__nbQueues->setVolatile(false);
    m_ListQueues__nbQueues->setChangeable(true);
    m_ListQueues__nbQueues->setUnsettable(false);
    m_ListQueues__nbQueues->setID(false);
    m_ListQueues__nbQueues->setUnique(true);
    m_ListQueues__nbQueues->setDerived(false);
    m_ListQueues__nbQueues->setOrdered(true);
    m_ListQueues__queues->setEType(m_QueueEClass);
    m_ListQueues__queues->setName("queues");
    m_ListQueues__queues->setDefaultValueLiteral("");
    m_ListQueues__queues->setLowerBound(0);
    m_ListQueues__queues->setUpperBound(-1);
    m_ListQueues__queues->setTransient(false);
    m_ListQueues__queues->setVolatile(false);
    m_ListQueues__queues->setChangeable(true);
    m_ListQueues__queues->setContainment(true);
    m_ListQueues__queues->setResolveProxies(true);
    m_ListQueues__queues->setUnique(true);
    m_ListQueues__queues->setDerived(false);
    m_ListQueues__queues->setOrdered(true);
    // Queue
    m_QueueEClass->setName("Queue");
    m_QueueEClass->setAbstract(false);
    m_QueueEClass->setInterface(false);
    m_Queue__name->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Queue__name->setName("name");
    m_Queue__name->setDefaultValueLiteral("");
    m_Queue__name->setLowerBound(0);
    m_Queue__name->setUpperBound(1);
    m_Queue__name->setTransient(false);
    m_Queue__name->setVolatile(false);
    m_Queue__name->setChangeable(true);
    m_Queue__name->setUnsettable(false);
    m_Queue__name->setID(false);
    m_Queue__name->setUnique(true);
    m_Queue__name->setDerived(false);
    m_Queue__name->setOrdered(true);
    m_Queue__maxJobCpu->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Queue__maxJobCpu->setName("maxJobCpu");
    m_Queue__maxJobCpu->setDefaultValueLiteral("-1");
    m_Queue__maxJobCpu->setLowerBound(0);
    m_Queue__maxJobCpu->setUpperBound(1);
    m_Queue__maxJobCpu->setTransient(false);
    m_Queue__maxJobCpu->setVolatile(false);
    m_Queue__maxJobCpu->setChangeable(true);
    m_Queue__maxJobCpu->setUnsettable(false);
    m_Queue__maxJobCpu->setID(false);
    m_Queue__maxJobCpu->setUnique(true);
    m_Queue__maxJobCpu->setDerived(false);
    m_Queue__maxJobCpu->setOrdered(true);
    m_Queue__maxProcCpu->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Queue__maxProcCpu->setName("maxProcCpu");
    m_Queue__maxProcCpu->setDefaultValueLiteral("-1");
    m_Queue__maxProcCpu->setLowerBound(0);
    m_Queue__maxProcCpu->setUpperBound(1);
    m_Queue__maxProcCpu->setTransient(false);
    m_Queue__maxProcCpu->setVolatile(false);
    m_Queue__maxProcCpu->setChangeable(true);
    m_Queue__maxProcCpu->setUnsettable(false);
    m_Queue__maxProcCpu->setID(false);
    m_Queue__maxProcCpu->setUnique(true);
    m_Queue__maxProcCpu->setDerived(false);
    m_Queue__maxProcCpu->setOrdered(true);
    m_Queue__memory->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Queue__memory->setName("memory");
    m_Queue__memory->setDefaultValueLiteral("-1");
    m_Queue__memory->setLowerBound(0);
    m_Queue__memory->setUpperBound(1);
    m_Queue__memory->setTransient(false);
    m_Queue__memory->setVolatile(false);
    m_Queue__memory->setChangeable(true);
    m_Queue__memory->setUnsettable(false);
    m_Queue__memory->setID(false);
    m_Queue__memory->setUnique(true);
    m_Queue__memory->setDerived(false);
    m_Queue__memory->setOrdered(true);
    m_Queue__wallTime->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Queue__wallTime->setName("wallTime");
    m_Queue__wallTime->setDefaultValueLiteral("-1");
    m_Queue__wallTime->setLowerBound(0);
    m_Queue__wallTime->setUpperBound(1);
    m_Queue__wallTime->setTransient(false);
    m_Queue__wallTime->setVolatile(false);
    m_Queue__wallTime->setChangeable(true);
    m_Queue__wallTime->setUnsettable(false);
    m_Queue__wallTime->setID(false);
    m_Queue__wallTime->setUnique(true);
    m_Queue__wallTime->setDerived(false);
    m_Queue__wallTime->setOrdered(true);
    m_Queue__node->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Queue__node->setName("node");
    m_Queue__node->setDefaultValueLiteral("-1");
    m_Queue__node->setLowerBound(0);
    m_Queue__node->setUpperBound(1);
    m_Queue__node->setTransient(false);
    m_Queue__node->setVolatile(false);
    m_Queue__node->setChangeable(true);
    m_Queue__node->setUnsettable(false);
    m_Queue__node->setID(false);
    m_Queue__node->setUnique(true);
    m_Queue__node->setDerived(false);
    m_Queue__node->setOrdered(true);
    m_Queue__nbRunningJobs->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Queue__nbRunningJobs->setName("nbRunningJobs");
    m_Queue__nbRunningJobs->setDefaultValueLiteral("0");
    m_Queue__nbRunningJobs->setLowerBound(0);
    m_Queue__nbRunningJobs->setUpperBound(1);
    m_Queue__nbRunningJobs->setTransient(false);
    m_Queue__nbRunningJobs->setVolatile(false);
    m_Queue__nbRunningJobs->setChangeable(true);
    m_Queue__nbRunningJobs->setUnsettable(false);
    m_Queue__nbRunningJobs->setID(false);
    m_Queue__nbRunningJobs->setUnique(true);
    m_Queue__nbRunningJobs->setDerived(false);
    m_Queue__nbRunningJobs->setOrdered(true);
    m_Queue__nbJobsInQueue->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Queue__nbJobsInQueue->setName("nbJobsInQueue");
    m_Queue__nbJobsInQueue->setDefaultValueLiteral("0");
    m_Queue__nbJobsInQueue->setLowerBound(0);
    m_Queue__nbJobsInQueue->setUpperBound(1);
    m_Queue__nbJobsInQueue->setTransient(false);
    m_Queue__nbJobsInQueue->setVolatile(false);
    m_Queue__nbJobsInQueue->setChangeable(true);
    m_Queue__nbJobsInQueue->setUnsettable(false);
    m_Queue__nbJobsInQueue->setID(false);
    m_Queue__nbJobsInQueue->setUnique(true);
    m_Queue__nbJobsInQueue->setDerived(false);
    m_Queue__nbJobsInQueue->setOrdered(true);
    m_Queue__state->setEType(m_QueueStatusEEnum);
    m_Queue__state->setName("state");
    m_Queue__state->setDefaultValueLiteral("-1");
    m_Queue__state->setLowerBound(0);
    m_Queue__state->setUpperBound(1);
    m_Queue__state->setTransient(false);
    m_Queue__state->setVolatile(false);
    m_Queue__state->setChangeable(true);
    m_Queue__state->setUnsettable(false);
    m_Queue__state->setID(false);
    m_Queue__state->setUnique(true);
    m_Queue__state->setDerived(false);
    m_Queue__state->setOrdered(true);
    m_Queue__priority->setEType(m_QueuePriorityEEnum);
    m_Queue__priority->setName("priority");
    m_Queue__priority->setDefaultValueLiteral("-1");
    m_Queue__priority->setLowerBound(0);
    m_Queue__priority->setUpperBound(1);
    m_Queue__priority->setTransient(false);
    m_Queue__priority->setVolatile(false);
    m_Queue__priority->setChangeable(true);
    m_Queue__priority->setUnsettable(false);
    m_Queue__priority->setID(false);
    m_Queue__priority->setUnique(true);
    m_Queue__priority->setDerived(false);
    m_Queue__priority->setOrdered(true);
    m_Queue__description->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Queue__description->setName("description");
    m_Queue__description->setDefaultValueLiteral("");
    m_Queue__description->setLowerBound(0);
    m_Queue__description->setUpperBound(1);
    m_Queue__description->setTransient(false);
    m_Queue__description->setVolatile(false);
    m_Queue__description->setChangeable(true);
    m_Queue__description->setUnsettable(false);
    m_Queue__description->setID(false);
    m_Queue__description->setUnique(true);
    m_Queue__description->setDerived(false);
    m_Queue__description->setOrdered(true);
    // JobResult
    m_JobResultEClass->setName("JobResult");
    m_JobResultEClass->setAbstract(false);
    m_JobResultEClass->setInterface(false);
    m_JobResult__jobId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_JobResult__jobId->setName("jobId");
    m_JobResult__jobId->setDefaultValueLiteral("");
    m_JobResult__jobId->setLowerBound(0);
    m_JobResult__jobId->setUpperBound(1);
    m_JobResult__jobId->setTransient(false);
    m_JobResult__jobId->setVolatile(false);
    m_JobResult__jobId->setChangeable(true);
    m_JobResult__jobId->setUnsettable(false);
    m_JobResult__jobId->setID(false);
    m_JobResult__jobId->setUnique(true);
    m_JobResult__jobId->setDerived(false);
    m_JobResult__jobId->setOrdered(true);
    m_JobResult__outputPath->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_JobResult__outputPath->setName("outputPath");
    m_JobResult__outputPath->setDefaultValueLiteral("");
    m_JobResult__outputPath->setLowerBound(0);
    m_JobResult__outputPath->setUpperBound(1);
    m_JobResult__outputPath->setTransient(false);
    m_JobResult__outputPath->setVolatile(false);
    m_JobResult__outputPath->setChangeable(true);
    m_JobResult__outputPath->setUnsettable(false);
    m_JobResult__outputPath->setID(false);
    m_JobResult__outputPath->setUnique(true);
    m_JobResult__outputPath->setDerived(false);
    m_JobResult__outputPath->setOrdered(true);
    m_JobResult__errorPath->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_JobResult__errorPath->setName("errorPath");
    m_JobResult__errorPath->setDefaultValueLiteral("");
    m_JobResult__errorPath->setLowerBound(0);
    m_JobResult__errorPath->setUpperBound(1);
    m_JobResult__errorPath->setTransient(false);
    m_JobResult__errorPath->setVolatile(false);
    m_JobResult__errorPath->setChangeable(true);
    m_JobResult__errorPath->setUnsettable(false);
    m_JobResult__errorPath->setID(false);
    m_JobResult__errorPath->setUnique(true);
    m_JobResult__errorPath->setDerived(false);
    m_JobResult__errorPath->setOrdered(true);
    m_JobResult__outputDir->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_JobResult__outputDir->setName("outputDir");
    m_JobResult__outputDir->setDefaultValueLiteral("");
    m_JobResult__outputDir->setLowerBound(0);
    m_JobResult__outputDir->setUpperBound(1);
    m_JobResult__outputDir->setTransient(false);
    m_JobResult__outputDir->setVolatile(false);
    m_JobResult__outputDir->setChangeable(true);
    m_JobResult__outputDir->setUnsettable(false);
    m_JobResult__outputDir->setID(false);
    m_JobResult__outputDir->setUnique(true);
    m_JobResult__outputDir->setDerived(false);
    m_JobResult__outputDir->setOrdered(true);
    // ListJobResults
    m_ListJobResultsEClass->setName("ListJobResults");
    m_ListJobResultsEClass->setAbstract(false);
    m_ListJobResultsEClass->setInterface(false);
    m_ListJobResults__nbJobs->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_ListJobResults__nbJobs->setName("nbJobs");
    m_ListJobResults__nbJobs->setDefaultValueLiteral("0");
    m_ListJobResults__nbJobs->setLowerBound(0);
    m_ListJobResults__nbJobs->setUpperBound(1);
    m_ListJobResults__nbJobs->setTransient(false);
    m_ListJobResults__nbJobs->setVolatile(false);
    m_ListJobResults__nbJobs->setChangeable(true);
    m_ListJobResults__nbJobs->setUnsettable(false);
    m_ListJobResults__nbJobs->setID(false);
    m_ListJobResults__nbJobs->setUnique(true);
    m_ListJobResults__nbJobs->setDerived(false);
    m_ListJobResults__nbJobs->setOrdered(true);
    m_ListJobResults__Results->setEType(m_JobResultEClass);
    m_ListJobResults__Results->setName("Results");
    m_ListJobResults__Results->setDefaultValueLiteral("");
    m_ListJobResults__Results->setLowerBound(0);
    m_ListJobResults__Results->setUpperBound(-1);
    m_ListJobResults__Results->setTransient(false);
    m_ListJobResults__Results->setVolatile(false);
    m_ListJobResults__Results->setChangeable(true);
    m_ListJobResults__Results->setContainment(true);
    m_ListJobResults__Results->setResolveProxies(true);
    m_ListJobResults__Results->setUnique(true);
    m_ListJobResults__Results->setDerived(false);
    m_ListJobResults__Results->setOrdered(true);
    // LoadCriterion
    m_LoadCriterionEClass->setName("LoadCriterion");
    m_LoadCriterionEClass->setAbstract(false);
    m_LoadCriterionEClass->setInterface(false);
    m_LoadCriterion__loadType->setEType(m_LoadTypeEEnum);
    m_LoadCriterion__loadType->setName("loadType");
    m_LoadCriterion__loadType->setDefaultValueLiteral("1");
    m_LoadCriterion__loadType->setLowerBound(0);
    m_LoadCriterion__loadType->setUpperBound(1);
    m_LoadCriterion__loadType->setTransient(false);
    m_LoadCriterion__loadType->setVolatile(false);
    m_LoadCriterion__loadType->setChangeable(true);
    m_LoadCriterion__loadType->setUnsettable(false);
    m_LoadCriterion__loadType->setID(false);
    m_LoadCriterion__loadType->setUnique(true);
    m_LoadCriterion__loadType->setDerived(false);
    m_LoadCriterion__loadType->setOrdered(true);
    // Work
    m_WorkEClass->setName("Work");
    m_WorkEClass->setAbstract(false);
    m_WorkEClass->setInterface(false);
    m_Work__sessionId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Work__sessionId->setName("sessionId");
    m_Work__sessionId->setDefaultValueLiteral("" "");
    m_Work__sessionId->setLowerBound(0);
    m_Work__sessionId->setUpperBound(1);
    m_Work__sessionId->setTransient(false);
    m_Work__sessionId->setVolatile(false);
    m_Work__sessionId->setChangeable(true);
    m_Work__sessionId->setUnsettable(false);
    m_Work__sessionId->setID(false);
    m_Work__sessionId->setUnique(true);
    m_Work__sessionId->setDerived(false);
    m_Work__sessionId->setOrdered(true);
    m_Work__applicationId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Work__applicationId->setName("applicationId");
    m_Work__applicationId->setDefaultValueLiteral("" "");
    m_Work__applicationId->setLowerBound(0);
    m_Work__applicationId->setUpperBound(1);
    m_Work__applicationId->setTransient(false);
    m_Work__applicationId->setVolatile(false);
    m_Work__applicationId->setChangeable(true);
    m_Work__applicationId->setUnsettable(false);
    m_Work__applicationId->setID(false);
    m_Work__applicationId->setUnique(true);
    m_Work__applicationId->setDerived(false);
    m_Work__applicationId->setOrdered(true);
    m_Work__subject->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Work__subject->setName("subject");
    m_Work__subject->setDefaultValueLiteral("" "");
    m_Work__subject->setLowerBound(0);
    m_Work__subject->setUpperBound(1);
    m_Work__subject->setTransient(false);
    m_Work__subject->setVolatile(false);
    m_Work__subject->setChangeable(true);
    m_Work__subject->setUnsettable(false);
    m_Work__subject->setID(false);
    m_Work__subject->setUnique(true);
    m_Work__subject->setDerived(false);
    m_Work__subject->setOrdered(true);
    m_Work__priority->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Work__priority->setName("priority");
    m_Work__priority->setDefaultValueLiteral("-1");
    m_Work__priority->setLowerBound(0);
    m_Work__priority->setUpperBound(1);
    m_Work__priority->setTransient(false);
    m_Work__priority->setVolatile(false);
    m_Work__priority->setChangeable(true);
    m_Work__priority->setUnsettable(false);
    m_Work__priority->setID(false);
    m_Work__priority->setUnique(true);
    m_Work__priority->setDerived(false);
    m_Work__priority->setOrdered(true);
    m_Work__status->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Work__status->setName("status");
    m_Work__status->setDefaultValueLiteral("-1");
    m_Work__status->setLowerBound(0);
    m_Work__status->setUpperBound(1);
    m_Work__status->setTransient(false);
    m_Work__status->setVolatile(false);
    m_Work__status->setChangeable(true);
    m_Work__status->setUnsettable(false);
    m_Work__status->setID(false);
    m_Work__status->setUnique(true);
    m_Work__status->setDerived(false);
    m_Work__status->setOrdered(true);
    m_Work__endDate->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Work__endDate->setName("endDate");
    m_Work__endDate->setDefaultValueLiteral("-1");
    m_Work__endDate->setLowerBound(0);
    m_Work__endDate->setUpperBound(1);
    m_Work__endDate->setTransient(false);
    m_Work__endDate->setVolatile(false);
    m_Work__endDate->setChangeable(true);
    m_Work__endDate->setUnsettable(false);
    m_Work__endDate->setID(false);
    m_Work__endDate->setUnique(true);
    m_Work__endDate->setDerived(false);
    m_Work__endDate->setOrdered(true);
    m_Work__owner->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Work__owner->setName("owner");
    m_Work__owner->setDefaultValueLiteral("");
    m_Work__owner->setLowerBound(0);
    m_Work__owner->setUpperBound(1);
    m_Work__owner->setTransient(false);
    m_Work__owner->setVolatile(false);
    m_Work__owner->setChangeable(true);
    m_Work__owner->setUnsettable(false);
    m_Work__owner->setID(false);
    m_Work__owner->setUnique(true);
    m_Work__owner->setDerived(false);
    m_Work__owner->setOrdered(true);
    m_Work__estimatedHour->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Work__estimatedHour->setName("estimatedHour");
    m_Work__estimatedHour->setDefaultValueLiteral("-1");
    m_Work__estimatedHour->setLowerBound(0);
    m_Work__estimatedHour->setUpperBound(1);
    m_Work__estimatedHour->setTransient(false);
    m_Work__estimatedHour->setVolatile(false);
    m_Work__estimatedHour->setChangeable(true);
    m_Work__estimatedHour->setUnsettable(false);
    m_Work__estimatedHour->setID(false);
    m_Work__estimatedHour->setUnique(true);
    m_Work__estimatedHour->setDerived(false);
    m_Work__estimatedHour->setOrdered(true);
    m_Work__doneRatio->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Work__doneRatio->setName("doneRatio");
    m_Work__doneRatio->setDefaultValueLiteral("0");
    m_Work__doneRatio->setLowerBound(0);
    m_Work__doneRatio->setUpperBound(1);
    m_Work__doneRatio->setTransient(false);
    m_Work__doneRatio->setVolatile(false);
    m_Work__doneRatio->setChangeable(true);
    m_Work__doneRatio->setUnsettable(false);
    m_Work__doneRatio->setID(false);
    m_Work__doneRatio->setUnique(true);
    m_Work__doneRatio->setDerived(false);
    m_Work__doneRatio->setOrdered(true);
    m_Work__description->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Work__description->setName("description");
    m_Work__description->setDefaultValueLiteral("");
    m_Work__description->setLowerBound(0);
    m_Work__description->setUpperBound(1);
    m_Work__description->setTransient(false);
    m_Work__description->setVolatile(false);
    m_Work__description->setChangeable(true);
    m_Work__description->setUnsettable(false);
    m_Work__description->setID(false);
    m_Work__description->setUnique(true);
    m_Work__description->setDerived(false);
    m_Work__description->setOrdered(true);
    m_Work__dateCreated->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Work__dateCreated->setName("dateCreated");
    m_Work__dateCreated->setDefaultValueLiteral("-1");
    m_Work__dateCreated->setLowerBound(0);
    m_Work__dateCreated->setUpperBound(1);
    m_Work__dateCreated->setTransient(false);
    m_Work__dateCreated->setVolatile(false);
    m_Work__dateCreated->setChangeable(true);
    m_Work__dateCreated->setUnsettable(false);
    m_Work__dateCreated->setID(false);
    m_Work__dateCreated->setUnique(true);
    m_Work__dateCreated->setDerived(false);
    m_Work__dateCreated->setOrdered(true);
    m_Work__dateEnded->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Work__dateEnded->setName("dateEnded");
    m_Work__dateEnded->setDefaultValueLiteral("-1");
    m_Work__dateEnded->setLowerBound(0);
    m_Work__dateEnded->setUpperBound(1);
    m_Work__dateEnded->setTransient(false);
    m_Work__dateEnded->setVolatile(false);
    m_Work__dateEnded->setChangeable(true);
    m_Work__dateEnded->setUnsettable(false);
    m_Work__dateEnded->setID(false);
    m_Work__dateEnded->setUnique(true);
    m_Work__dateEnded->setDerived(false);
    m_Work__dateEnded->setOrdered(true);
    m_Work__dateStarted->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Work__dateStarted->setName("dateStarted");
    m_Work__dateStarted->setDefaultValueLiteral("-1");
    m_Work__dateStarted->setLowerBound(0);
    m_Work__dateStarted->setUpperBound(1);
    m_Work__dateStarted->setTransient(false);
    m_Work__dateStarted->setVolatile(false);
    m_Work__dateStarted->setChangeable(true);
    m_Work__dateStarted->setUnsettable(false);
    m_Work__dateStarted->setID(false);
    m_Work__dateStarted->setUnique(true);
    m_Work__dateStarted->setDerived(false);
    m_Work__dateStarted->setOrdered(true);
    m_Work__lastUpdated->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Work__lastUpdated->setName("lastUpdated");
    m_Work__lastUpdated->setDefaultValueLiteral("-1");
    m_Work__lastUpdated->setLowerBound(0);
    m_Work__lastUpdated->setUpperBound(1);
    m_Work__lastUpdated->setTransient(false);
    m_Work__lastUpdated->setVolatile(false);
    m_Work__lastUpdated->setChangeable(true);
    m_Work__lastUpdated->setUnsettable(false);
    m_Work__lastUpdated->setID(false);
    m_Work__lastUpdated->setUnique(true);
    m_Work__lastUpdated->setDerived(false);
    m_Work__lastUpdated->setOrdered(true);
    m_Work__workId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Work__workId->setName("workId");
    m_Work__workId->setDefaultValueLiteral("");
    m_Work__workId->setLowerBound(0);
    m_Work__workId->setUpperBound(1);
    m_Work__workId->setTransient(false);
    m_Work__workId->setVolatile(false);
    m_Work__workId->setChangeable(true);
    m_Work__workId->setUnsettable(false);
    m_Work__workId->setID(false);
    m_Work__workId->setUnique(true);
    m_Work__workId->setDerived(false);
    m_Work__workId->setOrdered(true);
    m_Work__projectId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Work__projectId->setName("projectId");
    m_Work__projectId->setDefaultValueLiteral("" "");
    m_Work__projectId->setLowerBound(0);
    m_Work__projectId->setUpperBound(1);
    m_Work__projectId->setTransient(false);
    m_Work__projectId->setVolatile(false);
    m_Work__projectId->setChangeable(true);
    m_Work__projectId->setUnsettable(false);
    m_Work__projectId->setID(false);
    m_Work__projectId->setUnique(true);
    m_Work__projectId->setDerived(false);
    m_Work__projectId->setOrdered(true);
    m_Work__submitDate->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Work__submitDate->setName("submitDate");
    m_Work__submitDate->setDefaultValueLiteral("0");
    m_Work__submitDate->setLowerBound(0);
    m_Work__submitDate->setUpperBound(1);
    m_Work__submitDate->setTransient(false);
    m_Work__submitDate->setVolatile(false);
    m_Work__submitDate->setChangeable(true);
    m_Work__submitDate->setUnsettable(false);
    m_Work__submitDate->setID(false);
    m_Work__submitDate->setUnique(true);
    m_Work__submitDate->setDerived(false);
    m_Work__submitDate->setOrdered(true);
    m_Work__machineId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Work__machineId->setName("machineId");
    m_Work__machineId->setDefaultValueLiteral("" "");
    m_Work__machineId->setLowerBound(0);
    m_Work__machineId->setUpperBound(1);
    m_Work__machineId->setTransient(false);
    m_Work__machineId->setVolatile(false);
    m_Work__machineId->setChangeable(true);
    m_Work__machineId->setUnsettable(false);
    m_Work__machineId->setID(false);
    m_Work__machineId->setUnique(true);
    m_Work__machineId->setDerived(false);
    m_Work__machineId->setOrdered(true);
    m_Work__nbCPU->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Work__nbCPU->setName("nbCPU");
    m_Work__nbCPU->setDefaultValueLiteral("-1");
    m_Work__nbCPU->setLowerBound(0);
    m_Work__nbCPU->setUpperBound(1);
    m_Work__nbCPU->setTransient(false);
    m_Work__nbCPU->setVolatile(false);
    m_Work__nbCPU->setChangeable(true);
    m_Work__nbCPU->setUnsettable(false);
    m_Work__nbCPU->setID(false);
    m_Work__nbCPU->setUnique(true);
    m_Work__nbCPU->setDerived(false);
    m_Work__nbCPU->setOrdered(true);
    m_Work__dueDate->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Work__dueDate->setName("dueDate");
    m_Work__dueDate->setDefaultValueLiteral("-1");
    m_Work__dueDate->setLowerBound(0);
    m_Work__dueDate->setUpperBound(1);
    m_Work__dueDate->setTransient(false);
    m_Work__dueDate->setVolatile(false);
    m_Work__dueDate->setChangeable(true);
    m_Work__dueDate->setUnsettable(false);
    m_Work__dueDate->setID(false);
    m_Work__dueDate->setUnique(true);
    m_Work__dueDate->setDerived(false);
    m_Work__dueDate->setOrdered(true);
    // AddWorkOptions
    m_AddWorkOptionsEClass->setName("AddWorkOptions");
    m_AddWorkOptionsEClass->setAbstract(false);
    m_AddWorkOptionsEClass->setInterface(false);
    m_AddWorkOptions__applicationId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_AddWorkOptions__applicationId->setName("applicationId");
    m_AddWorkOptions__applicationId->setDefaultValueLiteral("" "");
    m_AddWorkOptions__applicationId->setLowerBound(0);
    m_AddWorkOptions__applicationId->setUpperBound(1);
    m_AddWorkOptions__applicationId->setTransient(false);
    m_AddWorkOptions__applicationId->setVolatile(false);
    m_AddWorkOptions__applicationId->setChangeable(true);
    m_AddWorkOptions__applicationId->setUnsettable(false);
    m_AddWorkOptions__applicationId->setID(false);
    m_AddWorkOptions__applicationId->setUnique(true);
    m_AddWorkOptions__applicationId->setDerived(false);
    m_AddWorkOptions__applicationId->setOrdered(true);
    m_AddWorkOptions__subject->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_AddWorkOptions__subject->setName("subject");
    m_AddWorkOptions__subject->setDefaultValueLiteral("" "");
    m_AddWorkOptions__subject->setLowerBound(0);
    m_AddWorkOptions__subject->setUpperBound(1);
    m_AddWorkOptions__subject->setTransient(false);
    m_AddWorkOptions__subject->setVolatile(false);
    m_AddWorkOptions__subject->setChangeable(true);
    m_AddWorkOptions__subject->setUnsettable(false);
    m_AddWorkOptions__subject->setID(false);
    m_AddWorkOptions__subject->setUnique(true);
    m_AddWorkOptions__subject->setDerived(false);
    m_AddWorkOptions__subject->setOrdered(true);
    m_AddWorkOptions__priority->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_AddWorkOptions__priority->setName("priority");
    m_AddWorkOptions__priority->setDefaultValueLiteral("-1");
    m_AddWorkOptions__priority->setLowerBound(0);
    m_AddWorkOptions__priority->setUpperBound(1);
    m_AddWorkOptions__priority->setTransient(false);
    m_AddWorkOptions__priority->setVolatile(false);
    m_AddWorkOptions__priority->setChangeable(true);
    m_AddWorkOptions__priority->setUnsettable(false);
    m_AddWorkOptions__priority->setID(false);
    m_AddWorkOptions__priority->setUnique(true);
    m_AddWorkOptions__priority->setDerived(false);
    m_AddWorkOptions__priority->setOrdered(true);
    m_AddWorkOptions__owner->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_AddWorkOptions__owner->setName("owner");
    m_AddWorkOptions__owner->setDefaultValueLiteral("");
    m_AddWorkOptions__owner->setLowerBound(0);
    m_AddWorkOptions__owner->setUpperBound(1);
    m_AddWorkOptions__owner->setTransient(false);
    m_AddWorkOptions__owner->setVolatile(false);
    m_AddWorkOptions__owner->setChangeable(true);
    m_AddWorkOptions__owner->setUnsettable(false);
    m_AddWorkOptions__owner->setID(false);
    m_AddWorkOptions__owner->setUnique(true);
    m_AddWorkOptions__owner->setDerived(false);
    m_AddWorkOptions__owner->setOrdered(true);
    m_AddWorkOptions__estimatedHour->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_AddWorkOptions__estimatedHour->setName("estimatedHour");
    m_AddWorkOptions__estimatedHour->setDefaultValueLiteral("-1");
    m_AddWorkOptions__estimatedHour->setLowerBound(0);
    m_AddWorkOptions__estimatedHour->setUpperBound(1);
    m_AddWorkOptions__estimatedHour->setTransient(false);
    m_AddWorkOptions__estimatedHour->setVolatile(false);
    m_AddWorkOptions__estimatedHour->setChangeable(true);
    m_AddWorkOptions__estimatedHour->setUnsettable(false);
    m_AddWorkOptions__estimatedHour->setID(false);
    m_AddWorkOptions__estimatedHour->setUnique(true);
    m_AddWorkOptions__estimatedHour->setDerived(false);
    m_AddWorkOptions__estimatedHour->setOrdered(true);
    m_AddWorkOptions__description->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_AddWorkOptions__description->setName("description");
    m_AddWorkOptions__description->setDefaultValueLiteral("");
    m_AddWorkOptions__description->setLowerBound(0);
    m_AddWorkOptions__description->setUpperBound(1);
    m_AddWorkOptions__description->setTransient(false);
    m_AddWorkOptions__description->setVolatile(false);
    m_AddWorkOptions__description->setChangeable(true);
    m_AddWorkOptions__description->setUnsettable(false);
    m_AddWorkOptions__description->setID(false);
    m_AddWorkOptions__description->setUnique(true);
    m_AddWorkOptions__description->setDerived(false);
    m_AddWorkOptions__description->setOrdered(true);
    m_AddWorkOptions__projectId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_AddWorkOptions__projectId->setName("projectId");
    m_AddWorkOptions__projectId->setDefaultValueLiteral("" "");
    m_AddWorkOptions__projectId->setLowerBound(0);
    m_AddWorkOptions__projectId->setUpperBound(1);
    m_AddWorkOptions__projectId->setTransient(false);
    m_AddWorkOptions__projectId->setVolatile(false);
    m_AddWorkOptions__projectId->setChangeable(true);
    m_AddWorkOptions__projectId->setUnsettable(false);
    m_AddWorkOptions__projectId->setID(false);
    m_AddWorkOptions__projectId->setUnique(true);
    m_AddWorkOptions__projectId->setDerived(false);
    m_AddWorkOptions__projectId->setOrdered(true);
    m_AddWorkOptions__machineId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_AddWorkOptions__machineId->setName("machineId");
    m_AddWorkOptions__machineId->setDefaultValueLiteral("" "");
    m_AddWorkOptions__machineId->setLowerBound(0);
    m_AddWorkOptions__machineId->setUpperBound(1);
    m_AddWorkOptions__machineId->setTransient(false);
    m_AddWorkOptions__machineId->setVolatile(false);
    m_AddWorkOptions__machineId->setChangeable(true);
    m_AddWorkOptions__machineId->setUnsettable(false);
    m_AddWorkOptions__machineId->setID(false);
    m_AddWorkOptions__machineId->setUnique(true);
    m_AddWorkOptions__machineId->setDerived(false);
    m_AddWorkOptions__machineId->setOrdered(true);
    m_AddWorkOptions__nbCPU->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_AddWorkOptions__nbCPU->setName("nbCPU");
    m_AddWorkOptions__nbCPU->setDefaultValueLiteral("-1");
    m_AddWorkOptions__nbCPU->setLowerBound(0);
    m_AddWorkOptions__nbCPU->setUpperBound(1);
    m_AddWorkOptions__nbCPU->setTransient(false);
    m_AddWorkOptions__nbCPU->setVolatile(false);
    m_AddWorkOptions__nbCPU->setChangeable(true);
    m_AddWorkOptions__nbCPU->setUnsettable(false);
    m_AddWorkOptions__nbCPU->setID(false);
    m_AddWorkOptions__nbCPU->setUnique(true);
    m_AddWorkOptions__nbCPU->setDerived(false);
    m_AddWorkOptions__nbCPU->setOrdered(true);
    // CancelOptions
    m_CancelOptionsEClass->setName("CancelOptions");
    m_CancelOptionsEClass->setAbstract(false);
    m_CancelOptionsEClass->setInterface(false);
    m_CancelOptions__machineId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_CancelOptions__machineId->setName("machineId");
    m_CancelOptions__machineId->setDefaultValueLiteral("" "");
    m_CancelOptions__machineId->setLowerBound(0);
    m_CancelOptions__machineId->setUpperBound(1);
    m_CancelOptions__machineId->setTransient(false);
    m_CancelOptions__machineId->setVolatile(false);
    m_CancelOptions__machineId->setChangeable(true);
    m_CancelOptions__machineId->setUnsettable(false);
    m_CancelOptions__machineId->setID(false);
    m_CancelOptions__machineId->setUnique(true);
    m_CancelOptions__machineId->setDerived(false);
    m_CancelOptions__machineId->setOrdered(true);
    m_CancelOptions__user->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_CancelOptions__user->setName("user");
    m_CancelOptions__user->setDefaultValueLiteral("");
    m_CancelOptions__user->setLowerBound(0);
    m_CancelOptions__user->setUpperBound(1);
    m_CancelOptions__user->setTransient(false);
    m_CancelOptions__user->setVolatile(false);
    m_CancelOptions__user->setChangeable(true);
    m_CancelOptions__user->setUnsettable(false);
    m_CancelOptions__user->setID(false);
    m_CancelOptions__user->setUnique(true);
    m_CancelOptions__user->setDerived(false);
    m_CancelOptions__user->setOrdered(true);
    m_CancelOptions__jobId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_CancelOptions__jobId->setName("jobId");
    m_CancelOptions__jobId->setDefaultValueLiteral("");
    m_CancelOptions__jobId->setLowerBound(0);
    m_CancelOptions__jobId->setUpperBound(1);
    m_CancelOptions__jobId->setTransient(false);
    m_CancelOptions__jobId->setVolatile(false);
    m_CancelOptions__jobId->setChangeable(true);
    m_CancelOptions__jobId->setUnsettable(false);
    m_CancelOptions__jobId->setID(false);
    m_CancelOptions__jobId->setUnique(true);
    m_CancelOptions__jobId->setDerived(false);
    m_CancelOptions__jobId->setOrdered(true);
    // JobOutputOptions
    m_JobOutputOptionsEClass->setName("JobOutputOptions");
    m_JobOutputOptionsEClass->setAbstract(false);
    m_JobOutputOptionsEClass->setInterface(false);
    m_JobOutputOptions__machineId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_JobOutputOptions__machineId->setName("machineId");
    m_JobOutputOptions__machineId->setDefaultValueLiteral("");
    m_JobOutputOptions__machineId->setLowerBound(0);
    m_JobOutputOptions__machineId->setUpperBound(1);
    m_JobOutputOptions__machineId->setTransient(false);
    m_JobOutputOptions__machineId->setVolatile(false);
    m_JobOutputOptions__machineId->setChangeable(true);
    m_JobOutputOptions__machineId->setUnsettable(false);
    m_JobOutputOptions__machineId->setID(false);
    m_JobOutputOptions__machineId->setUnique(true);
    m_JobOutputOptions__machineId->setDerived(false);
    m_JobOutputOptions__machineId->setOrdered(true);
    m_JobOutputOptions__outputDir->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_JobOutputOptions__outputDir->setName("outputDir");
    m_JobOutputOptions__outputDir->setDefaultValueLiteral("");
    m_JobOutputOptions__outputDir->setLowerBound(0);
    m_JobOutputOptions__outputDir->setUpperBound(1);
    m_JobOutputOptions__outputDir->setTransient(false);
    m_JobOutputOptions__outputDir->setVolatile(false);
    m_JobOutputOptions__outputDir->setChangeable(true);
    m_JobOutputOptions__outputDir->setUnsettable(false);
    m_JobOutputOptions__outputDir->setID(false);
    m_JobOutputOptions__outputDir->setUnique(true);
    m_JobOutputOptions__outputDir->setDerived(false);
    m_JobOutputOptions__outputDir->setOrdered(true);
    m_JobOutputOptions__days->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_JobOutputOptions__days->setName("days");
    m_JobOutputOptions__days->setDefaultValueLiteral("-1");
    m_JobOutputOptions__days->setLowerBound(0);
    m_JobOutputOptions__days->setUpperBound(1);
    m_JobOutputOptions__days->setTransient(false);
    m_JobOutputOptions__days->setVolatile(false);
    m_JobOutputOptions__days->setChangeable(true);
    m_JobOutputOptions__days->setUnsettable(false);
    m_JobOutputOptions__days->setID(false);
    m_JobOutputOptions__days->setUnique(true);
    m_JobOutputOptions__days->setDerived(false);
    m_JobOutputOptions__days->setOrdered(true);

    // TODO: Initialize data types


    // JobPriority
    m_JobPriorityEEnum->setName("JobPriority");
    m_JobPriorityEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // UNDEFINED
        _el->setName("UNDEFINED");
        _el->setValue(0);
        _el->setLiteral("UNDEFINED");
        _el->setEEnum(m_JobPriorityEEnum);
        m_JobPriorityEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // VERY_LOW
        _el->setName("VERY_LOW");
        _el->setValue(1);
        _el->setLiteral("VERY_LOW");
        _el->setEEnum(m_JobPriorityEEnum);
        m_JobPriorityEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // LOW
        _el->setName("LOW");
        _el->setValue(2);
        _el->setLiteral("LOW");
        _el->setEEnum(m_JobPriorityEEnum);
        m_JobPriorityEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // NORMAL
        _el->setName("NORMAL");
        _el->setValue(3);
        _el->setLiteral("NORMAL");
        _el->setEEnum(m_JobPriorityEEnum);
        m_JobPriorityEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // HIGH
        _el->setName("HIGH");
        _el->setValue(4);
        _el->setLiteral("HIGH");
        _el->setEEnum(m_JobPriorityEEnum);
        m_JobPriorityEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // VERY_HIGH
        _el->setName("VERY_HIGH");
        _el->setValue(5);
        _el->setLiteral("VERY_HIGH");
        _el->setEEnum(m_JobPriorityEEnum);
        m_JobPriorityEEnum->getELiterals().push_back(_el);
    }

    // JobStatus
    m_JobStatusEEnum->setName("JobStatus");
    m_JobStatusEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // UNDEFINED
        _el->setName("UNDEFINED");
        _el->setValue(0);
        _el->setLiteral("UNDEFINED");
        _el->setEEnum(m_JobStatusEEnum);
        m_JobStatusEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // SUBMITTED
        _el->setName("SUBMITTED");
        _el->setValue(1);
        _el->setLiteral("SUBMITTED");
        _el->setEEnum(m_JobStatusEEnum);
        m_JobStatusEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // QUEUED
        _el->setName("QUEUED");
        _el->setValue(2);
        _el->setLiteral("QUEUED");
        _el->setEEnum(m_JobStatusEEnum);
        m_JobStatusEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // WAITING
        _el->setName("WAITING");
        _el->setValue(3);
        _el->setLiteral("WAITING");
        _el->setEEnum(m_JobStatusEEnum);
        m_JobStatusEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // RUNNING
        _el->setName("RUNNING");
        _el->setValue(4);
        _el->setLiteral("RUNNING");
        _el->setEEnum(m_JobStatusEEnum);
        m_JobStatusEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // COMPLETED
        _el->setName("COMPLETED");
        _el->setValue(5);
        _el->setLiteral("COMPLETED");
        _el->setEEnum(m_JobStatusEEnum);
        m_JobStatusEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // CANCELLED
        _el->setName("CANCELLED");
        _el->setValue(6);
        _el->setLiteral("CANCELLED");
        _el->setEEnum(m_JobStatusEEnum);
        m_JobStatusEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // ALREADY_DOWNLOADED
        _el->setName("ALREADY_DOWNLOADED");
        _el->setValue(7);
        _el->setLiteral("ALREADY_DOWNLOADED");
        _el->setEEnum(m_JobStatusEEnum);
        m_JobStatusEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // FAILED
        _el->setName("FAILED");
        _el->setValue(8);
        _el->setLiteral("FAILED");
        _el->setEEnum(m_JobStatusEEnum);
        m_JobStatusEEnum->getELiterals().push_back(_el);
    }

    // QueuePriority
    m_QueuePriorityEEnum->setName("QueuePriority");
    m_QueuePriorityEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // UNDEFINED
        _el->setName("UNDEFINED");
        _el->setValue(0);
        _el->setLiteral("UNDEFINED");
        _el->setEEnum(m_QueuePriorityEEnum);
        m_QueuePriorityEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // VERY_LOW
        _el->setName("VERY_LOW");
        _el->setValue(1);
        _el->setLiteral("VERY_LOW");
        _el->setEEnum(m_QueuePriorityEEnum);
        m_QueuePriorityEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // LOW
        _el->setName("LOW");
        _el->setValue(2);
        _el->setLiteral("LOW");
        _el->setEEnum(m_QueuePriorityEEnum);
        m_QueuePriorityEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // NORMAL
        _el->setName("NORMAL");
        _el->setValue(3);
        _el->setLiteral("NORMAL");
        _el->setEEnum(m_QueuePriorityEEnum);
        m_QueuePriorityEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // HIGH
        _el->setName("HIGH");
        _el->setValue(4);
        _el->setLiteral("HIGH");
        _el->setEEnum(m_QueuePriorityEEnum);
        m_QueuePriorityEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // VERY_HIGH
        _el->setName("VERY_HIGH");
        _el->setValue(5);
        _el->setLiteral("VERY_HIGH");
        _el->setEEnum(m_QueuePriorityEEnum);
        m_QueuePriorityEEnum->getELiterals().push_back(_el);
    }

    // QueueStatus
    m_QueueStatusEEnum->setName("QueueStatus");
    m_QueueStatusEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // NOT_STARTED
        _el->setName("NOT_STARTED");
        _el->setValue(0);
        _el->setLiteral("NOT_STARTED");
        _el->setEEnum(m_QueueStatusEEnum);
        m_QueueStatusEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // STARTED
        _el->setName("STARTED");
        _el->setValue(1);
        _el->setLiteral("STARTED");
        _el->setEEnum(m_QueueStatusEEnum);
        m_QueueStatusEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // RUNNING
        _el->setName("RUNNING");
        _el->setValue(2);
        _el->setLiteral("RUNNING");
        _el->setEEnum(m_QueueStatusEEnum);
        m_QueueStatusEEnum->getELiterals().push_back(_el);
    }

    // LoadType
    m_LoadTypeEEnum->setName("LoadType");
    m_LoadTypeEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // USE_NB_WAITING_JOBS
        _el->setName("USE_NB_WAITING_JOBS");
        _el->setValue(0);
        _el->setLiteral("USE_NB_WAITING_JOBS");
        _el->setEEnum(m_LoadTypeEEnum);
        m_LoadTypeEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // USE_NB_JOBS
        _el->setName("USE_NB_JOBS");
        _el->setValue(1);
        _el->setLiteral("USE_NB_JOBS");
        _el->setEEnum(m_LoadTypeEEnum);
        m_LoadTypeEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // USE_NB_RUNNING_JOBS
        _el->setName("USE_NB_RUNNING_JOBS");
        _el->setValue(2);
        _el->setLiteral("USE_NB_RUNNING_JOBS");
        _el->setEEnum(m_LoadTypeEEnum);
        m_LoadTypeEEnum->getELiterals().push_back(_el);
    }

    _initialize();
}

::ecore::EClass_ptr TMS_DataPackage::getJob()
{
    return m_JobEClass;
}
::ecore::EClass_ptr TMS_DataPackage::getListJobs()
{
    return m_ListJobsEClass;
}
::ecore::EClass_ptr TMS_DataPackage::getSubmitOptions()
{
    return m_SubmitOptionsEClass;
}
::ecore::EClass_ptr TMS_DataPackage::getListJobsOptions()
{
    return m_ListJobsOptionsEClass;
}
::ecore::EEnum_ptr TMS_DataPackage::getJobPriority()
{
    return m_JobPriorityEEnum;
}
::ecore::EEnum_ptr TMS_DataPackage::getJobStatus()
{
    return m_JobStatusEEnum;
}
::ecore::EClass_ptr TMS_DataPackage::getProgressOptions()
{
    return m_ProgressOptionsEClass;
}
::ecore::EClass_ptr TMS_DataPackage::getListProgression()
{
    return m_ListProgressionEClass;
}
::ecore::EClass_ptr TMS_DataPackage::getProgression()
{
    return m_ProgressionEClass;
}
::ecore::EClass_ptr TMS_DataPackage::getListQueues()
{
    return m_ListQueuesEClass;
}
::ecore::EClass_ptr TMS_DataPackage::getQueue()
{
    return m_QueueEClass;
}
::ecore::EEnum_ptr TMS_DataPackage::getQueuePriority()
{
    return m_QueuePriorityEEnum;
}
::ecore::EEnum_ptr TMS_DataPackage::getQueueStatus()
{
    return m_QueueStatusEEnum;
}
::ecore::EClass_ptr TMS_DataPackage::getJobResult()
{
    return m_JobResultEClass;
}
::ecore::EClass_ptr TMS_DataPackage::getListJobResults()
{
    return m_ListJobResultsEClass;
}
::ecore::EClass_ptr TMS_DataPackage::getLoadCriterion()
{
    return m_LoadCriterionEClass;
}
::ecore::EEnum_ptr TMS_DataPackage::getLoadType()
{
    return m_LoadTypeEEnum;
}
::ecore::EClass_ptr TMS_DataPackage::getWork()
{
    return m_WorkEClass;
}
::ecore::EClass_ptr TMS_DataPackage::getAddWorkOptions()
{
    return m_AddWorkOptionsEClass;
}
::ecore::EClass_ptr TMS_DataPackage::getCancelOptions()
{
    return m_CancelOptionsEClass;
}
::ecore::EClass_ptr TMS_DataPackage::getJobOutputOptions()
{
    return m_JobOutputOptionsEClass;
}

::ecore::EAttribute_ptr TMS_DataPackage::getJob__sessionId()
{
    return m_Job__sessionId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__submitMachineId()
{
    return m_Job__submitMachineId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__submitMachineName()
{
    return m_Job__submitMachineName;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__jobId()
{
    return m_Job__jobId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__jobName()
{
    return m_Job__jobName;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__jobPath()
{
    return m_Job__jobPath;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__outputPath()
{
    return m_Job__outputPath;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__errorPath()
{
    return m_Job__errorPath;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__jobPrio()
{
    return m_Job__jobPrio;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__nbCpus()
{
    return m_Job__nbCpus;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__jobWorkingDir()
{
    return m_Job__jobWorkingDir;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__status()
{
    return m_Job__status;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__submitDate()
{
    return m_Job__submitDate;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__endDate()
{
    return m_Job__endDate;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__owner()
{
    return m_Job__owner;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__jobQueue()
{
    return m_Job__jobQueue;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__wallClockLimit()
{
    return m_Job__wallClockLimit;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__groupName()
{
    return m_Job__groupName;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__jobDescription()
{
    return m_Job__jobDescription;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__memLimit()
{
    return m_Job__memLimit;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__nbNodes()
{
    return m_Job__nbNodes;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__nbNodesAndCpuPerNode()
{
    return m_Job__nbNodesAndCpuPerNode;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__batchJobId()
{
    return m_Job__batchJobId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__outputDir()
{
    return m_Job__outputDir;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__workId()
{
    return m_Job__workId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__userId()
{
    return m_Job__userId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__vmId()
{
    return m_Job__vmId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJob__vmIp()
{
    return m_Job__vmIp;
}
::ecore::EAttribute_ptr TMS_DataPackage::getListJobs__nbJobs()
{
    return m_ListJobs__nbJobs;
}
::ecore::EAttribute_ptr TMS_DataPackage::getListJobs__nbRunningJobs()
{
    return m_ListJobs__nbRunningJobs;
}
::ecore::EAttribute_ptr TMS_DataPackage::getListJobs__nbWaitingJobs()
{
    return m_ListJobs__nbWaitingJobs;
}
::ecore::EReference_ptr TMS_DataPackage::getListJobs__jobs()
{
    return m_ListJobs__jobs;
}
::ecore::EAttribute_ptr TMS_DataPackage::getSubmitOptions__name()
{
    return m_SubmitOptions__name;
}
::ecore::EAttribute_ptr TMS_DataPackage::getSubmitOptions__queue()
{
    return m_SubmitOptions__queue;
}
::ecore::EAttribute_ptr TMS_DataPackage::getSubmitOptions__wallTime()
{
    return m_SubmitOptions__wallTime;
}
::ecore::EAttribute_ptr TMS_DataPackage::getSubmitOptions__memory()
{
    return m_SubmitOptions__memory;
}
::ecore::EAttribute_ptr TMS_DataPackage::getSubmitOptions__nbCpu()
{
    return m_SubmitOptions__nbCpu;
}
::ecore::EAttribute_ptr TMS_DataPackage::getSubmitOptions__nbNodesAndCpuPerNode()
{
    return m_SubmitOptions__nbNodesAndCpuPerNode;
}
::ecore::EAttribute_ptr TMS_DataPackage::getSubmitOptions__outputPath()
{
    return m_SubmitOptions__outputPath;
}
::ecore::EAttribute_ptr TMS_DataPackage::getSubmitOptions__errorPath()
{
    return m_SubmitOptions__errorPath;
}
::ecore::EAttribute_ptr TMS_DataPackage::getSubmitOptions__mailNotification()
{
    return m_SubmitOptions__mailNotification;
}
::ecore::EAttribute_ptr TMS_DataPackage::getSubmitOptions__mailNotifyUser()
{
    return m_SubmitOptions__mailNotifyUser;
}
::ecore::EAttribute_ptr TMS_DataPackage::getSubmitOptions__group()
{
    return m_SubmitOptions__group;
}
::ecore::EAttribute_ptr TMS_DataPackage::getSubmitOptions__workingDir()
{
    return m_SubmitOptions__workingDir;
}
::ecore::EAttribute_ptr TMS_DataPackage::getSubmitOptions__cpuTime()
{
    return m_SubmitOptions__cpuTime;
}
::ecore::EAttribute_ptr TMS_DataPackage::getSubmitOptions__selectQueueAutom()
{
    return m_SubmitOptions__selectQueueAutom;
}
::ecore::EReference_ptr TMS_DataPackage::getSubmitOptions__criterion()
{
    return m_SubmitOptions__criterion;
}
::ecore::EAttribute_ptr TMS_DataPackage::getSubmitOptions__fileParams()
{
    return m_SubmitOptions__fileParams;
}
::ecore::EAttribute_ptr TMS_DataPackage::getSubmitOptions__textParams()
{
    return m_SubmitOptions__textParams;
}
::ecore::EAttribute_ptr TMS_DataPackage::getSubmitOptions__workId()
{
    return m_SubmitOptions__workId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getSubmitOptions__specificParams()
{
    return m_SubmitOptions__specificParams;
}
::ecore::EAttribute_ptr TMS_DataPackage::getSubmitOptions__posix()
{
    return m_SubmitOptions__posix;
}
::ecore::EAttribute_ptr TMS_DataPackage::getSubmitOptions__machine()
{
    return m_SubmitOptions__machine;
}
::ecore::EAttribute_ptr TMS_DataPackage::getListJobsOptions__jobId()
{
    return m_ListJobsOptions__jobId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getListJobsOptions__nbCpu()
{
    return m_ListJobsOptions__nbCpu;
}
::ecore::EAttribute_ptr TMS_DataPackage::getListJobsOptions__fromSubmitDate()
{
    return m_ListJobsOptions__fromSubmitDate;
}
::ecore::EAttribute_ptr TMS_DataPackage::getListJobsOptions__toSubmitDate()
{
    return m_ListJobsOptions__toSubmitDate;
}
::ecore::EAttribute_ptr TMS_DataPackage::getListJobsOptions__owner()
{
    return m_ListJobsOptions__owner;
}
::ecore::EAttribute_ptr TMS_DataPackage::getListJobsOptions__status()
{
    return m_ListJobsOptions__status;
}
::ecore::EAttribute_ptr TMS_DataPackage::getListJobsOptions__priority()
{
    return m_ListJobsOptions__priority;
}
::ecore::EAttribute_ptr TMS_DataPackage::getListJobsOptions__queue()
{
    return m_ListJobsOptions__queue;
}
::ecore::EAttribute_ptr TMS_DataPackage::getListJobsOptions__multipleStatus()
{
    return m_ListJobsOptions__multipleStatus;
}
::ecore::EAttribute_ptr TMS_DataPackage::getListJobsOptions__batchJob()
{
    return m_ListJobsOptions__batchJob;
}
::ecore::EAttribute_ptr TMS_DataPackage::getListJobsOptions__workId()
{
    return m_ListJobsOptions__workId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getListJobsOptions__listAll()
{
    return m_ListJobsOptions__listAll;
}
::ecore::EAttribute_ptr TMS_DataPackage::getListJobsOptions__machineId()
{
    return m_ListJobsOptions__machineId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getProgressOptions__jobId()
{
    return m_ProgressOptions__jobId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getProgressOptions__user()
{
    return m_ProgressOptions__user;
}
::ecore::EAttribute_ptr TMS_DataPackage::getProgressOptions__machineId()
{
    return m_ProgressOptions__machineId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getListProgression__nbJobs()
{
    return m_ListProgression__nbJobs;
}
::ecore::EReference_ptr TMS_DataPackage::getListProgression__progress()
{
    return m_ListProgression__progress;
}
::ecore::EAttribute_ptr TMS_DataPackage::getProgression__jobId()
{
    return m_Progression__jobId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getProgression__jobName()
{
    return m_Progression__jobName;
}
::ecore::EAttribute_ptr TMS_DataPackage::getProgression__wallTime()
{
    return m_Progression__wallTime;
}
::ecore::EAttribute_ptr TMS_DataPackage::getProgression__startTime()
{
    return m_Progression__startTime;
}
::ecore::EAttribute_ptr TMS_DataPackage::getProgression__endTime()
{
    return m_Progression__endTime;
}
::ecore::EAttribute_ptr TMS_DataPackage::getProgression__percent()
{
    return m_Progression__percent;
}
::ecore::EAttribute_ptr TMS_DataPackage::getProgression__status()
{
    return m_Progression__status;
}
::ecore::EAttribute_ptr TMS_DataPackage::getListQueues__nbQueues()
{
    return m_ListQueues__nbQueues;
}
::ecore::EReference_ptr TMS_DataPackage::getListQueues__queues()
{
    return m_ListQueues__queues;
}
::ecore::EAttribute_ptr TMS_DataPackage::getQueue__name()
{
    return m_Queue__name;
}
::ecore::EAttribute_ptr TMS_DataPackage::getQueue__maxJobCpu()
{
    return m_Queue__maxJobCpu;
}
::ecore::EAttribute_ptr TMS_DataPackage::getQueue__maxProcCpu()
{
    return m_Queue__maxProcCpu;
}
::ecore::EAttribute_ptr TMS_DataPackage::getQueue__memory()
{
    return m_Queue__memory;
}
::ecore::EAttribute_ptr TMS_DataPackage::getQueue__wallTime()
{
    return m_Queue__wallTime;
}
::ecore::EAttribute_ptr TMS_DataPackage::getQueue__node()
{
    return m_Queue__node;
}
::ecore::EAttribute_ptr TMS_DataPackage::getQueue__nbRunningJobs()
{
    return m_Queue__nbRunningJobs;
}
::ecore::EAttribute_ptr TMS_DataPackage::getQueue__nbJobsInQueue()
{
    return m_Queue__nbJobsInQueue;
}
::ecore::EAttribute_ptr TMS_DataPackage::getQueue__state()
{
    return m_Queue__state;
}
::ecore::EAttribute_ptr TMS_DataPackage::getQueue__priority()
{
    return m_Queue__priority;
}
::ecore::EAttribute_ptr TMS_DataPackage::getQueue__description()
{
    return m_Queue__description;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJobResult__jobId()
{
    return m_JobResult__jobId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJobResult__outputPath()
{
    return m_JobResult__outputPath;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJobResult__errorPath()
{
    return m_JobResult__errorPath;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJobResult__outputDir()
{
    return m_JobResult__outputDir;
}
::ecore::EAttribute_ptr TMS_DataPackage::getListJobResults__nbJobs()
{
    return m_ListJobResults__nbJobs;
}
::ecore::EReference_ptr TMS_DataPackage::getListJobResults__Results()
{
    return m_ListJobResults__Results;
}
::ecore::EAttribute_ptr TMS_DataPackage::getLoadCriterion__loadType()
{
    return m_LoadCriterion__loadType;
}
::ecore::EAttribute_ptr TMS_DataPackage::getWork__sessionId()
{
    return m_Work__sessionId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getWork__applicationId()
{
    return m_Work__applicationId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getWork__subject()
{
    return m_Work__subject;
}
::ecore::EAttribute_ptr TMS_DataPackage::getWork__priority()
{
    return m_Work__priority;
}
::ecore::EAttribute_ptr TMS_DataPackage::getWork__status()
{
    return m_Work__status;
}
::ecore::EAttribute_ptr TMS_DataPackage::getWork__endDate()
{
    return m_Work__endDate;
}
::ecore::EAttribute_ptr TMS_DataPackage::getWork__owner()
{
    return m_Work__owner;
}
::ecore::EAttribute_ptr TMS_DataPackage::getWork__estimatedHour()
{
    return m_Work__estimatedHour;
}
::ecore::EAttribute_ptr TMS_DataPackage::getWork__doneRatio()
{
    return m_Work__doneRatio;
}
::ecore::EAttribute_ptr TMS_DataPackage::getWork__description()
{
    return m_Work__description;
}
::ecore::EAttribute_ptr TMS_DataPackage::getWork__dateCreated()
{
    return m_Work__dateCreated;
}
::ecore::EAttribute_ptr TMS_DataPackage::getWork__dateEnded()
{
    return m_Work__dateEnded;
}
::ecore::EAttribute_ptr TMS_DataPackage::getWork__dateStarted()
{
    return m_Work__dateStarted;
}
::ecore::EAttribute_ptr TMS_DataPackage::getWork__lastUpdated()
{
    return m_Work__lastUpdated;
}
::ecore::EAttribute_ptr TMS_DataPackage::getWork__workId()
{
    return m_Work__workId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getWork__projectId()
{
    return m_Work__projectId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getWork__submitDate()
{
    return m_Work__submitDate;
}
::ecore::EAttribute_ptr TMS_DataPackage::getWork__machineId()
{
    return m_Work__machineId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getWork__nbCPU()
{
    return m_Work__nbCPU;
}
::ecore::EAttribute_ptr TMS_DataPackage::getWork__dueDate()
{
    return m_Work__dueDate;
}
::ecore::EAttribute_ptr TMS_DataPackage::getAddWorkOptions__applicationId()
{
    return m_AddWorkOptions__applicationId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getAddWorkOptions__subject()
{
    return m_AddWorkOptions__subject;
}
::ecore::EAttribute_ptr TMS_DataPackage::getAddWorkOptions__priority()
{
    return m_AddWorkOptions__priority;
}
::ecore::EAttribute_ptr TMS_DataPackage::getAddWorkOptions__owner()
{
    return m_AddWorkOptions__owner;
}
::ecore::EAttribute_ptr TMS_DataPackage::getAddWorkOptions__estimatedHour()
{
    return m_AddWorkOptions__estimatedHour;
}
::ecore::EAttribute_ptr TMS_DataPackage::getAddWorkOptions__description()
{
    return m_AddWorkOptions__description;
}
::ecore::EAttribute_ptr TMS_DataPackage::getAddWorkOptions__projectId()
{
    return m_AddWorkOptions__projectId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getAddWorkOptions__machineId()
{
    return m_AddWorkOptions__machineId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getAddWorkOptions__nbCPU()
{
    return m_AddWorkOptions__nbCPU;
}
::ecore::EAttribute_ptr TMS_DataPackage::getCancelOptions__machineId()
{
    return m_CancelOptions__machineId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getCancelOptions__user()
{
    return m_CancelOptions__user;
}
::ecore::EAttribute_ptr TMS_DataPackage::getCancelOptions__jobId()
{
    return m_CancelOptions__jobId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJobOutputOptions__machineId()
{
    return m_JobOutputOptions__machineId;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJobOutputOptions__outputDir()
{
    return m_JobOutputOptions__outputDir;
}
::ecore::EAttribute_ptr TMS_DataPackage::getJobOutputOptions__days()
{
    return m_JobOutputOptions__days;
}

