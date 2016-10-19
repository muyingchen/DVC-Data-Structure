// Lab 6, Part 2: Developing And Testing A Stack Template

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

#include "Stack.h"

int main()
{
  Stack<double> calculator(10);
  Stack<double> calculatorcopy(10);
  double number;
  string input;
  bool quit = false;

  while (quit == false)
  {
    cout << "\nEnter: ";
    cin >> input;
    if (input == "q" || input == "Q")
    {
      quit = true;
      break;
    }
    else
    {
       if ((input != "+") && (input != "-") && (input != "*") && (input!= "/"))
       {
         number = atof(input.c_str());
         calculator.push(number);
         Stack<double> calculatorcopy = calculator;
         int size = calculatorcopy.size();
         cout << "Enter: ";
         for (int i = 0; i < size; i++)
         {
            cout << calculatorcopy.peek() << " ";
            calculatorcopy.pop();
          }
        }
        else if ((calculator.size() >= 2) && (input == "+" || input == "-"|| input == "*" || input == "/"))
        {
          if (input == "+")
          {
            double num1 = calculator.peek();
            calculator.pop();
            double num2 = calculator.peek();
            calculator.pop();
            double sum = num1 + num2;
            calculator.push(sum);
            Stack<double> calculatorcopy = calculator;
            int size = calculatorcopy.size();
            cout << "Enter: ";
            for (int i = 0; i <size; i++)
            {
              cout << calculatorcopy.peek() << " ";
              calculatorcopy.pop();
            }
          }
          else if (input == "-")
          {
            double num1 = calculator.peek();
            calculator.pop();
            double num2 = calculator.peek();
            calculator.pop();
            double difference = num2 - num1;
            calculator.push(difference);
            Stack<double> calculatorcopy = calculator;
            int size = calculatorcopy.size();
            cout << "Enter: ";
            for (int i = 0; i <size; i++)
            {
              cout << calculatorcopy.peek() << " ";
              calculatorcopy.pop();
            }
          }
          else if (input == "*")
          {
            double num1 = calculator.peek();
            calculator.pop();
            double num2 = calculator.peek();
            calculator.pop();
            double product = num2 * num1;
            calculator.push(product);
            Stack<double> calculatorcopy = calculator;
            int size = calculatorcopy.size();
            cout << "Enter: ";
            for (int i = 0; i <size; i++)
            {
              cout << calculatorcopy.peek() << " ";
              calculatorcopy.pop();
            }
          }
          else if (input == "/")
          {
            double num1 = calculator.peek();
            calculator.pop();
            double num2 = calculator.peek();
            calculator.pop();
            double division = num2 / num1;
            calculator.push(division);
            Stack<double> calculatorcopy = calculator;
            int size = calculatorcopy.size();
            cout << "Enter: ";
            for (int i = 0; i <size; i++)
            {
              cout << calculatorcopy.peek() << " ";
              calculatorcopy.pop();
            }
          }
        }
        else if ((calculator.size() < 2) && (input == "+" || input == "-"|| input == "*" || input == "/"))
          cout << "Please enter a number again";
     }
  }
}
