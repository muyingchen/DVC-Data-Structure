// Lab 7, Part 2: Server Simulation

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "Queue.h"
#include "DynamicArray.h"

int getRandomNumberOfArrivals(double);
char getIDTag();

struct Customer
{
  string ID;
  int arrivaltime;
  int serviceendtime;
};

int main()
{
  srand(time(0));// rand();
  // read the input values from a text file, one per line, in the order specified above.
  string num[10];
  string line;
  int nLine = 0;
  ifstream fin;
  // open file
  fin.open("simulation.txt");
  if (!fin.good()) throw "I/O error";
  while(fin.good())
  {
    getline(fin, line);
    if (line != "")
    {
      num[nLine] = line;
      nLine++;
    }
  }
  fin.close();

  // declare variables read from simulation.txt
  int servernumber = atoi(num[0].c_str());
  double avgarrivalrate = atof(num[1].c_str());
  int queuelength = atoi(num[2].c_str());
  int mintime = atoi(num[3].c_str());
  int maxtime = atoi(num[4].c_str());
  int stopclocktime = atoi(num[5].c_str());

  // output information from sumulation.txt
  cout << endl;
  cout << "number of servers:     " << servernumber << endl;
  cout << "customer arrival rate: " << avgarrivalrate << " per minute, for " << stopclocktime << " minutes" << endl;
  cout << "maximum queue length:  " << queuelength << endl;
  cout << "minimum service time:  " << mintime << endl;
  cout << "maximum service time:  " << maxtime << endl << endl;

  // declare and create and assign arrays and queues to be used in the solution
  Queue<Customer> waitqueue;
  DynamicArray<Customer> nowserving(servernumber);
  DynamicArray<bool> server(servernumber);
  // fill server array with true (idle)
  for (int i = 0; i < servernumber; i++)
    server[i] = true;

  // the clock time loop
  for (int time = 0;; time++) // the clock time
  {
    bool allidle = true;
    // handle all services scheduled to complete at this clock time
    for (int i = 0; i < servernumber; i++)
    {
      if (server[i] == false)
      {
        if (time == nowserving[i].serviceendtime) //the service end time of the customer that its now serving equals the clock time)
          server[i] = true;
      }
    }
    // handle new arrivals -- can be turned away if wait queue is at maximum length!
    if (time < stopclocktime) // clock time is less than the time at which new arrivals stop
    {
      int arrivals = getRandomNumberOfArrivals(avgarrivalrate);//get the #of of arrivals from the "Poisson process" (a whole number >= 0)
      cout << "arrivals: " << arrivals << endl;
      for (int i = 0; i < arrivals; i++) // for each arrival
      {
        if (waitqueue.size() < queuelength) // the wait queue is NOT full
        {
          Customer a; //create a new customer object
          a.arrivaltime = time; //set its arrival time equal to the current clock time
          a.ID = getIDTag(); // assign it an ID tag (A-Z)
          waitqueue.push(a); //push the new customer onto the wait queue
        }
      }
    }
    // for idle servers, move customer from wait queue and begin service
    for (int i = 0; i < servernumber; i++) // each server
    {
      if ((server[i] == true) && (!waitqueue.empty())) //server is idle AND the wait queue is not empty
      {
        int RNG = 1 + (rand() % (maxtime - mintime));
        nowserving[i] = waitqueue.front();
        waitqueue.pop(); //remove top customer from wait queue
        nowserving[i].serviceendtime = time + RNG; //set service end time to current clock time PLUS "random service interval"
        server[i] = false; //mark that server as busy
      }
      //if ((server[i] == true) && (waitqueue.empty())) allidle = true;
    }
    for (int i = 0; i < servernumber; i++)
    {
      if(server[i]==false) allidle = false;
    }
    // output the summary
    cout << endl <<"Time: " << time << endl;
    //output a visual prepresentation of the servers and the wait queue
    cout << "-----------------------------" << endl;
    cout << "server now serving wait queue" << endl;
    cout << "------ ----------- ----------" << endl;
    for (int i = 0; i < servernumber; i++)
    {
      cout << " " << i;// output the server's index number (zero-based)
      if (server[i] == false)
        cout << setw(9) << nowserving[i].ID;
      else
        cout << setw(9) << " "; //show the ID of the customer being served by that server (blank if idle)
      if (i == 0) //for server 0 only, show the IDs of customers in the wait queue
      {
        Queue<Customer> copy = waitqueue;
        cout << setw(12);
        for (int j = 0; j < waitqueue.size(); j++)
        {
          Customer temp;
          temp = copy.front();
          cout << temp.ID;
          copy.pop();
        }
        cout << endl;
      }
      else cout << endl;
      cout<< setw(0);
    }
    cout << "-----------------------------"<< endl;
    // if the end of the simulation has been reached, break
    if ((time > stopclocktime) && (allidle==true) && waitqueue.empty())
    {
      cout << "Done! " << endl;
      break;
    }
    // pause for the user to press ENTER
    cout << "Press ENTER to continue...";
    cin.ignore();
  }
}

int getRandomNumberOfArrivals(double averageArrivalRate)
{
  int arrivals = 0;
  double probOfnArrivals = exp(-averageArrivalRate);
  for (double randomValue = (double)rand() / RAND_MAX;
    (randomValue -= probOfnArrivals) > 0.0;
    probOfnArrivals *= averageArrivalRate / (double)++arrivals);
  return arrivals;
}

char getIDTag()
{
  static int count = 0;
  char temp;
	char IDTag[26] = {'A','B','C','D','E','F','G','H','I',
  'J','K','L','M','N','O','P','Q','R','S','T','U','V','W',
  'X','Y','Z'};
  if (count < 26)
  {
    temp = IDTag[count];
    count++;
  }
  else
  {
    count = 0;
    temp = IDTag[count];
    count++;
  }
  return temp;
}
