/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.sysfera.vishnu.api.vishnu.internal;

public class ESysInfoList {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected ESysInfoList(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(ESysInfoList obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        VISHNUJNI.delete_ESysInfoList(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void insert_all(ESysInfoList _q) {
    VISHNUJNI.ESysInfoList_insert_all(swigCPtr, this, ESysInfoList.getCPtr(_q), _q);
  }

  public void insert_at(long _pos, SystemInfo _obj) {
    VISHNUJNI.ESysInfoList_insert_at(swigCPtr, this, _pos, SystemInfo.getCPtr(_obj), _obj);
  }

  public SystemInfo at(long _index) {
    long cPtr = VISHNUJNI.ESysInfoList_at(swigCPtr, this, _index);
    return (cPtr == 0) ? null : new SystemInfo(cPtr, false);
  }

  public SystemInfo get(long _index) {
    long cPtr = VISHNUJNI.ESysInfoList_get(swigCPtr, this, _index);
    return (cPtr == 0) ? null : new SystemInfo(cPtr, false);
  }

  public void push_back(SystemInfo _obj) {
    VISHNUJNI.ESysInfoList_push_back(swigCPtr, this, SystemInfo.getCPtr(_obj), _obj);
  }

  public long size() {
    return VISHNUJNI.ESysInfoList_size(swigCPtr, this);
  }

  public void clear() {
    VISHNUJNI.ESysInfoList_clear(swigCPtr, this);
  }

}
