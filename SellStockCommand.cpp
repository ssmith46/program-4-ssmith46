/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 7, 2024
 *
 * File: SellStockCommand.cpp
 * Purpose: Contains the implementation of the 'SellStockCommand' class.
*/
#include "Command.h"
#include "CommandFactory.h"
#include "SellStockCommand.h"
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
* The constructor for a Sell Stock Command object.
*
* @param args -> The arguments that lead to the sell stock command.
* @param m -> The market that the command can influence.
* @param s -> The simulator that the command can influence.
*/
SellStockCommand::SellStockCommand(vector<string> args, Market* m, 
    Simulator* s, CommandFactory* cf) {
    /*Assign arguments to data members of object*/

    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}

/**
* This method overrides the base Command class's execute method.
* In this case, this method allows the user to specify which stock they would
* like to buy, and updates their portfolio and account balance to reflect this purchase
*/
void SellStockCommand::execute() {
    /*The prompt that will be used to get user input for the stock symbol to sell*/
    string stockNamePrompt = "Which stock would you like to sell shares of? ";
    stockNamePrompt += "('l' to list stock options)";

    /*Get a command object for method usage*/
    Command c = cf->getBaseCommand();

    /*A variable for understanding how many shares of that stock are own*/
    int numSharesOwn = 0;

    /*Get a pointer to the logged in trader*/
    Trader* t = this->s->getLoggedInTrader();

    /*A string for the stock symbol of the stock to sell*/
    string strStockToSell;

    /*Keep looping until the number of shares own is not 0, or the user cancels*/
    while (numSharesOwn == 0) {

        /*Get the string name of the stock the user would like to buy*/
        strStockToSell = c.whichStock(stockNamePrompt, "sell");

        /*Handle the case that the user entered a cancel during the selling of the stock*/
        if (strStockToSell.compare(";;;") == 0) {
            return;
        }

        /*Now have the name of the stock wanting to sell, but need to ensure that the
        * user actually owns some of that stock before continuing.
        */

        /*Calculate the number of shares of that stock the user owns*/
        numSharesOwn = t->getPortfolio()->howMuchStockOwned(strStockToSell);

        /*Check if that number is zero, and indicate this if so*/
        if (numSharesOwn == 0) {
            cout << endl;
            cout << "It seems you don't own any shares of " << strStockToSell;
            cout << "." << endl;
            cout << "Try a choosing a different stock symbol.";
        }

    }

    /*Create a prompt for finding the number of shares the user would like to sell*/
    string numSharesToSellPrompt = "";
    numSharesToSellPrompt += "How many shares of " + strStockToSell + " would you like to sell?";

    /*Set the number of shares to sell to -3 (-1 taken)*/
    int numSharesToSell = -3;
    /*Keep looping until the */
    while ((numSharesToSell == -3) || (numSharesToSell > numSharesOwn)) {
        /*Get the number of shares of that stock the user wants to sell*/
        numSharesToSell = c.howManyShares(strStockToSell, numSharesToSellPrompt, "sell");

        /*Handles the case the user canceled*/
        if (numSharesToSell == -1) {
            return;
        }
        /*Handle if the user tries to sell more shares than they own.*/
        else if (numSharesToSell > numSharesOwn) {
            /*Use the correct word "share" vs "shares" in output message.*/
            string correct = "share";
            if (numSharesOwn > 1) {
                correct += "s";
            }
            /*Indicate to the user that they don't own that number of stocks.*/
            cout << endl;
            cout << "You only have " << numSharesOwn << " " << correct;
            cout << " of " << strStockToSell << " stock.";
            cout << endl;
            cout << "Please pick a number less than or equal to this.";
        }
    }
    
    /*Get the account balance of the logged in trader*/
    double accountBalance = t->getBalance();
    /*Get the stock pointer of the stock trying to sell*/
    Stock* s = this->m->getStock(strStockToSell);
    /*Get the stock price of the stock selling*/
    double stockPrice = s->getPrice();

    /*Create a string stream for formatting the doubles*/
    stringstream ss;

    /*Get the total value and account balances to two decimal places*/

    double totalVal = (stockPrice * numSharesToSell) + 0.00000001;
    ss << fixed << setprecision(2) << totalVal;
    ss >> totalVal;
    ss.str("");
    ss << fixed << setprecision(2) << accountBalance;
    ss >> accountBalance;

    /*Get the correct notation for "share" vs "shares"*/
    string correctNotation = "share";
    if (numSharesToSell > 1) {
        correctNotation += "s";
    }
    /*If selling none, then return*/
    else if (numSharesToSell == 0) {
        return;
    }

    /*Double check that they are ok selling those stocks before continuing*/
    cout << endl;
    cout << "You are about to sell " << numSharesToSell << " " << correctNotation;
    cout << " of " << strStockToSell << " stock." << endl;
    
    /*Create a string for getting input*/
    string line;
    /*Create a variable for the args in the user input*/
    vector<string> allParts;

    /*Keep looping until stocks are sold or the user cancels*/
    while (1) {
        /*Prompt the user for confirmation before selling stocks*/
        cout << "Are you sure you want to continue? [y, n]" << endl;
        cout << "> ";
        /*Get user input*/
        getline(cin, line);
        /*Parse user input for arguments*/
        allParts = this->cf->parseLine(line);
        /*Indicate that the incorrect number of arguments were given*/
        if (allParts.size() != 1) {
            cout << endl;
            cout << "Please enter just one word for confirmation." << endl;
        }
        else {
            /*Get the answer of the user*/
            string ans = allParts.at(0);
            /*Handles the case that they do want to sell the stocks*/
            if (
                (ans.compare("y") == 0) ||
                (ans.compare("Y") == 0) ||
                (ans.compare("Yes") == 0) ||
                (ans.compare("yes") == 0)
                ) {
                /*Indicate that stocks are being sold*/
                cout << endl;
                cout << "Confirmed. Selling shares... ";

                /*Update the trader's account balance*/
                double newTotal = accountBalance + totalVal;
                t->setBalance(newTotal);
                /*Update their stock portfolio to have less shares*/
                t->getPortfolio()->sellStock(strStockToSell, numSharesToSell);
                /*Update the number of shares available for that stock*/
                this->m->getStock(strStockToSell)->addShares(numSharesToSell);
                /*Indicate that the shares have been sold successfully and exit*/
                cout << "Shares have been sold!" << endl;
                cout << "Your new account balance is: $";
                cout << fixed << setprecision(2) << t->getBalance();
                cout << endl;
                return;
            }
            /*Handles the case that the user doesn't want to sell the shares anymore*/
            else if (
                (ans.compare("n") == 0) ||
                (ans.compare("N") == 0) ||
                (ans.compare("No") == 0) ||
                (ans.compare("no") == 0) ||
                (Command::isCancel(ans))
                ) {
                /*Indicate that the transaction has been cancelled and return*/
                cout << endl;
                cout << "Understood. Selling stocks is a big deal." << endl;
                cout << "If you change your mind, you can always come back!";
                cout << endl;
                return;
            }
            /*Handles the case that the user input wasn't understood*/
            else {
                cout << endl;
                cout << "Hmm, I'm not sure I understand that. Please try again.";
                cout << endl;
            }
        }
    }
}