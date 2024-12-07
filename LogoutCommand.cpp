/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 6, 2024
 *
 * File: LogoutCommand.cpp
 * Purpose: Contains the implementation of the 'LogoutCommand' class.
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
* The constructor for a Logout Command object.
*
* @param args -> The arguments that lead to the creation of this command.
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
 * In this case, this method simply calls the simulator's "login"
 * method which replaces the currently logged in trader of the simulation.
 */
void LogoutCommand::execute() {
    /*Call the simulator's login method*/
    this->s->loginScreen();
    /*Indicate the the login was successful*/
    cout << endl;
    cout << "Login Successful, you are logged in as: " << s->getLoggedInTrader()->getName();
    cout << "." << endl;
}