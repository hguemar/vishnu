// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * TMS_Data/TMS_DataPackage.hpp
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
 * \file TMS_DataPackage.hpp
 * \brief The TMS_DataPackage class
 * \author Generated file
 * \date 31/03/2011
 */

#ifndef _TMS_DATAPACKAGE_HPP
#define _TMS_DATAPACKAGE_HPP

#include <ecore/EPackage.hpp>
#include <TMS_Data_forward.hpp>

namespace TMS_Data
{
    /**
     * \class TMS_DataPackage
     * \brief The package class (reflective API) for generated model TMS_Data
     */
    class TMS_DataPackage: public virtual ::ecore::EPackage
    {
    public:

        /**
         * \brief To get the instance of the singleton
         * \return Pointer to the instance
         */
        static TMS_DataPackage_ptr _instance();

        // IDs for classifiers

        /**
         * \brief Constant for AddWorkOptions class
         */
        static const int ADDWORKOPTIONS = 0;

        /**
         * \brief Constant for CancelOptions class
         */
        static const int CANCELOPTIONS = 1;

        /**
         * \brief Constant for Job class
         */
        static const int JOB = 2;

        /**
         * \brief Constant for JobOutputOptions class
         */
        static const int JOBOUTPUTOPTIONS = 3;

        /**
         * \brief Constant for JobPriority class
         */
        static const int JOBPRIORITY = 4;

        /**
         * \brief Constant for JobResult class
         */
        static const int JOBRESULT = 5;

        /**
         * \brief Constant for JobStatus class
         */
        static const int JOBSTATUS = 6;

        /**
         * \brief Constant for ListJobResults class
         */
        static const int LISTJOBRESULTS = 7;

        /**
         * \brief Constant for ListJobs class
         */
        static const int LISTJOBS = 8;

        /**
         * \brief Constant for ListJobsOptions class
         */
        static const int LISTJOBSOPTIONS = 9;

        /**
         * \brief Constant for ListProgression class
         */
        static const int LISTPROGRESSION = 10;

        /**
         * \brief Constant for ListQueues class
         */
        static const int LISTQUEUES = 11;

        /**
         * \brief Constant for LoadCriterion class
         */
        static const int LOADCRITERION = 12;

        /**
         * \brief Constant for LoadType class
         */
        static const int LOADTYPE = 13;

        /**
         * \brief Constant for Progression class
         */
        static const int PROGRESSION = 14;

        /**
         * \brief Constant for ProgressOptions class
         */
        static const int PROGRESSOPTIONS = 15;

        /**
         * \brief Constant for Queue class
         */
        static const int QUEUE = 16;

        /**
         * \brief Constant for QueuePriority class
         */
        static const int QUEUEPRIORITY = 17;

        /**
         * \brief Constant for QueueStatus class
         */
        static const int QUEUESTATUS = 18;

        /**
         * \brief Constant for SubmitOptions class
         */
        static const int SUBMITOPTIONS = 19;

        /**
         * \brief Constant for Work class
         */
        static const int WORK = 20;

        /**
         * \brief Constant for JOB__SESSIONID feature
         */
        static const int JOB__SESSIONID = 0;

        /**
         * \brief Constant for JOB__SUBMITMACHINEID feature
         */
        static const int JOB__SUBMITMACHINEID = 1;

        /**
         * \brief Constant for JOB__SUBMITMACHINENAME feature
         */
        static const int JOB__SUBMITMACHINENAME = 2;

        /**
         * \brief Constant for JOB__JOBID feature
         */
        static const int JOB__JOBID = 3;

        /**
         * \brief Constant for JOB__JOBNAME feature
         */
        static const int JOB__JOBNAME = 4;

        /**
         * \brief Constant for JOB__JOBPATH feature
         */
        static const int JOB__JOBPATH = 5;

        /**
         * \brief Constant for JOB__OUTPUTPATH feature
         */
        static const int JOB__OUTPUTPATH = 6;

        /**
         * \brief Constant for JOB__ERRORPATH feature
         */
        static const int JOB__ERRORPATH = 7;

        /**
         * \brief Constant for JOB__JOBPRIO feature
         */
        static const int JOB__JOBPRIO = 8;

        /**
         * \brief Constant for JOB__NBCPUS feature
         */
        static const int JOB__NBCPUS = 9;

        /**
         * \brief Constant for JOB__JOBWORKINGDIR feature
         */
        static const int JOB__JOBWORKINGDIR = 10;

        /**
         * \brief Constant for JOB__STATUS feature
         */
        static const int JOB__STATUS = 11;

        /**
         * \brief Constant for JOB__SUBMITDATE feature
         */
        static const int JOB__SUBMITDATE = 12;

        /**
         * \brief Constant for JOB__ENDDATE feature
         */
        static const int JOB__ENDDATE = 13;

        /**
         * \brief Constant for JOB__OWNER feature
         */
        static const int JOB__OWNER = 14;

        /**
         * \brief Constant for JOB__JOBQUEUE feature
         */
        static const int JOB__JOBQUEUE = 15;

        /**
         * \brief Constant for JOB__WALLCLOCKLIMIT feature
         */
        static const int JOB__WALLCLOCKLIMIT = 16;

        /**
         * \brief Constant for JOB__GROUPNAME feature
         */
        static const int JOB__GROUPNAME = 17;

        /**
         * \brief Constant for JOB__JOBDESCRIPTION feature
         */
        static const int JOB__JOBDESCRIPTION = 18;

        /**
         * \brief Constant for JOB__MEMLIMIT feature
         */
        static const int JOB__MEMLIMIT = 19;

        /**
         * \brief Constant for JOB__NBNODES feature
         */
        static const int JOB__NBNODES = 20;

        /**
         * \brief Constant for JOB__NBNODESANDCPUPERNODE feature
         */
        static const int JOB__NBNODESANDCPUPERNODE = 21;

        /**
         * \brief Constant for JOB__BATCHJOBID feature
         */
        static const int JOB__BATCHJOBID = 22;

        /**
         * \brief Constant for JOB__OUTPUTDIR feature
         */
        static const int JOB__OUTPUTDIR = 23;

        /**
         * \brief Constant for JOB__WORKID feature
         */
        static const int JOB__WORKID = 24;

        /**
         * \brief Constant for JOB__USERID feature
         */
        static const int JOB__USERID = 25;

        /**
         * \brief Constant for JOB__VMID feature
         */
        static const int JOB__VMID = 26;

        /**
         * \brief Constant for JOB__VMIP feature
         */
        static const int JOB__VMIP = 27;

        /**
         * \brief Constant for LISTJOBS__NBJOBS feature
         */
        static const int LISTJOBS__NBJOBS = 28;

        /**
         * \brief Constant for LISTJOBS__NBRUNNINGJOBS feature
         */
        static const int LISTJOBS__NBRUNNINGJOBS = 29;

        /**
         * \brief Constant for LISTJOBS__NBWAITINGJOBS feature
         */
        static const int LISTJOBS__NBWAITINGJOBS = 30;

        /**
         * \brief Constant for LISTJOBS__JOBS feature
         */
        static const int LISTJOBS__JOBS = 31;

        /**
         * \brief Constant for SUBMITOPTIONS__NAME feature
         */
        static const int SUBMITOPTIONS__NAME = 32;

        /**
         * \brief Constant for SUBMITOPTIONS__QUEUE feature
         */
        static const int SUBMITOPTIONS__QUEUE = 33;

        /**
         * \brief Constant for SUBMITOPTIONS__WALLTIME feature
         */
        static const int SUBMITOPTIONS__WALLTIME = 34;

        /**
         * \brief Constant for SUBMITOPTIONS__MEMORY feature
         */
        static const int SUBMITOPTIONS__MEMORY = 35;

        /**
         * \brief Constant for SUBMITOPTIONS__NBCPU feature
         */
        static const int SUBMITOPTIONS__NBCPU = 36;

        /**
         * \brief Constant for SUBMITOPTIONS__NBNODESANDCPUPERNODE feature
         */
        static const int SUBMITOPTIONS__NBNODESANDCPUPERNODE = 37;

        /**
         * \brief Constant for SUBMITOPTIONS__OUTPUTPATH feature
         */
        static const int SUBMITOPTIONS__OUTPUTPATH = 38;

        /**
         * \brief Constant for SUBMITOPTIONS__ERRORPATH feature
         */
        static const int SUBMITOPTIONS__ERRORPATH = 39;

        /**
         * \brief Constant for SUBMITOPTIONS__MAILNOTIFICATION feature
         */
        static const int SUBMITOPTIONS__MAILNOTIFICATION = 40;

        /**
         * \brief Constant for SUBMITOPTIONS__MAILNOTIFYUSER feature
         */
        static const int SUBMITOPTIONS__MAILNOTIFYUSER = 41;

        /**
         * \brief Constant for SUBMITOPTIONS__GROUP feature
         */
        static const int SUBMITOPTIONS__GROUP = 42;

        /**
         * \brief Constant for SUBMITOPTIONS__WORKINGDIR feature
         */
        static const int SUBMITOPTIONS__WORKINGDIR = 43;

        /**
         * \brief Constant for SUBMITOPTIONS__CPUTIME feature
         */
        static const int SUBMITOPTIONS__CPUTIME = 44;

        /**
         * \brief Constant for SUBMITOPTIONS__SELECTQUEUEAUTOM feature
         */
        static const int SUBMITOPTIONS__SELECTQUEUEAUTOM = 45;

        /**
         * \brief Constant for SUBMITOPTIONS__CRITERION feature
         */
        static const int SUBMITOPTIONS__CRITERION = 46;

        /**
         * \brief Constant for SUBMITOPTIONS__FILEPARAMS feature
         */
        static const int SUBMITOPTIONS__FILEPARAMS = 47;

        /**
         * \brief Constant for SUBMITOPTIONS__TEXTPARAMS feature
         */
        static const int SUBMITOPTIONS__TEXTPARAMS = 48;

        /**
         * \brief Constant for SUBMITOPTIONS__WORKID feature
         */
        static const int SUBMITOPTIONS__WORKID = 49;

        /**
         * \brief Constant for SUBMITOPTIONS__SPECIFICPARAMS feature
         */
        static const int SUBMITOPTIONS__SPECIFICPARAMS = 50;

        /**
         * \brief Constant for SUBMITOPTIONS__POSIX feature
         */
        static const int SUBMITOPTIONS__POSIX = 51;

        /**
         * \brief Constant for SUBMITOPTIONS__MACHINE feature
         */
        static const int SUBMITOPTIONS__MACHINE = 52;

        /**
         * \brief Constant for LISTJOBSOPTIONS__JOBID feature
         */
        static const int LISTJOBSOPTIONS__JOBID = 53;

        /**
         * \brief Constant for LISTJOBSOPTIONS__NBCPU feature
         */
        static const int LISTJOBSOPTIONS__NBCPU = 54;

        /**
         * \brief Constant for LISTJOBSOPTIONS__FROMSUBMITDATE feature
         */
        static const int LISTJOBSOPTIONS__FROMSUBMITDATE = 55;

        /**
         * \brief Constant for LISTJOBSOPTIONS__TOSUBMITDATE feature
         */
        static const int LISTJOBSOPTIONS__TOSUBMITDATE = 56;

        /**
         * \brief Constant for LISTJOBSOPTIONS__OWNER feature
         */
        static const int LISTJOBSOPTIONS__OWNER = 57;

        /**
         * \brief Constant for LISTJOBSOPTIONS__STATUS feature
         */
        static const int LISTJOBSOPTIONS__STATUS = 58;

        /**
         * \brief Constant for LISTJOBSOPTIONS__PRIORITY feature
         */
        static const int LISTJOBSOPTIONS__PRIORITY = 59;

        /**
         * \brief Constant for LISTJOBSOPTIONS__QUEUE feature
         */
        static const int LISTJOBSOPTIONS__QUEUE = 60;

        /**
         * \brief Constant for LISTJOBSOPTIONS__MULTIPLESTATUS feature
         */
        static const int LISTJOBSOPTIONS__MULTIPLESTATUS = 61;

        /**
         * \brief Constant for LISTJOBSOPTIONS__BATCHJOB feature
         */
        static const int LISTJOBSOPTIONS__BATCHJOB = 62;

        /**
         * \brief Constant for LISTJOBSOPTIONS__WORKID feature
         */
        static const int LISTJOBSOPTIONS__WORKID = 63;

        /**
         * \brief Constant for LISTJOBSOPTIONS__LISTALL feature
         */
        static const int LISTJOBSOPTIONS__LISTALL = 64;

        /**
         * \brief Constant for LISTJOBSOPTIONS__MACHINEID feature
         */
        static const int LISTJOBSOPTIONS__MACHINEID = 65;

        /**
         * \brief Constant for PROGRESSOPTIONS__JOBID feature
         */
        static const int PROGRESSOPTIONS__JOBID = 66;

        /**
         * \brief Constant for PROGRESSOPTIONS__USER feature
         */
        static const int PROGRESSOPTIONS__USER = 67;

        /**
         * \brief Constant for PROGRESSOPTIONS__MACHINEID feature
         */
        static const int PROGRESSOPTIONS__MACHINEID = 68;

        /**
         * \brief Constant for LISTPROGRESSION__NBJOBS feature
         */
        static const int LISTPROGRESSION__NBJOBS = 69;

        /**
         * \brief Constant for LISTPROGRESSION__PROGRESS feature
         */
        static const int LISTPROGRESSION__PROGRESS = 70;

        /**
         * \brief Constant for PROGRESSION__JOBID feature
         */
        static const int PROGRESSION__JOBID = 71;

        /**
         * \brief Constant for PROGRESSION__JOBNAME feature
         */
        static const int PROGRESSION__JOBNAME = 72;

        /**
         * \brief Constant for PROGRESSION__WALLTIME feature
         */
        static const int PROGRESSION__WALLTIME = 73;

        /**
         * \brief Constant for PROGRESSION__STARTTIME feature
         */
        static const int PROGRESSION__STARTTIME = 74;

        /**
         * \brief Constant for PROGRESSION__ENDTIME feature
         */
        static const int PROGRESSION__ENDTIME = 75;

        /**
         * \brief Constant for PROGRESSION__PERCENT feature
         */
        static const int PROGRESSION__PERCENT = 76;

        /**
         * \brief Constant for PROGRESSION__STATUS feature
         */
        static const int PROGRESSION__STATUS = 77;

        /**
         * \brief Constant for LISTQUEUES__NBQUEUES feature
         */
        static const int LISTQUEUES__NBQUEUES = 78;

        /**
         * \brief Constant for LISTQUEUES__QUEUES feature
         */
        static const int LISTQUEUES__QUEUES = 79;

        /**
         * \brief Constant for QUEUE__NAME feature
         */
        static const int QUEUE__NAME = 80;

        /**
         * \brief Constant for QUEUE__MAXJOBCPU feature
         */
        static const int QUEUE__MAXJOBCPU = 81;

        /**
         * \brief Constant for QUEUE__MAXPROCCPU feature
         */
        static const int QUEUE__MAXPROCCPU = 82;

        /**
         * \brief Constant for QUEUE__MEMORY feature
         */
        static const int QUEUE__MEMORY = 83;

        /**
         * \brief Constant for QUEUE__WALLTIME feature
         */
        static const int QUEUE__WALLTIME = 84;

        /**
         * \brief Constant for QUEUE__NODE feature
         */
        static const int QUEUE__NODE = 85;

        /**
         * \brief Constant for QUEUE__NBRUNNINGJOBS feature
         */
        static const int QUEUE__NBRUNNINGJOBS = 86;

        /**
         * \brief Constant for QUEUE__NBJOBSINQUEUE feature
         */
        static const int QUEUE__NBJOBSINQUEUE = 87;

        /**
         * \brief Constant for QUEUE__STATE feature
         */
        static const int QUEUE__STATE = 88;

        /**
         * \brief Constant for QUEUE__PRIORITY feature
         */
        static const int QUEUE__PRIORITY = 89;

        /**
         * \brief Constant for QUEUE__DESCRIPTION feature
         */
        static const int QUEUE__DESCRIPTION = 90;

        /**
         * \brief Constant for JOBRESULT__JOBID feature
         */
        static const int JOBRESULT__JOBID = 91;

        /**
         * \brief Constant for JOBRESULT__OUTPUTPATH feature
         */
        static const int JOBRESULT__OUTPUTPATH = 92;

        /**
         * \brief Constant for JOBRESULT__ERRORPATH feature
         */
        static const int JOBRESULT__ERRORPATH = 93;

        /**
         * \brief Constant for JOBRESULT__OUTPUTDIR feature
         */
        static const int JOBRESULT__OUTPUTDIR = 94;

        /**
         * \brief Constant for LISTJOBRESULTS__NBJOBS feature
         */
        static const int LISTJOBRESULTS__NBJOBS = 95;

        /**
         * \brief Constant for LISTJOBRESULTS__RESULTS feature
         */
        static const int LISTJOBRESULTS__RESULTS = 96;

        /**
         * \brief Constant for LOADCRITERION__LOADTYPE feature
         */
        static const int LOADCRITERION__LOADTYPE = 97;

        /**
         * \brief Constant for WORK__SESSIONID feature
         */
        static const int WORK__SESSIONID = 98;

        /**
         * \brief Constant for WORK__APPLICATIONID feature
         */
        static const int WORK__APPLICATIONID = 99;

        /**
         * \brief Constant for WORK__SUBJECT feature
         */
        static const int WORK__SUBJECT = 100;

        /**
         * \brief Constant for WORK__PRIORITY feature
         */
        static const int WORK__PRIORITY = 101;

        /**
         * \brief Constant for WORK__STATUS feature
         */
        static const int WORK__STATUS = 102;

        /**
         * \brief Constant for WORK__ENDDATE feature
         */
        static const int WORK__ENDDATE = 103;

        /**
         * \brief Constant for WORK__OWNER feature
         */
        static const int WORK__OWNER = 104;

        /**
         * \brief Constant for WORK__ESTIMATEDHOUR feature
         */
        static const int WORK__ESTIMATEDHOUR = 105;

        /**
         * \brief Constant for WORK__DONERATIO feature
         */
        static const int WORK__DONERATIO = 106;

        /**
         * \brief Constant for WORK__DESCRIPTION feature
         */
        static const int WORK__DESCRIPTION = 107;

        /**
         * \brief Constant for WORK__DATECREATED feature
         */
        static const int WORK__DATECREATED = 108;

        /**
         * \brief Constant for WORK__DATEENDED feature
         */
        static const int WORK__DATEENDED = 109;

        /**
         * \brief Constant for WORK__DATESTARTED feature
         */
        static const int WORK__DATESTARTED = 110;

        /**
         * \brief Constant for WORK__LASTUPDATED feature
         */
        static const int WORK__LASTUPDATED = 111;

        /**
         * \brief Constant for WORK__WORKID feature
         */
        static const int WORK__WORKID = 112;

        /**
         * \brief Constant for WORK__PROJECTID feature
         */
        static const int WORK__PROJECTID = 113;

        /**
         * \brief Constant for WORK__SUBMITDATE feature
         */
        static const int WORK__SUBMITDATE = 114;

        /**
         * \brief Constant for WORK__MACHINEID feature
         */
        static const int WORK__MACHINEID = 115;

        /**
         * \brief Constant for WORK__NBCPU feature
         */
        static const int WORK__NBCPU = 116;

        /**
         * \brief Constant for WORK__DUEDATE feature
         */
        static const int WORK__DUEDATE = 117;

        /**
         * \brief Constant for ADDWORKOPTIONS__APPLICATIONID feature
         */
        static const int ADDWORKOPTIONS__APPLICATIONID = 118;

        /**
         * \brief Constant for ADDWORKOPTIONS__SUBJECT feature
         */
        static const int ADDWORKOPTIONS__SUBJECT = 119;

        /**
         * \brief Constant for ADDWORKOPTIONS__PRIORITY feature
         */
        static const int ADDWORKOPTIONS__PRIORITY = 120;

        /**
         * \brief Constant for ADDWORKOPTIONS__OWNER feature
         */
        static const int ADDWORKOPTIONS__OWNER = 121;

        /**
         * \brief Constant for ADDWORKOPTIONS__ESTIMATEDHOUR feature
         */
        static const int ADDWORKOPTIONS__ESTIMATEDHOUR = 122;

        /**
         * \brief Constant for ADDWORKOPTIONS__DESCRIPTION feature
         */
        static const int ADDWORKOPTIONS__DESCRIPTION = 123;

        /**
         * \brief Constant for ADDWORKOPTIONS__PROJECTID feature
         */
        static const int ADDWORKOPTIONS__PROJECTID = 124;

        /**
         * \brief Constant for ADDWORKOPTIONS__MACHINEID feature
         */
        static const int ADDWORKOPTIONS__MACHINEID = 125;

        /**
         * \brief Constant for ADDWORKOPTIONS__NBCPU feature
         */
        static const int ADDWORKOPTIONS__NBCPU = 126;

        /**
         * \brief Constant for CANCELOPTIONS__MACHINEID feature
         */
        static const int CANCELOPTIONS__MACHINEID = 127;

        /**
         * \brief Constant for CANCELOPTIONS__USER feature
         */
        static const int CANCELOPTIONS__USER = 128;

        /**
         * \brief Constant for CANCELOPTIONS__JOBID feature
         */
        static const int CANCELOPTIONS__JOBID = 129;

        /**
         * \brief Constant for JOBOUTPUTOPTIONS__MACHINEID feature
         */
        static const int JOBOUTPUTOPTIONS__MACHINEID = 130;

        /**
         * \brief Constant for JOBOUTPUTOPTIONS__OUTPUTDIR feature
         */
        static const int JOBOUTPUTOPTIONS__OUTPUTDIR = 131;

        /**
         * \brief Constant for JOBOUTPUTOPTIONS__DAYS feature
         */
        static const int JOBOUTPUTOPTIONS__DAYS = 132;

        // EClassifiers methods

        /**
         * \brief Returns the reflective object for class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getJob();

        /**
         * \brief Returns the reflective object for class ListJobs
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getListJobs();

        /**
         * \brief Returns the reflective object for class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getSubmitOptions();

        /**
         * \brief Returns the reflective object for class ListJobsOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getListJobsOptions();

        /**
         * \brief Returns the reflective object for class JobPriority
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EEnum_ptr getJobPriority();

        /**
         * \brief Returns the reflective object for class JobStatus
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EEnum_ptr getJobStatus();

        /**
         * \brief Returns the reflective object for class ProgressOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getProgressOptions();

        /**
         * \brief Returns the reflective object for class ListProgression
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getListProgression();

        /**
         * \brief Returns the reflective object for class Progression
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getProgression();

        /**
         * \brief Returns the reflective object for class ListQueues
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getListQueues();

        /**
         * \brief Returns the reflective object for class Queue
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getQueue();

        /**
         * \brief Returns the reflective object for class QueuePriority
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EEnum_ptr getQueuePriority();

        /**
         * \brief Returns the reflective object for class QueueStatus
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EEnum_ptr getQueueStatus();

        /**
         * \brief Returns the reflective object for class JobResult
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getJobResult();

        /**
         * \brief Returns the reflective object for class ListJobResults
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getListJobResults();

        /**
         * \brief Returns the reflective object for class LoadCriterion
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getLoadCriterion();

        /**
         * \brief Returns the reflective object for class LoadType
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EEnum_ptr getLoadType();

        /**
         * \brief Returns the reflective object for class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getWork();

        /**
         * \brief Returns the reflective object for class AddWorkOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getAddWorkOptions();

        /**
         * \brief Returns the reflective object for class CancelOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getCancelOptions();

        /**
         * \brief Returns the reflective object for class JobOutputOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getJobOutputOptions();

        // EStructuralFeatures methods

        /**
         * \brief Returns the reflective object for feature sessionId of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__sessionId();

        /**
         * \brief Returns the reflective object for feature submitMachineId of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__submitMachineId();

        /**
         * \brief Returns the reflective object for feature submitMachineName of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__submitMachineName();

        /**
         * \brief Returns the reflective object for feature jobId of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__jobId();

        /**
         * \brief Returns the reflective object for feature jobName of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__jobName();

        /**
         * \brief Returns the reflective object for feature jobPath of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__jobPath();

        /**
         * \brief Returns the reflective object for feature outputPath of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__outputPath();

        /**
         * \brief Returns the reflective object for feature errorPath of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__errorPath();

        /**
         * \brief Returns the reflective object for feature jobPrio of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__jobPrio();

        /**
         * \brief Returns the reflective object for feature nbCpus of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__nbCpus();

        /**
         * \brief Returns the reflective object for feature jobWorkingDir of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__jobWorkingDir();

        /**
         * \brief Returns the reflective object for feature status of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__status();

        /**
         * \brief Returns the reflective object for feature submitDate of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__submitDate();

        /**
         * \brief Returns the reflective object for feature endDate of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__endDate();

        /**
         * \brief Returns the reflective object for feature owner of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__owner();

        /**
         * \brief Returns the reflective object for feature jobQueue of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__jobQueue();

        /**
         * \brief Returns the reflective object for feature wallClockLimit of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__wallClockLimit();

        /**
         * \brief Returns the reflective object for feature groupName of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__groupName();

        /**
         * \brief Returns the reflective object for feature jobDescription of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__jobDescription();

        /**
         * \brief Returns the reflective object for feature memLimit of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__memLimit();

        /**
         * \brief Returns the reflective object for feature nbNodes of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__nbNodes();

        /**
         * \brief Returns the reflective object for feature nbNodesAndCpuPerNode of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__nbNodesAndCpuPerNode();

        /**
         * \brief Returns the reflective object for feature batchJobId of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__batchJobId();

        /**
         * \brief Returns the reflective object for feature outputDir of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__outputDir();

        /**
         * \brief Returns the reflective object for feature workId of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__workId();

        /**
         * \brief Returns the reflective object for feature userId of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__userId();

        /**
         * \brief Returns the reflective object for feature vmId of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__vmId();

        /**
         * \brief Returns the reflective object for feature vmIp of class Job
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJob__vmIp();

        /**
         * \brief Returns the reflective object for feature nbJobs of class ListJobs
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListJobs__nbJobs();

        /**
         * \brief Returns the reflective object for feature nbRunningJobs of class ListJobs
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListJobs__nbRunningJobs();

        /**
         * \brief Returns the reflective object for feature nbWaitingJobs of class ListJobs
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListJobs__nbWaitingJobs();

        /**
         * \brief Returns the reflective object for feature jobs of class ListJobs
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EReference_ptr getListJobs__jobs();

        /**
         * \brief Returns the reflective object for feature name of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSubmitOptions__name();

        /**
         * \brief Returns the reflective object for feature queue of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSubmitOptions__queue();

        /**
         * \brief Returns the reflective object for feature wallTime of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSubmitOptions__wallTime();

        /**
         * \brief Returns the reflective object for feature memory of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSubmitOptions__memory();

        /**
         * \brief Returns the reflective object for feature nbCpu of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSubmitOptions__nbCpu();

        /**
         * \brief Returns the reflective object for feature nbNodesAndCpuPerNode of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr
                getSubmitOptions__nbNodesAndCpuPerNode();

        /**
         * \brief Returns the reflective object for feature outputPath of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSubmitOptions__outputPath();

        /**
         * \brief Returns the reflective object for feature errorPath of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSubmitOptions__errorPath();

        /**
         * \brief Returns the reflective object for feature mailNotification of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSubmitOptions__mailNotification();

        /**
         * \brief Returns the reflective object for feature mailNotifyUser of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSubmitOptions__mailNotifyUser();

        /**
         * \brief Returns the reflective object for feature group of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSubmitOptions__group();

        /**
         * \brief Returns the reflective object for feature workingDir of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSubmitOptions__workingDir();

        /**
         * \brief Returns the reflective object for feature cpuTime of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSubmitOptions__cpuTime();

        /**
         * \brief Returns the reflective object for feature selectQueueAutom of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSubmitOptions__selectQueueAutom();

        /**
         * \brief Returns the reflective object for feature criterion of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EReference_ptr getSubmitOptions__criterion();

        /**
         * \brief Returns the reflective object for feature fileParams of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSubmitOptions__fileParams();

        /**
         * \brief Returns the reflective object for feature textParams of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSubmitOptions__textParams();

        /**
         * \brief Returns the reflective object for feature workId of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSubmitOptions__workId();

        /**
         * \brief Returns the reflective object for feature specificParams of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSubmitOptions__specificParams();

        /**
         * \brief Returns the reflective object for feature posix of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSubmitOptions__posix();

        /**
         * \brief Returns the reflective object for feature machine of class SubmitOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSubmitOptions__machine();

        /**
         * \brief Returns the reflective object for feature jobId of class ListJobsOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListJobsOptions__jobId();

        /**
         * \brief Returns the reflective object for feature nbCpu of class ListJobsOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListJobsOptions__nbCpu();

        /**
         * \brief Returns the reflective object for feature fromSubmitDate of class ListJobsOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListJobsOptions__fromSubmitDate();

        /**
         * \brief Returns the reflective object for feature toSubmitDate of class ListJobsOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListJobsOptions__toSubmitDate();

        /**
         * \brief Returns the reflective object for feature owner of class ListJobsOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListJobsOptions__owner();

        /**
         * \brief Returns the reflective object for feature status of class ListJobsOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListJobsOptions__status();

        /**
         * \brief Returns the reflective object for feature priority of class ListJobsOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListJobsOptions__priority();

        /**
         * \brief Returns the reflective object for feature queue of class ListJobsOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListJobsOptions__queue();

        /**
         * \brief Returns the reflective object for feature multipleStatus of class ListJobsOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListJobsOptions__multipleStatus();

        /**
         * \brief Returns the reflective object for feature batchJob of class ListJobsOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListJobsOptions__batchJob();

        /**
         * \brief Returns the reflective object for feature workId of class ListJobsOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListJobsOptions__workId();

        /**
         * \brief Returns the reflective object for feature listAll of class ListJobsOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListJobsOptions__listAll();

        /**
         * \brief Returns the reflective object for feature machineId of class ListJobsOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListJobsOptions__machineId();

        /**
         * \brief Returns the reflective object for feature jobId of class ProgressOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getProgressOptions__jobId();

        /**
         * \brief Returns the reflective object for feature user of class ProgressOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getProgressOptions__user();

        /**
         * \brief Returns the reflective object for feature machineId of class ProgressOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getProgressOptions__machineId();

        /**
         * \brief Returns the reflective object for feature nbJobs of class ListProgression
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListProgression__nbJobs();

        /**
         * \brief Returns the reflective object for feature progress of class ListProgression
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EReference_ptr getListProgression__progress();

        /**
         * \brief Returns the reflective object for feature jobId of class Progression
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getProgression__jobId();

        /**
         * \brief Returns the reflective object for feature jobName of class Progression
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getProgression__jobName();

        /**
         * \brief Returns the reflective object for feature wallTime of class Progression
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getProgression__wallTime();

        /**
         * \brief Returns the reflective object for feature startTime of class Progression
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getProgression__startTime();

        /**
         * \brief Returns the reflective object for feature endTime of class Progression
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getProgression__endTime();

        /**
         * \brief Returns the reflective object for feature percent of class Progression
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getProgression__percent();

        /**
         * \brief Returns the reflective object for feature status of class Progression
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getProgression__status();

        /**
         * \brief Returns the reflective object for feature nbQueues of class ListQueues
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListQueues__nbQueues();

        /**
         * \brief Returns the reflective object for feature queues of class ListQueues
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EReference_ptr getListQueues__queues();

        /**
         * \brief Returns the reflective object for feature name of class Queue
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getQueue__name();

        /**
         * \brief Returns the reflective object for feature maxJobCpu of class Queue
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getQueue__maxJobCpu();

        /**
         * \brief Returns the reflective object for feature maxProcCpu of class Queue
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getQueue__maxProcCpu();

        /**
         * \brief Returns the reflective object for feature memory of class Queue
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getQueue__memory();

        /**
         * \brief Returns the reflective object for feature wallTime of class Queue
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getQueue__wallTime();

        /**
         * \brief Returns the reflective object for feature node of class Queue
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getQueue__node();

        /**
         * \brief Returns the reflective object for feature nbRunningJobs of class Queue
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getQueue__nbRunningJobs();

        /**
         * \brief Returns the reflective object for feature nbJobsInQueue of class Queue
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getQueue__nbJobsInQueue();

        /**
         * \brief Returns the reflective object for feature state of class Queue
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getQueue__state();

        /**
         * \brief Returns the reflective object for feature priority of class Queue
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getQueue__priority();

        /**
         * \brief Returns the reflective object for feature description of class Queue
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getQueue__description();

        /**
         * \brief Returns the reflective object for feature jobId of class JobResult
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJobResult__jobId();

        /**
         * \brief Returns the reflective object for feature outputPath of class JobResult
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJobResult__outputPath();

        /**
         * \brief Returns the reflective object for feature errorPath of class JobResult
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJobResult__errorPath();

        /**
         * \brief Returns the reflective object for feature outputDir of class JobResult
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJobResult__outputDir();

        /**
         * \brief Returns the reflective object for feature nbJobs of class ListJobResults
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListJobResults__nbJobs();

        /**
         * \brief Returns the reflective object for feature Results of class ListJobResults
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EReference_ptr getListJobResults__Results();

        /**
         * \brief Returns the reflective object for feature loadType of class LoadCriterion
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getLoadCriterion__loadType();

        /**
         * \brief Returns the reflective object for feature sessionId of class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getWork__sessionId();

        /**
         * \brief Returns the reflective object for feature applicationId of class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getWork__applicationId();

        /**
         * \brief Returns the reflective object for feature subject of class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getWork__subject();

        /**
         * \brief Returns the reflective object for feature priority of class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getWork__priority();

        /**
         * \brief Returns the reflective object for feature status of class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getWork__status();

        /**
         * \brief Returns the reflective object for feature endDate of class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getWork__endDate();

        /**
         * \brief Returns the reflective object for feature owner of class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getWork__owner();

        /**
         * \brief Returns the reflective object for feature estimatedHour of class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getWork__estimatedHour();

        /**
         * \brief Returns the reflective object for feature doneRatio of class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getWork__doneRatio();

        /**
         * \brief Returns the reflective object for feature description of class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getWork__description();

        /**
         * \brief Returns the reflective object for feature dateCreated of class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getWork__dateCreated();

        /**
         * \brief Returns the reflective object for feature dateEnded of class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getWork__dateEnded();

        /**
         * \brief Returns the reflective object for feature dateStarted of class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getWork__dateStarted();

        /**
         * \brief Returns the reflective object for feature lastUpdated of class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getWork__lastUpdated();

        /**
         * \brief Returns the reflective object for feature workId of class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getWork__workId();

        /**
         * \brief Returns the reflective object for feature projectId of class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getWork__projectId();

        /**
         * \brief Returns the reflective object for feature submitDate of class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getWork__submitDate();

        /**
         * \brief Returns the reflective object for feature machineId of class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getWork__machineId();

        /**
         * \brief Returns the reflective object for feature nbCPU of class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getWork__nbCPU();

        /**
         * \brief Returns the reflective object for feature dueDate of class Work
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getWork__dueDate();

        /**
         * \brief Returns the reflective object for feature applicationId of class AddWorkOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAddWorkOptions__applicationId();

        /**
         * \brief Returns the reflective object for feature subject of class AddWorkOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAddWorkOptions__subject();

        /**
         * \brief Returns the reflective object for feature priority of class AddWorkOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAddWorkOptions__priority();

        /**
         * \brief Returns the reflective object for feature owner of class AddWorkOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAddWorkOptions__owner();

        /**
         * \brief Returns the reflective object for feature estimatedHour of class AddWorkOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAddWorkOptions__estimatedHour();

        /**
         * \brief Returns the reflective object for feature description of class AddWorkOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAddWorkOptions__description();

        /**
         * \brief Returns the reflective object for feature projectId of class AddWorkOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAddWorkOptions__projectId();

        /**
         * \brief Returns the reflective object for feature machineId of class AddWorkOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAddWorkOptions__machineId();

        /**
         * \brief Returns the reflective object for feature nbCPU of class AddWorkOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAddWorkOptions__nbCPU();

        /**
         * \brief Returns the reflective object for feature machineId of class CancelOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getCancelOptions__machineId();

        /**
         * \brief Returns the reflective object for feature user of class CancelOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getCancelOptions__user();

        /**
         * \brief Returns the reflective object for feature jobId of class CancelOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getCancelOptions__jobId();

        /**
         * \brief Returns the reflective object for feature machineId of class JobOutputOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJobOutputOptions__machineId();

        /**
         * \brief Returns the reflective object for feature outputDir of class JobOutputOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJobOutputOptions__outputDir();

        /**
         * \brief Returns the reflective object for feature days of class JobOutputOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getJobOutputOptions__days();

    protected:

        /**
         * \brief The instance of the package
         */
        static std::auto_ptr< TMS_DataPackage > s_instance;

        TMS_DataPackage();

        // EClass instances 

        /**
         * \brief The instance for the class Job
         */
        ::ecore::EClass_ptr m_JobEClass;

        /**
         * \brief The instance for the class ListJobs
         */
        ::ecore::EClass_ptr m_ListJobsEClass;

        /**
         * \brief The instance for the class SubmitOptions
         */
        ::ecore::EClass_ptr m_SubmitOptionsEClass;

        /**
         * \brief The instance for the class ListJobsOptions
         */
        ::ecore::EClass_ptr m_ListJobsOptionsEClass;

        /**
         * \brief The instance for the class ProgressOptions
         */
        ::ecore::EClass_ptr m_ProgressOptionsEClass;

        /**
         * \brief The instance for the class ListProgression
         */
        ::ecore::EClass_ptr m_ListProgressionEClass;

        /**
         * \brief The instance for the class Progression
         */
        ::ecore::EClass_ptr m_ProgressionEClass;

        /**
         * \brief The instance for the class ListQueues
         */
        ::ecore::EClass_ptr m_ListQueuesEClass;

        /**
         * \brief The instance for the class Queue
         */
        ::ecore::EClass_ptr m_QueueEClass;

        /**
         * \brief The instance for the class JobResult
         */
        ::ecore::EClass_ptr m_JobResultEClass;

        /**
         * \brief The instance for the class ListJobResults
         */
        ::ecore::EClass_ptr m_ListJobResultsEClass;

        /**
         * \brief The instance for the class LoadCriterion
         */
        ::ecore::EClass_ptr m_LoadCriterionEClass;

        /**
         * \brief The instance for the class Work
         */
        ::ecore::EClass_ptr m_WorkEClass;

        /**
         * \brief The instance for the class AddWorkOptions
         */
        ::ecore::EClass_ptr m_AddWorkOptionsEClass;

        /**
         * \brief The instance for the class CancelOptions
         */
        ::ecore::EClass_ptr m_CancelOptionsEClass;

        /**
         * \brief The instance for the class JobOutputOptions
         */
        ::ecore::EClass_ptr m_JobOutputOptionsEClass;

        // EEnuminstances 

        /**
         * \brief The instance for the enum JobPriority
         */
        ::ecore::EEnum_ptr m_JobPriorityEEnum;

        /**
         * \brief The instance for the enum JobStatus
         */
        ::ecore::EEnum_ptr m_JobStatusEEnum;

        /**
         * \brief The instance for the enum QueuePriority
         */
        ::ecore::EEnum_ptr m_QueuePriorityEEnum;

        /**
         * \brief The instance for the enum QueueStatus
         */
        ::ecore::EEnum_ptr m_QueueStatusEEnum;

        /**
         * \brief The instance for the enum LoadType
         */
        ::ecore::EEnum_ptr m_LoadTypeEEnum;

        // EDataType instances 


        // EStructuralFeatures instances

        /**
         * \brief The instance for the feature sessionId of class Job
         */
        ::ecore::EAttribute_ptr m_Job__sessionId;

        /**
         * \brief The instance for the feature submitMachineId of class Job
         */
        ::ecore::EAttribute_ptr m_Job__submitMachineId;

        /**
         * \brief The instance for the feature submitMachineName of class Job
         */
        ::ecore::EAttribute_ptr m_Job__submitMachineName;

        /**
         * \brief The instance for the feature jobId of class Job
         */
        ::ecore::EAttribute_ptr m_Job__jobId;

        /**
         * \brief The instance for the feature jobName of class Job
         */
        ::ecore::EAttribute_ptr m_Job__jobName;

        /**
         * \brief The instance for the feature jobPath of class Job
         */
        ::ecore::EAttribute_ptr m_Job__jobPath;

        /**
         * \brief The instance for the feature outputPath of class Job
         */
        ::ecore::EAttribute_ptr m_Job__outputPath;

        /**
         * \brief The instance for the feature errorPath of class Job
         */
        ::ecore::EAttribute_ptr m_Job__errorPath;

        /**
         * \brief The instance for the feature jobPrio of class Job
         */
        ::ecore::EAttribute_ptr m_Job__jobPrio;

        /**
         * \brief The instance for the feature nbCpus of class Job
         */
        ::ecore::EAttribute_ptr m_Job__nbCpus;

        /**
         * \brief The instance for the feature jobWorkingDir of class Job
         */
        ::ecore::EAttribute_ptr m_Job__jobWorkingDir;

        /**
         * \brief The instance for the feature status of class Job
         */
        ::ecore::EAttribute_ptr m_Job__status;

        /**
         * \brief The instance for the feature submitDate of class Job
         */
        ::ecore::EAttribute_ptr m_Job__submitDate;

        /**
         * \brief The instance for the feature endDate of class Job
         */
        ::ecore::EAttribute_ptr m_Job__endDate;

        /**
         * \brief The instance for the feature owner of class Job
         */
        ::ecore::EAttribute_ptr m_Job__owner;

        /**
         * \brief The instance for the feature jobQueue of class Job
         */
        ::ecore::EAttribute_ptr m_Job__jobQueue;

        /**
         * \brief The instance for the feature wallClockLimit of class Job
         */
        ::ecore::EAttribute_ptr m_Job__wallClockLimit;

        /**
         * \brief The instance for the feature groupName of class Job
         */
        ::ecore::EAttribute_ptr m_Job__groupName;

        /**
         * \brief The instance for the feature jobDescription of class Job
         */
        ::ecore::EAttribute_ptr m_Job__jobDescription;

        /**
         * \brief The instance for the feature memLimit of class Job
         */
        ::ecore::EAttribute_ptr m_Job__memLimit;

        /**
         * \brief The instance for the feature nbNodes of class Job
         */
        ::ecore::EAttribute_ptr m_Job__nbNodes;

        /**
         * \brief The instance for the feature nbNodesAndCpuPerNode of class Job
         */
        ::ecore::EAttribute_ptr m_Job__nbNodesAndCpuPerNode;

        /**
         * \brief The instance for the feature batchJobId of class Job
         */
        ::ecore::EAttribute_ptr m_Job__batchJobId;

        /**
         * \brief The instance for the feature outputDir of class Job
         */
        ::ecore::EAttribute_ptr m_Job__outputDir;

        /**
         * \brief The instance for the feature workId of class Job
         */
        ::ecore::EAttribute_ptr m_Job__workId;

        /**
         * \brief The instance for the feature userId of class Job
         */
        ::ecore::EAttribute_ptr m_Job__userId;

        /**
         * \brief The instance for the feature vmId of class Job
         */
        ::ecore::EAttribute_ptr m_Job__vmId;

        /**
         * \brief The instance for the feature vmIp of class Job
         */
        ::ecore::EAttribute_ptr m_Job__vmIp;

        /**
         * \brief The instance for the feature nbJobs of class ListJobs
         */
        ::ecore::EAttribute_ptr m_ListJobs__nbJobs;

        /**
         * \brief The instance for the feature nbRunningJobs of class ListJobs
         */
        ::ecore::EAttribute_ptr m_ListJobs__nbRunningJobs;

        /**
         * \brief The instance for the feature nbWaitingJobs of class ListJobs
         */
        ::ecore::EAttribute_ptr m_ListJobs__nbWaitingJobs;

        /**
         * \brief The instance for the feature jobs of class ListJobs
         */
        ::ecore::EReference_ptr m_ListJobs__jobs;

        /**
         * \brief The instance for the feature name of class SubmitOptions
         */
        ::ecore::EAttribute_ptr m_SubmitOptions__name;

        /**
         * \brief The instance for the feature queue of class SubmitOptions
         */
        ::ecore::EAttribute_ptr m_SubmitOptions__queue;

        /**
         * \brief The instance for the feature wallTime of class SubmitOptions
         */
        ::ecore::EAttribute_ptr m_SubmitOptions__wallTime;

        /**
         * \brief The instance for the feature memory of class SubmitOptions
         */
        ::ecore::EAttribute_ptr m_SubmitOptions__memory;

        /**
         * \brief The instance for the feature nbCpu of class SubmitOptions
         */
        ::ecore::EAttribute_ptr m_SubmitOptions__nbCpu;

        /**
         * \brief The instance for the feature nbNodesAndCpuPerNode of class SubmitOptions
         */
        ::ecore::EAttribute_ptr m_SubmitOptions__nbNodesAndCpuPerNode;

        /**
         * \brief The instance for the feature outputPath of class SubmitOptions
         */
        ::ecore::EAttribute_ptr m_SubmitOptions__outputPath;

        /**
         * \brief The instance for the feature errorPath of class SubmitOptions
         */
        ::ecore::EAttribute_ptr m_SubmitOptions__errorPath;

        /**
         * \brief The instance for the feature mailNotification of class SubmitOptions
         */
        ::ecore::EAttribute_ptr m_SubmitOptions__mailNotification;

        /**
         * \brief The instance for the feature mailNotifyUser of class SubmitOptions
         */
        ::ecore::EAttribute_ptr m_SubmitOptions__mailNotifyUser;

        /**
         * \brief The instance for the feature group of class SubmitOptions
         */
        ::ecore::EAttribute_ptr m_SubmitOptions__group;

        /**
         * \brief The instance for the feature workingDir of class SubmitOptions
         */
        ::ecore::EAttribute_ptr m_SubmitOptions__workingDir;

        /**
         * \brief The instance for the feature cpuTime of class SubmitOptions
         */
        ::ecore::EAttribute_ptr m_SubmitOptions__cpuTime;

        /**
         * \brief The instance for the feature selectQueueAutom of class SubmitOptions
         */
        ::ecore::EAttribute_ptr m_SubmitOptions__selectQueueAutom;

        /**
         * \brief The instance for the feature criterion of class SubmitOptions
         */
        ::ecore::EReference_ptr m_SubmitOptions__criterion;

        /**
         * \brief The instance for the feature fileParams of class SubmitOptions
         */
        ::ecore::EAttribute_ptr m_SubmitOptions__fileParams;

        /**
         * \brief The instance for the feature textParams of class SubmitOptions
         */
        ::ecore::EAttribute_ptr m_SubmitOptions__textParams;

        /**
         * \brief The instance for the feature workId of class SubmitOptions
         */
        ::ecore::EAttribute_ptr m_SubmitOptions__workId;

        /**
         * \brief The instance for the feature specificParams of class SubmitOptions
         */
        ::ecore::EAttribute_ptr m_SubmitOptions__specificParams;

        /**
         * \brief The instance for the feature posix of class SubmitOptions
         */
        ::ecore::EAttribute_ptr m_SubmitOptions__posix;

        /**
         * \brief The instance for the feature machine of class SubmitOptions
         */
        ::ecore::EAttribute_ptr m_SubmitOptions__machine;

        /**
         * \brief The instance for the feature jobId of class ListJobsOptions
         */
        ::ecore::EAttribute_ptr m_ListJobsOptions__jobId;

        /**
         * \brief The instance for the feature nbCpu of class ListJobsOptions
         */
        ::ecore::EAttribute_ptr m_ListJobsOptions__nbCpu;

        /**
         * \brief The instance for the feature fromSubmitDate of class ListJobsOptions
         */
        ::ecore::EAttribute_ptr m_ListJobsOptions__fromSubmitDate;

        /**
         * \brief The instance for the feature toSubmitDate of class ListJobsOptions
         */
        ::ecore::EAttribute_ptr m_ListJobsOptions__toSubmitDate;

        /**
         * \brief The instance for the feature owner of class ListJobsOptions
         */
        ::ecore::EAttribute_ptr m_ListJobsOptions__owner;

        /**
         * \brief The instance for the feature status of class ListJobsOptions
         */
        ::ecore::EAttribute_ptr m_ListJobsOptions__status;

        /**
         * \brief The instance for the feature priority of class ListJobsOptions
         */
        ::ecore::EAttribute_ptr m_ListJobsOptions__priority;

        /**
         * \brief The instance for the feature queue of class ListJobsOptions
         */
        ::ecore::EAttribute_ptr m_ListJobsOptions__queue;

        /**
         * \brief The instance for the feature multipleStatus of class ListJobsOptions
         */
        ::ecore::EAttribute_ptr m_ListJobsOptions__multipleStatus;

        /**
         * \brief The instance for the feature batchJob of class ListJobsOptions
         */
        ::ecore::EAttribute_ptr m_ListJobsOptions__batchJob;

        /**
         * \brief The instance for the feature workId of class ListJobsOptions
         */
        ::ecore::EAttribute_ptr m_ListJobsOptions__workId;

        /**
         * \brief The instance for the feature listAll of class ListJobsOptions
         */
        ::ecore::EAttribute_ptr m_ListJobsOptions__listAll;

        /**
         * \brief The instance for the feature machineId of class ListJobsOptions
         */
        ::ecore::EAttribute_ptr m_ListJobsOptions__machineId;

        /**
         * \brief The instance for the feature jobId of class ProgressOptions
         */
        ::ecore::EAttribute_ptr m_ProgressOptions__jobId;

        /**
         * \brief The instance for the feature user of class ProgressOptions
         */
        ::ecore::EAttribute_ptr m_ProgressOptions__user;

        /**
         * \brief The instance for the feature machineId of class ProgressOptions
         */
        ::ecore::EAttribute_ptr m_ProgressOptions__machineId;

        /**
         * \brief The instance for the feature nbJobs of class ListProgression
         */
        ::ecore::EAttribute_ptr m_ListProgression__nbJobs;

        /**
         * \brief The instance for the feature progress of class ListProgression
         */
        ::ecore::EReference_ptr m_ListProgression__progress;

        /**
         * \brief The instance for the feature jobId of class Progression
         */
        ::ecore::EAttribute_ptr m_Progression__jobId;

        /**
         * \brief The instance for the feature jobName of class Progression
         */
        ::ecore::EAttribute_ptr m_Progression__jobName;

        /**
         * \brief The instance for the feature wallTime of class Progression
         */
        ::ecore::EAttribute_ptr m_Progression__wallTime;

        /**
         * \brief The instance for the feature startTime of class Progression
         */
        ::ecore::EAttribute_ptr m_Progression__startTime;

        /**
         * \brief The instance for the feature endTime of class Progression
         */
        ::ecore::EAttribute_ptr m_Progression__endTime;

        /**
         * \brief The instance for the feature percent of class Progression
         */
        ::ecore::EAttribute_ptr m_Progression__percent;

        /**
         * \brief The instance for the feature status of class Progression
         */
        ::ecore::EAttribute_ptr m_Progression__status;

        /**
         * \brief The instance for the feature nbQueues of class ListQueues
         */
        ::ecore::EAttribute_ptr m_ListQueues__nbQueues;

        /**
         * \brief The instance for the feature queues of class ListQueues
         */
        ::ecore::EReference_ptr m_ListQueues__queues;

        /**
         * \brief The instance for the feature name of class Queue
         */
        ::ecore::EAttribute_ptr m_Queue__name;

        /**
         * \brief The instance for the feature maxJobCpu of class Queue
         */
        ::ecore::EAttribute_ptr m_Queue__maxJobCpu;

        /**
         * \brief The instance for the feature maxProcCpu of class Queue
         */
        ::ecore::EAttribute_ptr m_Queue__maxProcCpu;

        /**
         * \brief The instance for the feature memory of class Queue
         */
        ::ecore::EAttribute_ptr m_Queue__memory;

        /**
         * \brief The instance for the feature wallTime of class Queue
         */
        ::ecore::EAttribute_ptr m_Queue__wallTime;

        /**
         * \brief The instance for the feature node of class Queue
         */
        ::ecore::EAttribute_ptr m_Queue__node;

        /**
         * \brief The instance for the feature nbRunningJobs of class Queue
         */
        ::ecore::EAttribute_ptr m_Queue__nbRunningJobs;

        /**
         * \brief The instance for the feature nbJobsInQueue of class Queue
         */
        ::ecore::EAttribute_ptr m_Queue__nbJobsInQueue;

        /**
         * \brief The instance for the feature state of class Queue
         */
        ::ecore::EAttribute_ptr m_Queue__state;

        /**
         * \brief The instance for the feature priority of class Queue
         */
        ::ecore::EAttribute_ptr m_Queue__priority;

        /**
         * \brief The instance for the feature description of class Queue
         */
        ::ecore::EAttribute_ptr m_Queue__description;

        /**
         * \brief The instance for the feature jobId of class JobResult
         */
        ::ecore::EAttribute_ptr m_JobResult__jobId;

        /**
         * \brief The instance for the feature outputPath of class JobResult
         */
        ::ecore::EAttribute_ptr m_JobResult__outputPath;

        /**
         * \brief The instance for the feature errorPath of class JobResult
         */
        ::ecore::EAttribute_ptr m_JobResult__errorPath;

        /**
         * \brief The instance for the feature outputDir of class JobResult
         */
        ::ecore::EAttribute_ptr m_JobResult__outputDir;

        /**
         * \brief The instance for the feature nbJobs of class ListJobResults
         */
        ::ecore::EAttribute_ptr m_ListJobResults__nbJobs;

        /**
         * \brief The instance for the feature Results of class ListJobResults
         */
        ::ecore::EReference_ptr m_ListJobResults__Results;

        /**
         * \brief The instance for the feature loadType of class LoadCriterion
         */
        ::ecore::EAttribute_ptr m_LoadCriterion__loadType;

        /**
         * \brief The instance for the feature sessionId of class Work
         */
        ::ecore::EAttribute_ptr m_Work__sessionId;

        /**
         * \brief The instance for the feature applicationId of class Work
         */
        ::ecore::EAttribute_ptr m_Work__applicationId;

        /**
         * \brief The instance for the feature subject of class Work
         */
        ::ecore::EAttribute_ptr m_Work__subject;

        /**
         * \brief The instance for the feature priority of class Work
         */
        ::ecore::EAttribute_ptr m_Work__priority;

        /**
         * \brief The instance for the feature status of class Work
         */
        ::ecore::EAttribute_ptr m_Work__status;

        /**
         * \brief The instance for the feature endDate of class Work
         */
        ::ecore::EAttribute_ptr m_Work__endDate;

        /**
         * \brief The instance for the feature owner of class Work
         */
        ::ecore::EAttribute_ptr m_Work__owner;

        /**
         * \brief The instance for the feature estimatedHour of class Work
         */
        ::ecore::EAttribute_ptr m_Work__estimatedHour;

        /**
         * \brief The instance for the feature doneRatio of class Work
         */
        ::ecore::EAttribute_ptr m_Work__doneRatio;

        /**
         * \brief The instance for the feature description of class Work
         */
        ::ecore::EAttribute_ptr m_Work__description;

        /**
         * \brief The instance for the feature dateCreated of class Work
         */
        ::ecore::EAttribute_ptr m_Work__dateCreated;

        /**
         * \brief The instance for the feature dateEnded of class Work
         */
        ::ecore::EAttribute_ptr m_Work__dateEnded;

        /**
         * \brief The instance for the feature dateStarted of class Work
         */
        ::ecore::EAttribute_ptr m_Work__dateStarted;

        /**
         * \brief The instance for the feature lastUpdated of class Work
         */
        ::ecore::EAttribute_ptr m_Work__lastUpdated;

        /**
         * \brief The instance for the feature workId of class Work
         */
        ::ecore::EAttribute_ptr m_Work__workId;

        /**
         * \brief The instance for the feature projectId of class Work
         */
        ::ecore::EAttribute_ptr m_Work__projectId;

        /**
         * \brief The instance for the feature submitDate of class Work
         */
        ::ecore::EAttribute_ptr m_Work__submitDate;

        /**
         * \brief The instance for the feature machineId of class Work
         */
        ::ecore::EAttribute_ptr m_Work__machineId;

        /**
         * \brief The instance for the feature nbCPU of class Work
         */
        ::ecore::EAttribute_ptr m_Work__nbCPU;

        /**
         * \brief The instance for the feature dueDate of class Work
         */
        ::ecore::EAttribute_ptr m_Work__dueDate;

        /**
         * \brief The instance for the feature applicationId of class AddWorkOptions
         */
        ::ecore::EAttribute_ptr m_AddWorkOptions__applicationId;

        /**
         * \brief The instance for the feature subject of class AddWorkOptions
         */
        ::ecore::EAttribute_ptr m_AddWorkOptions__subject;

        /**
         * \brief The instance for the feature priority of class AddWorkOptions
         */
        ::ecore::EAttribute_ptr m_AddWorkOptions__priority;

        /**
         * \brief The instance for the feature owner of class AddWorkOptions
         */
        ::ecore::EAttribute_ptr m_AddWorkOptions__owner;

        /**
         * \brief The instance for the feature estimatedHour of class AddWorkOptions
         */
        ::ecore::EAttribute_ptr m_AddWorkOptions__estimatedHour;

        /**
         * \brief The instance for the feature description of class AddWorkOptions
         */
        ::ecore::EAttribute_ptr m_AddWorkOptions__description;

        /**
         * \brief The instance for the feature projectId of class AddWorkOptions
         */
        ::ecore::EAttribute_ptr m_AddWorkOptions__projectId;

        /**
         * \brief The instance for the feature machineId of class AddWorkOptions
         */
        ::ecore::EAttribute_ptr m_AddWorkOptions__machineId;

        /**
         * \brief The instance for the feature nbCPU of class AddWorkOptions
         */
        ::ecore::EAttribute_ptr m_AddWorkOptions__nbCPU;

        /**
         * \brief The instance for the feature machineId of class CancelOptions
         */
        ::ecore::EAttribute_ptr m_CancelOptions__machineId;

        /**
         * \brief The instance for the feature user of class CancelOptions
         */
        ::ecore::EAttribute_ptr m_CancelOptions__user;

        /**
         * \brief The instance for the feature jobId of class CancelOptions
         */
        ::ecore::EAttribute_ptr m_CancelOptions__jobId;

        /**
         * \brief The instance for the feature machineId of class JobOutputOptions
         */
        ::ecore::EAttribute_ptr m_JobOutputOptions__machineId;

        /**
         * \brief The instance for the feature outputDir of class JobOutputOptions
         */
        ::ecore::EAttribute_ptr m_JobOutputOptions__outputDir;

        /**
         * \brief The instance for the feature days of class JobOutputOptions
         */
        ::ecore::EAttribute_ptr m_JobOutputOptions__days;

    };

} // TMS_Data


#endif // _TMS_DATAPACKAGE_HPP
