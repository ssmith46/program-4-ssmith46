/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 7, 2024
 *
 * File: AddStockCommand.cpp
 * Purpose: Contains the implementation of the abstract 'AddStockCommand' class.
*/
#include "Command.h"
#include "CommandFactory.h"
#include "AddStockCommand.h"
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
* The constructor for a Add Stock Command object.
*
* @param args -> The arguments that lead to the mistake command.
* @param m -> The market that the command can influence.
* @param s -> The simulator that the command can influence.
*/
AddStockCommand::AddStockCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf) {
    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}

/**
* This method overrides the base Command class's execute method.
*/
void AddStockCommand::execute() {

    string strStockSymbol = "";
    double currPrice = -1.0;
    int numShares = -1;

    /*First get the name of the stock that would like to created*/
    string line;
    vector<string> allParts;

    cout << endl;
    while (strStockSymbol.compare("") == 0) {
        cout << "What would you like the symbol of this stock to be?" << endl;
        cout << "> ";
        getline(cin, line);
        allParts = this->cf->parseLine(line);
        if (allParts.size() == 0) {
            cout << endl;
            cout << "Your stock symbol must be at least one character long.";
            cout << endl;
        }
        else if (allParts.size() > 1) {
            cout << endl;
            cout << "Please ensure the stock symbol is only one word long. (no spaces)";
            cout << endl;
        }
        else if (Command::isCancel(allParts.at(0))) {
            cout << endl;
            cout << "Canceling stock creation.";
            cout << endl;
            return;
        }
        else {
            
            /*Check if that stock already exists*/
            if (this->m->getStock(allParts.at(0)) == nullptr) {
                /*This means the stock doesn't exist*/
                strStockSymbol = allParts.at(0);
            }
            else {
                cout << endl;
                cout << "It seems that a stock already exists with that symbol.";
                cout << "Please try a different stock symbol.";
                cout << endl;
            }
        } 
    }

    cout << endl;

    /*Figure out how many shares would like to be added*/
    while (numShares == -1) {
        cout << "How many shares would you like for the ";
        cout << strStockSymbol << " stock to have?" << endl;
        cout << "> ";
        getline(cin, line);
        allParts = this->cf->parseLine(line);
        if (allParts.size() != 1) {
            cout << endl;
            cout << "Please ensure you enter one number." << endl;
        }
        else if (Command::isCancel(allParts.at(0))) {
            cout << endl;
            cout << "Canceling stock creation.";
            cout << endl;
            return;
        }
        else {
            try {
                int trialNum = stoi(allParts.at(0));
                if (trialNum < 0) {
                    cout << endl;
                    cout << "The number of shares must be a positive value." << endl;
                }
                else if (trialNum > 99999999) {
                    cout << endl;
                    cout << "Please ensure the number of shares is less than 1 billion.";
                    cout << endl;
                }
                else {
                    numShares = trialNum;
                }
            }
            catch (...) {
                cout << endl;
                cout << "Please enter a valid integer for the number of shares.";
                cout << endl;
                
            }
        }

    }
     

    /*Figure out current price*/
    while (currPrice < 0) {
        cout << "What would you like the starting price of ";
        cout << strStockSymbol << " stock to be?" << endl;
        cout << "> ";
        getline(cin, line);
        allParts = this->cf->parseLine(line);
        if (allParts.size() == 0) {
            cout << endl;
            cout << "Please enter at least one number for the price of the stock.";
            cout << endl;
        }
        else if (allParts.size() > 1) {
            cout << endl;
            cout << "Please enter only one number for the price of the stock.";
            cout << endl;
        }
        else if (Command::isCancel(allParts.at(0))) {
            cout << endl;
            cout << "Canceling stock creation.";
            cout << endl;
            return;
        }
        else {
            try {
                string strPrice = allParts.at(0);
                if (strPrice.substr(0, 1).compare("$") == 0) {
                    strPrice = strPrice.substr(1, strPrice.length() - 1);
                }
                double entered = stod(strPrice);
                if (round(entered / 0.01) * 0.01 < .01) {
                    cout << endl;
                    cout << "Please start the price at at least one penny.";
                    cout << endl;
                }
                else {
                    currPrice = entered;
                }
            }
            catch (...) {
                cout << endl;
                cout << "Please enter a valid decimal value for the price of the stock.";
                cout << endl;
            }
        }
    }


    cout << endl;
    cout << "Creating stock... ";

    Stock newStock(strStockSymbol, currPrice, numShares);
    this->m->addStock(newStock);

    cout << "Stock created!" << endl;

    return;

    /*Create stock and add it to the market*/

    /*Give confirmation that stock was added*/

}