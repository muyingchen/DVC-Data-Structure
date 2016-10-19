#include<iostream>
#include<queue>
using namespace std;

#include<cassert>

#include "PriorityQueue.h"
#include "PriorityQueue.h"// ifndef test

int main()
{
  // programmer's identification
  cout << "\nProgrammer: Muying Chen\n";
  cout << "Programmer's ID: 1489049\n";
  cout << "File: " << __FILE__ << endl;

  // testing push function
  PriorityQueue<int> pq;
  pq.push(100); // requires that less-than be defined
  pq.push(200);
  pq.push(20);
  pq.push(2);
  pq.push(15);
  pq.push(70);
  pq.push(90);
  pq.push(110);
  pq.push(60);
  pq.push(1000);
  cout << "size: " << pq.size( ) << endl; // initially zero
  assert(10 == pq.size());
  cout << "top: " << pq.top( ) << endl; // returns largest value
  assert(1000 == pq.top());

  const PriorityQueue<int> pq1 = pq;
  assert(10 == pq1.size());

  // object assignment test
  PriorityQueue<int> pq2;
  pq2 = pq1;
  assert(10 == pq2. size());

  // pop
  pq.pop();
  cout << "size after pop once: " << pq.size() << endl;
  assert(9 == pq.size());
  cout << "top after pop once: " << pq.top( ) << endl; // returns largest value
  assert(200 == pq.top());
  pq.pop();
  pq.pop();
  cout << "size after pop 3 times: " << pq.size() << endl;
  assert(7 == pq.size());
  cout << "top after pop 3 times: " << pq.top( ) << endl; // returns largest value
  assert(100 == pq.top());

  pq.clear();
  assert (pq.empty() == 1);
  assert (pq.size() == 0);

  cout << endl << "done testing" << endl;
}
