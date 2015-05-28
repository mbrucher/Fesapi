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

public class SeismicLineFeatureVector : global::System.IDisposable, global::System.Collections.IEnumerable
    , global::System.Collections.Generic.IList<f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature>
 {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal SeismicLineFeatureVector(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(SeismicLineFeatureVector obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~SeismicLineFeatureVector() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          fesapiPINVOKE.delete_SeismicLineFeatureVector(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public SeismicLineFeatureVector(global::System.Collections.ICollection c) : this() {
    if (c == null)
      throw new global::System.ArgumentNullException("c");
    foreach (f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature element in c) {
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

  public f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature this[int index]  {
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

  public void CopyTo(f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature[] array)
  {
    CopyTo(0, array, 0, this.Count);
  }

  public void CopyTo(f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature[] array, int arrayIndex)
  {
    CopyTo(0, array, arrayIndex, this.Count);
  }

  public void CopyTo(int index, f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature[] array, int arrayIndex, int count)
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

  global::System.Collections.Generic.IEnumerator<f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature> global::System.Collections.Generic.IEnumerable<f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature>.GetEnumerator() {
    return new SeismicLineFeatureVectorEnumerator(this);
  }

  global::System.Collections.IEnumerator global::System.Collections.IEnumerable.GetEnumerator() {
    return new SeismicLineFeatureVectorEnumerator(this);
  }

  public SeismicLineFeatureVectorEnumerator GetEnumerator() {
    return new SeismicLineFeatureVectorEnumerator(this);
  }

  // Type-safe enumerator
  /// Note that the IEnumerator documentation requires an InvalidOperationException to be thrown
  /// whenever the collection is modified. This has been done for changes in the size of the
  /// collection but not when one of the elements of the collection is modified as it is a bit
  /// tricky to detect unmanaged code that modifies the collection under our feet.
  public sealed class SeismicLineFeatureVectorEnumerator : global::System.Collections.IEnumerator
    , global::System.Collections.Generic.IEnumerator<f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature>
  {
    private SeismicLineFeatureVector collectionRef;
    private int currentIndex;
    private object currentObject;
    private int currentSize;

    public SeismicLineFeatureVectorEnumerator(SeismicLineFeatureVector collection) {
      collectionRef = collection;
      currentIndex = -1;
      currentObject = null;
      currentSize = collectionRef.Count;
    }

    // Type-safe iterator Current
    public f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature Current {
      get {
        if (currentIndex == -1)
          throw new global::System.InvalidOperationException("Enumeration not started.");
        if (currentIndex > currentSize - 1)
          throw new global::System.InvalidOperationException("Enumeration finished.");
        if (currentObject == null)
          throw new global::System.InvalidOperationException("Collection modified.");
        return (f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature)currentObject;
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
    fesapiPINVOKE.SeismicLineFeatureVector_Clear(swigCPtr);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Add(f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature x) {
    fesapiPINVOKE.SeismicLineFeatureVector_Add(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature.getCPtr(x));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  private uint size() {
    uint ret = fesapiPINVOKE.SeismicLineFeatureVector_size(swigCPtr);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private uint capacity() {
    uint ret = fesapiPINVOKE.SeismicLineFeatureVector_capacity(swigCPtr);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private void reserve(uint n) {
    fesapiPINVOKE.SeismicLineFeatureVector_reserve(swigCPtr, n);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public SeismicLineFeatureVector() : this(fesapiPINVOKE.new_SeismicLineFeatureVector__SWIG_0(), true) {
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public SeismicLineFeatureVector(SeismicLineFeatureVector other) : this(fesapiPINVOKE.new_SeismicLineFeatureVector__SWIG_1(SeismicLineFeatureVector.getCPtr(other)), true) {
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public SeismicLineFeatureVector(int capacity) : this(fesapiPINVOKE.new_SeismicLineFeatureVector__SWIG_2(capacity), true) {
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  private f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature getitemcopy(int index) {
    global::System.IntPtr cPtr = fesapiPINVOKE.SeismicLineFeatureVector_getitemcopy(swigCPtr, index);
    f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature(cPtr, false);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature getitem(int index) {
    global::System.IntPtr cPtr = fesapiPINVOKE.SeismicLineFeatureVector_getitem(swigCPtr, index);
    f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature(cPtr, false);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private void setitem(int index, f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature val) {
    fesapiPINVOKE.SeismicLineFeatureVector_setitem(swigCPtr, index, f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature.getCPtr(val));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void AddRange(SeismicLineFeatureVector values) {
    fesapiPINVOKE.SeismicLineFeatureVector_AddRange(swigCPtr, SeismicLineFeatureVector.getCPtr(values));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public SeismicLineFeatureVector GetRange(int index, int count) {
    global::System.IntPtr cPtr = fesapiPINVOKE.SeismicLineFeatureVector_GetRange(swigCPtr, index, count);
    SeismicLineFeatureVector ret = (cPtr == global::System.IntPtr.Zero) ? null : new SeismicLineFeatureVector(cPtr, true);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Insert(int index, f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature x) {
    fesapiPINVOKE.SeismicLineFeatureVector_Insert(swigCPtr, index, f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature.getCPtr(x));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void InsertRange(int index, SeismicLineFeatureVector values) {
    fesapiPINVOKE.SeismicLineFeatureVector_InsertRange(swigCPtr, index, SeismicLineFeatureVector.getCPtr(values));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void RemoveAt(int index) {
    fesapiPINVOKE.SeismicLineFeatureVector_RemoveAt(swigCPtr, index);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void RemoveRange(int index, int count) {
    fesapiPINVOKE.SeismicLineFeatureVector_RemoveRange(swigCPtr, index, count);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public static SeismicLineFeatureVector Repeat(f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature value, int count) {
    global::System.IntPtr cPtr = fesapiPINVOKE.SeismicLineFeatureVector_Repeat(f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature.getCPtr(value), count);
    SeismicLineFeatureVector ret = (cPtr == global::System.IntPtr.Zero) ? null : new SeismicLineFeatureVector(cPtr, true);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Reverse() {
    fesapiPINVOKE.SeismicLineFeatureVector_Reverse__SWIG_0(swigCPtr);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Reverse(int index, int count) {
    fesapiPINVOKE.SeismicLineFeatureVector_Reverse__SWIG_1(swigCPtr, index, count);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void SetRange(int index, SeismicLineFeatureVector values) {
    fesapiPINVOKE.SeismicLineFeatureVector_SetRange(swigCPtr, index, SeismicLineFeatureVector.getCPtr(values));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool Contains(f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature value) {
    bool ret = fesapiPINVOKE.SeismicLineFeatureVector_Contains(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature.getCPtr(value));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int IndexOf(f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature value) {
    int ret = fesapiPINVOKE.SeismicLineFeatureVector_IndexOf(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature.getCPtr(value));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int LastIndexOf(f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature value) {
    int ret = fesapiPINVOKE.SeismicLineFeatureVector_LastIndexOf(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature.getCPtr(value));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool Remove(f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature value) {
    bool ret = fesapiPINVOKE.SeismicLineFeatureVector_Remove(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.SeismicLineFeature.getCPtr(value));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}
