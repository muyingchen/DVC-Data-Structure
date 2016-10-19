// Lab 15, Graph Searches Part 2

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <vector>
using namespace std;

struct Vertex
{
  string name;
  bool isVisited;
  list<int> adjacentVertices;
};

queue<int> doDepthFirstSearch(int iOriginVertex, vector<Vertex>& database)
{
  //create an empty result queue if ints to return at end of function call
  queue<int> searchOrder;
  //create a stack of ints to store the "to-do" list
  stack<int> todolist;
  //initialize each node in database: set to "not visited"
  for (int i = 0; i < database.size(); i++) database[i].isVisited = false;
  //push start node's index onto the "to-do" list
  todolist.push(iOriginVertex);
  //while the "to-do" list is not empty
  while (!todolist.empty())
  {
    //peek/pop a node's index from the "to-do" list
    int i = todolist.top();
    todolist.pop();
    //if that node has not yet been visited
    if (!database[i].isVisited)
    {
      //mark the node as visited
      database[i].isVisited = true;
      //push node's index onto the result queue
      searchOrder.push(i);
      list<int>::reverse_iterator it;
      //for each of that node's neighbors (in reverse order)
      for (it = database[i].adjacentVertices.rbegin(); it != database[i].adjacentVertices.rend(); ++it)
      {
        //if neighbor has not yet been visited
        if (!database[*it].isVisited)
          //push neighbor's index onto the "to-do" list
          todolist.push(*it);
      }
    }
  }
  return searchOrder;
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
    string fromCity, toCity;

    // read one edge
    getline(fin, fromCity);
    getline(fin, toCity);
    fin.ignore(1000, 10); // skip the line with distance
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
    database[iFromVertex].adjacentVertices.push_back(iToVertex);
    database[iToVertex].adjacentVertices.push_back(iFromVertex);
  }
  fin.close();
  cout << "Input file processed\n\n";

  while (true)
  {
    // get the start city for the search
    string startCity;
    cout << "\nEnter the start city [blank to exit]: ";
    getline(cin, startCity);
    if (startCity.length() == 0) break;

    // find the start city
    int i;
    for (i = 0; i < database.size(); i++)
      if (database[i].name == startCity)
        break;

    // DFS result
    cout << "DFS";
    queue<int> q = doDepthFirstSearch(i, database);
    while(!q.empty())
    {
      cout  << '-'<< database[q.front()].name;
      q.pop();
    }
    cout << endl;
  }
}
