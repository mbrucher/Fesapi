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

public class LogVector : global::System.IDisposable, global::System.Collections.IEnumerable
    , global::System.Collections.Generic.IList<f2i.energisticsStandardsApi.witsml1_4_1_1.Log>
 {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal LogVector(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(LogVector obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~LogVector() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          fesapiPINVOKE.delete_LogVector(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public LogVector(global::System.Collections.ICollection c) : this() {
    if (c == null)
      throw new global::System.ArgumentNullException("c");
    foreach (f2i.energisticsStandardsApi.witsml1_4_1_1.Log element in c) {
      this.Add(element);
    }
  }

  public bool IsFixedSize {
    get {
      return false;
    }
  }

  public bool IsReadOnly {
    get {
      return false;
    }
  }

  public f2i.energisticsStandardsApi.witsml1_4_1_1.Log this[int index]  {
    get {
      return getitem(index);
    }
    set {
      setitem(index, value);
    }
  }

  public int Capacity {
    get {
      return (int)capacity();
    }
    set {
      if (value < size())
        throw new global::System.ArgumentOutOfRangeException("Capacity");
      reserve((uint)value);
    }
  }

  public int Count {
    get {
      return (int)size();
    }
  }

  public bool IsSynchronized {
    get {
      return false;
    }
  }

  public void CopyTo(f2i.energisticsStandardsApi.witsml1_4_1_1.Log[] array)
  {
    CopyTo(0, array, 0, this.Count);
  }

  public void CopyTo(f2i.energisticsStandardsApi.witsml1_4_1_1.Log[] array, int arrayIndex)
  {
    CopyTo(0, array, arrayIndex, this.Count);
  }

  public void CopyTo(int index, f2i.energisticsStandardsApi.witsml1_4_1_1.Log[] array, int arrayIndex, int count)
  {
    if (array == null)
      throw new global::System.ArgumentNullException("array");
    if (index < 0)
      throw new global::System.ArgumentOutOfRangeException("index", "Value is less than zero");
    if (arrayIndex < 0)
      throw new global::System.ArgumentOutOfRangeException("arrayIndex", "Value is less than zero");
    if (count < 0)
      throw new global::System.ArgumentOutOfRangeException("count", "Value is less than zero");
    if (array.Rank > 1)
      throw new global::System.ArgumentException("Multi dimensional array.", "array");
    if (index+count > this.Count || arrayIndex+count > array.Length)
      throw new global::System.ArgumentException("Number of elements to copy is too large.");
    for (int i=0; i<count; i++)
      array.SetValue(getitemcopy(index+i), arrayIndex+i);
  }

  global::System.Collections.Generic.IEnumerator<f2i.energisticsStandardsApi.witsml1_4_1_1.Log> global::System.Collections.Generic.IEnumerable<f2i.energisticsStandardsApi.witsml1_4_1_1.Log>.GetEnumerator() {
    return new LogVectorEnumerator(this);
  }

  global::System.Collections.IEnumerator global::System.Collections.IEnumerable.GetEnumerator() {
    return new LogVectorEnumerator(this);
  }

  public LogVectorEnumerator GetEnumerator() {
    return new LogVectorEnumerator(this);
  }

  // Type-safe enumerator
  /// Note that the IEnumerator documentation requires an InvalidOperationException to be thrown
  /// whenever the collection is modified. This has been done for changes in the size of the
  /// collection but not when one of the elements of the collection is modified as it is a bit
  /// tricky to detect unmanaged code that modifies the collection under our feet.
  public sealed class LogVectorEnumerator : global::System.Collections.IEnumerator
    , global::System.Collections.Generic.IEnumerator<f2i.energisticsStandardsApi.witsml1_4_1_1.Log>
  {
    private LogVector collectionRef;
    private int currentIndex;
    private object currentObject;
    private int currentSize;

    public LogVectorEnumerator(LogVector collection) {
      collectionRef = collection;
      currentIndex = -1;
      currentObject = null;
      currentSize = collectionRef.Count;
    }

    // Type-safe iterator Current
    public f2i.energisticsStandardsApi.witsml1_4_1_1.Log Current {
      get {
        if (currentIndex == -1)
          throw new global::System.InvalidOperationException("Enumeration not started.");
        if (currentIndex > currentSize - 1)
          throw new global::System.InvalidOperationException("Enumeration finished.");
        if (currentObject == null)
          throw new global::System.InvalidOperationException("Collection modified.");
        return (f2i.energisticsStandardsApi.witsml1_4_1_1.Log)currentObject;
      }
    }

    // Type-unsafe IEnumerator.Current
    object global::System.Collections.IEnumerator.Current {
      get {
        return Current;
      }
    }

    public bool MoveNext() {
      int size = collectionRef.Count;
      bool moveOkay = (currentIndex+1 < size) && (size == currentSize);
      if (moveOkay) {
        currentIndex++;
        currentObject = collectionRef[currentIndex];
      } else {
        currentObject = null;
      }
      return moveOkay;
    }

    public void Reset() {
      currentIndex = -1;
      currentObject = null;
      if (collectionRef.Count != currentSize) {
        throw new global::System.InvalidOperationException("Collection modified.");
      }
    }

    public void Dispose() {
        currentIndex = -1;
        currentObject = null;
    }
  }

  public void Clear() {
    fesapiPINVOKE.LogVector_Clear(swigCPtr);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Add(f2i.energisticsStandardsApi.witsml1_4_1_1.Log x) {
    fesapiPINVOKE.LogVector_Add(swigCPtr, f2i.energisticsStandardsApi.witsml1_4_1_1.Log.getCPtr(x));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  private uint size() {
    uint ret = fesapiPINVOKE.LogVector_size(swigCPtr);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private uint capacity() {
    uint ret = fesapiPINVOKE.LogVector_capacity(swigCPtr);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private void reserve(uint n) {
    fesapiPINVOKE.LogVector_reserve(swigCPtr, n);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public LogVector() : this(fesapiPINVOKE.new_LogVector__SWIG_0(), true) {
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public LogVector(LogVector other) : this(fesapiPINVOKE.new_LogVector__SWIG_1(LogVector.getCPtr(other)), true) {
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public LogVector(int capacity) : this(fesapiPINVOKE.new_LogVector__SWIG_2(capacity), true) {
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  private f2i.energisticsStandardsApi.witsml1_4_1_1.Log getitemcopy(int index) {
    global::System.IntPtr cPtr = fesapiPINVOKE.LogVector_getitemcopy(swigCPtr, index);
    f2i.energisticsStandardsApi.witsml1_4_1_1.Log ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.witsml1_4_1_1.Log(cPtr, false);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private f2i.energisticsStandardsApi.witsml1_4_1_1.Log getitem(int index) {
    global::System.IntPtr cPtr = fesapiPINVOKE.LogVector_getitem(swigCPtr, index);
    f2i.energisticsStandardsApi.witsml1_4_1_1.Log ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.witsml1_4_1_1.Log(cPtr, false);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private void setitem(int index, f2i.energisticsStandardsApi.witsml1_4_1_1.Log val) {
    fesapiPINVOKE.LogVector_setitem(swigCPtr, index, f2i.energisticsStandardsApi.witsml1_4_1_1.Log.getCPtr(val));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void AddRange(LogVector values) {
    fesapiPINVOKE.LogVector_AddRange(swigCPtr, LogVector.getCPtr(values));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public LogVector GetRange(int index, int count) {
    global::System.IntPtr cPtr = fesapiPINVOKE.LogVector_GetRange(swigCPtr, index, count);
    LogVector ret = (cPtr == global::System.IntPtr.Zero) ? null : new LogVector(cPtr, true);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Insert(int index, f2i.energisticsStandardsApi.witsml1_4_1_1.Log x) {
    fesapiPINVOKE.LogVector_Insert(swigCPtr, index, f2i.energisticsStandardsApi.witsml1_4_1_1.Log.getCPtr(x));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void InsertRange(int index, LogVector values) {
    fesapiPINVOKE.LogVector_InsertRange(swigCPtr, index, LogVector.getCPtr(values));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void RemoveAt(int index) {
    fesapiPINVOKE.LogVector_RemoveAt(swigCPtr, index);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void RemoveRange(int index, int count) {
    fesapiPINVOKE.LogVector_RemoveRange(swigCPtr, index, count);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public static LogVector Repeat(f2i.energisticsStandardsApi.witsml1_4_1_1.Log value, int count) {
    global::System.IntPtr cPtr = fesapiPINVOKE.LogVector_Repeat(f2i.energisticsStandardsApi.witsml1_4_1_1.Log.getCPtr(value), count);
    LogVector ret = (cPtr == global::System.IntPtr.Zero) ? null : new LogVector(cPtr, true);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Reverse() {
    fesapiPINVOKE.LogVector_Reverse__SWIG_0(swigCPtr);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Reverse(int index, int count) {
    fesapiPINVOKE.LogVector_Reverse__SWIG_1(swigCPtr, index, count);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void SetRange(int index, LogVector values) {
    fesapiPINVOKE.LogVector_SetRange(swigCPtr, index, LogVector.getCPtr(values));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool Contains(f2i.energisticsStandardsApi.witsml1_4_1_1.Log value) {
    bool ret = fesapiPINVOKE.LogVector_Contains(swigCPtr, f2i.energisticsStandardsApi.witsml1_4_1_1.Log.getCPtr(value));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int IndexOf(f2i.energisticsStandardsApi.witsml1_4_1_1.Log value) {
    int ret = fesapiPINVOKE.LogVector_IndexOf(swigCPtr, f2i.energisticsStandardsApi.witsml1_4_1_1.Log.getCPtr(value));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int LastIndexOf(f2i.energisticsStandardsApi.witsml1_4_1_1.Log value) {
    int ret = fesapiPINVOKE.LogVector_LastIndexOf(swigCPtr, f2i.energisticsStandardsApi.witsml1_4_1_1.Log.getCPtr(value));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool Remove(f2i.energisticsStandardsApi.witsml1_4_1_1.Log value) {
    bool ret = fesapiPINVOKE.LogVector_Remove(swigCPtr, f2i.energisticsStandardsApi.witsml1_4_1_1.Log.getCPtr(value));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}
