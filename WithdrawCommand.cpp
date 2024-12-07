/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 7, 2024
 *
 * File: WithdrawCommand.cpp
 * Purpose: Contains the implementation of the abstract 'WithdrawCommand' class.
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
* The constructor for a List Stocks Command object.
*
* @param args -> The arguments that lead to the mistake command.
* @param m -> The market that the command can influence.
* @param s -> The simulator that the command can influence.
*/
WithdrawCommand::WithdrawCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf) {
    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}
/**
 * This method overrides the base Command class's execute method.
 */
void WithdrawCommand::execute() {

    string line;
    vector<string> allParts;
    while (1) {
        cout << endl;
        cout << "How much money would you like to withdraw?" << endl;
        cout << "> ";
        getline(cin, line);
        allParts = this->cf->parseLine(line);

        if (allParts.size() == 0) {
            cout << "Hmm, you didn't enter any amount. Please try again." << endl;
        }
        else if (Command::isCancel(allParts.at(0)) == true) {
            cout << endl;
            cout << "Canceling withdraw." << endl;
            return;
        }
        else if (allParts.size() != 1) {
            cout << "Please enter one valid number to withdraw.";
            cout << endl;
        }
        else {
            try {
                string amount = allParts.at(0);
                if (amount.substr(0, 1).compare("$") == 0) {
                    amount = amount.substr(1, amount.length() - 1);
                }
                double inputNum = stod(amount);

                if (inputNum < 0) {
                    cout << endl;
                    cout << "For negative numbers, try making a deposit instead.";
                }
                else if (round(inputNum / 0.01) * 0.01 < .01) {
                    cout << endl;
                    cout << "Please ensure that your withdraw is at least one penny.";
                }
                else if (inputNum == 0) {
                    cout << "Why? .....Just..... why? Sure I guess." << endl;
                    return;
                }
                else if (inputNum > 100000) {
                    cout << "Please enter an amount less than one hundred thousand dollars.";
                    cout << " (We get charged crazy fees otherwise).";
                    cout << endl;
                }
                else {
                    stringstream ss;
                    Trader* t;
                    t = this->s->getLoggedInTrader();
                    inputNum = round(inputNum / 0.01) * 0.01;

                    double newTot = t->getBalance() - inputNum;
                    
                    if (((newTot < 0) && (newTot > -0.001)) || (newTot >= 0)) {
                        cout << endl;
                        cout << "Making withdraw... ";
                        ss << fixed << setprecision(2) << newTot;
                        ss >> inputNum;
                        this->s->getLoggedInTrader()->setBalance(newTot);
                        cout << "Complete!";
                        cout << endl;
                        cout << "Your new account balance is: $";
                        cout << fixed << setprecision(2) << t->getBalance();
                        cout << endl;
                        return;
                    }
                    else {
                        cout << endl;
                        cout << "You only have $" << fixed << setprecision(2);
                        cout << t->getBalance() << " in your account." << endl;
                        cout << "Please enter a a value less than or equal to this.";
                    }
                }
            }
            catch (...) {
                cout << endl;
                cout << "Please enter a valid amount to deposit." << endl;
            }
        }
    }
}