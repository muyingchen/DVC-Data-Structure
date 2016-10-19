// Lab 5, Programming For Big Data

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

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
  int subjectNumber;
};

int main()
{
  // for parsing the input file
  char* token;
  char buf[1000];
  const char* const tab = "\t";
  int numberOfTermsSeen = 0; // to track where we are in the following "array"
  int numberOfSubjectSeen = 0;
  DynamicArray<SectionsForTerm> alreadySeen(200);
  DynamicArray<Subject> dvcsubject(150);
  // open the input file
  ifstream fin;
  fin.open("dvc-schedule.txt");
  if (!fin.good()) throw "I/O error";

  cout << "Parsing" << endl;
int count = 0;
int duplicate = 0;
  // read the input file
  while (fin.good())
  {
    bool found = false;
    bool termfound = false;
    bool subjectfound = false;
    // read the line
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
    const string subjectcode(course.begin(), course.begin() + course.find('-')); //converstring section to int section
    // duplicate checking
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
            subjectfound = true;
            break;
          }
        }
        if (!found)
        {
          alreadySeen[i].seenSectionNumbers[alreadySeen[i].numberOfSectionsSeen] = section;
          alreadySeen[i].numberOfSectionsSeen++;
          numberOfTermsSeen++;
          termfound = true;
        }
        break;
      }
    }
    // done duplicate checking

    if (termfound == false)
    {
      alreadySeen[numberOfTermsSeen].term = term;
      alreadySeen[numberOfTermsSeen].seenSectionNumbers[0] = section;
      alreadySeen[numberOfTermsSeen].numberOfSectionsSeen = 1;
      numberOfTermsSeen++;
    }
    for (int i = 0; i < numberOfSubjectSeen; i++)
    {
      if (subjectfound == false)
      {
        if (dvcsubject[i].subject == subjectcode)
        {
          dvcsubject[i].subjectNumber++;
          subjectfound = true;
          break;
        }
        continue;
      }
    }
    if (subjectfound == false)
    {
      dvcsubject[numberOfSubjectSeen].subjectNumber = 1;
      dvcsubject[numberOfSubjectSeen].subject = subjectcode;
      numberOfSubjectSeen++;
    }
    count++;
    if (count%2000 == 0) cout <<"."; cout.flush();
  }
  fin.close();
  cout << "\nDuplicate is " << duplicate << endl << endl;
  cout << "Subject count " << numberOfSubjectSeen << endl;
  cout << "Term count " << numberOfTermsSeen << endl;
}
