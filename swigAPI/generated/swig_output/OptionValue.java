/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.sysfera.vishnu.api.vishnu.internal;

public class OptionValue extends EObject {
  private long swigCPtr;

  public OptionValue(long cPtr, boolean cMemoryOwn) {
    super(VISHNUJNI.OptionValue_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(OptionValue obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        VISHNUJNI.delete_OptionValue(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public OptionValue() {
    this(VISHNUJNI.new_OptionValue(), true);
  }

  public void _initialize() {
    VISHNUJNI.OptionValue__initialize(swigCPtr, this);
  }

  public String getOptionName() {
    return VISHNUJNI.OptionValue_getOptionName(swigCPtr, this);
  }

  public void setOptionName(String _optionName) {
    VISHNUJNI.OptionValue_setOptionName(swigCPtr, this, _optionName);
  }

  public String getValue() {
    return VISHNUJNI.OptionValue_getValue(swigCPtr, this);
  }

  public void setValue(String _value) {
    VISHNUJNI.OptionValue_setValue(swigCPtr, this, _value);
  }

  public SWIGTYPE_p_ecorecpp__mapping__any eGet(int _featureID, boolean _resolve) {
    return new SWIGTYPE_p_ecorecpp__mapping__any(VISHNUJNI.OptionValue_eGet(swigCPtr, this, _featureID, _resolve), true);
  }

  public void eSet(int _featureID, SWIGTYPE_p_ecorecpp__mapping__any _newValue) {
    VISHNUJNI.OptionValue_eSet(swigCPtr, this, _featureID, SWIGTYPE_p_ecorecpp__mapping__any.getCPtr(_newValue));
  }

  public boolean eIsSet(int _featureID) {
    return VISHNUJNI.OptionValue_eIsSet(swigCPtr, this, _featureID);
  }

  public void eUnset(int _featureID) {
    VISHNUJNI.OptionValue_eUnset(swigCPtr, this, _featureID);
  }

  public SWIGTYPE_p_ecore__EClass _eClass() {
    long cPtr = VISHNUJNI.OptionValue__eClass(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_ecore__EClass(cPtr, false);
  }

}
