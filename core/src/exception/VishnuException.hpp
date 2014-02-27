/**
 * \file VishnuException.hpp
 * \brief This file defines the super class for the Vishnu exceptions.
 * \author Kevin Coulomb (kevin.coulomb@sysfera.com)
 */
#ifndef __VISHNUEXCEPTION__
#define __VISHNUEXCEPTION__

#include <exception>
#include <map>
#include <string>

/**
 * \brief If everything is ok , no need to define exception so
 */
static const int VISHNU_OK = 0;
/**
 * \brief This class represents the root of all the exception of the system
 * \class VishnuException
 */
class VishnuException : public std::exception {
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
     * \brief internal exception
     */
    INTERNAL  = 4 ,
    /**
     * \brief not an exception
     */
    NONE      = 5
  } ExceptionType;

  /**
   * \brief Default constructor
   */
  VishnuException();
  /**
   * \brief Copy constructor
   */
  VishnuException(const VishnuException& e);
  /**
   * \brief Constructor
   */
  VishnuException(int msg, std::string msgComp = "");
  /**
   * \brief Default destructor
   */
  virtual ~VishnuException() throw(){};
  /**
   * \brief To get the type of the exception in integer
   * \return Returns the type of the exception
   */
  ExceptionType
  getTypeI() const {return mtype;}
  /**
   * \brief Function to get the exception type in string
   * \return Returns the type of the exception
   */
  virtual std::string
  getTypeS() const {return "";};
  /**
   * \brief To get a complement to the message
   * \return Returns a complement to the generic error message
   */
  virtual const char*
  what() const throw();
  /**
   * \brief To get the generic message
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
   * \param t The type of the exception
   */
  void
  setType(ExceptionType t){mtype = t;}
  /**
   * \brief Function to set the complement of a message
   * \param m The complement of the message
   */
  void
  setMsgComp(std::string m){mmsgc = m;}
  /**
   * \brief Function to set the generic message
   * \param val The val of the msg
   */
  void
  setMsg(int val){mval = val;}
  /**
   * \brief Function to append a complement to the detailled message
   * \param s The message to append
   */
  void
  appendMsgComp(std::string s);
  /**
   * \brief To get the mval as an int
   */
  int
  getMsgI() const;
  /**
   * \brief Function to initialize all the generic messages
   */
  virtual void
  initMsg() = 0;
  /**
   * \brief Function to get the string associated to the exception
   * \return the exception as a string
   */
  std::string
  buildExceptionString() const;
  /**
   * \brief Implementation of the equal operator
   * \param e the object to assign
   * \return the object exception with the new values
   */
  VishnuException&
  operator=(const VishnuException &e);


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
   *  \brief The type of the exception (UMS, TMS, FMS, NONE)
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
};

#endif // VISHNUEXCEPTION
