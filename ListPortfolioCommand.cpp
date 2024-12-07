/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 6, 2024
 *
 * File: ListPortfolioCommand.cpp
 * Purpose: Contains the implementation of the abstract 'ListPortfolioCommand' class.
*/
#include "Command.h"
#include "CommandFactory.h"
#include "ListPortfolioCommand.h"
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
ListPortfolioCommand::ListPortfolioCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf) {
    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}
/**
 * This method overrides the base Command class's execute method.
 */
void ListPortfolioCommand::execute() {
    cout << endl;
    cout << "Current Account Balance: $" << fixed << setprecision(2) << this->s->getLoggedInTrader()->getBalance();
    cout << endl;
    cout << this->s->getLoggedInTrader()->getPortfolio()->stocks_toString();
}