/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: November 26, 2024
 * 
 * File: Market.h
 * Purpose: Contains the declaration of the 'Market' class.
*/
#ifndef Market_H
#define Market_H

/*Forward declare class so it will compile.*/
class Market;

#include <string>
#include "Stock.h"
#include <vector>

using namespace std;

/**
 * Purpose:
 * - The purpose of this class is to host all of the Stock objects, and be able to
 *   fluctuate their prices on a random basis.
 * 
 * Data Members:
 * - vector<Stock*> allStocks -> This vector of stock pointers holds pointers to 
 *   all of the Stock objects that exist in the simulation.
 * - int randSeed -> This is the random seed that is used when fluctuating the prices
 *   of the stocks.
 * - int marketViolence -> This is used to help guage how aggresive the growth/drop
 *   of stock prices can be on each fluctuation during the simulation.
 * 
 * Member Functions:
 * - Market() -> The constructor for the Market class, where the all stocks vector, and
 *   random seeds are initialized.
 * - string stocks_toString() -> Convert all of the stocks in the simulation to a printable
 *   string format.
 * - bool addStock(Stock toAdd) -> Adds a stock to the vector of all the stocks in the simulation.
 *   Returns a boolean indicating whether the addition was successful (true) or not (false).
 * - Stock* getStock(string symbol) -> Returns a pointer to the stock with the given symbol.
 * - void setMarketSeed(int seed) -> Sets the seed for the random number generator used in 
 *   fluctuating stock prices.
 * - int getMarketViolence() -> Get the number that is used to dictate how aggressive the changes
 *   of stock prices can be in each change.
 * - void setMarketViolence(int violence) -> Set the aggressiveness that the market can be during
 *   stock price changes.
 * - void randomlyUpdateStocks() -> Fluctuate the prices of all the stocks in the simulation,
 *   randomly based on the random seed.
 * 
 * Class Usage:
 * - This class is used to help manage all the Stocks, as well as their price changes,
 *   during the run of the simulation.
*/
class Market {
    public:
        /**
         * The constructor for the Market class.
         */
        Market();
        /**
         * Converts all the stocks in the simulation to their 'to_string()' equivalents.
         * 
         * @return -> Returns the string resembeling all of the Stocks in the simulation.
         */
        string stocks_toString();
        /**
         * Adds a stock to the simulation that can then be bought, sold, and fluctuates like
         * the other stocks.
         * 
         * @param toAdd -> The stock that will be added to the simulation. 
         * @return -> A boolean indicating whether the stock was added sucessfully or not. 
         */
        bool addStock(Stock toAdd);
        /**
         * Returns a stock pointer for the Stock with the specified symbol.
         * 
         * @param symbol -> The symbol of the stock that is wanting to be retrieved. 
         * @return -> Either the stock pointer to the stock that has that matching symbol,
         * or a nullptr, indicating that no stock currently has that symbol in the simulation. 
         */
        Stock* getStock(string symbol);
        /**
         * Sets the seed of the random number generator for the simulation.
         * 
         * @param seed -> The seed to set the random number generator to for the simulation. 
         */
        void setMarketSeed(int seed);
        /**
         * Returns what the current aggressiveness of the simulation is. 
         * 
         * @return -> Returns the aggressiveness of the simulation.
         */
        int getMarketViolence();
        /**
         * Sets the aggressiveness for the change of stock prices during the simulation. 
         * 
         * @param violence -> The aggressiveness to set the simulation to.
         */
        void setMarketViolence(int violence);
        /**
         * A method used to randomly change the stock prices of the simulation.
         */
        void randomlyUpdateStocks();
        
    private:
        /*A vector that contains pointers to all the stocks in the simulation.*/
        vector<Stock*> allStocks;
        /*The seed used in the random number generator for stock price changes.*/
        int randSeed;
        /*The aggressiveness for the max stock price change allowed at a time.*/
        int marketViolence;
        
};
#endif
