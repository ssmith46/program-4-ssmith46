/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: November 26, 2024
 * 
 * File: Stock.h
 * Purpose: Contains the declaration of the 'Stock' class.
*/
#ifndef Stock_H
#define Stock_H
#include <string>

using namespace std;

/**
 * Purpose:
 * - This class is meant to represent Stocks as they apear in the real world, with
 *   things like Price, Symbol, Amount, etc.
 * - In this program, stocks are things that can be bought and sold by traders.
 * 
 * Data Members:
 * - string symbol -> The uniquely identifying symbol for the stock.
 * - double price -> The current price that a stock can be bought or sold for.
 * - int shares -> The total number of these stocks that exist in the simulation.
 * - char growthSymbol -> A '+' or '-' representing growth or decline in value.
 * - double lastChange -> The last change that the stock experienced (how much).
 * 
 * Member Functions:
 * - Stock(string symbol, double price, int shares) -> The Constructor for the Stock class.
 * - void setSymbol(string symbol) -> Setter for the symbol of a stock.
 * - string getSymbol() -> Getter for the symbol of a stock.
 * - void setPrice(double price) -> Setter for the price of a stock.
 * - double getPrice() -> Getter for the price of a stock.
 * - void setShares(int amount) -> Setter for the number of shares a stock has.
 * - int getShares() -> Getter for the number of shares a stock has left.
 * - void addShares(int amount) -> Adder for the number of shares a stock has left.
 * - void removeShares(int amount) -> Subtractor for the number of shares a stock has left.
 * - void setGrowthSymbol(char Symbol) -> Setter for the growth symbol of a stock.
 * - char getGrowthSymbol() -> Getter for the growth symbol of a stock.
 * - void setLastChange(double change) -> Setter for the last change that a stock experienced.
 * - double getLastChange() -> Getter for the last change that a stock experienced.
 * - double operator*=(double amountToChangeBy) -> An operation defintion that allows a
 *   stock to '*=' some double, and correctly update the price, as well as the last change
 *   that stock experienced.
 * - string toString() -> Converts the stock to a printable string version.
 * 
 * Class Usage:
 * - This class is used in the simulation as things that can be bought and sold by traders.
 *   Without it, the entire program would be kind of odd, as the Simulation is meant to 
 *   model the buying and selling of stocks, thus this class is a crucial one within the system.
*/
class Stock {
    public:
        /**
         * Constructor for a stock object
         * 
         * @param symbol -> The unique symbol for that stock. 
         * @param price -> The current price of that stock.
         * @param shares -> The number of remaining shares left of that stock.
         */
        Stock(string symbol, double price, int shares);
        /**
         * A setter for a stock's symbol
         * 
         * @param symbol -> The symbol to set as the stock's symbol.
         */
        void setSymbol(string symbol);
        /**
         * A getter for a stock's symbol
         * 
         * @return -> The symbol of that stock.
         */
        string getSymbol();
        /**
         * A setter for a stock's price
         * 
         * @param -> The price to set as the stock's current price.
         */
        void setPrice(double price);
        /**
         * A getter for the current price of a stock. 
         * 
         * @return -> The current price of a stock.
         */
        double getPrice();
        /**
         * A setter for the number of shares a stock has left.
         * 
         * @param amount -> The number of shares to set as how many shares are left.
         */
        void setShares(int amount);
        /**
         * A getter for the number of shares a stock has left. 
         * 
         * @return -> The number of shares a stock has left.
         */
        int getShares();
        /**
         * An adder for the number of shares a stock has left.
         * 
         * @param amount -> The number of shares to add for a stock having left.
         */
        void addShares(int amount);
        /**
         * A subtractor for the number of shares a stock has left. 
         * 
         * @param amount -> The number of shares to subtract from a stock having left.
         */
        void removeShares(int amount);
        /**
         * A setter for the growth symbol of a stock. 
         * 
         * @param symbol -> The symbol to change the stock's growth symbol to.
         */
        void setGrowthSymbol(char symbol);
        /**
         * A getter for the growth symbol of a stock. 
         * 
         * @return -> The growth symbol of a stock based on the last change.
         */
        char getGrowthSymbol();
        void setLastChange(double change);
        double getLastChange();
        /*This will return the new price of the Stock*/
        double operator*=(double amountToChangeBy);
        string toString();
    private:
        string symbol;
        double price;
        int shares;
        char growthSymbol;
        double lastChange;
};
#endif
