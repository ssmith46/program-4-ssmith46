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
    string stockNamePrompt = "Which stock would you like to buy shares of? ";
    stockNamePrompt += "('l' to list stock options)";

    /*args[0] should be 'buy' or 'purchase' at this point.*/
    /*args[1] should be 'stock' or 'stocks' at this point.*/

    Command c = cf->getBaseCommand();

    /*Get the string name of the stock the user would like to buy*/
    string strStockToBuy = c.whichStock(stockNamePrompt);

    /*Handle the case that the user entered a cancel during the buying of the stock*/
    if (strStockToBuy.compare(";;;") == 0) {
        return;
    }

    string numSharesToBuyPrompt = "";
    numSharesToBuyPrompt += "How many shares of " + strStockToBuy + " would you like to buy?";
    /*Get the number of shares of that stock the user wants to buy*/
    int numSharesToBuy = c.howManyShares(strStockToBuy, numSharesToBuyPrompt);

    /*Handles the case the user canceled*/
    if (numSharesToBuy == -1) {
        return;
    }

    Trader* t = this->s->getLoggedInTrader();
    double accountBalance = t->getBalance();

    Stock* s = this->m->getStock(strStockToBuy);

    double stockPrice = s->getPrice();

    stringstream ss;
    double totalCost = (stockPrice * numSharesToBuy) + 0.00000001;
    ss << fixed << setprecision(2) << totalCost;
    ss >> totalCost;
    ss.str("");
    ss << fixed << setprecision(2) << accountBalance;
    ss >> accountBalance;
    accountBalance += .01;

    /*Handles the case that they don't have enough money in their account.*/
    if ((totalCost != accountBalance) && (accountBalance - totalCost < 0)) {
        accountBalance -= .01;
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
    else { /*They have enough money in their account.*/
        cout << "Buying " << numSharesToBuy << " shares of " << strStockToBuy << " stock..." << endl;
        t->buyStock(s, numSharesToBuy);
        s->removeShares(numSharesToBuy);
        cout << "Purchase complete!"; cout << endl;
    }

   


    
}

