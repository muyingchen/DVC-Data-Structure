#include<iostream>
#include<queue>
using namespace std;

#include<cassert>

#include "AssociativeArray.h"
#include "AssociativeArray.h"// ifndef test

int main()
{
  AssociativeArray<string, int> a;

  // testing push function
  a["a"] = 1;
  a["b"] = 2;
  a["c"] = 3;
  a["d"] = 4;
  cout << "Expected size: 4\n";
  cout << "Actual size: " << a.size() << endl;
  assert(4 == a.size());

  // const object copy test
  const AssociativeArray<string, int> b = a;
  assert(4 == b.size());

  // object assignment test
  AssociativeArray<string, int> c;
  c = a;
  assert(4 == c. size());

  // getter and setter
  assert(a["a"] == 1);
  a["d"] = 10;
  assert(a["d"] == 10);

  // containskey
  assert(a.containsKey("b") == 1);

  // delete key
  a.deleteKey("d");
  assert(3 == a.size());

  // keys getter
  for (queue<string> keys = a.keys(); !keys.empty(); keys.pop())
     cout << keys.front() << " " << a[keys.front()] << endl;

  // clear
  a.clear();
  assert(a.size() == 0);
}
