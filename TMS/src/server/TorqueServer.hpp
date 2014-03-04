/**
 * \file TorqueServer.hpp
 * \brief This file contains the VISHNU TorqueServer class.
 * \author Daouda Traore (daouda.traore@sysfera.com)
 * \date April 2011
 */

#ifndef TMS_TORQUE_SERVER_H
#define TMS_TORQUE_SERVER_H

#include "BatchServer.hpp"
#include <string>
#include "pbs_ifl.h"

/**
 * \class TorqueServer
 * \brief TorqueServer class implementation
 */
class TorqueServer : public BatchServer
{
  public:

    /**
     * \brief Constructor
     */
    TorqueServer();

    /**
     * \brief Function to submit Torque job
     * \param scriptPath the path to the script containing the job characteristique
     * \param options the options to submit job
     * \param job The job data structure
     * \param envp The list of environment variables used by Torque submission function
     * \return raises an exception on error
     */
    int
    submit(const std::string& scriptPath,
          const TMS_Data::SubmitOptions& options,
          TMS_Data::Job& job,
          char** envp=NULL);

    /**
     * \brief Function to cancel job
     * \param jobId the identifier of the job to cancel
     * \return raises an exception on error
     */
    int
    cancel(const std::string& jobId) ;

    /**
     * \brief Function to get the status of the job
     * \param jobId the identifier of the job
     * \return -1 if the job is unknown or server not  unavailable
     */
    int
    getJobState(const std::string& jobId);

    /**
     * \brief Function to get the start time of the job
     * \param jobId the identifier of the job
     * \return 0 if the job is unknown or server not  unavailable
     */
    time_t
    getJobStartTime(const std::string& jobId);


    /**
     * \brief Function to request the status of queues
     * \param optQueueName (optional) the name of the queue to request
     * \return The requested status in to ListQueues data structure
     */
    TMS_Data::ListQueues*
    listQueues(const std::string& optQueueName=std::string());

    /**
     * \brief Function to get a list of submitted jobs
     * \param listOfJobs the ListJobs structure to fill
     * \param ignoredIds the list of job ids to ignore
     */
    void fillListOfJobs(TMS_Data::ListJobs*& listOfJobs,
                        const std::vector<std::string>& ignoredIds=std::vector<std::string>());

    /**
     * \brief Destructor
     */
    ~TorqueServer();

  private:

    /**
     * \brief Function to cancel job on remote machine
     * \param jobId The identifier of the job
     * \param remoteServer the name of the remote server
     * \param isLocal is the remoteServer is local
     * \return raises an exception on error
     */
    int
    pbs_cancel(const char* jobId,
               char remoteServer[],
               bool isLocal=true);

    /**
     * \brief Function to treat the submission options
     * \param scriptPath The job script path
     * \param options the object which contains the SubmitOptions options values
     * \param cmdsOptions The list of the option value
     * \return raises an exception on error
     */
    void
    processOptions(const char* scriptPath,
                   const TMS_Data::SubmitOptions& options,
                   std::vector<std::string>& cmdsOptions);

    /**
     * \brief Function to convert the Torque state into VISHNU state
     * \param state the state to convert
     * \return VISHNU state
     */
    int
    convertTorqueStateToVishnuState(std::string state);

    /**
     * \brief Function to convert the Torque priority into VISHNU priority
     * \param prio the priority to convert
     * \return VISHNU state
     */
    int
    convertTorquePrioToVishnuPrio(const int& prio);

    /**
     * \brief Function To fill the info concerning a job
     * \param job: The job to fill
     * \param p: The batch status structure containing the job info
     */
    void
    fillJobInfo(TMS_Data::Job &job,
                struct batch_status *p);

    /**
     * \brief Function to get the number of nodes in the torque node format
     * \param format The node format
     * \param nbCpu The minimum number of cpu per node
     * \param maxNbCpu The maximum number of cpu per node
     * \return the number of node
     */
    int
    getNbNodesInNodeFormat(const std::string& format,
                           int& nbCpu,
                           int& maxNbCpu);

    /**
     * \brief Function to get the torque formated cpu per node
     * \param cpu The given cpu in string
     * \param scriptPath The path of the script that enventually contain the node format or the number of node
     * \return formated cpu per node
     */
    std::string
    getFormatedCpuPerNode(const int& cpu,
                          const std::string& scriptPath);

    /**
     * \brief Function to insert some additional content (valueToInsert)
     * \param valueToFind string to find
     * \param valueToInsert to insert
     * \param begin The begin position of the substring in src
     * \param end The end position of the substring in src
     * \param src The string to modify
     */
    void
    findAndInsert(const std::string& valueToFind,
                  const std::string& valueToInsert,
                  const size_t& begin,
                  size_t& end,
                  std::string& src);

    /**
     * \brief Function to compute the number of nodes and cpus in the torque format nodes
     * \param nextNodeContent The node content to parse
     * \param ppn The syntaxe containing the number of processors per node
     * \param nbNodes The computed number of nodes
     * \param nbCpu The minimum number of cpus
     * \param maxNbCpu The maximum number of cpus
     */
    void
    computeNbNodesAndNbCpu(const std::string& nextNodeContent,
                           const std::string& ppn,
                           int& nbNodes,
                           int& nbCpu,
                           int& maxNbCpu);

    /**
     * \brief Function to get the torque number of nodes in cripy
     * \param scriptPath The path of the script that enventually contain the node format or the number of node
     * \param nbCpu The maximum number of cpus in the script
     * \return the number of nodes in the given script
     */
    int
    getTorqueNbNodesInScript(const std::string& scriptPath,
                             int& nbCpu);

    /**
     * \brief Function to get the value of TORQUE resource (nodes, walltime, cpu) in the script
     * \param file The file contain the script to scan
     * \param resourceName The name of the option (nodes, walltime, cpu) whose value will be returned
     * \return The value of the resource
     */
    std::string
    getTorqueResourceValue(const char* file,
                           const std::string& resourceName);

    /**
     * \brief Function to request the status of queues
     * \param optQueueName (optional) The name of the queue to request
     * \return The requested status in to ListQueues data structure
     */
    TMS_Data::ListQueues*
    queuesResourceMin(const std::string& optQueueName);

    /**
     * \brief Function to convert torque memory into mb
     * \param memStr memory to convert
     * \return the converted memory
     */
    int
    convertTorqueMem(const std::string& memStr);

    /**
     * \brief Function to replace some environment varia*bles in a string
     * \param scriptpath The script path to modify
     */
    void replaceEnvVariables(const char* scriptPath);


    /**
     * \brief ListQueues returned
     */
    TMS_Data::ListQueues_ptr mlistQueues;
    /**
     * \brief The name of the server to connect
     */
    char serverOut[PBS_MAXSERVERNAME + PBS_MAXPORTNUM + 2];

};

#endif
