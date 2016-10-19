// Lab 10, HashTable Template, Part 1

#include <list>
#include <queue>
using namespace std;

#ifndef HashTable_h
#define HashTable_h

template <typename K, typename V, int CAP>
class HashTable
{
private:
  int(*hashCode)(const K&); // alias for hash code function
  struct Node
  {
    K key;
    V value;
  };
  list<Node> data[CAP];
  int siz;
  V dummy;
public:
  HashTable(int(*h)(const K&)=0); // main constructor
  HashTable(const HashTable<K,V,CAP>&); // copy constructor
  HashTable<K,V,CAP>& operator= (const HashTable<K,V,CAP>&); // assignment operator
  ~HashTable(); // destructor
  V operator[](const K&) const; // getter
  V& operator[] (const K&); // setter
  bool containsKey(const K&) const; // getter
  void deleteKey(const K&); // setter
  queue<K> keys() const; // keys getter
  int size() const {return siz;} // size getter
  void clear(); // clear setter
  double loadFactor() const {return 1.0 * siz / CAP;} // get load factor
};

template <typename K, typename V, int CAP> // main constructor
HashTable<K,V,CAP>:: HashTable(int(*hashCode)(const K&))
{
  siz = 0;
  this->hashCode = hashCode;
}

template <typename K, typename V, int CAP> // copy constructor
HashTable<K,V,CAP>:: HashTable(const HashTable<K,V,CAP>& original)
{
  siz = original.siz;
  hashCode = original.hashCode;
  for(int i = 0; i < CAP; i++)
    data[i] = original.data[i];
}

template <typename K, typename V, int CAP> // assignment operator
HashTable<K,V,CAP>& HashTable<K,V,CAP>:: operator= (const HashTable<K,V,CAP>& original)
{
  if (this != &original)
  {
    siz = original.siz;
    hashCode = original.hashCode;
    for(int i = 0; i < CAP; i++)
      data[i] = original.data[i];
  }
  return *this;
}
template <typename K, typename V, int CAP> // destructor
HashTable<K,V,CAP>:: ~HashTable()
{
  for (int i = 0; i < CAP; i++)
    data[i].clear();
}

template <typename K, typename V, int CAP> // getter
V HashTable<K,V,CAP>:: operator[](const K& key) const
{
  int index = hashCode(key) % CAP;
  if (index < 0) index += CAP;
  typename list<Node>::const_iterator it;
  for (it = data[index].begin(); it != data[index].end(); it++)
    if (it->key == key) break;
  if(it != data[index].end()) return it->value;
  else (it == data[index].end()) return dummy;
}

template <typename K, typename V, int CAP> // setter
V& HashTable<K,V,CAP>:: operator[](const K& key)
{
  int index = hashCode(key) % CAP;
  if (index < 0) index += CAP;
  typename list<Node>::iterator it;
  for (it = data[index].begin(); it != data[index].end(); it++)
    if (it->key == key) break;
  if (it != data[index].end()) return it->value;
  else
  {
    Node n;
    n.key = key;
    n.value = V();
    data[index].push_back(n);
    ++siz;
  }
  return data[index].back().value;
}

template <typename K, typename V, int CAP> // containsKey getter
bool HashTable<K,V,CAP>:: containsKey(const K& key) const
{
  bool result;
  int index = hashCode(key) % CAP;
  if (index < 0) index += CAP;
  typename list<Node>::const_iterator it;
  for (it = data[index].begin(); it != data[index].end(); it++)
    if (it->key == key) break;
  if (it != data[index].end()) result = true;
  else result = false;
  return result;
}

template <typename K, typename V, int CAP>
void HashTable<K,V,CAP>:: deleteKey(const K& key) // setter
{
  int index = hashCode(key) % CAP;
  if (index < 0) index += CAP;
  typename list<Node>::iterator it;
  for (it = data[index].begin(); it != data[index].end(); it++)
    if (it->key == key) break;
  if (it!= data[index].end())
  {
    if (data[index].size() == 1)
    {
      --siz;
      data[index].erase(it);
    }
    else data[index].erase(it);
  }
}

template <typename K, typename V, int CAP> // keys getter
queue<K> HashTable<K,V,CAP>:: keys() const
{
  queue<K> key;
  typename list<Node>::const_iterator it;
  for (int i = 0; i < CAP; i++)
  {
    for (it = data[i].begin(); it != data[i].end(); it++)
      key.push(it->key);
  }
  return key;
}

template <typename K, typename V, int CAP> // clear
void HashTable<K,V,CAP>:: clear()
{
  for (int i = 0; i < CAP; i++)
  {
    data[i].clear();
  }
  siz = 0;
}

#endif
