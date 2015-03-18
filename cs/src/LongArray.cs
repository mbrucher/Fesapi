//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.5
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace f2i.energisticsStandardsApi {

public class LongArray : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal LongArray(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(LongArray obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~LongArray() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          energisticsApiPINVOKE.delete_LongArray(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public LongArray(int nelements) : this(energisticsApiPINVOKE.new_LongArray(nelements), true) {
  }

  public int getitem(int index) {
    int ret = energisticsApiPINVOKE.LongArray_getitem(swigCPtr, index);
    return ret;
  }

  public void setitem(int index, int value) {
    energisticsApiPINVOKE.LongArray_setitem(swigCPtr, index, value);
  }

  public SWIGTYPE_p_long cast() {
    global::System.IntPtr cPtr = energisticsApiPINVOKE.LongArray_cast(swigCPtr);
    SWIGTYPE_p_long ret = (cPtr == global::System.IntPtr.Zero) ? null : new SWIGTYPE_p_long(cPtr, false);
    return ret;
  }

  public static LongArray frompointer(SWIGTYPE_p_long t) {
    global::System.IntPtr cPtr = energisticsApiPINVOKE.LongArray_frompointer(SWIGTYPE_p_long.getCPtr(t));
    LongArray ret = (cPtr == global::System.IntPtr.Zero) ? null : new LongArray(cPtr, false);
    return ret;
  }

}

}