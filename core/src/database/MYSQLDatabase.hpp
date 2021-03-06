/**
 * \file MYSQLDatabase.hpp
 * \brief This file presents a SQL database.
 * \author Kevin Coulomb (kevin.coulomb@sysfera.com)
 * \date 15/12/10
 */

#ifndef _MYSDLDATABASE_H_
#define _MYSQLDATABASE_H_

#include <string>
#include <pthread.h>

#include "Database.hpp"
#include "DatabaseResult.hpp"
#include "DbConfiguration.hpp"
#include "MYSQLRequestFactory.hpp"

#include "mysql.h"

/**
 * \class MYSQLDatabase
 * \brief MYSQL implementation of the Database
 */
class MYSQLDatabase : public Database{
public :
  /**
   * \brief Function to process the request in the database
   * \param request The request to process (must contain a SINGLE SQL statement without a semicolumn)
   * \param transacId the id of the transaction if one is used
   * \return 0 on success, an error code otherwise
   */
  int
  process(std::string request, int transacId = -1);
  /**
  * \brief To make a create a pool of MySQL connections
  * \return raises an exception on error
  */
  int
  connect();

  /**
  * \brief To make a connection to the database and store the return db handler to a given pool's index
  * \param poolIdx the index in connexion pool
  * \return raises an exception on error
  */
  void connectPoolIndex(const int& poolIdx);

  /**
   * \brief Constructor, raises an exception on error
   * \param dbConfig  the configuration of the database client
   */
  MYSQLDatabase(DbConfiguration dbConfig);

  /**
   * \brief Destructor, raises an exception on error
   */
  ~MYSQLDatabase();

  /**
  * \brief To get the result of a select request
  * \param request The request to process
  * \param transacId the id of the transaction if one is used
  * \return An object which encapsulates the database results
  */
  DatabaseResult*
  getResult(std::string request, int transacId = -1);

  /**
   * \brief To get the type of database
   * \return An enum identifying the type of database
   */
  DbConfiguration::db_type_t
  getDbType() { return DbConfiguration::MYSQL; }

  /**
 * \brief Start a transaction
 * \return The transaction ID
 */
  virtual int
  startTransaction();

  /**
 * \brief End a transaction
 * \param transactionID: The ID of the transaction
 */
  virtual void
  endTransaction(int transactionID);

  /**
 * \brief Cancel a transaction
 * \param transactionID: The ID of the transaction
 */
  virtual void
  cancelTransaction(int transactionID);

  /**
 * \brief To commit a transaction
 * \param transactionID: The ID of the transaction
 */
  virtual void
  flush(int transactionID);
  /**
 * \brief To get a unique id
 * \param table: The table to use to generate the id
 * \param fields: The fields of the table
 * \param val: The values of the fields to insert
 * \param tid: The transaction id
 * \param primary the primary key on the table
 * \return A new integer never returned by this function
 */
  virtual int
  generateId(std::string table, std::string fields, std::string val, int tid, std::string primary);
/**
 * \brief To get a request from a request file based on a key
 * \param key the key indicating the request to get
 * \return the corresponding sql request
 */
  virtual std::string
  getRequest(const int key);

  /**
   * @brief escapeData : transform a sql data to a SQL-escaped string for MySQL
   * @param data: the string to transform
   * @return a espaced string
   */
  virtual std::string
  escapeData(const std::string& data);

private :
  /**
   * \brief To get a valid connexion
   * \param pos The position of the connection gotten in the pool
   * \return A valid and free connection
   */
  MYSQL* getConnection(int& pos);

  /**
   * \brief To release a connexion
   * \param pos The position of the connection to release
   */
  void releaseConnection(int pos);

  /**
   * \brief An element of the pool
   */
  typedef struct pool_t{
    /**
     * \brief If the connexion is used
     */
    bool mused;
    /**
     * \brief The connection mysql structure
     */
    MYSQL mmysql;
    /**
     * \brief The associated mutex
     */
    pthread_mutex_t mmutex;
  }pool_t;
  /////////////////////////////////
  // Attributes
  /////////////////////////////////
  /**
   * \brief The configuration of the database client
   */
  DbConfiguration mconfig;
  /**
   * \brief The pool of connection
   */
  pool_t *mpool;

  /////////////////////////////////
  // Functions
  /////////////////////////////////
  /**
   * \brief To disconnect from the database
   * \return 0 on success, an error code otherwise
   */
  int
  disconnect();

  /**
   * \brief Request factory
   */
  MYSQLRequestFactory mmysqlfact;
};


#endif // MYSQLDATABASE
