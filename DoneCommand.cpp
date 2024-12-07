/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 7, 2024
 *
 * File: DoneCommand.cpp
 * Purpose: Contains the implementation of the 'DoneCommand' class.
*/
#include "Command.h"
#include "CommandFactory.h"
#include "DoneCommand.h"
#include "Market.h"
#include "Simulator.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

using namespace std;

/**
* The constructor for a Done Command object.
*
* @param args -> The arguments that lead to the creation of the done command.
* @param m -> The market that the command can influence.
* @param s -> The simulator that the command can influence.
*/
DoneCommand::DoneCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf) {
    /*Assign data members based on arguments*/

    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}

/**
* This method overrides the base Command class's execute method.
* In this case, it simply changes the state of the simulator's 'running'
* bool to false, to end the simulation.
*/
void DoneCommand::execute() {
    /*Turn the simulator's running to false*/
    this->s->setRunning(false);
}