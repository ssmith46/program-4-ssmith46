/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 6, 2024
 *
 * File: ListStocksCommand.cpp
 * Purpose: Contains the implementation of the abstract 'ListStocksCommand' class.
*/
#include "Command.h"
#include "CommandFactory.h"
#include "ListStocksCommand.h"
#include "Market.h"
#include "Simulator.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

/**
* The constructor for a List Stocks Command object.
*
* @param args -> The arguments that lead to the mistake command.
* @param m -> The market that the command can influence.
* @param s -> The simulator that the command can influence.
*/
ListStocksCommand::ListStocksCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf) {
    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}
/**
 * This method overrides the base Command class's execute method.
 */
void ListStocksCommand::execute() {
    cout << endl;
    cout << this->m->stocks_toString();
}
