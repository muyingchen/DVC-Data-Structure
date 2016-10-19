// Lab 11, PriorityQueue Template Part 2

#include <iostream>
#include <string>
using namespace std;

#include <cassert> 
#include <cmath>
#include <cstdlib> // for srand and rand
#include <ctime> // for clock(), clock_t, time, and CLOCKS_PER_SEC

#include "PriorityQueue.h"

int main()
{
  srand(time(0)); rand(); // seed the random number generator (in case you need it)

  int n = 500000; // THE STARTING PROBLEM SIZE (MAX 250 MILLION)
  const int reps = n / 100; // one percent of starting n

  cout.setf(ios::fixed);
  cout.precision(4);
  double elapsedSecondsNorm = 0;
  for (int cycle = 0; cycle < 4; cycle++, n*= 2)
  {
    // problem setup goes here -- create a data structure of size n
    PriorityQueue<int> a(2*n);
    // assert that n is the size of the data structure if applicable
    for (int i = 0; i < n; i++) a.push(rand());
    //assert(a.size() == n); // or something like that...
    assert(a.size() == n);
    // start the timer, do something, and stop the timer
    clock_t startTime = clock();
    for (int rep = 0; rep < reps; rep++)
    {
      // do something where n is the "size" of the problem
      a.pop();
    }
    clock_t endTime = clock();

    // validation block -- assure that process worked if applicable
    assert(a.size() == n - reps);
    // compute timing results
    double elapsedSeconds = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    double factor = pow(2.0, double(cycle));
    if (cycle == 0) elapsedSecondsNorm = elapsedSeconds;
    double expectedSecondsLog = log(double(n)) / log(n / factor) * elapsedSecondsNorm;

    // reporting block
    cout << elapsedSeconds;
    if (cycle == 0) cout << " (expected)";
    else cout << " (expected " << elapsedSecondsNorm << " to " << expectedSecondsLog << ')';
    cout << " for n=" << n << endl;
  }
}
