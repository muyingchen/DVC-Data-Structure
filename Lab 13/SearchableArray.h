// Lab 13, SearchableArray Template

#include <algorithm>
using namespace std;

#ifndef SearchableArray_h
#define SearchableArray_h

template <typename V>
class SearchableArray
{
private:
  V* values;
  int CAP;
  V dummy;
public:
  SearchableArray(int = 2);  // main constructor
  SearchableArray(const SearchableArray<V>&); // copy constructor
  SearchableArray<V>& operator=(const SearchableArray<V>&); // assignment operators
  ~SearchableArray() {delete [] values;}
  V operator[](int) const; //getter
  V& operator[](int); // setter
  int capacity() const {return CAP;} // return capacity
  void capacity(int);  // capacity setter
  void sort(int); // sorting function
  int bsearch(int, const V&) const;// search function
};

template <typename V>
SearchableArray<V>:: SearchableArray(int CAP) // main constructor
{
  this->CAP = CAP;
  values = new V[CAP];
}

template <typename V>
SearchableArray<V>:: SearchableArray(const SearchableArray<V>& original) // copy constructor
{
  CAP = original.CAP;
  values = new V[CAP];
  for (int i = 0; i < CAP; i++)
    values[i] = original.values[i];
}

template <typename V>
SearchableArray<V>& SearchableArray<V>:: operator=(const SearchableArray<V>& original)
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
V SearchableArray<V>:: operator[] (int index) const // getter
{
  if ( index < 0 ) return dummy;
  if ( index >= CAP ) return dummy;
  return values[index];
}
template <typename V>
V& SearchableArray<V>:: operator[] (int index) // setter
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
void SearchableArray<V>:: capacity(int CAP) // capacity setter
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
void SearchableArray<V>:: sort(int n) // merge sort
{
  V* temp = new V[n];
  for (int subarraysize = 1; subarraysize < n; subarraysize *= 2)
  {
    if (n < subarraysize) break;
    int index = 0;
    for (int i = 0; i < n; i++) temp[i] = values[i];
    for (int i = 0; i < subarraysize; i += 2 * subarraysize)
    {
      int left = i;
      int leftMax = min (n, left + subarraysize);
      int right = leftMax;
      int rightMax = min(n, right + subarraysize);
      while ((left < leftMax) || (right < rightMax))
      {
        if (left == leftMax) values[index++] = temp[right++];
        else if (right == rightMax) values[index++] = temp[left++];
        else if (temp[right] < temp[left]) values[index++] = temp[right++];
        else values[index++] = temp[left++];
      }
    }
  }
  delete [] temp;
}

template <typename V>
int SearchableArray<V>:: bsearch (int element, const V& matchThis) const
{
  int n = element - 1;
  int s = 0; // start of a range of the array to search
  int e = n; // end of a range of the array to search
  int m = 0; // the matching value's index
  while (m != n) // "n" means no match was found
  {
     m = (s + e - 1) / 2; // the middle element
     if (matchThis == values[m]) break; // got lucky -- matches middle element
     else if (s >= e - 1) m = n; // 1-element array and it did not match
     else if (matchThis < values[m]) e = m; // look between s and m-1
     else s = m + 1; // look between m+1 and e-1
  }
  if (m!=n) return m;
  else return -1;
}
#endif
