// Lab 2, StaticArray Template Part 1

#include<iostream>
using namespace std;

#include<cassert>

#include "StaticArray.h"
#include "StaticArray.h" // ifndef test

int main()
{
  StaticArray<int,100> a;

  // testing Array::capacity
  cout << "\nTesting StaticArray<int,100>::capacity\n";
  cout << "Expected: 100\n";
  cout << "Actual: " << a.capacity() << endl;
  assert(100 == a.capacity());

  // testing Array::operator[] setter
  a[19] = 34;
  a[99] = 65;
  a[0] = 46;
  a[-10] = -1;
  cout << "\nTesting StaitcArray<int,100>::operator[] setter\n";
  cout << "Expected: 34 for a[19] \n";
  cout << "Actual: " << a[19] << endl;
  assert(34 == a[19]);
  cout << "Expected: 65 for a[99] \n";
  cout << "Actual: " << a[99] << endl;
  assert(65 == a[99]);
  cout << "Expected: 46 for a[0] \n";
  cout << "Actual: " << a[0] << endl;
  assert(46 == a[0]);
  cout << "Expected: -1 for a[-10] \n";
  cout << "Actual: " << a[-10] << endl;
  assert(-1 == a[-12]);  // any out of range uses dummy
  assert(-1 == a[100]); // checks upper end of range
  assert(99 != a[99]); // checks upper end of range
  assert(0 != a[0]); // checks lower end of range

  // testing Array:operator[] getter
  const StaticArray<int,100> b = a;
  cout << "\nTesting StaticArray<int,100>::operator[] getter\n";
  cout << "Expected: 34 for b[19] \n";
  cout << "Actual: " << b[19] << endl;
  assert(34 == b[19]);
  cout << "Expected: 65 for b[99] \n";
  cout << "Actual: " << b[99] << endl;
  assert(65 == b[99]);
  cout << "Expected: 46 for b[0] \n";
  cout << "Actual: " << b[0] << endl;
  assert(46 == b[0]);
  cout << "Expected: -1 for b[-10] \n";
  cout << "Actual: " << b[-10] << endl;
  assert(-1 == b[-12]);  // any out of range uses dummy
  assert(-1 == b[100]); // checks upper end of range
  assert(99 != b[99]); // checks upper end of range
  assert(0 != b[0]); // checks lower end of range

  // const object copy test
  assert(a.capacity() == b.capacity());
  for (int i = 0; i < 10; i++)
    assert(a[i] == b[i]);

  // object assignment test
  StaticArray<int,100> c;
  c = a;
  assert(a.capacity() == c.capacity());
  for (int i = 0; i < 10; i++)
  assert(a[i] == c[i]);
}
