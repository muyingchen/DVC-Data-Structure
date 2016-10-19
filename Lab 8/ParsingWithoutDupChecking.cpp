// Lab 8, Part 1: Perform A Simple Timing Study

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include <ctime>
#include <cmath> // for log and pow
#include <cstring> // for strtok, strcpy, and atoi

int main()
{
  char* token;
  char buf[1000];
  const char* const tab = "\t";
  ifstream fin;
  int n = 8000;
  string bigOh = "O(n)";  // YOUR PREDICTION: O(n), O(n log n), or O(n squared)
  cout.setf(ios::fixed);
  cout.precision(4);
  double elapsedSecondsNorm = 0;
  double expectedSeconds = 0;


  for (int cycle = 0; cycle < 4; cycle++, n*= 2)
  {
    clock_t startTime = clock( );
    fin.open("dvc-schedule.txt");
    if (!fin.good()) throw "I/O error";
    for(int i = 0; fin.good() && i < n; i++)
    {
      string line;
      getline(fin, line);
      strcpy(buf, line.c_str());
      if (buf[0] == 0) continue; // skip blank lines
      // parse the line
      const string term(token = strtok(buf, tab));
      const string section(token = strtok(0, tab));
      const string course((token = strtok(0, tab)) ? token : "");
      const string instructor((token = strtok(0, tab)) ? token : "");
      const string whenWhere((token = strtok(0, tab)) ? token : "");
      if (course.find('-') == string::npos) continue; // invalid line: no dash in course name
      const string subjectcode(course.begin(), course.begin() + course.find('-'));
    }
    fin.close();
    clock_t endTime = clock( );

    double elapsedSeconds = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    double factor = pow(2.0, double(cycle));
    if (cycle == 0)
      elapsedSecondsNorm = elapsedSeconds;
    else if (bigOh == "O(n)")
      expectedSeconds = factor * elapsedSecondsNorm;
    else if (bigOh == "O(n log n)")
      expectedSeconds = factor * log(double(n)) / log(n / factor) * elapsedSecondsNorm;
    else if (bigOh == "O(n squared)")
      expectedSeconds = factor * factor * elapsedSecondsNorm;

    cout << elapsedSeconds;
    if (cycle == 0) cout << " (expected " << bigOh << ')';
    else cout << " (expected " << expectedSeconds << ')';
    cout << " for n=" << n << endl;
  }
}
