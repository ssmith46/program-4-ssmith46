/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 7, 2024
 *
 * File: WithdrawCommand.cpp
 * Purpose: Contains the implementation of the 'WithdrawCommand' class.
*/
#include "Command.h"
#include "CommandFactory.h"
#include "WithdrawCommand.h"
#include "Market.h"
#include "Simulator.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

/**
* The constructor for a Withdraw Command object.
*
* @param args -> The arguments that lead to the command being created.
* @param m -> The market that the command can influence.
* @param s -> The simulator that the command can influence.
*/
WithdrawCommand::WithdrawCommand(vector<string> args, Market* m, 
    Simulator* s, CommandFactory* cf) {
    /*Assign arguments to data members of object*/
    
    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}
/**
 * This method overrides the base Command class's execute method.
 * In this case, this method prompts the user for an amount they would
 * like to withdraw from their account balance, and updates their trader's
 * account accordingly.
 */
void WithdrawCommand::execute() {
    /*A string that will be used for reading user input*/
    string line;
    /*A vector that will be used to parse the user input for words*/
    vector<string> allParts;
    /*Keep looping until the withdraw is made successfully, or the user cancels*/
    while (1) {
        /*Prompt the user for input*/
        cout << endl;
        cout << "How much money would you like to withdraw?" << endl;
        cout << "> ";
        /*Get the user input*/
        getline(cin, line);
        /*Parse the user input for words*/
        allParts = this->cf->parseLine(line);

        /*Check and indicate if the user enters no words*/
        if (allParts.size() == 0) {
            cout << "Hmm, you didn't enter any amount. Please try again." << endl;
        }
        /*Check and indicate if the user cancels the transaction*/
        else if (Command::isCancel(allParts.at(0)) == true) {
            cout << endl;
            cout << "Canceling withdraw." << endl;
            return;
        }
        /*Check and indicate if user gives too many/few arguments in input*/
        else if (allParts.size() != 1) {
            cout << "Please enter one valid number to withdraw.";
            cout << endl;
        }
        else {
            try {
                /*Get the string of the user input*/
                string amount = allParts.at(0);

                /*Check the input for a "$" symbol and trim if applicable*/
                if (amount.substr(0, 1).compare("$") == 0) {
                    amount = amount.substr(1, amount.length() - 1);
                }
                
                /*Attempt to convert the user input into a double*/
                double inputNum = stod(amount);

                /*Check and indicate if the user enetered a negative value*/
                if (inputNum < 0) {
                    cout << endl;
                    cout << "For negative numbers, try making a deposit instead.";
                }
                /*Check and indicate if the user entered a value less than a penny.*/
                else if (round(inputNum / 0.01) * 0.01 < .01) {
                    cout << endl;
                    cout << "Please ensure that your withdraw is at least one penny.";
                }
                /*Check and indicate if the user entered zero*/
                else if (inputNum == 0) {
                    cout << endl;
                    cout << "Why? .....Just..... why? Sure I guess." << endl;
                    return;
                }
                else {
                    /*Create a string stream for getting the correct number of decimal places*/
                    stringstream ss;

                    /*Get a pointer to the logged in trader of the simulator*/
                    Trader* t;
                    t = this->s->getLoggedInTrader();

                    /*Round their input to the nearest penny*/
                    inputNum = round(inputNum / 0.01) * 0.01;

                    /*Calculate the new total the trader will have in their account after 
                      the withdraw*/
                    double newTot = t->getBalance() - inputNum;
                    
                    /*Handles the case the user enters a valid amount to withdraw*/
                    if (((newTot < 0) && (newTot > -0.001)) || (newTot >= 0)) {
                        /*Indicate that withdraw process has begun*/
                        cout << endl;
                        cout << "Making withdraw... ";
                        /*Set the precision of the withdraw amount*/
                        ss << fixed << setprecision(2) << newTot;
                        ss >> inputNum;
                        /*Update the account balance of the logged in trader*/
                        this->s->getLoggedInTrader()->setBalance(newTot);
                        /*Indicate that the transaction was completed successfully*/
                        cout << "Complete!";
                        cout << endl;
                        cout << "Your new account balance is: $";
                        cout << fixed << setprecision(2) << t->getBalance();
                        cout << endl;
                        return;
                    }
                    /*Indicate that the user is attempting to withdraw more money than they have*/
                    else {
                        cout << endl;
                        cout << "You only have $" << fixed << setprecision(2);
                        cout << t->getBalance() << " in your account." << endl;
                        cout << "Please enter a a value less than or equal to this.";
                    }
                }
            }
            /*Catch exception and indicate if the user entered a non-double-parseable amount
              to withdraw*/
            catch (...) {
                cout << endl;
                cout << "Please enter a valid amount to withdraw.";
            }
        }
    }
}