// Lab 6, Part 1: Developing And Testing A Stack Template

#include<iostream>
#include<string>
using namespace std;

#include<cassert>

#include "Stack.h"
#include "Stack.h" // ifndef test

int main()
{
  Stack<int> number;

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
  const Stack<int> number1 = number;
  assert(4 == number1.size());

  // object assignment test
  Stack<int> number2;
  number2 = number;
  assert(4 == number2. size());

  // testing peek function
  int topnumber = number.peek();
  cout << "\nTesting peek function\n";
  cout << "Expected number: 40\n";
  cout << "Actual number: " << topnumber << endl;
  assert(40 == topnumber);

  // testing pop function
  number.pop();
  cout << "\nTesting pop function once\n";
  cout << "Expected number: 30\n";
  cout << "Actual number: " << number.peek() << endl;
  assert(30 == number.peek());

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
