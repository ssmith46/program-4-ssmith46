/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: November 26, 2024
 * 
 * File: Market.cpp
 * Purpose: Contains the implementation of the 'Market' class.
*/
#include "Market.h"
#include "Stock.h"
#include <string>
#include <iostream>

using namespace std;

/**
* The constructor for the Market class.
*/
Market::Market(){
    /*Initialize the market random seed value.*/
    this->randSeed = 12;
    /*Initialize the randomness of stock change value.*/
    this->marketViolence = 10;
}
/**
* Converts all the stocks in the simulation to their 'to_string()' equivalents.
* 
* @return -> Returns the string resembeling all of the Stocks in the simulation.
*/
string Market::stocks_toString(){
    /*Initialize the string to be returned as the empty string.*/
    string retVal = "";
    /*Iterate over all the stocks in the allStocks vector.*/
    for (int i = 0; i<this->allStocks.size(); i++){
        /*Go through all the stocks in the simulation and get their 'to_string()' equivalents.*/
        /*This 'if' is to help format the string correctly with a '\n' character*/
        if (i == this->allStocks.size()-1){
            retVal += (this->allStocks.at(i))->toString();
        } else {
            retVal += (this->allStocks.at(i))->toString() + "\n";
        }
    }
    /*Returns the string that was created above.*/
    return retVal;
}

/**
* Adds a stock to the simulation that can then be bought, sold, and fluctuates like
* the other stocks.
* 
* @param toAdd -> The stock that will be added to the simulation. 
* @return -> A boolean indicating whether the stock was added sucessfully or not. 
*/
bool Market::addStock(Stock toAdd){
    /*Get the symbol of the stock that is attempting to be added*/
    string uniqueSymbol = toAdd.getSymbol();

    /*Go through all the Stocks, and ensure that none of them share the
      same symbol as the one that is trying to be added, as they must each
      be unique.*/
    for (int i = 0; i<this->allStocks.size(); i++){
        if ((this->allStocks.at(i))->getSymbol().compare(uniqueSymbol) == 0){
            /*Indicate that the stock could not be added successfully.*/
            return false;
        }
    }

    /*Upon reaching this point, it's ok to the stock to the allStocks vector.*/
    this->allStocks.push_back(&toAdd);

    /*Indicate that the stock was added successfully.*/
    return true;
}

/**
* Returns a stock pointer for the Stock with the specified symbol.
* 
* @param symbol -> The symbol of the stock that is wanting to be retrieved. 
* @return -> Either the stock pointer to the stock that has that matching symbol,
* or a nullptr, indicating that no stock currently has that symbol in the simulation. 
*/
Stock* Market::getStock(string symbol){
    /*The number of stocks in allStocks (the size).*/
    int numStocks = this->allStocks.size();
    /*The stock pointer on for this iteration.*/
    Stock *on;
    /*Iterate through all the stocks.*/
    for(int i = 0; i<numStocks; i++){
        /*Get the stock on for this iteration.*/
        on = this->allStocks.at(i);
        /*Check if it's the stock that is being looked for. Return if so.*/
        if (on->getSymbol().compare(symbol) == 0){
            return on;
        }
    }

    /*No stock in the market has that symbol, return a nullptr.*/
    return nullptr;
}

/**
* Sets the seed of the random number generator for the simulation.
* 
* @param seed -> The seed to set the random number generator to for the simulation. 
*/
void Market::setMarketSeed(int seed){
    /*Set the seed of the RNG for the simulation.*/
    this->randSeed = seed;
    srand(this->randSeed);
}

/**
* Returns what the current aggressiveness of the simulation is. 
* 
* @return -> Returns the aggressiveness of the simulation.
*/
int Market::getMarketViolence(){
    return this->marketViolence;
}

/**
* Sets the aggressiveness for the change of stock prices during the simulation. 
* 
* @param violence -> The aggressiveness to set the simulation to.
*/
void Market::setMarketViolence(int violence){
    this->marketViolence = violence;
}

/**
* A method used to randomly change the stock prices of the simulation.
*/
void Market::randomlyUpdateStocks(){
    
    /*Create a variable for the random number generated for stock price change.*/
    int randNum;
    /*Create a variable for the aggressiveness of the stock price chagne.*/
    double growth;
    /*Variable for stock on clarity during loop.*/
    Stock *s;

    /*Loop through all of the stocks in the market*/
    for (int i = 0; i<this->allStocks.size(); i++){

        /*Get the stock on for this iteration.*/
        s = this->allStocks.at(i);
        
        /*Get a random number to calculate whether the price change will be positive or
          negative. This algorithm results in a 1/3 chance of negative growth. This can 
          be changed by tweaking the below variable. */
        int oneInXNeg = 3;
        if (randNum % oneInXNeg == 0){
            growth = -1;
        } else {
            growth = 1;
        }
        
        /*Using the market violence, calculate the change of the stock price.*/
        randNum = rand() % this->getMarketViolence();
        growth *= (randNum/(double)100);
        
        /*Change the stock price using the above calculated.*/
        *s *= growth;
    }
}