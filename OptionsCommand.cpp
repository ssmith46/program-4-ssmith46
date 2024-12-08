/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 7, 2024
 *
 * File: OptionsCommand.cpp
 * Purpose: Contains the implementation of the 'OptionsCommand' class.
*/
#include "Command.h"
#include "CommandFactory.h"
#include "OptionsCommand.h"
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
* The constructor for an Options Stock Command object.
*
* @param args -> The arguments that lead to the options command.
* @param m -> The market that the command can influence.
* @param s -> The simulator that the command can influence.
*/
OptionsCommand::OptionsCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf) {
    /*Assign arguments to data members of object*/

    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}

/**
* This method overrides the base Command class's execute method.
* In this case, all the available commands supported by the simulation are given
*/
void OptionsCommand::execute() {
    /*Print out all the commands currently supported by the simulation*/
    cout << endl;
    cout << "'see portfolio' -> See your account balance and stock shares.";
    cout << endl;
    cout << "'see stocks' -> See all available stocks on the market.";
    cout << endl;
    cout << "'buy stock' -> Buy stocks and add them to your portfolio.";
    cout << endl;
    cout << "'sell stock' -> Sell shares of stocks in your portfolio.";
    cout << endl;
    cout << "'deposit' -> Add money to your account balance.";
    cout << endl;
    cout << "'withdraw' -> Take money out of your account balance.";
    cout << endl;
    cout << "'fluctuate stocks' -> Randomly fluctuate stock prices.";
    cout << endl;
    cout << "'add stock' -> Create a new stock for the market.";
    cout << endl;
    cout << "'set seed' -> Change the random/violent seed for price fluctuation.";
    cout << endl;
    cout << "'logout' -> Logout from the current trader profile.";
    cout << endl;
    cout << "'exit' -> End the program.";
    cout << endl;
    cout << "'options' -> View the options for available actions. (Obviously)";
    cout << endl;
}