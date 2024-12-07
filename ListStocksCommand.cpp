/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 6, 2024
 *
 * File: ListStocksCommand.cpp
 * Purpose: Contains the implementation of the 'ListStocksCommand' class.
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
* @param args -> The arguments that lead to the creation of this command.
* @param m -> The market that the command can influence.
* @param s -> The simulator that the command can influence.
*/
ListStocksCommand::ListStocksCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf) {
    /*Assign arguments to data members of object*/

    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}
/**
 * This method overrides the base Command class's execute method.
 * In this case, this method displays a table of the attributes
 * of all the stocks currently on the market.
 */
void ListStocksCommand::execute() {
    /*Get the string of the stocks in the market and print it*/
    cout << endl;
    cout << this->m->stocks_toString();
}
