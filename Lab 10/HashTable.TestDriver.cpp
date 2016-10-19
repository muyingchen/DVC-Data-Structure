#include<iostream>
#include<queue>
#include<list>
using namespace std;

#include<cassert>

#include "HashTable.h"
#include "HashTable.h"// ifndef test

int hashCode(const string& key)
{
  int result = 0;
  for (int i = 0; i < key.length(); i++)
    result += key.at(i);
  return result;
}

int main()
{
  HashTable<string, int, 10> a(hashCode);

  // testing push function
  a["a"] = 1;
  a["b"] = 2;
  a["c"] = 3;
  a["d"] = 4;
  cout << "Expected size: 4\n";
  cout << "Actual size: " << a.size() << endl;
  assert(4 == a.size());

  // const object copy test
  HashTable<string, int, 10> b(hashCode) ;
  b=a;
  assert(4 == b.size());

  // object assignment test
  HashTable<string, int, 10> c(hashCode);
  c = a;
  assert(4 == c. size());

  // getter and setter
  assert(a["a"] == 1);
  assert(a["b"] == 2);
  a["d"] = 10;
  assert(a["d"] == 10);

  // containskey
  assert(a.containsKey("b") == 1);
  assert(a.containsKey("c") == 1);

  // delete key
  a.deleteKey("d");
  assert(3 == a.size());

  // keys getter
  for (queue<string> keys = a.keys(); !keys.empty(); keys.pop())
     cout << keys.front() << " " << a[keys.front()] << endl;

   a.clear();
  cout << "size " << a.size() << endl;

}
