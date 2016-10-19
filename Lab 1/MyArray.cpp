// Lab 1, Array Class Part 2

#include<iostream>
#include<string>
using namespace std;

#include <cstdlib>

class Array
{
  int values[100];
  int dummy;

  public:
  int capacity() const {return 100;}
  int operator[](int) const; // getter
  int& operator[](int); // setter
};

int main()
{
  Array arr, index_value;
  int count = 0; // index for the index_value array
  string x, y;  // user input strings
  int arrindex, arrval; // user input integers

  // fill the index_value array with numbers from 0 - 99
  for (int i = 0; i < index_value.capacity(); i++)
    index_value[i] = i;

  // prompt user input
  for (int i = 0; i < arr.capacity(); i++)
  {
    cout << "Input an index and a value [Q to quit]:  ";
    cin >> x;
    if ( x == "q" || x == "Q") break;
    cin >> y;
    if ( y == "q" || y == "Q" ) break;

    arrindex = atoi(x.c_str());
    arrval = atoi(y.c_str());  // convert string to int
    arr[arrindex] = arrval;

    if (arrindex == index_value[arrindex])
    {
      index_value[arrindex] = 1000;
      count++;   // count the unique index
    }
    else
      continue;
  }

  // prompt unique indexes and output all indexes and values
  cout << "\nYou stored this many values: " << count << endl;
  cout << "The index-value pairs are: \n";
  for (int i = 0; i < arr.capacity(); i++)
  {
    if (index_value[i] == 1000)
      cout << "  " << i << " " << arr[i] << endl;
    else
      continue;
  }

  // event-controlled loop prompts for valid index and value with corresponding index
  while (true)
  {
    int index;
    string buf;
    cout << "Input an index for me to look up [Q to quit]: ";
    cin>> buf;
    if (buf == "Q" || buf == "q") break;
    else
      index = atoi(buf.c_str());
    if ( index < 0 || index >= 100)
      cout << "I didn't find it" << endl;
    else if ( index_value[index] != 1000 )
      cout << "Index is not in use" << endl;
    else
    {
      if (index_value[index] == 1000)
        cout << "Found it -- the value stored at " << index << " is " << arr[index] << endl;
      else
        continue;
    }
  }
}

int Array::operator[](int index) const
{
  if ( index < 0 || index >= 100 )
    return -999;
  else
    return values[index];
}

int& Array::operator[](int index)
{
  if ( index < 0 || index >= 100 )
    return dummy;
  else
    return values[index];
}
