/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: November 26, 2024
 * 
 * File: StockPortfolio.h
 * Purpose: Contains the declaration of the 'StockPortfolio' class.
*/
#ifndef StockPortfolio_H
#define StockPortfolio_H

/*Forward declare class so it will compile.*/
class StockPortfolio;

#include <string>
#include <vector>
#include "Trader.h"
#include "Stock.h"

using namespace std;

/**
 * This struct is what each entry in the Stock Portfolio is
 * and it contains information needed for calculating the worth of that stock amount.
 * 
 * @member stock -> A stock pointer to the stock that is owned, so price can be retreived.
 * @member amountOwned -> The number of shares of that stock that are owned by the trader.
 */
struct PortfolioEntry {
    Stock* stock;
    int amountOwned;
};

/**
 * Purpose:
 * - This class acts as the contained for all the stocks a trader owns. The worth
 *   of all their stocks can be calculated using this class, and it will automatically
 *   update as the stock prices fluctuate.
 * 
 * Data Members:
 * - vector<PortfolioEntry> portEnts -> A vector containing entries of type struct portfolio
 *   entry, as defined above. 
 * - double totalVal -> The current totalValue of the stock portfolio.
 * - Trader t -> The owner of the stock portfolio.
 * 
 * Member Functions:
 * - int howMuchStockOwned(string symbol) -> Given the symbol of a stock, return how many shares
 *   a trader currently has of that stock in their portfolio. If they do not currently have any
 *   shares of the specified stock, then zero is the return value. 
 * - string sellStock(string symbol, int amount) -> Given the symbol, and amount to sell, a 
 *   stock portfolio can be updated to reflect the new sale of stocks. A string is returned 
 *   indicating if the trader successfully sold the stock.
 * - bool buyStocks(Stock* s, int amount) -> Given a pointer to the stock that would like to
 *   be purchased, and the amount of that stock that would like to be purchased, update the
 *   stock portfolio accordingly. 
 * - void printStocks() -> Convert the stocks currently in the stock portfolio of a trader
 *   into a human readable string and return this.
 * 
 * Class Usage:
 * - This class is used to organize the stocks that a trader owns by giving them a place
 *   to reside within the simulation. This also gives an easy way to calculate the
 *   total worth of a trader's stock portfolio.
*/
class StockPortfolio {
    public:
        /**
         * Calculate how much stock of a certain symbol a trader has in their portfolio. 
         * 
         * @param symbol -> The Stock that would like to be figured out how much is owned. 
         * @return -> Returns the number of shares owned by the trader of that stock, or
         * zero is no shares of that stock are currently owned. 
         */
        int howMuchStockOwned(string symbol);
        /**
         * Sells the specified number of shares, of the specified stock within the trader's
         * portfolio. 
         * 
         * @param symbol -> The stock that would like to be sold. 
         * @param amount -> The number of shares of the specified stock to sell. 
         * @return string -> Signifies whether the stock was sold or not.
         */
        string sellStock(string symbol, int amount);
        /**
         * Buys the specifies amount of shares of the specified stock. Creates a new entry in
         * the portEnts if there isn't currently an entry to match the stock being bought. 
         * 
         * @param s -> A pointer to the stock that would like to be bought. 
         * @param amount -> The number of shares that would like to be boughten of the
         * specified stock. 
         * @return -> Returns whether the transaction of buying that stock was successful or not
         * in the format of a message. 
         */
        string buyStocks(Stock* s, int amount);
        /**
         * Convert all of the currently owned stocks into human readable format, and return them. 
         * 
         * @return -> The human readable format of the worth of each stock. 
         */
        string stocks_toString();
    private:
        /*A vector filled with the portfolio entries of the stocks that are owned by a trader.*/
        vector<PortfolioEntry> portEnts;
        /*The current worth of the portfolio, as calculated by current stock price.*/
        double totalVal;
        /*Owner of the stock portfolio.*/
        Trader *t;
};
#endif
