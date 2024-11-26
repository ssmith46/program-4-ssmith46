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
        Market();
        string stocks_toString();
        bool addStock(Stock toAdd);
        Stock* getStock(string symbol);
        void setMarketSeed(int seed);
        int getMarketViolence();
        void setMarketViolence(int violence);
        void randomlyUpdateStocks();
        

        bool hydrateStocks(ifstream& in);
    private:
        vector<Stock*> allStocks;
        int randSeed;
        int marketViolence;
        
};
#endif
