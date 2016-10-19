// Lab 6, Part 1: Developing And Testing A Stack Template

#include <algorithm>
using namespace std;

#ifndef Stack_h
#define Stack_h

template <typename V>
class Stack
{
private:
  V* values;
  int cap;
  int siz; // track size
  void capacity(int);
public:
  Stack(int = 2); // may have a defaulted parameter
  Stack(const Stack<V>&); // copy constructor
  Stack<V>& operator=(const Stack<V>&); // assignment opearator
  ~Stack(){delete [] values;}
  void push(const V&);
  V& peek();
  void pop(){if (siz > 0) --siz;}
  int size() const {return siz;}
  bool empty() const;
  void clear(){siz = 0;}
};

template <typename V> // main constructor
Stack<V>:: Stack(int cap)
{
  this->siz = 0;
  this->cap = cap;
  values = new V[cap];
}

template <typename V> // copy constructor
Stack<V>:: Stack(const Stack<V>& original)
{
  cap = original.cap;
  values = new V[cap];
  siz = original.siz;
  for (int i = 0; i < cap; i++)
    values[i] = original.values[i];
}

template <typename V> // assignment operator
Stack<V>& Stack<V>:: operator=(const Stack<V>& original)
{
  if (this != &original)
  {
    delete [] values;
    cap = original.cap;
    values = new V[cap];
    siz = original.siz;
    for (int i = 0; i < cap; i++)
      values[i] = original.values[i];
  }
  return *this;
}

template <typename V> // capacity function
void Stack<V>:: capacity(int cap)
{
  V* temp = new V[cap];
  int limit = min (cap, this->cap);
  for (int i = 0; i < limit; i++)
    temp[i] = values[i];
  delete [] values;
  values = temp;
  this->cap = cap;
}

template <typename V> // push
void Stack<V>:: push(const V& value)
{
  if (cap == siz) capacity(cap*2);
  values[siz] = value;
  ++siz;
}

template <typename V> // peek
V& Stack<V>:: peek()
{
  if (siz < 0)
    return values[0];
  if (siz >= cap)
  {
    capacity(2*siz);
    return values[siz-1];
  }
  return values[siz-1];
}

template <typename V> // empty
bool Stack<V>::empty() const
{
  bool isempty = false;
  if (siz == 0) isempty = true;
  else return isempty = false;
  return isempty;
}

#endif
