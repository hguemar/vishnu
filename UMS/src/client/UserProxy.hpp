/**
 * \file UserProxy.hpp
 * \brief This file contains the VISHNU UserProxy class.
 * \authors Daouda Traore (daouda.traore@sysfera.com)
 */
#ifndef _USER_PROXY_H_
#define _USER_PROXY_H_

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

//class UserProxy;
class SessionProxy;
#include "SessionProxy.hpp"
#include "User.hpp"

/**
 * \class UserProxy 
 * \brief UserProxy class implementation 
 */
class UserProxy
{

public:
 
 /**
  * \fn  UserProxy(const std::string& userId, const std::string& password) 
  * \param userId the user identifier
  * \password the user password 
  * \brief Constructor, raises an exception on error
  */	
  UserProxy(const std::string& userId, const std::string& password);
 /**
  * \fn explicit explicit UserProxy(SessionProxy session) 
  * \param session The object which encapsulates the session information (ex: identifier of the session)
  * \brief Constructor, raises an exception on error
  */
  explicit UserProxy(SessionProxy session);
  /**
  * \fn explicit UserProxy(const UMS_Data::User& user) 
  * \param user The object which encapsulates the user information 
  * \brief Constructor, raises an exception on error
  */
  explicit UserProxy(const UMS_Data::User& user);
  /**
   * \brief Function to add new user 
   * \fn  int add(const UMS_Data::User& user)
   * \param user The object which encapsulates the user information
   * \return raises an exception on error
   */
  int add(const UMS_Data::User& newUser);
  /**
   * \brief Function to update user information 
   * \fn  int update(const UMS_Data::User& user)
   * \param user The object which encapsulates the user information
   * \return raises an exception on error
   */
  int update(const UMS_Data::User& user);
  /**
   * \brief Function to remove user information 
   * \fn  int deleteUser(const UMS_Data::User& user) 
   * \param user The object which encapsulates the user information
   * \return raises an exception on error
   */
  int deleteUser(const UMS_Data::User& user);
  /**
   * \brief Function to change user password 
   * \fn  int changePassword(const std::string& password, const std::string& newPassword) 
   * \param oldPassword the old password of the user
   * \param newPassword the new password of the user 
   * \return raises an exception on error
   */
  int changePassword(const std::string& oldPassword, const std::string& newPassword);
  /**
   * \brief Function to reset user password 
   * \fn  int resetPassword(UMS_Data::User& user)
   * \param user The object which encapsulates the user information 
   * \return raises an exception on error
   */
  int resetPassword(UMS_Data::User& user);
  /**
   * \brief Function get user information 
   * \fn  UMS_Data::User getData()
   * \return User object encapsulates the information of the user 
   * \return raises an exception on error
   */
  UMS_Data::User getData() const;
  /**
   * \brief Function get SessionProxy object which contains the VISHNU session identifier 
   * \fn SessionProxy getSessionProxy() 
   * \return a SessionProy object which contains the VISHNU session information 
   * \return raises an exception on error
   */
  SessionProxy getSessionProxy() const;

  /**
   * \fn ~UserProxy()
   * \brief Destructor, raises an exception on error
   */	
  ~UserProxy();

private:

  /**
   * \brief Function to combine add() and update() into one function 
   * \fn  int _addUserInformation(const UMS_Data::User& user, bool isNewUser=true)
   * \param user The object which encapsulates the user information 
   * \param isNewUser to select the call of add or update function 
   * \return raises an exception on error
   */
  int _addUserInformation(const UMS_Data::User& user, bool isNewUser=true);

   /////////////////////////////////
  // Attributes
  /////////////////////////////////

 /**
  * \brief The object which encapsulates the user information 
  */
  UMS_Data::User muser;
 /**
  * \brief The pointer to the SessionProxy object containing the encrypted identifier of the session
  *  generated by VISHNU
  */
  SessionProxy* msessionProxy;

};
#endif
