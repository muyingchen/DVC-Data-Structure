// Lab 12, SortableArray Template

#include <algorithm>
using namespace std;

#ifndef SortableArray_h
#define SortableArray_h

template <typename V>
class SortableArray
{
private:
  V* values;
  int CAP;
  V dummy;
public:
  SortableArray(int = 2);  // main constructor
  SortableArray(const SortableArray<V>&); // copy constructor
  SortableArray<V>& operator=(const SortableArray<V>&); // assignment operators
  ~SortableArray() {delete [] values;}
  V operator[](int) const; //getter
  V& operator[](int); // setter
  int capacity() const {return CAP;} // return capacity
  void capacity(int);  // capacity setter
  void sort(int); // sorting function
};

template <typename V>
SortableArray<V>:: SortableArray (int CAP) // main constructor
{
  this->CAP = CAP;
  values = new V[CAP];
}

template <typename V>
SortableArray<V>:: SortableArray (const SortableArray<V>& original) // copy constructor
{
  CAP = original.CAP;
  values = new V[CAP];
  for (int i = 0; i < CAP; i++)
    values[i] = original.values[i];
}

template <typename V>
SortableArray<V>& SortableArray<V>:: operator=(const SortableArray<V>& original)
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

template <typename V>
V SortableArray<V>:: operator[] (int index) const // getter
{
  if ( index < 0 ) return dummy;
  if ( index >= CAP ) return dummy;
  return values[index];
}
template <typename V>
V& SortableArray<V>:: operator[] (int index) // setter
{
  if (index < 0) return dummy;
  else if (index >= CAP)
  {
    capacity(2*index);
    return values[index];
  }
  else return values[index];
}

template <typename V>
void SortableArray<V>:: capacity(int CAP) // capacity setter
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
void SortableArray<V>:: sort(int n) // merge sort
{
  //the name of the array to be sorted is "a" and its size is "n"
  //create a dynamic array of size n as a working space, named "temp"
  V* temp = new V[n];
  //create an integer to track the size of the sub-arrays in each iteration -- set to 1
  //start a loop
  for (int subarraysize = 1; subarraysize < n; subarraysize *= 2)
  {
    //if the sub-array size for this iteration is greater than n, break -- nothing more to do!
    if (n < subarraysize) break;
    //declare and set an "index" to 0 -- the next position in the array to fill
    int index = 0;
    //copy the array into the working space -- the whole thing!
    for (int i = 0; i < n; i++) temp[i] = values[i];
    //start a loop to visit each adjacent pair of sub-arrays, with a counter i=0
    for (int i = 0; i < subarraysize; i += 2 * subarraysize)
    {
      //create these integers to track the lead and end values of the two sub-arrays being merged:
      int left = i;
      int leftMax = min (n, left + subarraysize);
      int right = leftMax;
      int rightMax = min(n, right + subarraysize);
      //start another loop to run as long as left < leftMax OR right < rightMax
      while ((left < leftMax) || (right < rightMax))
      {
        if (left == leftMax) values[index++] = temp[right++];
        else if (right == rightMax) values[index++] = temp[left++];
        else if (temp[right] < temp[left]) values[index++] = temp[right++];
        else values[index++] = temp[left++];
      }
      //add two sub-array sizes to i for the next cycle of the inner loop
    }
    //double the sub-array size for the next iteration
  }
 // deallocate the working space array
  delete [] temp;
}
#endif
