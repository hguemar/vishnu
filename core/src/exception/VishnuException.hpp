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

/**
 * \file VishnuException.hpp
 * \brief This file defines the super class for the Vishnu exceptions.
 * \author Kevin Coulomb (kevin.coulomb@sysfera.com)
 */
#ifndef __VISHNUEXCEPTION__
#define __VISHNUEXCEPTION__

#include <iostream>
#include <cstdlib>
#include <exception>
#include <map>

/**
 * \brief This class represents the root of all the exception of the system
 * \class VishnuException
 */
class VishnuException :
  public std::exception {
public:

  /**
   * \brief The type of exception
   */
typedef enum ExceptionType{
  /**
   * \brief UMS exception
   */
  UMS  	    = 0 ,
  /**
   * \brief TMS exception
   */
  TMS  	    = 1 ,
  /**
   * \brief FMS exception
   */
  FMS  	    = 2 ,
  /**
   * \brief IMS exception
   */
  IMS  	    = 3 ,
  /**
   * \brief internal exception
   */
  INTERNAL  = 4 ,
  /**
   * \brief not an exception
   */
  NONE      = 5
} ExceptionType;

private :

protected :

  /**
   * \brief Map containing The generic messages
   */
  mutable std::map<int, std::string> mp;
  /**
   *  \brief A complementatry message to the exception
   */
  std::string   mmsgc;
  /**
   *  \brief The type of the exception (UMS, TMS, FMS, IMS, NONE)
   */
  ExceptionType mtype;
  /**
   *  \brief An exception code refereing to a generic message. -1 means no generic error message.
   */
  int           mval;
  /**
   * \brief The full exception message
   */
  mutable std::string   mfullMsg;

public :

  /**
   * \brief Default constructor
   * \fn VishnuException()
   */
  VishnuException();
  /**
   * \brief Copy constructor
   * \fn VishnuException(const VishnuException& e)
   */
  VishnuException(const VishnuException& e);
  /**
   * \brief Constructor
   * \fn VishnuException(int msg, std::string msgComp = "")
   */
  VishnuException(int msg, std::string msgComp = "");
  /**
   * \brief Default destructor
   * \fn ~VishnuException() throw()
   */
  virtual ~VishnuException() throw(){};
  /**
   * \brief To get the type of the exception in integer
   * \fn ExceptionType getTypeI() const
   * \return Returns the type of the exception
   */
  ExceptionType
  getTypeI() const {return mtype;}
  /**
   * \brief Function to get the exception type in string
   * \fn virtual std::string getTypeS() const
   * \return Returns the type of the exception
   */
  virtual std::string
  getTypeS() const {return "";};
  /**
   * \brief To get a complement to the message
   * \fn virtual const char* what()const throw()
   * \return Returns a complement to the generic error message
   */
  virtual const char*
  what() const throw();
  /**
   * \brief To get the generic message
   * \fn virtual std::string getMsg() const
   * \return Returns the message
   */
  virtual std::string
  getMsg() const {return "";}

  /**
   * \brief To get the complementary message
   * \return Returns the message
   */
  virtual std::string
  getMsgComp() const {return mmsgc;}
  /**
   * \brief Function to set the type of the exception
   * \fn void setType(ExceptionType t)
   * \param t The type of the exception
   */
  void
  setType(ExceptionType t){mtype = t;}
  /**
   * \brief Function to set the complement of a message
   * \fn void setMsgComp(std::string m)
   * \param m The complement of the message
   */
  void
  setMsgComp(std::string m){mmsgc = m;}
  /**
   * \brief Function to set the generic message
   * \fn void setMsg(int val)
   * \param val The val of the msg
   */
  void
  setMsg(int val){mval = val;}
  /**
   * \brief Function to append a complement to the detailled message
   * \fn void appendMsgComp(std::string s)
   * \param s The message to append
   */
  void
  appendMsgComp(std::string s);
  /**
   * \brief To get the mval as an int
   * \fn int getMsgI() const
   */
  int
  getMsgI() const;
  /**
   * \brief Function to initialize all the generic messages
   * \fn virtual void initMsg() = 0
   */
  virtual void
  initMsg() = 0;
  /**
  * \brief Function to get the string associated to the exception
  * \fn    std::string buildExceptionString() const
  * \return the exception as a string
  */
  std::string
  buildExceptionString() const;
};

#endif // VISHNUEXCEPTION
