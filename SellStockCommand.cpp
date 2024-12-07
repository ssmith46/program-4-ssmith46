/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 7, 2024
 *
 * File: SellStockCommand.cpp
 * Purpose: Contains the implementation of the abstract 'SellStockCommand' class.
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
* The constructor for a Buy Stock Command object.
*
* @param args -> The arguments that lead to the mistake command.
* @param m -> The market that the command can influence.
* @param s -> The simulator that the command can influence.
*/
SellStockCommand::SellStockCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf) {
    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}

/**
* This method overrides the base Command class's execute method.
*/
void SellStockCommand::execute() {
    string stockNamePrompt = "Which stock would you like to sell shares of? ";
    stockNamePrompt += "('l' to list stock options)";

    /*args[0] should be 'buy' or 'purchase' at this point.*/
    /*args[1] should be 'stock' or 'stocks' at this point.*/

    Command c = cf->getBaseCommand();

    bool ownSomeOfThatStock = false;
    int numSharesOwn = 0;

    Trader* t = this->s->getLoggedInTrader();

    string strStockToSell;

    while (numSharesOwn == 0) {
        /*Get the string name of the stock the user would like to buy*/
        strStockToSell = c.whichStock(stockNamePrompt, "sell");

        /*Handle the case that the user entered a cancel during the buying of the stock*/
        if (strStockToSell.compare(";;;") == 0) {
            return;
        }

        /*Now have the name of the stock wanting to sell, but need to ensure that the
        * user actually owns some of that stock before continuing.
        */

        numSharesOwn = t->getPortfolio()->howMuchStockOwned(strStockToSell);

        if (numSharesOwn == 0) {
            cout << endl;
            cout << "It seems you don't own any shares of " << strStockToSell;
            cout << "." << endl;
            cout << "Try a choosing a different stock symbol.";
        }

    }

    string numSharesToSellPrompt = "";
    numSharesToSellPrompt += "How many shares of " + strStockToSell + " would you like to sell?";
    int numSharesToSell = -3;
    while ((numSharesToSell == -3) || (numSharesToSell > numSharesOwn)) {
        /*Get the number of shares of that stock the user wants to sell*/
        numSharesToSell = c.howManyShares(strStockToSell, numSharesToSellPrompt);

        /*Handles the case the user canceled*/
        if (numSharesToSell == -1) {
            return;
        }
    }
    
    
    
    double accountBalance = t->getBalance();
    Stock* s = this->m->getStock(strStockToSell);
    double stockPrice = s->getPrice();

    stringstream ss;
    double totalVal = (stockPrice * numSharesToSell) + 0.00000001;
    ss << fixed << setprecision(2) << totalVal;
    ss >> totalVal;
    ss.str("");
    ss << fixed << setprecision(2) << accountBalance;
    ss >> accountBalance;

    string correctNotation = "share";
    if (numSharesToSell > 1) {
        correctNotation += "s";
    }
    else if (numSharesToSell == 0) {
        return;
    }
    /*Handles the case that they don't have enough money in their account.*/
    cout << endl;
    cout << "You are about to sell " << numSharesToSell << " " << correctNotation;
    cout << " of " << strStockToSell << " stock." << endl;
    
    string line;
    vector<string> allParts;

    while (1) {
        cout << "Are you sure you want to continue? [y, n]" << endl;
        cout << "> ";
        getline(cin, line);
        allParts = this->cf->parseLine(line);

        if (allParts.size() != 1) {
            cout << endl;
            cout << "Please enter just one word for confirmation." << endl;
        }
        else {
            string ans = allParts.at(0);
            if (
                (ans.compare("y") == 0) ||
                (ans.compare("Y") == 0) ||
                (ans.compare("Yes") == 0) ||
                (ans.compare("yes") == 0)
                ) {
                cout << endl;
                cout << "Confirmed. Selling shares... ";
                /*Do the stuff to sell the shares here*/

                /*Update the trader's account balance*/
                double newTotal = accountBalance + totalVal;
                t->setBalance(newTotal);
                /*Update their stock portfolio to have less shares*/
                t->getPortfolio()->sellStock(strStockToSell, numSharesToSell);
                /*Update the number of shares available for that stock*/
                this->m->getStock(strStockToSell)->addShares(numSharesToSell);
                cout << "Shares have been sold!" << endl;
                cout << "Your new account balance is: $";
                cout << fixed << setprecision(2) << t->getBalance();
                cout << endl;
                return;
            }
            else if (
                (ans.compare("n") == 0) ||
                (ans.compare("N") == 0) ||
                (ans.compare("No") == 0) ||
                (ans.compare("no") == 0) ||
                (Command::isCancel(ans))
                ) {
                cout << endl;
                cout << "Understood. Selling stocks is a big deal." << endl;
                cout << "If you change your mind, you can always come back!";
                cout << endl;
                return;
            }
            else {
                cout << endl;
                cout << "Hmm, I'm not sure I understand that. Please try again.";
                cout << endl;
            }
        }
    }

}