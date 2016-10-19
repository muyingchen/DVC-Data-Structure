// Lab 14, BinaryTree Templates Part 1

#include <iostream>
#include <map>
#include <string>
#include <fstream>
using namespace std;

#include <cstring>
#include <cstdlib>

struct Term
{
  string semester;
  int year;
};

bool operator<(const Term& a, const Term& b)
{
  if (a.year < b.year) return true;
  else if(a.year == b.year)
  {
    if (b.semester == "Fall") return true;
    else if (a.semester == "Spring" && b.semester == "Summer") return true;
    else return false;
  }
  else return false;
}

int main()
{ 
  Term searchterm;
  map<string, Term> coursemap;
  map<string, Term> ::iterator it;
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

    // split term into semester and year
    const string termsemester(term.begin(), term.begin() + term.find(' '));
    const string termyear(term, term.find(' ')+1, term.length() - term.find(' '));
    searchterm.semester = termsemester;
    searchterm.year = atoi(termyear.c_str());

    if (coursemap[course] < searchterm)
      coursemap[course] = searchterm;
    else continue;
  }
  fin.close();
  // prompt loop for user input
  while (true)
  {
    string buf;
    cout << "Please enter a course name (include upper case subject code, a dash, "
    << " and alphanumeric sequence number such as COMSC-210): ";
    cin >> buf;
    if (buf == "X" || buf == "x") break;
    it = coursemap.find(buf);
    if (it != coursemap.end())
      cout << buf << " was last offered in " << coursemap[buf].semester << " " << coursemap[buf].year << endl << endl;
    else
      cout << buf << " was not found as far back as year 2000 " << endl << endl;
  }
}
