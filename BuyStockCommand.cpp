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
#include <cstdlib>

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

    /*Get the string name of the stock the user would like to buy*/
    string strStockToBuy = this->whichStock();

    /*Handle the case that the user entered a cancel during the buying of the stock*/
    if (strStockToBuy.compare(";;;") == 0) {
        return;
    }
    /*Get the number of shares of that stock the user wants to buy*/
    int numSharesToBuy = this->howMany(strStockToBuy);

    /*Handles the case the user canceled*/
    if (numSharesToBuy == -1) {
        return;
    }

    cout << "Fin. Buying " << numSharesToBuy << " shares of " << strStockToBuy << " stock." << endl;

    
}

/**
* Get the name of the stock the user would like to purchase.
*
* @return -> A string for the stock the user would like to purchase.
*/
string BuyStockCommand::whichStock() {

    /*The string to return to the client code.*/
    string retVal = "";

    /*Create a variable for the line of input from the user.*/
    string line;
    /*Parse the line for the stock that the user would like buy*/
    vector<string> parts;

    while (1) {
        cout << endl;
        cout << "Which stock would you like to buy shares of? ('l' to list options)";
        cout << endl;
        /*Indicate to user where to type.*/
        cout << "> ";
        /*Get a line of input from the user.*/
        getline(cin, line);
        parts = this->cf->parseLine(line);

        while (parts.size() != 1) {

            cout << endl;
            cout << "A stock's symbol should be only one word long. ";
            cout << "Please try again." << endl;
            cout << "Which stock would you like to buy shares of? ('l' to list options)";
            cout << endl;

            /*Indicate to user where to type.*/
            cout << "> ";
            /*Get a line of input from the user.*/
            getline(cin, line);

            parts = this->cf->parseLine(line);
        }

        /*Check if the user changed their mind and would like to cancel*/
        if (Command::isCancel(parts.at(0))) {
            cout << endl;
            cout << "Transaction canceled." << endl;
            return ";;;";
        }

        Stock* s = this->m->getStock(parts.at(0));
        if (s == nullptr) {
            cout << endl;
            cout << "That doesn't seem to be a valid stock name. Please try again.";
        }
        else {
            return parts.at(0);
        }
    }
}

/**
* Get the number of shares of a stock the user would like to purchase.
*
* @return -> An int for the number of shares the user would like to purchase.
*/
int BuyStockCommand::howMany(string stockName) {
    /*The number of shares of that stock to buy*/
    int retVal = 0;

    /*Create a variable for the line of input from the user.*/
    string line;
    /*Parse the line for the stock that the user would like buy*/
    vector<string> parts;

    while (1) {
        cout << endl;
        cout << "How many shares of " << stockName << " stock would you like to buy?";
        cout << endl;
        /*Indicate to user where to type.*/
        cout << "> ";
        /*Get a line of input from the user.*/
        getline(cin, line);
        parts = this->cf->parseLine(line);
        while (parts.size() != 1) {
            cout << endl;
            cout << "There should only be one argument for the number of stocks to buy. ";
            cout << "Please try again." << endl;

            /*Indicate to user where to type.*/
            cout << "> ";
            /*Get a line of input from the user.*/
            getline(cin, line);

            parts = this->cf->parseLine(line);
        }
        /*Check if the user changed their mind and would like to cancel*/
        if (isCancel(parts.at(0))) {
            cout << endl;
            cout << "Transaction canceled." << endl;
            return -1;
        }

        try {
            int numToBuy = stoi(parts.at(0));
            if (numToBuy == 0) {
                cout << endl;
                cout << "I mean sure. I guess you can buy none. Waste of both our times. ";
                cout << endl;
                return -1;
            }
            else if (numToBuy < 0) {
                cout << endl;
                cout << "The number of stocks to buy has to be a positive number. ";
                cout << "Please try again.";
            }
            else {
                /*Need to check that there are that many shares or more left for purchase*/
                int numSharesLeft = this->m->getStock(stockName)->getShares();
                if (numSharesLeft < numToBuy) {
                    cout << endl;
                    cout << "There are only " << numSharesLeft << " shares left. " << endl;
                    cout << "Please pick a number less than or equal to this total.";
                }
                else {
                    return numToBuy;
                }
            }
        }
        catch (const invalid_argument& e) {
            cout << endl;
            cout << "That doesn't seem to be a valid number of shares to buy." << endl;
            cout << "Please enter a valid integer value. ";
        }
        catch (const out_of_range& e) {
            cout << endl;
            cout << "That value seems to be too big. Please try a smaller one.";
        }
     
    }
}