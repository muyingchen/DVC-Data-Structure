// Lab 12, SortableArray Template

#include<iostream>
#include<string>
using namespace std;

#include <cstdlib>

#include "SortableArray.h"

int main()
{
  SortableArray<double>arr(100);
  SortableArray<bool>index_value(100);
  int count = 0; // index for the index_value array
  string x, y;  // user input strings
  int arrindex, element; // user input index
  double arrval; // user input value

  // fill the bool index_value DynamicArray with false
  for (int i = 0; i < index_value.capacity(); i++)
    index_value[i] = false;

  // prompt user input
  for (int i = 0; i < arr.capacity(); i++)
  {
    cout << "Input an index and a value [Q to quit]:  ";
    cin >> x;
    if ( x == "q" || x == "Q" ) break;
    cin >> y;
    if ( y == "q" || y == "Q" ) break;

    arrindex = atoi(x.c_str()); // convert string to int
    arrval = atof(y.c_str());  // convert string to double
    if (arrindex >= arr.capacity())
    {
      int x = arrindex-1;
      arr.capacity(2*arrindex);
      arr[arrindex] = arrval;
      index_value.capacity(2*arrindex);
      for (int i = x; i < index_value.capacity(); i++)
        index_value[i] = false;
    }
    else
      arr[arrindex] = arrval;

    if (arrindex >= 0 && index_value[arrindex] == false)
    {
      count++;
      index_value[arrindex] = true;
    }
  }

  // prompt unique indexes and output all indexes and values
  cout << "\nYou stored this many values: " << count << endl;
  cout << "The index-value pairs are: \n";
  for (int i = 0; i < arr.capacity(); i++)
    if (index_value[i] == true)
      cout << i << "=>" << arr[i] << " ";

  // prompt sorting function
  cout << "\n\nEnter the number of values you want to sort (avoid hole index): ";
  cin >> element;
  arr.sort(element);
  for (int i = 0; i < arr.capacity(); i++)
    if (index_value[i] == true)
      cout << i << "=>" << arr[i] << " ";

  // event-controlled loop prompts for valid index and value with corresponding index
  while (true)
  {
    int index;
    string buf;
    cout << endl << "Input an index for me to look up [Q to quit]: ";
    cin>> buf;
    if (buf == "Q" || buf == "q") break;
    else
      index = atoi(buf.c_str());
    if ( index < 0 || index > arr.capacity())
      cout << "I didn't find it" << endl;
    else if ( index_value[index] == false)
      cout << "Index is not in use" << endl;
    else
    {
      if (index_value[index] == true)
        cout << "Found it -- the value stored at " << index << " is " << arr[index] << endl;
    }
  }
}
