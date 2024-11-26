/*
Project: Stock Simulator C++ Final Project
Author: Sullivan Smith
Date: November 26, 2024

File: Command.h
Purpose: Contains the declaration of the abstract 'Command' class.
*/

#ifndef Command_H
#define Command_H

#include <string>
#include <sstream>
#include "Market.h"
#include "Simulator.h"

using namespace std;
/*
Purpose:
- Manipulate the state of the Stock Simulation based on input provided by the user.
- This is the base class that will be inherited by more specific commands,
  such as "BuyStockCommand".

Data Members:
- Simulator s -> The simulator that the command will be able to manipulate.
- Market m -> The market that the command will be able to manipulate.

- Having access to these two data members will allow the command to change 
  anything about the Simulation.

Member Functions:
- Command(string type, vector<string> args, Market m, Simulator s)
    -> The constructor for the command object. 
- execute() -> A void abstract method that is overidden by child commands

Class Usage:
- This class is used to manipulate the simulation based off of
  user entered strings to specify arguments. 
*/
class Command {
    public:
        /*Constructor*/
        Command(string type, vector<string> args, Market m, Simulator s);
        void execute();
    private:
        Simulator s;
        Market m;
};
#endif
