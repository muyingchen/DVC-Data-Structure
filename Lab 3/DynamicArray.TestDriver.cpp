// Lab 3, Dynamic Array Template Part 1

#include<iostream>
using namespace std;

#include<cassert>

#include "DynamicArray.h"
#include "DynamicArray.h" // ifndef test

int main()
{
  DynamicArray<int> a;
  DynamicArray<int> x(100);

  // testing DynamicArray::capacity() and default constructor
  cout << "\nTesting DynamicArray<int>::capacity() and default constructor\n";
  cout << "Expected: 2\n";
  cout << "Actual: " << a.capacity() << endl;
  assert(2 == a.capacity());

  // testing main constructor
  cout << "\nTesting main constructor\n";
  cout << "Expected: 100\n";
  cout << "Actual: " << x.capacity() << endl;
  assert(100 == x.capacity());

  // testing capacity setter
  a.capacity(200);
  cout << "\nTesting capacity setter increase\n";
  cout << "Expected: 200\n";
  cout << "Actual: " << a.capacity() << endl;
  assert(200 == a.capacity());
  a.capacity(20);
  cout << "\nTesting capacity setter decrease\n";
  cout << "Expected: 20\n";
  cout << "Actual: " << a.capacity() << endl;
  assert(20 == a.capacity());

  // testing DynamicArray::operator[] setter
  a[0] = 46;
  a[10] = 34;
  a[99] = 65;
  a[-10] = -1;
  cout << "\nTesting DynamicArray<int>::operator[] setter\n";
  cout << "Expected: 46 for a[0] \n";
  cout << "Actual: " << a[0] << endl;
  assert(46 == a[0]);
  cout << "Expected: 34 for a[10] \n";
  cout << "Actual: " << a[10] << endl;
  assert(34 == a[10]);
  cout << "Expected: 65 for a[99] \n";
  cout << "Actual: " << a[99] << endl;
  assert(65 == a[99]);
  cout << "Expected: -1 for a[-10] \n";
  cout << "Actual: " << a[-10] << endl;
  assert(-1 == a[-12]);  // any out of range uses dummy
  assert(99 != a[99]); // checks upper end of range
  assert(0 != a[0]); // checks lower end of range

  // testing Array:operator[] getter
  const DynamicArray<int> b = a;
  cout << "\nTesting DynamicArray<int>::operator[] getter\n";
  cout << "Expected: 46 for b[0] \n";
  cout << "Actual: " << b[0] << endl;
  assert(46 == b[0]);
  cout << "Expected: 34 for b[10] \n";
  cout << "Actual: " << b[10] << endl;
  assert(34 == b[10]);
  cout << "Expected: 65 for b[99] \n";
  cout << "Actual: " << b[99] << endl;
  assert(65 == b[99]);
  assert(99 != b[99]);
  assert(0 != b[0]);

  // const object copy test
  assert(a.capacity() == b.capacity());
  for (int i = 0; i < b.capacity(); i++)
    assert(a[i] == b[i]);

  // object assignment test
  DynamicArray<int> c;
  c = a;
  assert(a.capacity() == c.capacity());
  for (int i = 0; i < c.capacity(); i++)
  assert(a[i] == c[i]);
}
