/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 6, 2024
 *
 * File: LogoutCommand.cpp
 * Purpose: Contains the implementation of the abstract 'LogoutCommand' class.
*/
#include "Command.h"
#include "CommandFactory.h"
#include "LogoutCommand.h"
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
LogoutCommand::LogoutCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf) {
    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}
/**
 * This method overrides the base Command class's execute method.
 */
void LogoutCommand::execute() {
    this->s->loginScreen();
    cout << endl;
    cout << "Login Successful, you are logged in as: " << s->getLoggedInTrader()->getName();
    cout << "." << endl;
}