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
#include <sstream>
#include <cmath>
#include <iomanip>

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

string Market::get_seperator(int length) {
    string retVal = "--";
    for (int i = 0; i < length; i++) {
        retVal += "-";
    }
    return retVal;
}

string Market::get_spacedWord(string word, int length) {
    int numSpaces = length - word.length();
    string retVal = " ";
    for (int i = 0; i < numSpaces; i++) {
        retVal += " ";
    }
    retVal += word;
    retVal += " ";

    return retVal;
}

/**
* Converts all the stocks in the simulation to their 'to_string()' equivalents.
* 
* @return -> Returns the string resembeling all of the Stocks in the simulation.
*/
string Market::stocks_toString(){


    if (this->allStocks.size() == 0) {
        return "There are currently no stocks in the simulation.\n";
    }

    /*Initialize the string to be returned as the empty string.*/
    string retVal = "";


    string symbolTitle = "Symbols";
    string changeTitle = "Last Value Change";
    string priceTitle = "Stock Prices";
    string sharesTitle = "Shares Left";



    int longestLengthName = symbolTitle.length() + 1;
    int longestLengthPrice = priceTitle.length() + 1;
    int longestLengthShares = sharesTitle.length() + 1;
    int longestLastChange = changeTitle.length() +1;
    Stock on;
    for (int i = 0; i < this->allStocks.size(); i++) {
        on = this->allStocks.at(i);
        if (on.getSymbol().length() > longestLengthName) {
            longestLengthName = on.getSymbol().length();
        }
        int places = 4;
        double price = on.getPrice();
        while (price >= 1.0) {
            price *= .1;
            places += 1;
        }
        if (places > longestLengthPrice) {
            longestLengthPrice = places;
        }
        places = 1;
        int sharesLeft = on.getShares();
        while (sharesLeft >= 1.0) {
            sharesLeft *= .1;
            places += 1;
        }
        if (places > longestLengthShares) {
            longestLengthShares = places;
        }
        double lastChange = (int)on.getLastChange();
        places = 4;
        while (lastChange >= 1.0) {
            lastChange *= .1;
            places += 1;
        }
        if (places > longestLastChange) {
            longestLastChange = places;
        }
    }

    string sep = "";

    sep += "+";
    sep += this->get_seperator(longestLengthName);
    sep += "+";
    sep += this->get_seperator(longestLastChange);
    sep += "+";
    sep += this->get_seperator(longestLengthPrice);
    sep += "+";
    sep += this->get_seperator(longestLengthShares);
    sep += "+";
    sep += "\n";

    retVal += sep;

    retVal += "|";
    retVal += this->get_spacedWord(symbolTitle, longestLengthName);
    retVal += "|";
    retVal += this->get_spacedWord(changeTitle, longestLastChange);
    retVal += "|";
    retVal += this->get_spacedWord(priceTitle, longestLengthPrice);
    retVal += "|"; 
    retVal += this->get_spacedWord(sharesTitle, longestLengthShares);
    retVal += "|";
    retVal += "\n";

    retVal += sep;

    
    /*Iterate over all the stocks in the allStocks vector.*/
    for (int i = 0; i<this->allStocks.size(); i++){
        /*Go through all the stocks in the simulation and get their 'to_string()' equivalents.*/
        /*This 'if' is to help format the string correctly with a '\n' character*/
        on = allStocks.at(i);
        retVal += "|";
        retVal += this->get_spacedWord(on.getSymbol(), longestLengthName);
        retVal += "|";
        stringstream ss;
        double lastChange = abs(on.getLastChange());
        char changeSym = on.getGrowthSymbol();
        ss << fixed << setprecision(2) << (lastChange*100);
        string fixedChange = changeSym + ss.str() + "%";
        retVal += this->get_spacedWord(fixedChange, longestLastChange);
        retVal += "|";
        ss.str("");
        ss << fixed << setprecision(2) << on.getPrice();
        string fixedPrice = "$" + ss.str();
        retVal += this->get_spacedWord(fixedPrice, longestLengthPrice);
        retVal += "|";
        retVal += this->get_spacedWord(to_string(on.getShares()), longestLengthShares);
        retVal += "|";
        retVal += "\n";
    }

    retVal += sep;

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
        if ((this->allStocks.at(i)).getSymbol().compare(uniqueSymbol) == 0){
            /*Indicate that the stock could not be added successfully.*/
            return false;
        }
    }

    /*Upon reaching this point, it's ok to the stock to the allStocks vector.*/
    this->allStocks.push_back(toAdd);

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
    Stock on;
    /*Iterate through all the stocks.*/
    for(int i = 0; i<numStocks; i++){
        /*Get the stock on for this iteration.*/
        on = this->allStocks.at(i);
        /*Check if it's the stock that is being looked for. Return if so.*/
        if (on.getSymbol().compare(symbol) == 0){
            return &(this->allStocks.at(i));
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
    Stock s;

    /*Loop through all of the stocks in the market*/
    for (int i = 0; i<this->allStocks.size(); i++){
        /*Get the stock on for this iteration.*/
        s = this->allStocks.at(i);
        randNum = rand();
        /*Get a random number to calculate whether the price change will be positive or
          negative. This algorithm results in a 1/3 chance of negative growth. This can 
          be changed by tweaking the below variable. */
        int oneInXNeg = 2;
        if (s.getPrice() < 50) {
            oneInXNeg = 4;
        }
        else if (s.getPrice() > 1000000) {
            oneInXNeg = 1;
        }
        if (randNum % oneInXNeg == 0){
            growth = -1;
        } else {
            growth = 1;
        }
        
        /*Using the market violence, calculate the change of the stock price.*/
        randNum = rand() % this->getMarketViolence();
        growth *= (randNum/(double)100);
        
        randNum = rand() % 100;
        growth += ((randNum * .01)/100);
        
        /*Change the stock price using the above calculated.*/
        this->allStocks.at(i).change(growth);
    }
}