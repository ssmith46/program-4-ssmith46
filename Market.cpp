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

/**
* Get a string of '-' that is of length ('length' + 2)
* 
* @param length -> The length the return string should be (+2)
* @return -> a string of '-' symbol of length ('length' + 2)
*/
string Market::get_seperator(int length) {
    /*Create a string for the return value*/
    string retVal = "--";
    /*Add '-' symbols in accordance with the length argument*/
    for (int i = 0; i < length; i++) {
        retVal += "-";
    }
    /*Return the created string*/
    return retVal;
}
/**
* Get a string that is left space padded and of length 'length'
*
* @param word -> The word to space pad
* @param length -> The length the resulting string should be after padding
* @return -> The left space padded string
*/
string Market::get_spacedWord(string word, int length) {
    /*Calculate the number of spaces to add to the retval + 1*/
    int numSpaces = length - word.length();
    /*Create the retval string*/
    string retVal = " ";
    /*Add spaces in accordance with the specified length*/
    for (int i = 0; i < numSpaces; i++) {
        retVal += " ";
    }
    /*Add the given word*/
    retVal += word;
    /*Add a space after the word*/
    retVal += " ";

    /*Return the created string*/
    return retVal;
}

/**
* Converts all the stocks in the simulation to their 'to_string()' equivalents.
* 
* @return -> Returns the string resembeling all of the Stocks in the simulation.
*/
string Market::stocks_toString(){

    /*Check if there are no stocks in the simulation, and return if so*/
    if (this->allStocks.size() == 0) {
        return "There are currently no stocks in the simulation.\n";
    }

    /*Initialize the string to be returned as the empty string.*/
    string retVal = "";

    /*Create titles for the returned table*/

    string symbolTitle = "Symbols";
    string changeTitle = "Last Value Change";
    string priceTitle = "Stock Prices";
    string sharesTitle = "Shares Left";


    /*Set the longest length of each column's spacing to the titles as default*/

    int longestLengthName = symbolTitle.length() + 1;
    int longestLengthPrice = priceTitle.length() + 1;
    int longestLengthShares = sharesTitle.length() + 1;
    int longestLastChange = changeTitle.length() +1;

    /*Create a Stock variable for iterating through the simulation's stocks*/
    Stock on;

    /*Iterate through all the stocks in the simulation*/
    for (int i = 0; i < this->allStocks.size(); i++) {
        /*Get the stock for this iteration*/
        on = this->allStocks.at(i);

        /*Check if the symbol of the stock on is longer than the current longest column length*/
        if (on.getSymbol().length() > longestLengthName) {
            /*Replace if so*/
            longestLengthName = on.getSymbol().length();
        }

        /*Default the number of places for a price to 4*/
        int places = 4;
        double price = on.getPrice();
        /*Figure out the number of places for this price*/
        while (price >= 1.0) {
            price *= .1;
            places += 1;
        }
        /*Check if this price has more places than there are chars in the longest column length*/
        if (places > longestLengthPrice) {
            longestLengthPrice = places;
        }

        /*Set the number of places to 1 for number of shares*/
        places = 1;
        /*Get the number of share for the stock on this iteration*/
        int sharesLeft = on.getShares();
        /*Calculate the number of places this stock has for the number of shares*/
        while (sharesLeft >= 1.0) {
            sharesLeft *= .1;
            places += 1;
        }
        /*Check if this number has more places than there are chars in the longest column length*/
        if (places > longestLengthShares) {
            longestLengthShares = places;
        }

        /*Get the last change this stock price experienced*/
        double lastChange = (int)on.getLastChange();
        /*Default the number of places to 4*/
        places = 4;
        /*Calculate how many places in the last change this stock experienced*/
        while (lastChange >= 1.0) {
            lastChange *= .1;
            places += 1;
        }
        /*Check if this number has more places than there are chars in the longest column length*/
        if (places > longestLastChange) {
            longestLastChange = places;
        }
    }

    /*Create a seperator string*/
    string sep = "";

    /*Add to the seperator string based off the lengths calculated above*/
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

    /*Add the seperator to the return value*/
    retVal += sep;

    /*Add the column titles to the return value*/
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

    /*Add the seperator to the return value*/
    retVal += sep;

    
    /*Iterate over all the stocks in the allStocks vector.*/
    for (int i = 0; i<this->allStocks.size(); i++){
        /*Get the stock on for this iteration*/
        on = allStocks.at(i);
        /*Add the space seperated symbol to the table*/
        retVal += "|";
        retVal += this->get_spacedWord(on.getSymbol(), longestLengthName);

        /*Add the last change to the table*/
        retVal += "|";
        /*Use a string stream to get it the correct precision*/
        stringstream ss;
        /*Get the absolute value of the last change*/
        double lastChange = abs(on.getLastChange());
        /*Get the last change symbol for the last change*/
        char changeSym = on.getGrowthSymbol();
        /*Fix the precision to two decimal places*/
        ss << fixed << setprecision(2) << (lastChange*100);
        /*Create a string with the change symbol, change value, and '%' sign*/
        string fixedChange = changeSym + ss.str() + "%";
        /*Add the space seperated price change to the retval*/
        retVal += this->get_spacedWord(fixedChange, longestLastChange);

        /*Add the price to the table*/
        retVal += "|";
        /*User a string stream to format the precision of the price to two
          decimal places*/
        ss.str("");
        ss << fixed << setprecision(2) << on.getPrice();
        /*Add the '$' to the price*/
        string fixedPrice = "$" + ss.str();
        /*Add the spaced price to the table*/
        retVal += this->get_spacedWord(fixedPrice, longestLengthPrice);

        /*Add the number of shares remaining to the table*/
        retVal += "|";
        /*Get the spaced number of shares*/
        retVal += this->get_spacedWord(to_string(on.getShares()), longestLengthShares);
        retVal += "|";
        
        /*Add a new line to the retVal*/
        retVal += "\n";

    }

    /*Add one final seperator to the bottom of the table*/
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
          negative. This algorithm works as follows:
          
          - price < 50:
            - 25% chance of being negative
          - price > 1000000
            - 100% chance of being negative
          - otherwise:
            - 50% change of being negative
        
        */
        /*The default 50/50 chance*/
        int oneInXNeg = 2;
        /*Handle when stock price gets really low*/
        if (s.getPrice() < 50) {
            oneInXNeg = 4;
        }
        /*Handle when stock price gets really high*/
        else if (s.getPrice() > 1000000) {
            oneInXNeg = 1;
        }
        /*Figure out if negative of positive*/
        if (randNum % oneInXNeg == 0){
            growth = -1;
        } else {
            growth = 1;
        }
        
        /*Using the market violence, calculate the change of the stock price.*/
        randNum = rand() % this->getMarketViolence();
        growth *= (randNum/(double)100);
        
        /*Get the ones place too*/
        randNum = rand() % 100;
        growth += ((randNum * .01)/100);
        
        /*Change the stock price using the above calculated.*/
        this->allStocks.at(i).change(growth);
    }
}