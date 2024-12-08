/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 6, 2024
 *
 * File: ListPortfolioCommand.cpp
 * Purpose: Contains the implementation of the 'ListPortfolioCommand' class.
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
* The constructor for a List Portfolio Command object.
*
* @param args -> The arguments that lead to the creation of the command.
* @param m -> The market that the command can influence.
* @param s -> The simulator that the command can influence.
*/
ListPortfolioCommand::ListPortfolioCommand(vector<string> args, Market* m,
    Simulator* s, CommandFactory* cf) {
    /*Assign arguments to data members of the object*/

    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}
/**
 * This method overrides the base Command class's execute method.
 * In this case, this method displays the account balance of the logged in trader
 * as well as displaying all the stocks they currently have in their portfolio.
 */
void ListPortfolioCommand::execute() {
    /*Display the account balance of the logged in trader*/
    cout << endl;
    cout << "Current Account Balance: $" << fixed << setprecision(2);
    cout << this->s->getLoggedInTrader()->getBalance();

    cout << this->s->getLoggedInTrader()->getName() << endl;

    /*Display the stocks in the logged in trader's portfolio*/
    cout << endl;
    cout << this->s->getLoggedInTrader()->listPortfolio();
}