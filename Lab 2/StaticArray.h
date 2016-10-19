// Lab 2, StaticArray Template Part 1

#ifndef StaticArray_h
#define StaticArray_h

template <typename V, int CAP>
class StaticArray
{
  private:
    V dummy;
    V values[CAP];
  public:
    V operator[](int) const; //getter
    V& operator[](int); // setter
    int capacity() const {return CAP;} // return capacity
};

template <typename V, int CAP>
V StaticArray<V,CAP>::operator[](int index) const
{
  if (index < 0 || index >= CAP)
    return dummy;
  else
    return values[index];
}

template <typename V, int CAP>
V& StaticArray<V,CAP>::operator[](int index)
{
  if (index < 0 || index >= CAP)
    return dummy;
  else
    return values[index];
}

#endif
