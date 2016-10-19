// Lab 4, Applying A Data Structure To A Big Data Application

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#include <cstring> // for strtok and strcpy

#include "DynamicArray.h"

int main()
{
  // for parsing the input file
  char* token;
  char buf[1000];
  const char* const tab = "\t";

  // create dynamic arrays for dvc schedule
  DynamicArray<string> dvcterm(1000);
  DynamicArray<string> dvcsection(1000);
  DynamicArray<string> dvcsubjectcode(1000);
  DynamicArray<string> subject(50);
  DynamicArray<int> subjectnumber(50);

  // open the input file
  ifstream fin;
  fin.open("dvc-schedule.txt");
  if (!fin.good()) throw "I/O error";

  // read the input file
  cout << "Parsing the file\n";
int count = 0;
int duplicate = 0;
  while (fin.good())
  {
    bool found = false;
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
    const string subjectcode(course.begin(), course.begin() + course.find('-'));
    // check for duplicates
    for (int i = 0; i < count; i++)
    {
      if (dvcsection[i] == section && dvcterm[i] == term)
      {
        found = true;
        duplicate++;
        break;
      }
    }

    if (count%1000==0) cout << "."; cout.flush();

    // fill dynamic array with strings from dvc schedule
    if (found == false)
    {
      dvcterm[count] = term;
      dvcsection[count] = section;
      dvcsubjectcode[count] = subjectcode;
      count++;
    }
  }
  fin.close();
  
  cout << "\nParsing finished" << endl;
  cout << "Count is " << count << endl;
  cout << "Duplicate is " << duplicate << endl;

  // sorting
  cout << "\nSorting" << endl;
  for (int i = 0; i < count; i++)
  {
    if (i%1000==0) cout << "."; cout.flush();
    for (int j = i+1; j < count; j++)
    {
      if (dvcsubjectcode[j] < dvcsubjectcode[i])
        swap(dvcsubjectcode[i], dvcsubjectcode[j]);
    }
  }
  cout << "\nSorting finished" << endl;

  // display results
  cout << endl << "Display results " << endl;
int linecounter = 0;
int subjectcounter = 0;
  for (int i = 0; i < count; i++)
  {
    if (dvcsubjectcode[i] == dvcsubjectcode[i+1]) linecounter++;
    if (dvcsubjectcode[i] != dvcsubjectcode[i+1])
    {
      subject[subjectcounter] = dvcsubjectcode[i];
      subjectnumber[subjectcounter] = linecounter+1;
      subjectcounter++;
      linecounter = 0;
    }
  }
  for (int i = 0; i < subjectcounter; i++)
    cout << subject[i] << ", " << subjectnumber[i] << " sections" << endl;
}
