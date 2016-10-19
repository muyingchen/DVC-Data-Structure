// Lab 4, Applying A Data Structure To A Big Data Application

#include <algorithm>
using namespace std;

#ifndef DynamicArray_h
#define DynamicArray_h

template <typename V>
class DynamicArray
{
  private:
    V* values;
    int CAP;
    V dummy;
  public:
    DynamicArray(int = 2);  // main constructor
    DynamicArray(const DynamicArray<V>&); // copy constructor
    ~DynamicArray() {delete [] values;}
    V operator[](int) const; //getter
    V& operator[](int); // setter
    DynamicArray<V>& operator=(const DynamicArray<V>&); // assignment operators
    int capacity() const {return CAP;} // return capacity
    void capacity(int);  // capacity setter
};

template <typename V>
DynamicArray<V>:: DynamicArray (int CAP)
{
  this->CAP = CAP;
  values = new V[CAP];
}

template <typename V>
DynamicArray<V>:: DynamicArray (const DynamicArray<V>& original)
{
  CAP = original.CAP;
  values = new V[CAP];
  for (int i = 0; i < CAP; i++)
    values[i] = original.values[i];
}

template <typename V>
void DynamicArray<V>::capacity(int CAP)
{
  V* temp = new V[CAP];
  int limit = min(CAP,this->CAP);
  for (int i = 0; i < limit; i++)
    temp[i] = values[i];
  delete [] values;
  values = temp;
  this->CAP = CAP;
}

template <typename V>
V DynamicArray<V>::operator[](int index) const
{
  if ( index < 0 ) return dummy;
  if ( index >= CAP ) return dummy;
  return values[index];
}

template <typename V>
V& DynamicArray<V>::operator[](int index)
{
  if ( index < 0 ) return dummy;
  if ( index >= CAP )
  {
    capacity(2*index);
    return values[index];
  }
  return values[index];
}

template <typename V>
DynamicArray<V>& DynamicArray<V>:: operator=(const DynamicArray<V>& original)
{
  if (this != &original)
  {
    delete [] values;
    CAP = original.CAP;
    values = new V[CAP];
    for (int i = 0; i < CAP; i++)
      values[i] = original.values[i];
  }
  return *this;
}

#endif
