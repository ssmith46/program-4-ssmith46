/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 3, 2024
 *
 * File: BuyStockCommand.cpp
 * Purpose: Contains the implementation of the 'BuyStockCommand' class.
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
* @param args -> The arguments that lead to the buy stock command.
* @param m -> The market that the command can influence.
* @param s -> The simulator that the command can influence.
*/
BuyStockCommand::BuyStockCommand(vector<string> args, 
    Market* m, Simulator* s, CommandFactory *cf){
    /*Assign arguments to data members of object*/

    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}

/**
* This method overrides the base Command class's execute method.
* In this case, this method prompts the user for input and updates the simulation
* to allow the user to buy a stock.
* - Updates their trader's account balance
* - Updates their stock portfolio
* - Updates the number of remaining shares for that stock
*/
void BuyStockCommand::execute() {
    /*Create the prompt that will be used to get user input*/
    string stockNamePrompt = "Which stock would you like to buy shares of? ";
    stockNamePrompt += "('l' to list stock options)";

    /*Create a command object so have access to the command specific methods*/
    Command c = cf->getBaseCommand();

    /*Get the string symbol of the stock the user would like to buy*/
    string strStockToBuy = c.whichStock(stockNamePrompt, "buy");

    /*Handle the case that the user entered a cancel during the buying of the stock*/
    if (strStockToBuy.compare(";;;") == 0) {
        return;
    }

    /*Create the prompt that will be used to get user input for number of shares*/
    string numSharesToBuyPrompt = "";
    numSharesToBuyPrompt += "How many shares of " + strStockToBuy + " would you like to buy?";

    /*Get the number of shares of that stock the user wants to buy*/
    int numSharesToBuy = c.howManyShares(strStockToBuy, numSharesToBuyPrompt, "buy");

    /*Handles the case the user canceled*/
    if (numSharesToBuy == -1) {
        return;
    }

    /*Get a pointer to the logged in trader*/
    Trader* t = this->s->getLoggedInTrader();
    /*Get the balance of the logged in trader*/
    double accountBalance = t->getBalance();
    /*Get a pointer to the stock trying to buy*/
    Stock* s = this->m->getStock(strStockToBuy);
    /*Get the price of the stock trying to buy*/
    double stockPrice = s->getPrice();

    /*Create a string stream for formatting double values*/
    stringstream ss;
    /*Calculate the total cost of the purchase being made*/
    /*Add 0.00000001 to it for double issues*/
    double totalCost = (stockPrice * numSharesToBuy) + 0.00000001;
    
    /*Set the precision for account balance and total cost to two decimal places*/
    ss << fixed << setprecision(2) << totalCost;
    ss >> totalCost;
    ss.str("");
    ss << fixed << setprecision(2) << accountBalance;
    ss >> accountBalance;


    /*Figure out if they don't have enough money in their account.*/

    /*This is the case they have enough money in their account*/
    /*(Give very little smidge room for double issues)*/
    if (((accountBalance - totalCost < 0) && (accountBalance - totalCost > -0.001)) ||
        (accountBalance - totalCost >= 0)) {
        /*Indicate that the purchase process has begun*/
        cout << endl;
        cout << "Buying " << numSharesToBuy << " shares of " << strStockToBuy << " stock...";
        /*Buy the stocks for the trader*/
        t->buyStock(s, numSharesToBuy);
        /*Remove the bought shares from the stock*/
        s->removeShares(numSharesToBuy);
        /*Indicate the the purchase was sucessful*/
        cout << " Purchase complete!"; cout << endl;
    }
    else { /*They don't have enough money in their account.*/

        /*Indicate to the user that they don't have enough money in their account*/
        cout << endl;
        cout << "Unfortunately, you don't have enough funds to make this purchase.";
        cout << endl;
        /*Figure out if should say "share" or "shares" in output*/
        string correctShares = "share";
        if (numSharesToBuy > 1) {
            correctShares += "s";
        }

        /*Tell user how much they would need to have to make the purchase*/
        cout << "To buy " << numSharesToBuy << " " << correctShares;
        cout << " of " << strStockToBuy << " would cost ";
        cout << "$" << fixed << setprecision(2) << totalCost << endl;
        cout << "You have $" << fixed << setprecision(2) << accountBalance << " in ";
        cout << "your account." << endl;
        cout << "Please deposit more money, or lower your purchase price.";
        cout << endl;
    }

}

