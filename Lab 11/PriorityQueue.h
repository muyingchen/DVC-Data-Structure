// Lab 11, PriorityQueue Template Part 1

#include <algorithm>
using namespace std;

#ifndef PriorityQueue_h
#define PriorityQueue_h

template <typename V>
class PriorityQueue
{
private:
  V* values;
  int siz;
  int CAP;
  void capacity(int); // increase capacity
public:
  PriorityQueue(int = 2); // main constructor
  PriorityQueue(const PriorityQueue<V>&); // copy constructor
  PriorityQueue<V>& operator=(const PriorityQueue<V>&); // assignment operator
  ~PriorityQueue() {delete [] values;}
  const V& top(); // return top largest value
  void push(const V&); // push
  void pop(); // pop highest value
  void clear() {siz = 0;} // clear
  bool empty() const {return siz == 0;}  // empty
  int size() const {return siz;} // size
};

template <typename V>
PriorityQueue<V>:: PriorityQueue(int CAP) // main constructor
{
  this->CAP = CAP;
  values = new V[CAP];
  siz = 0;
}

template <typename V>
PriorityQueue<V>:: PriorityQueue(const PriorityQueue<V>& original) // copy constructor
{
  CAP = original.CAP;
  values = new V[CAP];
  siz = original.siz;
  for (int i = 0; i < CAP; i++)
  {
    values[i] = original.values[i];
  }
}

template <typename V> // assignment operator
PriorityQueue<V>& PriorityQueue<V>:: operator= (const PriorityQueue<V>& original)
{
  if (this != &original)
  {
    delete [] values;
    CAP = original.CAP;
    values = new V[CAP];
    siz = original.siz;
    for (int i = 0; i < CAP; i++)
      values[i] = original.values[i];
  }
  return *this;
}

template <typename V>
void PriorityQueue<V>:: capacity(int CAP)
{
  V* temp = new V[CAP];
  int limit = min(CAP, this->CAP);
  for (int i = 0; i < limit; i++)
    temp[i] = values[i];
  delete [] values;
  values = temp;
  this->CAP = CAP;
}

template <typename V>
const V& PriorityQueue<V>:: top() // return leargest value
{
  if (siz < 0)
    return values[0];
  else if (siz >= CAP)
  {
    capacity(2*siz);
    return values[0];
  }
 else return values[0];
}

template <typename V>
void PriorityQueue<V>:: push(const V& value) // push
{
  if (CAP == siz) capacity(CAP*2);
  values[siz] = value;
  int index = siz;
  int parent_index = (index + 1) / 2 - 1;
  while(!(parent_index < 0) && !(values[index] < values[parent_index])) // max-heap
  {
    swap(values[parent_index], values[index]);
    index = parent_index;
    parent_index = (index + 1) / 2 - 1;
  }
  ++siz;
}

template <typename V>
void PriorityQueue<V>:: pop() // pop filling the hole
{
  int index = 0;
  int parent_index;
  int leftchild_index = 2 * index + 1;
  int rightchild_index = 2 * index + 2;
  while ((leftchild_index < siz) && (rightchild_index < siz))  // top down loop
  {
    if (values[rightchild_index] < values[leftchild_index])
    {
      values[index] = values[leftchild_index];
      index = leftchild_index;
    }
    else
    {
      values[index] = values[rightchild_index];
      index = rightchild_index;
    }
    leftchild_index = 2 * index + 1;
    rightchild_index = 2 * index + 2;
  }
  --siz;
  values[index] = values[siz];
  parent_index = (index + 1) / 2 - 1;
  while(!(parent_index < 0) && !(values[index] < values[parent_index])) // bottom up loop
  {
    swap(values[parent_index], values[index]);
    index = parent_index;
    parent_index = (index + 1) / 2 - 1;
  }
}

#endif
