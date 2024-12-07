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
            cout << "Try a choosing a different stock symbol." << endl;
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


    /*Handles the case that they don't have enough money in their account.*/
    if (((accountBalance - totalCost < 0) && (accountBalance - totalCost > -0.001)) ||
        (accountBalance - totalCost >= 0)) {
        cout << endl;
        cout << "Buying " << numSharesToBuy << " shares of " << strStockToBuy << " stock..." << endl;
        t->buyStock(s, numSharesToBuy);
        s->removeShares(numSharesToBuy);
        cout << "Purchase complete!"; cout << endl;
    }
    else { /*They don't have enough money in their account.*/
        cout << endl;
        cout << "Unfortunately, you don't have enough funds to make this purchase.";
        cout << endl;
        string correctShares = "share";
        if (numSharesToBuy > 1) {
            correctShares += "s";
        }
        cout << "To buy " << numSharesToBuy << " " << correctShares;
        cout << " of " << strStockToBuy << " would cost ";
        cout << "$" << fixed << setprecision(2) << totalCost << endl;
        cout << "You have $" << fixed << setprecision(2) << accountBalance << " in ";
        cout << "your account." << endl;
        cout << "Please deposit more money, or lower your purchase price.";
        cout << endl;
    }





}