/**
* \file UserServer.cpp
* \brief This file implements the Class which manipulates VISHNU user data on server side.
* \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
* \date 31/01/2011
*/

#include "UserServer.hpp"

/**
* \brief Constructor
* \fn UserServer(std::string userId, std::string password)
* \param userId The userId of the user
* \param password The password of the user
*/
UserServer::UserServer(std::string userId, std::string password) {
  DbFactory factory;
  muser.setUserId(userId);
  muser.setPassword(password);
  mdatabaseVishnu = factory.getDatabaseInstance();
  msessionServer = NULL;
}

/**
* \brief Constructor
* \fn UserServer(const UMS_Data::User& user)
* \param user The user data structure
*/
UserServer::UserServer(const UMS_Data::User& user):muser(user) {
  DbFactory factory;
  mdatabaseVishnu = factory.getDatabaseInstance();
  msessionServer = NULL;
}

/**
* \brief Constructor
* \fn UserServer(SessionServer sessionServer)
* \param sessionServer The object to manipulate session
*/
UserServer::UserServer(SessionServer sessionServer): msessionServer(&sessionServer) {
  DbFactory factory;
  mdatabaseVishnu = factory.getDatabaseInstance();
}

/**
* \brief Function to add a new VISHNU user
* \fn int add(UMS_Data::User*& user)
* \param user The user data structure
* \return raises an exception on error
*/
int
UserServer::add(UMS_Data::User*& user) {
  std::string pwd;
  std::string sqlInsert = "insert into users (vishnu_vishnuid, userid, pwd, firstname, lastname,\
  privilege, email, passwordstate, status) values ";

  std::string idUserGenerated;
  std::string passwordCrypted;
  //std::string salt;
  int userCpt;


  try {
    if (exist()) {
      if (isAdmin()) {

        //Generation of password
        pwd = generatePassword(user->getLastname(), user->getFirstname());
        user->setPassword(pwd.substr(0,PASSWORD_MAX_SIZE));

        std::cout << "========== Password generated:" << user->getPassword()<< "============" << std::endl;

        //To get the user counter
        userCpt = convertToInt(getAttrVishnu("usercpt", Vishnuid::mvishnuid));

        //Generation of userid
        idUserGenerated =
        getGeneratedName(getAttrVishnu("formatiduser", Vishnuid::mvishnuid).c_str(),
                                                      userCpt,
                                                      USER,
                                                      user->getLastname());

        incrementCpt("usercpt", userCpt);

        std::cout << "idgenerated" << idUserGenerated << std::endl;

        user->setUserId(idUserGenerated);

        //To get the password encrypted
        passwordCrypted = vishnu::cryptPassword(user->getUserId(), user->getPassword());

        //If the user to add exists
        if (getAttribut("where userid='"+user->getUserId()+"'").size() == 0) {

          //To insert user on the database
          mdatabaseVishnu->process(sqlInsert + "(" + Vishnuid::mvishnuid+", \
          '"+user->getUserId()+"','"+passwordCrypted+"','"
          + user->getFirstname()+"','"+user->getLastname()+"',"+
          convertToString(user->getPrivilege()) +",'"+user->getEmail() +"', \
          0, "+convertToString(user->getStatus())+")");

        }// END If the user to add exists
        else {
          UMSVishnuException e (ERRCODE_USERID_EXISTING);
          throw e;
        }
      } //END if the user is an admin
      else {
        UMSVishnuException e (ERRCODE_NO_ADMIN);
        throw e;
      }
    } //END if the user exists
    else {
      UMSVishnuException e (ERRCODE_UNKNOWN_USER);
      throw e;
    }
  }
  catch (VishnuException& e) {
    throw;
  }
  return 0;
}//END: add(UMS_Data::User*& user)

/**
* \brief Function to update user information
* \fn int update(UMS_Data::User*& user)
* \param user The user data structure
* \return raises an exception on error
*/
int
UserServer::update(UMS_Data::User *user) {
  std::string sqlCommand = "";
  try {
    if (exist()) {
      if (isAdmin()) {
        //if the user whose information will be updated exists
        if (getAttribut("where userid='"+user->getUserId()+"'").size() != 0) {

          //if a new fisrtname has been defined
          if (user->getFirstname().size() != 0) {
            sqlCommand.append("UPDATE users SET firstname='"+user->getFirstname()+"'"+"\
            where userid='"+user->getUserId()+"';");
          }

          //if a new lastname has been defined
          if (user->getLastname().size() != 0) {
            sqlCommand.append("UPDATE users SET lastname='"+user->getLastname()+"'"+"\
            where userid='"+user->getUserId()+"';");
          }

          //if a new email has been defined
          if (user->getEmail().size() != 0) {
            sqlCommand.append("UPDATE users SET email='"+user->getEmail()+"'"+"\
            where userid='"+user->getUserId()+"';");
          }

          //if the user will be locked
          if (user->getStatus() == 0) {
            //if the user is not already locked
            if (convertToInt(getAttribut("where userid='"+user->getUserId()+"'", "status")) != 0) {
              sqlCommand.append("UPDATE users SET status="+convertToString(user->getStatus())+""+"\
              where userid='"+user->getUserId()+"';");
            } //End if the user is not already locked
            else {
              UMSVishnuException e (ERRCODE_USER_ALREADY_LOCKED);
              throw e;
            }
          } //End if the user will be locked
          else {
            sqlCommand.append("UPDATE users SET status="+convertToString(user->getStatus())+""+"\
            where userid='"+user->getUserId()+"';");
          }

          // if the user whose privilege will be updated is not an admin
          if (convertToInt(getAttribut("where userid='"+user->getUserId()+"'", "privilege")) != 1) {
            sqlCommand.append("UPDATE users SET privilege="+convertToString(user->getPrivilege())+""+"\
            where userid='"+user->getUserId()+"';");
          }

          std::cout <<"SQL COMMAND:"<<sqlCommand;
          mdatabaseVishnu->process(sqlCommand.c_str());

        } // End if the user whose information will be updated exists
        else {
          UMSVishnuException e (ERRCODE_UNKNOWN_USERID);
          throw e;
        }
      } //END if the user is an admin
      else {
        UMSVishnuException e (ERRCODE_NO_ADMIN);
        throw e;
      }
    } //END if the user exists
    else {
      UMSVishnuException e (ERRCODE_UNKNOWN_USER);
      throw e;
    }
  }
  catch (VishnuException& e) {
    throw;
  }
  return 0;
} //END: update(UMS_Data::User *user)

/**
* \brief Function to delete VISHNU user
* \fn int deleteUser(UMS_Data::User user)
* \param user The user data structure
* \return raises an exception on error
*/
int
UserServer::deleteUser(UMS_Data::User user) {

  try {
    //If the user to delete is not the super VISHNU admin
    if (user.getUserId().compare(utilServer::ROOTUSERNAME) != 0) {
      //If the user exists
      if (exist()) {
        if (isAdmin()) {
          //if the user who will be deleted exist
          if (getAttribut("where userid='"+user.getUserId()+"'").size() != 0) {
            //Execution of the sql code to delete the user
            mdatabaseVishnu->process("DELETE FROM users where userid='"+user.getUserId()+"'");
          } // End if the user who will be deleted exist
          else {
            UMSVishnuException e (ERRCODE_UNKNOWN_USERID);
            throw e;
          }
        } //END if the user is an admin
        else {
          UMSVishnuException e (ERRCODE_NO_ADMIN);
          throw e;
        }
      } //END if the user exists
      else {
        UMSVishnuException e (ERRCODE_UNKNOWN_USER);
        throw e;
      }
    }//END If the user to delete is not the super VISHNU admin
    else {
      UserException e (ERRCODE_INVALID_PARAM, "It is not possible to delete this user. It is the VISHNU root user");
      throw e;
    }
  }
  catch (VishnuException& e) {
    throw;
  }
  return 0;
}//END: deleteUser(UMS_Data::User user)

/**
* \brief Function to change VISHNU user password
* \fn int changePassword(std::string newPassword)
* \param newPassword The new password of the user
* \return raises an exception on error
*/
int
UserServer::changePassword(std::string newPassword) {
  std::string sqlChangePwd;
  std::string sqlUpdatePwdState;
  std::string passwordCrypted;
  std::string salt;

  try {
    //If the user exist (the flagForChangePwd is set to true to avoid the password state checking)
    if (exist(true)) {

      //sql code to change the user password
      sqlChangePwd = "UPDATE users SET pwd='"+newPassword+"'where \
      userid='"+muser.getUserId()+"' and pwd='"+muser.getPassword()+"';";

      //sql code to update the passwordstate
      sqlUpdatePwdState = "UPDATE users SET passwordstate=1 \
      where userid='"+muser.getUserId()+"' and pwd='"+newPassword+"';";

      sqlChangePwd.append(sqlUpdatePwdState);
      mdatabaseVishnu->process(sqlChangePwd.c_str());

      //Put the new user's password
      muser.setPassword(newPassword);
    } //End If the user exist with the flagForChangePwd to true ti avoid the passwordstate checking
    else {
      UMSVishnuException e (ERRCODE_UNKNOWN_USER);
      throw e;
    }
  }
  catch (VishnuException& e) {
    throw;
  }
  return 0;
}//END: changePassword(std::string newPassword)

/**
* \brief Function to change VISHNU user password
* \fn int resetPassword(UMS_Data::User user)
* \param user The user data structure
* \return raises an exception on error
*/
int
UserServer::resetPassword(UMS_Data::User& user) {
  std::string sqlResetPwd;
  std::string sqlUpdatePwdState;
  std::string passwordCrypted;
  std::string pwd;

  try {
    //If the user exists
    if (exist()) {
      //if the user is an admin
      if (isAdmin()) {
        //if the user whose password will be reset exists
        if (getAttribut("where userid='"+user.getUserId()+"'").size() != 0) {
          //generation of a new password
          pwd = generatePassword(user.getUserId(), user.getUserId());
          user.setPassword(pwd.substr(0,PASSWORD_MAX_SIZE));
          std::cout << "========== Password reset:" << user.getPassword()<< "============" << std::endl;

          //to get the password encryptes
          passwordCrypted = vishnu::cryptPassword(user.getUserId(), user.getPassword());

          //The sql code to reset the password
          sqlResetPwd = "UPDATE users SET pwd='"+passwordCrypted+"'where \
          userid='"+user.getUserId()+"';";
          //sql code to update the passwordstate
          sqlUpdatePwdState = "UPDATE users SET passwordstate=0 \
          where userid='"+user.getUserId()+"' and pwd='"+passwordCrypted+"';";
          //To append the previous sql codes
          sqlResetPwd.append(sqlUpdatePwdState);
          //Execution of the sql code on the database
          mdatabaseVishnu->process( sqlResetPwd.c_str());
        } // End if the user whose password will be reset exists
        else {
          UMSVishnuException e (ERRCODE_UNKNOWN_USERID);
          throw e;
        }
      } //END if the user is an admin
      else {
        UMSVishnuException e (ERRCODE_NO_ADMIN);
        throw e;
      }
    } //END if the user exists
    else {
      UMSVishnuException e (ERRCODE_UNKNOWN_USER);
      throw e;
    }
  }
  catch (VishnuException& e) {
    throw;
  }
  return 0;
}//END: resetPassword(UMS_Data::User user)

/**
* \fn ~UserServer()
* \brief Destructor
*/
UserServer::~UserServer() {
}
/**
* \brief Function to get user information
* \fn UMS_Data::User getData()
* \return  The user data structure
*/
UMS_Data::User
UserServer::getData() {
  return muser;
}

/**
* \brief Function to initialize user data for constructor with sessionServer
* \fn init()
*/
void
UserServer::init(){
  std::string numUser;
  std::string sessionState;

  //if userId and password have not been defined
  if ((muser.getUserId().size() == 0) && (muser.getUserId().size() == 0)) {
    try {
      //To get the users_numuserid by using the sessionServer
      numUser =
      msessionServer->getAttribut("where\
      sessionkey='"+msessionServer->getData().getSessionKey()+"'", "users_numuserid");

      //if the session key is found
      if (numUser.size() != 0) {
        //To get the session state
        sessionState =
        msessionServer->getAttribut("where\
        sessionkey='"+msessionServer->getData().getSessionKey()+"'", "state");

        //if the session is active
        if (convertToInt(sessionState) == 1) {
          muser.setUserId(getAttribut("where numuserid='"+numUser+"'", "userid"));
          muser.setPassword(getAttribut("where numuserid='"+numUser+"'", "pwd"));
        } //End if the session is active
        else {
          UMSVishnuException e (ERRCODE_SESSIONKEY_EXPIRED);
          throw e;
        }

      } //END If the session key is found
      else {
        UMSVishnuException e (ERRCODE_SESSIONKEY_NOT_FOUND);
        throw e;
      }
    }
    catch (VishnuException& e) {
      throw;
    }
  }//END If the userId and password have not been defined
} //END: void init()
/**
* \brief Function to check user on database
* \fn bool exist(bool flagForChangePwd)
* \param flagForChangePwd A flag to check the password state
* \return true if the password state has not to be checked else false
*/
bool UserServer::exist(bool flagForChangePwd) {

  bool existUser = true;
  try {
      //If the user is on the database
    if (getAttribut("where userid='"+muser.getUserId()+"'and pwd='"+muser.getPassword()+"'").size() != 0) {
        //If the user is not locked
        if (isAttributOk("status", 1)) {
          //if the flag to check the password state is set
          if (!flagForChangePwd) {
            //If the passwordstate is active
            if (isAttributOk("passwordstate", 1)) {
              return existUser;
            } //END If the passwordstate is active
            else {
              UMSVishnuException e (ERRCODE_TEMPORARY_PASSWORD);
              throw e;
            }
          }//END the flag to check the password state is set
          else {
            return existUser;
          }
        } //END if the user is not locked
        else {
          UMSVishnuException e (ERRCODE_USER_LOCKED);
          throw e;
        }
    }//END if the user is on the database
    else {
      existUser = false;
    }
  }// END try
  catch (VishnuException& e) {
          throw;
  }
  return existUser;
} //END: exist(bool flagForChangePwd)

/**
* \brief Function to check the VISHNU user privilege
* \fn bool isAdmin()
* \return true if the user is an admin else false
*/
bool
UserServer::isAdmin() {
  try {
    return (convertToInt (getAttribut("where userid='"+muser.getUserId()+"'and \
    pwd='"+muser.getPassword()+"'", " privilege")) != 0);
  }
  catch (VishnuException& e) {
  throw;
  }
}

/**
* \brief Function to check the user attribut value
* \fn bool isAttributOk(std::string attributName, int valueOk)
* \param attributName The name of the attribut to check
* \param valueOk the value which will be compare to attribut name value
* \return true if the attributName value is valueOk
*/
bool
UserServer::isAttributOk(std::string attributName, int valueOk) {
  try {
    return (convertToInt(getAttribut("where userid='"+muser.getUserId()+"'and \
    pwd='"+muser.getPassword()+"'", attributName)) == valueOk);
  }
  catch (VishnuException& e) {
    throw;
  }
}

/**
* \brief Function to get user information from the database vishnu
* \fn getAttribut(std::string condition, std::string attrname);
* \param condition The condition of the select request
* \param attrname the name of the attribut to get
* \return the value of the attribut or empty string if no results
*/
std::string UserServer::getAttribut(std::string condition, std::string attrname) {

  DatabaseResult* result;
  std::vector<std::string>::iterator ii;

  std::string sqlCommand("SELECT "+attrname+" FROM users "+condition);
  std::cout << "SQL COMMAND:" << sqlCommand << std::endl;

  try {
    result = mdatabaseVishnu->getResult(sqlCommand.c_str());
    return result->getFirstElement();
  }
  catch (VishnuException& e) {
    throw;
  }

}

/**
* \brief Function to check a userId
* \fn bool existuserId(std::string userId)
* \param userId The userId to check
* \return true if the userId exists
*/
bool
UserServer::existuserId(std::string userId) {
  bool existUser = true;

  try {
    //If the userID exists on the database
    if (getAttribut("where userid='"+userId+"'").size() != 0)	{
      //If the user is not locked
      if ( convertToInt(getAttribut("where userid='"+userId+"'", "status")) == 1) {
        return existUser;
      } //END if the user is not locked
      else {
        UMSVishnuException e (ERRCODE_USER_LOCKED);
        throw e;
      }
    }//END If the userID exists on the database
    else {
      existUser = false;
    }
  }// END try
  catch (VishnuException& e) {
    throw;
  }
  return existUser;
}

/**
* \brief Function to generate a password
* \fn generatePassword(std::string value1, std::string value2)
* \param value1 a string used to generate the password
* \param value2 a string used to generate the password
* \return an encrypted message
*/
std::string
UserServer::generatePassword(std::string value1, std::string value2) {

  std::string salt = "$1$"+value1 + convertToString(utilServer::generate_numbers())+value2+"$";
  std::string clef = value2+convertToString(utilServer::generate_numbers());

  return (std::string(crypt(clef.c_str(), salt.c_str())+salt.length()));
}
