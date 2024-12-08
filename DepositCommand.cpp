/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 6, 2024
 *
 * File: DepositCommand.cpp
 * Purpose: Contains the implementation of the 'DepositCommand' class.
*/
#include "Command.h"
#include "CommandFactory.h"
#include "DepositCommand.h"
#include "Market.h"
#include "Simulator.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

/**
* The constructor for a Deposit Stocks Command object.
*
* @param args -> The arguments that lead to the mistake command.
* @param m -> The market that the command can influence.
* @param s -> The simulator that the command can influence.
*/
DepositCommand::DepositCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf) {
    /*Set arguments to data members*/

    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}
/**
 * This method overrides the base Command class's execute method.
 * In this case, this method gets user input and update's the 
 * logged in trader's balance according to the depositted amount.
 */
void DepositCommand::execute() {
    /*Create a string for gettting user input*/
    string line;
    /*Create a vector for the parts of the user entered input*/
    vector<string> allParts;
    /*Keep looping until the user enters a valid amount to deposit*/
    while (1) {
        /*Prompt the user for input*/
        cout << endl;
        cout << "How much money would you like to deposit?" << endl;
        cout << "> ";
        /*Get a line of input from the user*/
        getline(cin, line);
        /*Parse the inputted line for the words*/
        allParts = this->cf->parseLine(line);
        /*Check and indicate if the user didn't enter any input*/
        if (allParts.size() == 0) {
            cout << "Hmm, you didn't enter any amount. Please try again." << endl;
        }
        /*Check and indicate if the user wants to cancel this transaction*/
        else if (Command::isCancel(allParts.at(0)) == true) {
            cout << endl;
            cout << "Canceling deposit." << endl;
            return;
        }
        /*Check and indicate if the user entered too many arguments*/
        else if (allParts.size() != 1) {
            cout << "Please enter one valid number to deposit.";
            cout << endl;
        }
        /*Handles the case that they only entered one argument*/
        else {
            try {
                /*Get the argument that the user entered*/
                string amount = allParts.at(0);
                /*Check and trim the '$' symbol if applicable*/
                if (amount.substr(0, 1).compare("$") == 0) {
                    amount = amount.substr(1, amount.length() - 1);
                }
                /*Attempt to convert the user input into a double for the amount depositing*/
                double inputNum = stod(amount);
                /*Check and indicate if the user entered a negative value*/
                if (inputNum < 0) {
                    cout << endl;
                    cout << "For negative numbers, try making a withdraw instead.";
                    cout << endl;
                }
                /*Check and indicate if the user didn't enter at least a penny*/
                else if (round(inputNum / 0.01) * 0.01 < .01) {
                    cout << endl;
                    cout << "Please ensure that your deposit is at least one penny.";
                    cout << endl;
                }
                /*Check and indicate if the user doesn't want to deposit anything*/
                else if (inputNum == 0) {
                    cout << "Why? .....Just..... why?" << endl;
                    return;
                }
                /*Check and indicate if the user is entering too much to deposit*/
                else if (inputNum >= 100000) {
                    cout << "Please enter an amount less than one hundred thousand dollars.";
                    cout << " (We get charged crazy fees otherwise).";
                    cout << endl;
                }
                else {
                    /*Create a string stream for formatting doubles*/
                    stringstream ss;

                    /*Create a pointer to a trader and get the logged in trader*/
                    Trader* t;
                    t = this->s->getLoggedInTrader();

                    /*Get the number the user inputted*/
                    inputNum = round(inputNum / 0.01) * 0.01;
                    /*Add the total balance that the user has in their account*/
                    inputNum += t->getBalance();

                    /*Get the new account balance to two decimal places only*/
                    ss << fixed << setprecision(2) << inputNum;
                    ss >> inputNum;

                    /*Set the logged in trader's balance to this new total*/
                    this->s->getLoggedInTrader()->setBalance(inputNum);
                    
                    /*Indicate to the user that the transaction was completed successfully*/
                    cout << endl;
                    cout << "The money has been deposited." << endl;
                    cout << "Your new balance is: $" << fixed << setprecision(2);
                    cout << inputNum << endl;
                    return;
                }
            }
            /*Catch exception if user didn't enter a validly parseable double*/
            /*Indicate to the user that it must be a valid amount to deposit*/
            catch (...) {
                cout << endl;
                cout << "Please enter a valid amount to deposit." << endl;
            }
        }
    }
}