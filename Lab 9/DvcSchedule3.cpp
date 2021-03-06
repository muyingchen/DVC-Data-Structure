// Lab 9, Part 2, DVC Schedule 3

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;

#include <cstring>

#include "DynamicArray.h"
#include "AssociativeArray.h"

int main()
{
  // define arrays
  AssociativeArray<string, AssociativeArray<string,int> > sectionCounts;
  AssociativeArray<string, int> subjectCounts;
  AssociativeArray<string, AssociativeArray<string, bool> > alreadySeen;
  DynamicArray<string> courseCopy;
  DynamicArray<string> subjectCopy;
  // for parsing the input file
  char* token;
  char buf[1000];
  const char* const tab = "\t";
  ifstream fin;
  fin.open("dvc-schedule.txt");
  if (!fin.good()) throw "I/O error";

  cout << "Parsing" << endl;
int count = 0;
int duplicate = 0;

  while (fin.good())
  {
    bool termfound = false;
    bool subjectfound = false;

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
    // duplicate checking

    if (alreadySeen[term].containsKey(section))
    {
      subjectfound = true;
      alreadySeen[term][section] = true;
      duplicate++;
    }
    else alreadySeen[term][section] = false;

    // counting
    if (!subjectfound)
    {
      if (sectionCounts.containsKey(subjectcode))
      {
        if (sectionCounts[subjectcode].containsKey(course))
        {
          sectionCounts[subjectcode][course]++;
        }
        else
        {
          subjectCounts[subjectcode]++;
          sectionCounts[subjectcode][course] = 1;
        }
      }
      else
      {
        sectionCounts[subjectcode][course] = 1;
        subjectCounts[subjectcode] = 1;
      }
    }

    count++;
    if (count%5000 == 0) cout <<"."; cout.flush();
  }
  fin.close();
  cout << endl;
  // copying and sorting arrays
  int index = 0;
  for(queue<string> keys = sectionCounts.keys(); !keys.empty(); keys.pop())
  {
    subjectCopy[index] = keys.front();
    index++;
  }

  for (int i = 0; i < sectionCounts.size(); i++)
  {
    for (int j = i+1; j < sectionCounts.size(); j++)
    {
      if (subjectCopy[j] < subjectCopy[i])
        swap(subjectCopy[i], subjectCopy[j]);
    }
  }
  // display result
  for (int i = 0; i < sectionCounts.size(); i++)
  {
    int id = 0;
    cout << subjectCopy[i] << ", " << subjectCounts[subjectCopy[i]] << " course(s)" << endl;
    for(queue<string> keys = sectionCounts[subjectCopy[i]].keys(); !keys.empty(); keys.pop())
    {
      courseCopy[id] = keys.front();
      id++;
    }
    for (int j = 0; j < sectionCounts[subjectCopy[i]].size(); j++)
      cout << "  " << courseCopy[j] << ", " << sectionCounts[subjectCopy[i]][courseCopy[j]] << " section(s)" << endl;
  }
}
