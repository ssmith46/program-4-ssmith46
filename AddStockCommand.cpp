/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 7, 2024
 *
 * File: SellStockCommand.cpp
 * Purpose: Contains the implementation of the abstract 'SellStockCommand' class.
*/
#include "Command.h"
#include "CommandFactory.h"
#include "AddStockCommand.h"
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
* The constructor for a Add Stock Command object.
*
* @param args -> The arguments that lead to the mistake command.
* @param m -> The market that the command can influence.
* @param s -> The simulator that the command can influence.
*/
AddStockCommand::AddStockCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf) {
    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}

/**
* This method overrides the base Command class's execute method.
*/
void AddStockCommand::execute() {
    /*First get the name of the stock that would like to created*/

    /*Check if that stock already exists*/

    /*Figure out how many shares would like to be added*/

    /*Figure out current price*/

    /*Create stock and add it to the market*/

    /*Give confirmation that stock was added*/

}