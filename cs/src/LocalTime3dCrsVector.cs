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

public class LocalTime3dCrsVector : global::System.IDisposable, global::System.Collections.IEnumerable
    , global::System.Collections.Generic.IList<f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs>
 {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal LocalTime3dCrsVector(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(LocalTime3dCrsVector obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~LocalTime3dCrsVector() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          fesapiPINVOKE.delete_LocalTime3dCrsVector(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public LocalTime3dCrsVector(global::System.Collections.ICollection c) : this() {
    if (c == null)
      throw new global::System.ArgumentNullException("c");
    foreach (f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs element in c) {
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

  public f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs this[int index]  {
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

  public void CopyTo(f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs[] array)
  {
    CopyTo(0, array, 0, this.Count);
  }

  public void CopyTo(f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs[] array, int arrayIndex)
  {
    CopyTo(0, array, arrayIndex, this.Count);
  }

  public void CopyTo(int index, f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs[] array, int arrayIndex, int count)
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

  global::System.Collections.Generic.IEnumerator<f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs> global::System.Collections.Generic.IEnumerable<f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs>.GetEnumerator() {
    return new LocalTime3dCrsVectorEnumerator(this);
  }

  global::System.Collections.IEnumerator global::System.Collections.IEnumerable.GetEnumerator() {
    return new LocalTime3dCrsVectorEnumerator(this);
  }

  public LocalTime3dCrsVectorEnumerator GetEnumerator() {
    return new LocalTime3dCrsVectorEnumerator(this);
  }

  // Type-safe enumerator
  /// Note that the IEnumerator documentation requires an InvalidOperationException to be thrown
  /// whenever the collection is modified. This has been done for changes in the size of the
  /// collection but not when one of the elements of the collection is modified as it is a bit
  /// tricky to detect unmanaged code that modifies the collection under our feet.
  public sealed class LocalTime3dCrsVectorEnumerator : global::System.Collections.IEnumerator
    , global::System.Collections.Generic.IEnumerator<f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs>
  {
    private LocalTime3dCrsVector collectionRef;
    private int currentIndex;
    private object currentObject;
    private int currentSize;

    public LocalTime3dCrsVectorEnumerator(LocalTime3dCrsVector collection) {
      collectionRef = collection;
      currentIndex = -1;
      currentObject = null;
      currentSize = collectionRef.Count;
    }

    // Type-safe iterator Current
    public f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs Current {
      get {
        if (currentIndex == -1)
          throw new global::System.InvalidOperationException("Enumeration not started.");
        if (currentIndex > currentSize - 1)
          throw new global::System.InvalidOperationException("Enumeration finished.");
        if (currentObject == null)
          throw new global::System.InvalidOperationException("Collection modified.");
        return (f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs)currentObject;
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
    fesapiPINVOKE.LocalTime3dCrsVector_Clear(swigCPtr);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Add(f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs x) {
    fesapiPINVOKE.LocalTime3dCrsVector_Add(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs.getCPtr(x));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  private uint size() {
    uint ret = fesapiPINVOKE.LocalTime3dCrsVector_size(swigCPtr);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private uint capacity() {
    uint ret = fesapiPINVOKE.LocalTime3dCrsVector_capacity(swigCPtr);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private void reserve(uint n) {
    fesapiPINVOKE.LocalTime3dCrsVector_reserve(swigCPtr, n);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public LocalTime3dCrsVector() : this(fesapiPINVOKE.new_LocalTime3dCrsVector__SWIG_0(), true) {
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public LocalTime3dCrsVector(LocalTime3dCrsVector other) : this(fesapiPINVOKE.new_LocalTime3dCrsVector__SWIG_1(LocalTime3dCrsVector.getCPtr(other)), true) {
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public LocalTime3dCrsVector(int capacity) : this(fesapiPINVOKE.new_LocalTime3dCrsVector__SWIG_2(capacity), true) {
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  private f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs getitemcopy(int index) {
    global::System.IntPtr cPtr = fesapiPINVOKE.LocalTime3dCrsVector_getitemcopy(swigCPtr, index);
    f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs(cPtr, false);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs getitem(int index) {
    global::System.IntPtr cPtr = fesapiPINVOKE.LocalTime3dCrsVector_getitem(swigCPtr, index);
    f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs(cPtr, false);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private void setitem(int index, f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs val) {
    fesapiPINVOKE.LocalTime3dCrsVector_setitem(swigCPtr, index, f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs.getCPtr(val));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void AddRange(LocalTime3dCrsVector values) {
    fesapiPINVOKE.LocalTime3dCrsVector_AddRange(swigCPtr, LocalTime3dCrsVector.getCPtr(values));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public LocalTime3dCrsVector GetRange(int index, int count) {
    global::System.IntPtr cPtr = fesapiPINVOKE.LocalTime3dCrsVector_GetRange(swigCPtr, index, count);
    LocalTime3dCrsVector ret = (cPtr == global::System.IntPtr.Zero) ? null : new LocalTime3dCrsVector(cPtr, true);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Insert(int index, f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs x) {
    fesapiPINVOKE.LocalTime3dCrsVector_Insert(swigCPtr, index, f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs.getCPtr(x));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void InsertRange(int index, LocalTime3dCrsVector values) {
    fesapiPINVOKE.LocalTime3dCrsVector_InsertRange(swigCPtr, index, LocalTime3dCrsVector.getCPtr(values));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void RemoveAt(int index) {
    fesapiPINVOKE.LocalTime3dCrsVector_RemoveAt(swigCPtr, index);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void RemoveRange(int index, int count) {
    fesapiPINVOKE.LocalTime3dCrsVector_RemoveRange(swigCPtr, index, count);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public static LocalTime3dCrsVector Repeat(f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs value, int count) {
    global::System.IntPtr cPtr = fesapiPINVOKE.LocalTime3dCrsVector_Repeat(f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs.getCPtr(value), count);
    LocalTime3dCrsVector ret = (cPtr == global::System.IntPtr.Zero) ? null : new LocalTime3dCrsVector(cPtr, true);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Reverse() {
    fesapiPINVOKE.LocalTime3dCrsVector_Reverse__SWIG_0(swigCPtr);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Reverse(int index, int count) {
    fesapiPINVOKE.LocalTime3dCrsVector_Reverse__SWIG_1(swigCPtr, index, count);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void SetRange(int index, LocalTime3dCrsVector values) {
    fesapiPINVOKE.LocalTime3dCrsVector_SetRange(swigCPtr, index, LocalTime3dCrsVector.getCPtr(values));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool Contains(f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs value) {
    bool ret = fesapiPINVOKE.LocalTime3dCrsVector_Contains(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs.getCPtr(value));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int IndexOf(f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs value) {
    int ret = fesapiPINVOKE.LocalTime3dCrsVector_IndexOf(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs.getCPtr(value));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int LastIndexOf(f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs value) {
    int ret = fesapiPINVOKE.LocalTime3dCrsVector_LastIndexOf(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs.getCPtr(value));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool Remove(f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs value) {
    bool ret = fesapiPINVOKE.LocalTime3dCrsVector_Remove(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.LocalTime3dCrs.getCPtr(value));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}
