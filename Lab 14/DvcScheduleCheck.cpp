// Lab 14, BinaryTree Templates Part 2

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <list>
#include <algorithm>
using namespace std;

#include <cstring>
#include <cstdlib>

int main()
{ 
  map<string, list<string> > duplicate;
  map<string, list<string> > ::iterator it;
  list<string> ::iterator iterator;
  // for parsing the input file
  char* token;
  char buf[1000];
  const char* const tab = "\t";
  ifstream fin;
  fin.open("dvc-schedule.txt");
  if (!fin.good()) throw "I/O error";

  while (fin.good())
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
    const string termkey = term + " " + section;

    it = duplicate.find(termkey);
    if (it != duplicate.end())
    {
      iterator = find(duplicate[termkey].begin(), duplicate[termkey].end(), course);
      if (iterator == duplicate[termkey].end())
        duplicate[termkey].push_back(course);
    }
    else duplicate[termkey].push_back(course);
  }
  fin.close();

  cout << "\n Term | Section |  Duplicate Courses "<< endl;
  cout << "-------------------------------------" << endl;
  for (it = duplicate.begin(); it != duplicate.end(); ++it)
  {
    if (it->second.size() > 1)
    {
      cout << it->first << "    ";
      for (iterator = it->second.begin(); iterator != it->second.end(); ++iterator)
        cout << *iterator << "  ";
      cout << endl;
    }
  }
}
