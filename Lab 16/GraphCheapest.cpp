// Lab 16, Graph Routes Part 2

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <utility>
using namespace std;

#include <cstdlib>

struct Vertex
{
  string name;
  bool isVisited;
  list<pair<int, double> > adjacentVertices;
  int prev;
  double cost;
};

pair<stack<int>, double> getCheapestRoute(int iStart, int iEnd, vector<Vertex>& database)
{
  pair<stack<int>, double> result;
  list<pair<int, double> >::iterator it; // to iterate over adjacentVertices
// TO DO -- write this function
  //set prev=-1 for all nodes, and mark all as not visited
  for (int i = 0;i < database.size(); i++)
  {
    database[i].prev = -1;
    database[i].isVisited = false;
    database[i].cost = 0.0;
  }
  //create a queue of ints to store the "to-do" list
  queue<int> todolist;
  //mark start node as "visited" and push it onto the "to-do" list
  database[iStart].isVisited = true;
  todolist.push(iStart);
  //while the "to-do" list is not empty
  while (!todolist.empty())
  {
    //peek/pop a node's index from the "to-do" list -- call it the "node under consideration"
    int i = todolist.front(); // node under consideration
    todolist.pop();
    //for each of that node's neighbors
    for (it = database[i].adjacentVertices.begin(); it != database[i].adjacentVertices.end(); ++it)
    {
      //calculate "new cost" = cost to the node under consideration PLUS the neighbor's edge cost
      double newcost = database[i].cost + it->second;
      //if neighbor's been visited AND the new cost is not less than the current cost, "continue;"
      if (database[it->first].isVisited && newcost>= database[it->first].cost) continue;
     // set neighbor's cost to the new cost
      database[it->first].cost = newcost;
      //set neighbor's prev to the index of the node under consideration
      database[it->first].prev = i;
     // mark neighbor as visited
      database[it->first].isVisited = true;
      //push neighbor's index' into the "to-do" list
      todolist.push(it->first);
    }
  }
  //build a stack of entries, starting from the end node, back towards the start
  for (int i = iEnd; i != -1; i = database[i].prev)
    result.first.push(i);
  result.second = database[iEnd].cost;
  return result;
}

int main()
{
  ifstream fin;
  fin.open("cities.txt");
  if (!fin.good()) throw "I/O error";

  // process the input file
  vector<Vertex> database;
  while (fin.good()) // EOF loop
  {
    string fromCity, toCity, cost;

    // read one edge
    getline(fin, fromCity);
    getline(fin, toCity);
    getline(fin, cost);
    fin.ignore(1000, 10); // skip the separator

    // add vertices for new cities included in the edge
    int iToVertex = -1, iFromVertex = -1, i;
    for (i = 0; i < database.size(); i++) // seek "to" city
      if (database[i].name == fromCity)
        break;
    if (i == database.size()) // not in database yet
    {
      // store the vertex if it is new
      Vertex fromVertex;
      fromVertex.name = fromCity;
      database.push_back(fromVertex);
    }
    iFromVertex = i;

    for (i = 0; i < database.size(); i++) // seek "from" city
      if (database[i].name == toCity)
        break;
    if (i == database.size()) // not in vector yet
    {
      // store the vertex if it is new
      Vertex toVertex;
      toVertex.name = toCity;
      database.push_back(toVertex);
    }
    iToVertex = i;

    // store bi-directional edges
    double edgeCost = atof(cost.c_str());
    database[iFromVertex].adjacentVertices.push_back(pair<int, double>(iToVertex, edgeCost));
    database[iToVertex].adjacentVertices.push_back(pair<int, double>(iFromVertex, edgeCost));
  }
  fin.close();
  cout << "Input file processed\n\n";

  while (true)
  {
    string fromCity, toCity;
    cout << "\nEnter the source city [blank to exit]: ";
    getline(cin, fromCity);
    if (fromCity.length() == 0) break;

    // find the from city
    int iFrom;
    for (iFrom = 0; iFrom < database.size(); iFrom++)
      if (database[iFrom].name == fromCity)
        break;

    cout << "Enter the destination city [blank to exit]: ";
    getline(cin, toCity);
    if (toCity.length() == 0) break;

    // find the destination city
    int iTo;
    for (iTo = 0; iTo < database.size(); iTo++)
      if (database[iTo].name == toCity)
        break;

    cout << "Route";
    pair<stack<int>, double> result = getCheapestRoute(iFrom, iTo, database);
    while (!result.first.empty()){cout << "-" << database[result.first.top()].name; result.first.pop();}
    cout << "\nTotal Miles: " << result.second;
    cout << endl;
  }
}
