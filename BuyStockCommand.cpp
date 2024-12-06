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
    /*args[0] should be 'buy' or 'purchase' at this point.*/
    /*args[1] should be 'stock' or 'stocks' at this point.*/

    Command c = cf->getBaseCommand();

    /*Get the string name of the stock the user would like to buy*/
    string strStockToBuy = c.whichStock();

    /*Handle the case that the user entered a cancel during the buying of the stock*/
    if (strStockToBuy.compare(";;;") == 0) {
        return;
    }

    /*Get the number of shares of that stock the user wants to buy*/
    int numSharesToBuy = c.howMany(strStockToBuy);

    /*Handles the case the user canceled*/
    if (numSharesToBuy == -1) {
        return;
    }

    Trader* t = this->s->getLoggedInTrader();
    double accountBalance = t->getBalance();

    Stock* s = this->m->getStock(strStockToBuy);

    double stockPrice = s->getPrice();

    double totalCost = round((stockPrice * numSharesToBuy)*100.0)/100.0;

    /*Handles the case that they don't have enough money in their account.*/
    if (totalCost > accountBalance) {
        cout << endl;
        cout << "Unfortuneatly, you don't have enough funds to make this purchase.";
        cout << endl;

        string correctShares = "share";
        if (numSharesToBuy > 1) {
            correctShares += "s";
        }
        cout << "To buy " << numSharesToBuy << " " << correctShares;
        cout << " of " << strStockToBuy << " would cost ";
        cout << "$" << totalCost << endl;
        cout << "You only have $" << accountBalance << " in ";
        cout << "your account." << endl;
        cout << "Please deposit more money, or lower your purchase price.";
        cout << endl;
    }
    else { /*They have enough money in their account.*/
        t->buyStock(s, numSharesToBuy);
        s->removeShares(numSharesToBuy);
        cout << "Fin. Buying " << numSharesToBuy << " shares of " << strStockToBuy << " stock." << endl;
    }

   


    
}

