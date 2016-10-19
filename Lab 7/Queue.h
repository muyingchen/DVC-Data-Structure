// Lab 7, Part 1: Developing And Testing A Queue Template

#ifndef Queue_h
#define Queue_h

template <typename V>
class Queue
{
private:
  struct Node
  {
    V value;
    Node* next;
  };
  Node* firstNode;
  Node* lastNode;
  int siz; // track size
  V dummy;
public:
  Queue(); // may have a defaulted parameter
  Queue(const Queue<V>&); // copy constructor
  Queue<V>& operator= (const Queue<V>&); // assignment operator
  ~Queue(); // destructor
  void push(const V&);
  V& front(); // return a mutable reference to the oldest node
  V& back(); // return a mutable reference to the newest node
  void pop(); // remove the oldest node
  int size() const {return siz;}
  bool empty() const;
  void clear();
};

template <typename V> // main constructor
Queue<V>:: Queue()
{
  firstNode = 0;
  lastNode = 0;
  siz = 0;
}

template <typename V> // copy constructor
Queue<V>:: Queue(const Queue<V>& original)
{
  firstNode = 0;
  lastNode = 0;
  siz = original.siz;
  for (Node* p = original.firstNode; p; p = p->next)
  {
    Node* temp = new Node;
    temp->value = p->value;
    temp->next = 0;
    if (lastNode) lastNode->next = temp;
    else firstNode = temp;
    lastNode = temp;
  }
}

template <typename V> // assignment operator
Queue<V>& Queue<V>::operator=(const Queue<V>& original)
{
  if (this != &original)
  {
    // deallocate existing list
    while (firstNode)
    {
      Node* p = firstNode->next;
      delete firstNode;
      firstNode = p;
    }
    // build new queue
    Node* lastNode = 0;
    for (Node* p = original.firstNode; p; p = p->next)
    {
      Node* temp = new Node;
      temp->value = p->value;
      temp->next = 0;
      if (lastNode) lastNode->next = temp;
      else firstNode = temp;
      lastNode = temp;
    }
    siz = original.siz;
  }
  return *this;
}

template <typename V> // destructor
Queue<V>:: ~Queue()
{
  while (firstNode)
  {
    Node* p = firstNode;
    firstNode = firstNode->next;
    delete p;
  }
}

template <typename V> // push
void Queue<V>::push(const V& value)
{
  Node* temp = new Node;
  temp->value = value;
  temp->next = 0;
  if (lastNode) lastNode->next = temp;
  else firstNode = temp;
  lastNode = temp;
  ++siz;
}

template <typename V> // front
V& Queue<V>:: front()
{
  if (firstNode == 0) return dummy;
  else return firstNode->value;
}

template <typename V> // back
V& Queue<V>:: back()
{
  if (lastNode == 0) return dummy;
  else return lastNode->value;
}

template <typename V> // pop
void Queue<V>::pop()
{
  if (firstNode)
  {
    Node* p = firstNode;
    firstNode = firstNode->next;
    delete p;
    --siz;
  }
  if (siz == 0)
    lastNode = 0;
}

template <typename V>
bool Queue<V>::empty() const
{
  bool isempty = false;
  if (siz == 0) isempty = true;
  else return isempty = false;
  return isempty;
}

template <typename V>
void Queue<V>::clear()
{
  while (firstNode)
  {
    Node* p = firstNode;
    firstNode = firstNode->next;
    delete p;
    --siz;
  }
  lastNode = 0;
}

#endif
