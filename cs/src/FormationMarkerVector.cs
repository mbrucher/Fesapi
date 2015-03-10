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

public class FormationMarkerVector : global::System.IDisposable, global::System.Collections.IEnumerable
    , global::System.Collections.Generic.IList<f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker>
 {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal FormationMarkerVector(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(FormationMarkerVector obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~FormationMarkerVector() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          energisticsApiPINVOKE.delete_FormationMarkerVector(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public FormationMarkerVector(global::System.Collections.ICollection c) : this() {
    if (c == null)
      throw new global::System.ArgumentNullException("c");
    foreach (f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker element in c) {
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

  public f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker this[int index]  {
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

  public void CopyTo(f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker[] array)
  {
    CopyTo(0, array, 0, this.Count);
  }

  public void CopyTo(f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker[] array, int arrayIndex)
  {
    CopyTo(0, array, arrayIndex, this.Count);
  }

  public void CopyTo(int index, f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker[] array, int arrayIndex, int count)
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

  global::System.Collections.Generic.IEnumerator<f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker> global::System.Collections.Generic.IEnumerable<f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker>.GetEnumerator() {
    return new FormationMarkerVectorEnumerator(this);
  }

  global::System.Collections.IEnumerator global::System.Collections.IEnumerable.GetEnumerator() {
    return new FormationMarkerVectorEnumerator(this);
  }

  public FormationMarkerVectorEnumerator GetEnumerator() {
    return new FormationMarkerVectorEnumerator(this);
  }

  // Type-safe enumerator
  /// Note that the IEnumerator documentation requires an InvalidOperationException to be thrown
  /// whenever the collection is modified. This has been done for changes in the size of the
  /// collection but not when one of the elements of the collection is modified as it is a bit
  /// tricky to detect unmanaged code that modifies the collection under our feet.
  public sealed class FormationMarkerVectorEnumerator : global::System.Collections.IEnumerator
    , global::System.Collections.Generic.IEnumerator<f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker>
  {
    private FormationMarkerVector collectionRef;
    private int currentIndex;
    private object currentObject;
    private int currentSize;

    public FormationMarkerVectorEnumerator(FormationMarkerVector collection) {
      collectionRef = collection;
      currentIndex = -1;
      currentObject = null;
      currentSize = collectionRef.Count;
    }

    // Type-safe iterator Current
    public f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker Current {
      get {
        if (currentIndex == -1)
          throw new global::System.InvalidOperationException("Enumeration not started.");
        if (currentIndex > currentSize - 1)
          throw new global::System.InvalidOperationException("Enumeration finished.");
        if (currentObject == null)
          throw new global::System.InvalidOperationException("Collection modified.");
        return (f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker)currentObject;
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
    energisticsApiPINVOKE.FormationMarkerVector_Clear(swigCPtr);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Add(f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker x) {
    energisticsApiPINVOKE.FormationMarkerVector_Add(swigCPtr, f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker.getCPtr(x));
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  private uint size() {
    uint ret = energisticsApiPINVOKE.FormationMarkerVector_size(swigCPtr);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private uint capacity() {
    uint ret = energisticsApiPINVOKE.FormationMarkerVector_capacity(swigCPtr);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private void reserve(uint n) {
    energisticsApiPINVOKE.FormationMarkerVector_reserve(swigCPtr, n);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public FormationMarkerVector() : this(energisticsApiPINVOKE.new_FormationMarkerVector__SWIG_0(), true) {
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public FormationMarkerVector(FormationMarkerVector other) : this(energisticsApiPINVOKE.new_FormationMarkerVector__SWIG_1(FormationMarkerVector.getCPtr(other)), true) {
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public FormationMarkerVector(int capacity) : this(energisticsApiPINVOKE.new_FormationMarkerVector__SWIG_2(capacity), true) {
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  private f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker getitemcopy(int index) {
    global::System.IntPtr cPtr = energisticsApiPINVOKE.FormationMarkerVector_getitemcopy(swigCPtr, index);
    f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker(cPtr, false);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker getitem(int index) {
    global::System.IntPtr cPtr = energisticsApiPINVOKE.FormationMarkerVector_getitem(swigCPtr, index);
    f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker(cPtr, false);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private void setitem(int index, f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker val) {
    energisticsApiPINVOKE.FormationMarkerVector_setitem(swigCPtr, index, f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker.getCPtr(val));
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void AddRange(FormationMarkerVector values) {
    energisticsApiPINVOKE.FormationMarkerVector_AddRange(swigCPtr, FormationMarkerVector.getCPtr(values));
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public FormationMarkerVector GetRange(int index, int count) {
    global::System.IntPtr cPtr = energisticsApiPINVOKE.FormationMarkerVector_GetRange(swigCPtr, index, count);
    FormationMarkerVector ret = (cPtr == global::System.IntPtr.Zero) ? null : new FormationMarkerVector(cPtr, true);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Insert(int index, f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker x) {
    energisticsApiPINVOKE.FormationMarkerVector_Insert(swigCPtr, index, f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker.getCPtr(x));
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void InsertRange(int index, FormationMarkerVector values) {
    energisticsApiPINVOKE.FormationMarkerVector_InsertRange(swigCPtr, index, FormationMarkerVector.getCPtr(values));
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void RemoveAt(int index) {
    energisticsApiPINVOKE.FormationMarkerVector_RemoveAt(swigCPtr, index);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void RemoveRange(int index, int count) {
    energisticsApiPINVOKE.FormationMarkerVector_RemoveRange(swigCPtr, index, count);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public static FormationMarkerVector Repeat(f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker value, int count) {
    global::System.IntPtr cPtr = energisticsApiPINVOKE.FormationMarkerVector_Repeat(f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker.getCPtr(value), count);
    FormationMarkerVector ret = (cPtr == global::System.IntPtr.Zero) ? null : new FormationMarkerVector(cPtr, true);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Reverse() {
    energisticsApiPINVOKE.FormationMarkerVector_Reverse__SWIG_0(swigCPtr);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Reverse(int index, int count) {
    energisticsApiPINVOKE.FormationMarkerVector_Reverse__SWIG_1(swigCPtr, index, count);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void SetRange(int index, FormationMarkerVector values) {
    energisticsApiPINVOKE.FormationMarkerVector_SetRange(swigCPtr, index, FormationMarkerVector.getCPtr(values));
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool Contains(f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker value) {
    bool ret = energisticsApiPINVOKE.FormationMarkerVector_Contains(swigCPtr, f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker.getCPtr(value));
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int IndexOf(f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker value) {
    int ret = energisticsApiPINVOKE.FormationMarkerVector_IndexOf(swigCPtr, f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker.getCPtr(value));
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int LastIndexOf(f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker value) {
    int ret = energisticsApiPINVOKE.FormationMarkerVector_LastIndexOf(swigCPtr, f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker.getCPtr(value));
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool Remove(f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker value) {
    bool ret = energisticsApiPINVOKE.FormationMarkerVector_Remove(swigCPtr, f2i.energisticsStandardsApi.witsml1_4_1_1.FormationMarker.getCPtr(value));
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}
