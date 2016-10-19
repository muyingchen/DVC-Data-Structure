// Lab 15, Graph Searches Part 1

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct Vertex
{
  string name;

  bool isVisited;
  list<int> adjacentVertices;
};

queue<int> doBreadthFirstSearch(int iOriginVertex, vector<Vertex>& database)
{
  //create an empty result queue of ints to return at end of function call
  queue<int> searchOrder; // return this queue of indices
  //create another queue of ints to store the "to-do" list
  queue<int> todolist;
  //initialize each node in database: set to "not visited"
  for (int i = 0; i < database.size(); i++) database[i].isVisited = false;
  //mark starting node as "visited"
  database[iOriginVertex].isVisited = true;
  //push start node's index onto the result queue
  searchOrder.push(iOriginVertex);
  //push start node's index onto the "to-do" list
  todolist.push(iOriginVertex);
  //while the "to-do" list is not empty
  while (!todolist.empty())
  {
    //peek/pop a node's index from the "to-do" list
    int i = todolist.front();
    todolist.pop();
    //for each of that node's neighbors
    list<int>::const_iterator it;
    for (it = database[i].adjacentVertices.begin(); it != database[i].adjacentVertices.end(); it++)
    {
      //if neighbor has not yet been visited
      if (!database[*it].isVisited)
      {
        //mark neighbor as visited
        database[*it].isVisited = true;
        //push neighbor's index onto the result queue
        searchOrder.push(*it);
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

    // BFS result
    cout << "BFS";
    queue<int> q = doBreadthFirstSearch(i, database);
    while(!q.empty())
    {
      cout  << '-'<< database[q.front()].name;
      q.pop();
    }
    cout << endl;
  }
}
