// Lab 9, Part 1  

#include <queue>
using namespace std;

#ifndef AssociativeArray_h
#define AssociativeArray_h

template <typename K, typename V>
class AssociativeArray
{
private:
  struct Node
  {
    K key;
    V value;
    Node* next;
  };
  Node* firstNode;
  int siz;
  V dummy;
public:
  AssociativeArray(); // main constructor
  AssociativeArray(const AssociativeArray<K,V>&); // copy constructor
  AssociativeArray<K,V>& operator= (const AssociativeArray<K,V>&); // assignment operator
  ~AssociativeArray(); // destructor
  V operator[](const K&) const; // getter
  V& operator[](const K&); // setter
  bool containsKey(const K&) const; // getter
  void deleteKey(const K&); // setter
  queue<K> keys() const; // keys getter
  int size() const {return siz;} // size getter
  void clear(); // clear setter
};

template <typename K, typename V> // main constructor
AssociativeArray<K,V>:: AssociativeArray()
{
  firstNode = 0;
  siz = 0;
}

template <typename K, typename V> // copy constructor
AssociativeArray<K,V>:: AssociativeArray(const AssociativeArray<K,V>& original)
{
  firstNode = 0;
  Node* lastNode = 0; // temporary tail
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

template <typename K, typename V> // assignment operator
AssociativeArray<K,V>& AssociativeArray<K,V>:: operator= (const AssociativeArray<K,V>&  original)
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
     Node* lastNode = 0; // temporary tail
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

template <typename K, typename V> // destructor
AssociativeArray<K,V>:: ~AssociativeArray()
{
  while (firstNode)
  {
    Node* p = firstNode;
    firstNode = firstNode->next;
    delete p;
  }
}

template <typename K, typename V> // getter
V AssociativeArray<K,V>:: operator[](const K& key) const
{
  for (Node* p = firstNode; p; p = p->next)
    if (p->key == key)
      return p->value;
  return dummy;
}

template <typename K, typename V> // setter
V& AssociativeArray<K,V>:: operator[](const K& key)
{
  for (Node* p = firstNode; p; p = p->next)
    if (p->key == key)
      return p->value;
  ++siz;
  Node* temp = new Node;
  temp->key = key;
  temp->next = firstNode;
  firstNode = temp;
  return firstNode->value;
}

template <typename K, typename V> // containskeys
bool AssociativeArray<K,V>:: containsKey(const K& key) const
{
  for (Node* p = firstNode; p; p = p->next)
    if (p->key == key) return true;
  return false;
}

template <typename K, typename V> // delete key
void AssociativeArray<K,V>:: deleteKey(const K& key)
{
  // find the matching node
  Node* p, *prev; // declare above loop so that it survives below the loop
  for (p = firstNode, prev = 0; p; prev = p, p = p->next)
    if (p->key == key)
      break;
  // if found (that is, p did not run off the end of the list)
  if (p)
  {
    --siz;
    if (prev) prev->next = p->next; // skips over the node at p
    else firstNode = p->next; // there's a new head, possibly zero
    delete p; // we're done with this node
  }
}

template <typename K, typename V>  // keys getter
queue<K> AssociativeArray<K,V>:: keys() const
{
  queue<K> key;
  Node* p, *prev;
  for (p = firstNode, prev = 0; p; prev = p, p = p->next)
    key.push(p->key);
  return key;
}
template <typename K, typename V> // clear
void AssociativeArray<K,V>:: clear()
{
  while (firstNode)
  {
    Node* p = firstNode;
    firstNode = firstNode->next;
    delete p;
    --siz;
  }
}
#endif
