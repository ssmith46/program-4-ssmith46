/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 3, 2024
 *
 * File: BuyStockCommand.cpp
 * Purpose: Contains the implementation of the abstract 'BuyStockCommand' class.
*/
#include "Command.h"
#include "CommandFactory.h"
#include "BuyStockCommand.h"
#include "Market.h"
#include "Simulator.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/**
* The constructor for a Buy Stock Command object.
*
* @param args -> The arguments that lead to the mistake command.
* @param m -> The market that the command can influence.
* @param s -> The simulator that the command can influence.
*/
BuyStockCommand::BuyStockCommand(vector<string> args, Market* m, Simulator* s, CommandFactory *cf) {
    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}

/**
* This method overrides the base Command class's execute method.
*/
void BuyStockCommand::execute() {
    /*args[0] should be 'buy' or 'purchase' at this point.*/
    /*args[1] should be 'stock' or 'stocks' at this point.*/

    /*User can enter c or cancel in order to cancel the command at any point*/
    /*Need to get a line of input for which stock the user wants to buy*/

    /*Create a variable for the line of input from the user.*/
    string line;
    /*Indicate to user where to type.*/
    cout << "> ";
    /*Get a line of input from the user.*/
    getline(cin, line);

    vector<string> parts = this->cf->parseLine(line);
}