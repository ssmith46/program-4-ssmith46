/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: November 26, 2024
 * 
 * File: Trader.cpp
 * Purpose: Contains the implementation of the 'Trader' class.
*/
#include "Trader.h"
#include <iostream>
#include <string>

using namespace std;

/**
* A default Constructor so the compiler is happy. 
*/
Trader::Trader(Market *m){ 
    StockPortfolio s(m);
    this->sp = s;
}

/**
* A constructor for a Trader instance. 
* 
* @param name -> The name that this trader will have in the simulation. 
* @param username -> The username that this trader will have during the simulation. 
* @param accountBalance -> The starting account balance of this Trader. 
*/
Trader::Trader(string name, string username, double accountBalance, Market *m) {
    /*Initialize the fields with the given arguments.*/

    this->name = name;
    this->username = username;
    this->balance = accountBalance;

    StockPortfolio s(m);
    this->sp = s;

}

/**
* A setter for the name of a Trader. 
* 
* @param name -> The name to set as the Trader's new name.
*/
void Trader::setName(string name){
    this->name = name;
}

/**
* A getter for the name of a Trader. 
* 
* @return -> The name of the trader.
*/
string Trader::getName(){
    return this->name;
}

/**
* A setter for the account balance of a trader. 
* 
* @param balance -> The balance to set as the Trader's account balance.
*/
void Trader::setBalance(double balance){
    this->balance = balance;
}

/**
* A getter for the current balance of a Trader. 
* 
* @return -> Returns the current value of the accountBalance.
*/
double Trader::getBalance(){
    return this->balance;
}

/**
* A method used to buy stock for a Trader's portfolio.
* 
* @param stock -> A pointer to the stock that is wanting to be bought. 
* @param quantity -> The number of shares of the specified stock wanting to be bought. 
*/
void Trader::buyStock(Stock *stock, int amount){
    /*Obtain the account Balance of this trader*/
    double accountBalance = this->getBalance();
    /*Calculate the total purchase price of the purchase being made*/
    double purchasePrice = (stock->getPrice() * amount);

    /*Give an extremely small room for double subtractiion issues*/
    /*If it's close enough to zero, just set it to zero*/
    if ((accountBalance - purchasePrice < 0) && (accountBalance - purchasePrice > -0.001)) {
        this->setBalance(0);
    }
    /*Otherwise, it's just a normal transaction.*/
    else {
        this->setBalance(accountBalance - purchasePrice);
    }
    /*Check that the stock portfolio corrently buys the stock*/
    if (this->sp.buyStocks(stock, amount).compare("Fail") == 0) {
        cout << "Failed to buy the stock." << endl;
    }
}

/**
* A setter used to set the username of a trader. 
* 
* @param username -> The new username to set as the trader's.
*/
void Trader::setUsername(string username){
    this->username = username;
}

/**
* A getter used to return the username of a trader. 
* 
* @return -> The username of the trader.
*/
string Trader::getUsername(){
    return this->username;
}

/**
* A getter used to return a pointer to the
* stock portfolio of a trader
*
* @return -> A pointer to a Trader's stock prtfolio
*/
StockPortfolio* Trader::getPortfolio() {
    return &(this->sp);
}

string Trader::listPortfolio() {
    return this->sp.stocks_toString();
}