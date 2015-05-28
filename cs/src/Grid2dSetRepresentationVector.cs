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

public class Grid2dSetRepresentationVector : global::System.IDisposable, global::System.Collections.IEnumerable
    , global::System.Collections.Generic.IList<f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation>
 {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal Grid2dSetRepresentationVector(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(Grid2dSetRepresentationVector obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~Grid2dSetRepresentationVector() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          fesapiPINVOKE.delete_Grid2dSetRepresentationVector(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public Grid2dSetRepresentationVector(global::System.Collections.ICollection c) : this() {
    if (c == null)
      throw new global::System.ArgumentNullException("c");
    foreach (f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation element in c) {
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

  public f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation this[int index]  {
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

  public void CopyTo(f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation[] array)
  {
    CopyTo(0, array, 0, this.Count);
  }

  public void CopyTo(f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation[] array, int arrayIndex)
  {
    CopyTo(0, array, arrayIndex, this.Count);
  }

  public void CopyTo(int index, f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation[] array, int arrayIndex, int count)
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

  global::System.Collections.Generic.IEnumerator<f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation> global::System.Collections.Generic.IEnumerable<f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation>.GetEnumerator() {
    return new Grid2dSetRepresentationVectorEnumerator(this);
  }

  global::System.Collections.IEnumerator global::System.Collections.IEnumerable.GetEnumerator() {
    return new Grid2dSetRepresentationVectorEnumerator(this);
  }

  public Grid2dSetRepresentationVectorEnumerator GetEnumerator() {
    return new Grid2dSetRepresentationVectorEnumerator(this);
  }

  // Type-safe enumerator
  /// Note that the IEnumerator documentation requires an InvalidOperationException to be thrown
  /// whenever the collection is modified. This has been done for changes in the size of the
  /// collection but not when one of the elements of the collection is modified as it is a bit
  /// tricky to detect unmanaged code that modifies the collection under our feet.
  public sealed class Grid2dSetRepresentationVectorEnumerator : global::System.Collections.IEnumerator
    , global::System.Collections.Generic.IEnumerator<f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation>
  {
    private Grid2dSetRepresentationVector collectionRef;
    private int currentIndex;
    private object currentObject;
    private int currentSize;

    public Grid2dSetRepresentationVectorEnumerator(Grid2dSetRepresentationVector collection) {
      collectionRef = collection;
      currentIndex = -1;
      currentObject = null;
      currentSize = collectionRef.Count;
    }

    // Type-safe iterator Current
    public f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation Current {
      get {
        if (currentIndex == -1)
          throw new global::System.InvalidOperationException("Enumeration not started.");
        if (currentIndex > currentSize - 1)
          throw new global::System.InvalidOperationException("Enumeration finished.");
        if (currentObject == null)
          throw new global::System.InvalidOperationException("Collection modified.");
        return (f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation)currentObject;
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
    fesapiPINVOKE.Grid2dSetRepresentationVector_Clear(swigCPtr);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Add(f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation x) {
    fesapiPINVOKE.Grid2dSetRepresentationVector_Add(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation.getCPtr(x));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  private uint size() {
    uint ret = fesapiPINVOKE.Grid2dSetRepresentationVector_size(swigCPtr);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private uint capacity() {
    uint ret = fesapiPINVOKE.Grid2dSetRepresentationVector_capacity(swigCPtr);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private void reserve(uint n) {
    fesapiPINVOKE.Grid2dSetRepresentationVector_reserve(swigCPtr, n);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public Grid2dSetRepresentationVector() : this(fesapiPINVOKE.new_Grid2dSetRepresentationVector__SWIG_0(), true) {
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public Grid2dSetRepresentationVector(Grid2dSetRepresentationVector other) : this(fesapiPINVOKE.new_Grid2dSetRepresentationVector__SWIG_1(Grid2dSetRepresentationVector.getCPtr(other)), true) {
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public Grid2dSetRepresentationVector(int capacity) : this(fesapiPINVOKE.new_Grid2dSetRepresentationVector__SWIG_2(capacity), true) {
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  private f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation getitemcopy(int index) {
    global::System.IntPtr cPtr = fesapiPINVOKE.Grid2dSetRepresentationVector_getitemcopy(swigCPtr, index);
    f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation(cPtr, false);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation getitem(int index) {
    global::System.IntPtr cPtr = fesapiPINVOKE.Grid2dSetRepresentationVector_getitem(swigCPtr, index);
    f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation(cPtr, false);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private void setitem(int index, f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation val) {
    fesapiPINVOKE.Grid2dSetRepresentationVector_setitem(swigCPtr, index, f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation.getCPtr(val));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void AddRange(Grid2dSetRepresentationVector values) {
    fesapiPINVOKE.Grid2dSetRepresentationVector_AddRange(swigCPtr, Grid2dSetRepresentationVector.getCPtr(values));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public Grid2dSetRepresentationVector GetRange(int index, int count) {
    global::System.IntPtr cPtr = fesapiPINVOKE.Grid2dSetRepresentationVector_GetRange(swigCPtr, index, count);
    Grid2dSetRepresentationVector ret = (cPtr == global::System.IntPtr.Zero) ? null : new Grid2dSetRepresentationVector(cPtr, true);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Insert(int index, f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation x) {
    fesapiPINVOKE.Grid2dSetRepresentationVector_Insert(swigCPtr, index, f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation.getCPtr(x));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void InsertRange(int index, Grid2dSetRepresentationVector values) {
    fesapiPINVOKE.Grid2dSetRepresentationVector_InsertRange(swigCPtr, index, Grid2dSetRepresentationVector.getCPtr(values));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void RemoveAt(int index) {
    fesapiPINVOKE.Grid2dSetRepresentationVector_RemoveAt(swigCPtr, index);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void RemoveRange(int index, int count) {
    fesapiPINVOKE.Grid2dSetRepresentationVector_RemoveRange(swigCPtr, index, count);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public static Grid2dSetRepresentationVector Repeat(f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation value, int count) {
    global::System.IntPtr cPtr = fesapiPINVOKE.Grid2dSetRepresentationVector_Repeat(f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation.getCPtr(value), count);
    Grid2dSetRepresentationVector ret = (cPtr == global::System.IntPtr.Zero) ? null : new Grid2dSetRepresentationVector(cPtr, true);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Reverse() {
    fesapiPINVOKE.Grid2dSetRepresentationVector_Reverse__SWIG_0(swigCPtr);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Reverse(int index, int count) {
    fesapiPINVOKE.Grid2dSetRepresentationVector_Reverse__SWIG_1(swigCPtr, index, count);
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void SetRange(int index, Grid2dSetRepresentationVector values) {
    fesapiPINVOKE.Grid2dSetRepresentationVector_SetRange(swigCPtr, index, Grid2dSetRepresentationVector.getCPtr(values));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool Contains(f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation value) {
    bool ret = fesapiPINVOKE.Grid2dSetRepresentationVector_Contains(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation.getCPtr(value));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int IndexOf(f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation value) {
    int ret = fesapiPINVOKE.Grid2dSetRepresentationVector_IndexOf(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation.getCPtr(value));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int LastIndexOf(f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation value) {
    int ret = fesapiPINVOKE.Grid2dSetRepresentationVector_LastIndexOf(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation.getCPtr(value));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool Remove(f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation value) {
    bool ret = fesapiPINVOKE.Grid2dSetRepresentationVector_Remove(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.Grid2dSetRepresentation.getCPtr(value));
    if (fesapiPINVOKE.SWIGPendingException.Pending) throw fesapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}
