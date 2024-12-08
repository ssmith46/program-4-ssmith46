/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: November 26, 2024
 * 
 * File: Trader.h
 * Purpose: Contains the declaration of the 'Trader' class.
*/
#ifndef Trader_H
#define Trader_H

/*Forward declare class so it will compile.*/
class Trader;

#include <string>
#include "Stock.h"
#include "StockPortfolio.h"

using namespace std;

/**
 * Purpose:
 * - This class represents the user as an object within the simulation. A trader is able
 *   to buy a sell stocks on the market.
 * 
 * Data Members:
 * - string name -> The name of the user logged in as a trader.
 * - string username -> The username of the trader, used for logging in.
 * - double balance -> The current balance of the trader's account. 
 * - StockPortfolio sp -> The stock portfolio containing detailis on the trader's stocks.
 * 
 * Member Functions:
 * - Trader() -> A default constructor for a Trader.
 * - Trader(string name, string username, double accountBalance) -> A constructor for 
 *   creating instances of Traders.
 * - double getBalance() -> A getter for the account balance of a trader.
 * - void setBalance(double balance) -> A setter for the account balance of a trader.
 * - void setName(string name) -> A setter for the name of a trader.
 * - string getName() -> A getter for the name of a trader.
 * - void setUsername(string username) -> A setter for the username of a trader.
 * - string getUsername() -> A getter for the username of a trader.
 * - void buyStock(Stock *stock, int quantity) -> A method used to buy stock for a trader.
 *  StockPortfolio* getPortfolio() -> A getter used to return a pointer to the
 *  stock portfolio of a trader
 * 
 * Class Usage:
 * - This class is used to represent a user interacting with stocks within the simulation.
 *   It is here that further details could be added to remember more things about the user,
 *   such as occupation, and banking details.
*/
class Trader {
    public:
        /**
         * A default Constructor so the compiler is happy. 
         */
        Trader();
        /**
         * A constructor for a Trader instance. 
         * 
         * @param name -> The name that this trader will have in the simulation. 
         * @param username -> The username that this trader will have during the simulation. 
         * @param accountBalance -> The starting account balance of this Trader. 
         */
        Trader(string name, string username, double accountBalance);
        /**
         * A getter for the current balance of a Trader. 
         * 
         * @return -> Returns the current value of the accountBalance.
         */
        double getBalance();
        /**
         * A setter for the account balance of a trader. 
         * 
         * @param balance -> The balance to set as the Trader's account balance.
         */
        void setBalance(double balance);
        /**
         * A setter for the name of a Trader. 
         * 
         * @param name -> The name to set as the Trader's new name.
         */
        void setName(string name);
        /**
         * A getter for the name of a Trader. 
         * 
         * @return -> The name of the trader.
         */
        string getName();
        /**
         * A setter used to set the username of a trader. 
         * 
         * @param username -> The new username to set as the trader's.
         */
        void setUsername(string username);
        /**
         * A getter used to return the username of a trader. 
         * 
         * @return -> The username of the trader.
         */
        string getUsername();
        /**
         * A method used to buy stock for a Trader's portfolio.
         * 
         * @param stock -> A pointer to the stock that is wanting to be bought. 
         * @param quantity -> The number of shares of the specified stock wanting to be bought. 
         */
        void buyStock(Stock *stock, int quantity);
        /**
        * A getter used to return a pointer to the
        * stock portfolio of a trader
        * 
        * @return -> A pointer to a Trader's stock prtfolio
        */
        StockPortfolio* getPortfolio();

        string listPortfolio();
    private:
        /*The name of the Trader.*/
        string name;
        /*The username of the Trader.*/
        string username;
        /*The account balance of the Trader.*/
        double balance;
        /*The stock portfolio of the trader.*/
        StockPortfolio sp;
};
#endif
