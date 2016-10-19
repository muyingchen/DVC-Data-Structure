// Lab 8, Part 1: Perform A Simple Timing Study

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include <ctime>
#include <cmath> // for log and pow
#include <cstring> // for strtok, strcpy, and atoi

#include "DynamicArray.h"

struct SectionsForTerm
{
  string term;
  int numberOfSectionsSeen; // to track where we are in the following "array"
  DynamicArray<string> seenSectionNumbers; // store non-duplicated section numbers
};

struct Subject
{
  string subject;
  int subjectnumber;
};

int main()
{
  char* token;
  char buf[1000];
  const char* const tab = "\t";
  ifstream fin;
  int numberOfTermsSeen = 0; // to track where we are in the following "array"
  int numberOfSubjectSeen = 0;
  DynamicArray<SectionsForTerm> alreadySeen(200);

  int n = 8000;
  string bigOh = "O(n)";
  cout.setf(ios::fixed);
  cout.precision(4);
  double elapsedSecondsNorm = 0;
  double expectedSeconds = 0;
  int duplicate = 0;

  for (int cycle = 0; cycle < 4; cycle++, n*= 2)
  {
    clock_t startTime = clock( );
    fin.open("dvc-schedule.txt");
    if (!fin.good()) throw "I/O error";
    for(int i = 0; fin.good() && i < n; i++)
    {
      bool found = false;
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

      for (int i = 0; i < numberOfTermsSeen; i++)
      {
        if (alreadySeen[i].term == term)
        {
          for (int j = 0; j < alreadySeen[i].numberOfSectionsSeen; j++)
          {
            if (alreadySeen[i].seenSectionNumbers[j] == section)
            {
              duplicate++;
              found = true;
              break;
            }
          }
        }
      }
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
