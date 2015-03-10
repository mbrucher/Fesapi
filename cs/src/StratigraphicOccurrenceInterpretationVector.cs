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

public class StratigraphicOccurrenceInterpretationVector : global::System.IDisposable, global::System.Collections.IEnumerable
    , global::System.Collections.Generic.IList<f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation>
 {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal StratigraphicOccurrenceInterpretationVector(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(StratigraphicOccurrenceInterpretationVector obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~StratigraphicOccurrenceInterpretationVector() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          energisticsApiPINVOKE.delete_StratigraphicOccurrenceInterpretationVector(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public StratigraphicOccurrenceInterpretationVector(global::System.Collections.ICollection c) : this() {
    if (c == null)
      throw new global::System.ArgumentNullException("c");
    foreach (f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation element in c) {
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

  public f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation this[int index]  {
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

  public void CopyTo(f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation[] array)
  {
    CopyTo(0, array, 0, this.Count);
  }

  public void CopyTo(f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation[] array, int arrayIndex)
  {
    CopyTo(0, array, arrayIndex, this.Count);
  }

  public void CopyTo(int index, f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation[] array, int arrayIndex, int count)
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

  global::System.Collections.Generic.IEnumerator<f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation> global::System.Collections.Generic.IEnumerable<f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation>.GetEnumerator() {
    return new StratigraphicOccurrenceInterpretationVectorEnumerator(this);
  }

  global::System.Collections.IEnumerator global::System.Collections.IEnumerable.GetEnumerator() {
    return new StratigraphicOccurrenceInterpretationVectorEnumerator(this);
  }

  public StratigraphicOccurrenceInterpretationVectorEnumerator GetEnumerator() {
    return new StratigraphicOccurrenceInterpretationVectorEnumerator(this);
  }

  // Type-safe enumerator
  /// Note that the IEnumerator documentation requires an InvalidOperationException to be thrown
  /// whenever the collection is modified. This has been done for changes in the size of the
  /// collection but not when one of the elements of the collection is modified as it is a bit
  /// tricky to detect unmanaged code that modifies the collection under our feet.
  public sealed class StratigraphicOccurrenceInterpretationVectorEnumerator : global::System.Collections.IEnumerator
    , global::System.Collections.Generic.IEnumerator<f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation>
  {
    private StratigraphicOccurrenceInterpretationVector collectionRef;
    private int currentIndex;
    private object currentObject;
    private int currentSize;

    public StratigraphicOccurrenceInterpretationVectorEnumerator(StratigraphicOccurrenceInterpretationVector collection) {
      collectionRef = collection;
      currentIndex = -1;
      currentObject = null;
      currentSize = collectionRef.Count;
    }

    // Type-safe iterator Current
    public f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation Current {
      get {
        if (currentIndex == -1)
          throw new global::System.InvalidOperationException("Enumeration not started.");
        if (currentIndex > currentSize - 1)
          throw new global::System.InvalidOperationException("Enumeration finished.");
        if (currentObject == null)
          throw new global::System.InvalidOperationException("Collection modified.");
        return (f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation)currentObject;
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
    energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_Clear(swigCPtr);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Add(f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation x) {
    energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_Add(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation.getCPtr(x));
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  private uint size() {
    uint ret = energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_size(swigCPtr);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private uint capacity() {
    uint ret = energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_capacity(swigCPtr);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private void reserve(uint n) {
    energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_reserve(swigCPtr, n);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public StratigraphicOccurrenceInterpretationVector() : this(energisticsApiPINVOKE.new_StratigraphicOccurrenceInterpretationVector__SWIG_0(), true) {
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public StratigraphicOccurrenceInterpretationVector(StratigraphicOccurrenceInterpretationVector other) : this(energisticsApiPINVOKE.new_StratigraphicOccurrenceInterpretationVector__SWIG_1(StratigraphicOccurrenceInterpretationVector.getCPtr(other)), true) {
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public StratigraphicOccurrenceInterpretationVector(int capacity) : this(energisticsApiPINVOKE.new_StratigraphicOccurrenceInterpretationVector__SWIG_2(capacity), true) {
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  private f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation getitemcopy(int index) {
    global::System.IntPtr cPtr = energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_getitemcopy(swigCPtr, index);
    f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation(cPtr, false);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation getitem(int index) {
    global::System.IntPtr cPtr = energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_getitem(swigCPtr, index);
    f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation ret = (cPtr == global::System.IntPtr.Zero) ? null : new f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation(cPtr, false);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private void setitem(int index, f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation val) {
    energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_setitem(swigCPtr, index, f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation.getCPtr(val));
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void AddRange(StratigraphicOccurrenceInterpretationVector values) {
    energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_AddRange(swigCPtr, StratigraphicOccurrenceInterpretationVector.getCPtr(values));
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public StratigraphicOccurrenceInterpretationVector GetRange(int index, int count) {
    global::System.IntPtr cPtr = energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_GetRange(swigCPtr, index, count);
    StratigraphicOccurrenceInterpretationVector ret = (cPtr == global::System.IntPtr.Zero) ? null : new StratigraphicOccurrenceInterpretationVector(cPtr, true);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Insert(int index, f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation x) {
    energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_Insert(swigCPtr, index, f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation.getCPtr(x));
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void InsertRange(int index, StratigraphicOccurrenceInterpretationVector values) {
    energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_InsertRange(swigCPtr, index, StratigraphicOccurrenceInterpretationVector.getCPtr(values));
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void RemoveAt(int index) {
    energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_RemoveAt(swigCPtr, index);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void RemoveRange(int index, int count) {
    energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_RemoveRange(swigCPtr, index, count);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public static StratigraphicOccurrenceInterpretationVector Repeat(f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation value, int count) {
    global::System.IntPtr cPtr = energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_Repeat(f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation.getCPtr(value), count);
    StratigraphicOccurrenceInterpretationVector ret = (cPtr == global::System.IntPtr.Zero) ? null : new StratigraphicOccurrenceInterpretationVector(cPtr, true);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Reverse() {
    energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_Reverse__SWIG_0(swigCPtr);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Reverse(int index, int count) {
    energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_Reverse__SWIG_1(swigCPtr, index, count);
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public void SetRange(int index, StratigraphicOccurrenceInterpretationVector values) {
    energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_SetRange(swigCPtr, index, StratigraphicOccurrenceInterpretationVector.getCPtr(values));
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool Contains(f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation value) {
    bool ret = energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_Contains(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation.getCPtr(value));
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int IndexOf(f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation value) {
    int ret = energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_IndexOf(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation.getCPtr(value));
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int LastIndexOf(f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation value) {
    int ret = energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_LastIndexOf(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation.getCPtr(value));
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool Remove(f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation value) {
    bool ret = energisticsApiPINVOKE.StratigraphicOccurrenceInterpretationVector_Remove(swigCPtr, f2i.energisticsStandardsApi.resqml2_0.StratigraphicOccurrenceInterpretation.getCPtr(value));
    if (energisticsApiPINVOKE.SWIGPendingException.Pending) throw energisticsApiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}
