/****************************************************************************
  Implements Lindenmayer system, output in Matlab format
  Jöran Roslund, 1991-2021
  This is a c++11 version of an original Turbo Pascal program

  File format of data file: Dragon curve example with comments

 ----------------------------------
  4     # number of directions
  2     # number of production rules
  X     # input of first rule
  X+YF+ # output of first rule
  Y     # input of second rule
  -FX-Y # output of second rule
  X     # axiom
  ---------------------------------

  Vocab:

  F: Draw one step forward
  f: Move one step forward
  +: Turn right by angular quantum (360 degrees/number of directions)
  -: Turn left by angular quantum
  |: Turn back
  [: Save turtle state on stack (push)
  ]: Pop turtle stack

***************************************************************************/

#include <string>
#include <stack>
#include <map>
#include <fstream>
#include <cmath>
#include <iostream>
#include <sstream>

struct TurtleState {
  int dir;
  float x;
  float y;
};

// Definitions
std::map<char, std::string> rules;
int turtleDirN; // Number of directions

// Context
TurtleState turtle; // Current turtle state
std::stack<TurtleState> turtleStack; // Stack of turtle states


void initializeIt(std::string & axiom, const char* filename)
{
  std::ifstream data(filename);
  data >> turtleDirN;
  turtle.dir = 0;
  turtle.x = 0.0;
  turtle.y = 0,0;
  int numberOfRules;
  data >> numberOfRules;

  char symbol;
  std::string rule;
  for (int i=0; i<numberOfRules; ++i)
  {
    data >> symbol;
    data >> rule;
    rules.insert({symbol, rule});
  }
  data >> axiom;
  data.close();
}

void controlTurtle(const std::string command_string)
{
  // Convenient stuff, to avoid trigonometric calcs in every step
  // (Original version from 1991 was run on an IBM 286 ...)
  const int maxDir = 20; // Highest number of directions we can handle
  float CO[maxDir]; // LUT of direction cosines
  float SI[maxDir]; // LUT of direction sines

  const float pi = 3.141592654;
  for (int i=0; i<turtleDirN; ++i)
  {
    CO[i] = cos(2*pi*i/turtleDirN);
    SI[i] = sin(2*pi*i/turtleDirN);
  }

  const float scale = 1.0;
  for (char const &command: command_string)
  {
    float oldX;
    float oldY;

    switch (command)
    {
    case 'F':
    case 'f':
      oldX = turtle.x;
      oldY = turtle.y;
      turtle.x += CO[turtle.dir]*scale;
      turtle.y += SI[turtle.dir]*scale;
      if (command == 'F')
	{
	  std::cout << "line([" << oldX << " " << turtle.x << "],[" << oldY <<
	    " " << turtle.y << "])" << std::endl;
	}
      break;

    case '+':
      turtle.dir = (turtle.dir-1 + turtleDirN) % turtleDirN;
      break;

    case '-':
      turtle.dir = (turtle.dir+1) % turtleDirN;
      break;

    case '|':
      turtle.dir = (turtle.dir + turtleDirN/2) % turtleDirN;
      break;

    case '[':
      turtleStack.push(turtle);
      break;

    case ']':
      turtle = turtleStack.top();
      turtleStack.pop();
      break;
    }
  }
}

std::string convert(const std::string command_string, const int level)
{
  if (level == 1)
  {
    return command_string;
  }
  else
  {
    std::string output_string;
    std::stringstream ss;
  
    // Go through command string
    for (char const &command: command_string)
    {
      auto it = rules.find(command);
      if (it != rules.end()) // Conversion rule found
      {
	ss << it->second;
      }
      else // rule not found
      {
	ss << command;
      }
    }
    ss >> output_string;
    return convert(output_string, level-1);
  }
}

int main(int argc, char* argv[])
{
  std::string axiom; // Sic
  char* datafile(argv[1]);
  const int numberOfIterations = atoi(argv[2]);
  
  initializeIt(axiom, datafile);
  controlTurtle(convert(axiom, numberOfIterations));

  return 0;
}
