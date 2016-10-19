// Lab 7, Part 1: Developing And Testing A Queue Template

#include<iostream>
using namespace std;

#include<cassert>

#include "Queue.h"
#include "Queue.h" // ifndef test

int main()
{
  Queue<int> number;

  // testing push function
  number.push(10);
  number.push(20);
  number.push(30);
  number.push(40);
  cout << "\nTesting push function and size function\n";
  cout << "Expected size: 4\n";
  cout << "Actual size: " << number.size() << endl;
  assert(4 == number.size());

  // const object copy test
  const Queue<int> number1 = number;
  assert(4 == number1.size());

  // object assignment test
  Queue<int> number2;
  number2 = number;
  assert(4 == number2. size());

  // testing front and back function
  int topnumber = number.front();
  int bottomnumber = number.back();
  cout << "\nTesting front function\n";
  cout << "Expected number: 10\n";
  cout << "Actual number: " << topnumber << endl;
  assert(10 == topnumber);
  cout << "\nTesting back function\n";
  cout << "Expected number: 40\n";
  cout << "Actual number: " << bottomnumber << endl;
  assert(40 == bottomnumber);

  // testing pop function
  number.pop();
  cout << "\nTesting pop function once\n";
  cout << "Expected number: 20\n";
  cout << "Actual number: " << number.front() << endl;
  assert(20 == number.front());

  // testing clear function
  number.clear();
  cout << "\nTesting clear function\n";
  cout << "Expected size: 0\n";
  cout << "Actual: " << number.size() << endl;
  assert(0 == number.size());

  // testing empty function
  cout << "\nTesting empty function\n";
  cout << "Expected: 1\n";
  cout << "Actual: " << number.empty() << endl;
  assert(1 == number.empty());
}
