/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: November 26, 2024
 * 
 * File: StockPortfolio.cpp
 * Purpose: Contains the implementation of the 'StockPortfolio' class.
*/
#include "StockPortfolio.h"
#include "Trader.h"
#include "Market.h"
#include "Stock.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

StockPortfolio::StockPortfolio() { }

/**
* The default constructor for the stockportfolio so complier doesn't complain
*/
StockPortfolio::StockPortfolio(Market *m) { 
    /*Set the default total of the stock portfolio*/
    this->totalVal = 0;
    this->m = m;
}

/**
* Calculate how much stock of a certain symbol a trader has in their portfolio. 
* 
* @param symbol -> The Stock that would like to be figured out how much is owned. 
* @return -> Returns the number of shares owned by the trader of that stock, or
* zero is no shares of that stock are currently owned. 
*/
int StockPortfolio::howMuchStockOwned(string symbol){
    /*Calculate the size of the portfolio for iterating through.*/
    int entries = this->portEnts.size();
    /*Create a variable to represent the currently on portEnt.*/
    struct PortfolioEntry pe;
    /*Iterate through all the portEnts in the portfolio.*/
    for (int i = 0; i<entries; i++){
        /*Get the currently on portEnt.*/
        pe = this->portEnts.at(i);
        /*Check if the stock symbol of this stock matches what looking for. Return if so.*/
        if (pe.stockSymbol.compare(symbol) == 0){
            return pe.amountOwned;
        }
    }

    /*By making it to here, this signifies that the trader has none of that
      stock currently in their portfolio.*/
    return 0;
}

/**
* Sells the specified number of shares, of the specified stock within the trader's
* portfolio. 
* 
* @param symbol -> The stock that would like to be sold. 
* @param amount -> The number of shares of the specified stock to sell. 
* @return string -> Signifies whether the stock was sold or not.
*/
void StockPortfolio::sellStock(string symbol, int amount){
    /*Calculate the number of portfolio entries in portEnts*/
    int numEnts = this->portEnts.size();
    /*Create a variable for portfolio entry on during iteration*/
    PortfolioEntry on;
    /*Loop through all the portfolio entries in the stock portfolio*/
    for (int i = 0; i < numEnts; i++) {
        /*Get the portfolio entry on for this iteration*/
        on = this->portEnts.at(i);
        /*Check if this is the stock looking for*/
        if (on.stockSymbol.compare(symbol) == 0) {
            /*This is the stock that is being sold*/

            /*Calculate the new number of stocks in the portfolio*/
            int newTot = on.amountOwned - amount;
            /*If the new total is zero, get rid of this entry*/
            if (newTot == 0) {
                /*Need to remove the stock entry entirely*/
                this->portEnts.erase(this->portEnts.begin() + i);
                return;
            }
            /*If it's more than zero just update the amount*/
            else if (newTot > 0) {
                /*Just update to the newTot*/
                this->portEnts.at(0).amountOwned = newTot;
                return;
            }
            /*This shouldn't ever happend, but indicate error if so*/
            else {
                cout << endl;
                cout << "Error: Selling more stock than currently have." << endl;
                return;
            }
        }
    }
}

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
string StockPortfolio::buyStocks(Stock* s, int amount){
    /*Create a variable for the portfolio entry on during iterations*/
    PortfolioEntry on;
    /*Keep track of the position found*/
    int posFound = -1;
    /*Create a variable for the portfolio entry symbol for iteration on*/
    string onSymbol;
    /*Get the symbol looking for from argument s*/
    string symbolLookingFor = s->getSymbol();
    /*Iteratre through all the stocks in the portfolio*/
    for (int i = 0; i < this->portEnts.size(); i++) {
        /*Get the portfolio entry on this iteration*/
        on = this->portEnts.at(i);
        /*Get the symbol of the portfolio entry on*/
        onSymbol = on.stockSymbol;

        /*If they match, then keep track of the position at*/
        if (onSymbol.compare(symbolLookingFor) == 0) {
            posFound = i;
        }
    }

    /*Check if an entry already exists for that stock*/
    /*This means need to create a new entry for that stock.*/
    if (posFound == -1) {
        /*Create a new portfolio entry*/
        PortfolioEntry newEnt;
        /*Set the stock of this entry to the one buying*/
        newEnt.stockSymbol = s->getSymbol();
        /*Set the amount owned of the entry to the amount buying*/
        newEnt.amountOwned = amount;
        /*Add the new entry to the portfolio entry*/
        this->portEnts.push_back(newEnt);
        /*Return that the purchase was successful*/
        return "Successful Purchase.";
    }
    /*That entry already exisits, just update it*/
    else {
        /*Get the entry that the stock was out*/
        PortfolioEntry* updating = &(this->portEnts.at(posFound));
        /*Update the amount owned of that entry*/
        updating->amountOwned += amount;
        /*return that the purchase was successful*/
        return "Successful Purchase.";
    }
}

/**
* Convert all of the currently owned stocks into human readable format, and return them. 
* 
* @return -> The human readable format of the worth of each stock. 
*/
string StockPortfolio::stocks_toString(){


    /*If there are no entries in the portfolio, indicate this*/
    if (this->portEnts.size() == 0) {
        return "There are currently no stocks in your portfolio.\n";
    }

    /*Create the string for the return value*/
    string retVal = "";

    /*Create a double for the total value of a portfolio*/
    double totalValue = 0.00;
    /*Calculate the size of the portfolio.*/
    int entries = this->portEnts.size();
    /*Create a variable for the currently on portEnt.*/
    struct PortfolioEntry pe;
    /*Iterate through all the entries in the portfolio*/
    for (int i = 0; i < entries; i++) {
        /*Get the portfolio entry on*/
        pe = this->portEnts.at(i);
        /*Increase the value of the portfolio*/
        totalValue += ((this->m->getStock(pe.stockSymbol)->getPrice())*pe.amountOwned);
    }

    /*Create a string stream for formatting doubles*/
    stringstream ss;
    ss << fixed << setprecision(2) << totalValue;

    /*Add the portfolio worth to the retval*/
    retVal += "Total portfolio worth: $" + ss.str() + "\n";

    /*Create titles for the columns of the portfolio table*/
    string symbolTitle = "Symbols";
    string changeTitle = "Last Value Change";
    string priceTitle = "Stock Prices";
    string sharesTitle = "Shares Own";
    string stockSharesTitle = "Stock Shares Worth";

    /*Calculate the size of the column titles, and default the longest length to these*/
    int longestLengthName = symbolTitle.length() + 1;
    int longestLengthPrice = priceTitle.length() + 1;
    int longestLengthShares = sharesTitle.length() + 1;
    int longestLastChange = changeTitle.length() + 1;
    int longestStockShares = stockSharesTitle.length() + 1;

    /*Create a portfolio entry for the portEnt on*/
    PortfolioEntry on;
    /*Iterate through all the portfolio entries of the portfolio*/
    for (int i = 0; i < this->portEnts.size(); i++) {

        /*Get the portfolio entry on for this iteration*/
        on = this->portEnts.at(i);

        /*Calculate the length of the symbol for this portfolio entry stock symbol*/
        if (on.stockSymbol.length() > longestLengthName) {
            /*Replace as the longest if longer than the old longest*/
            longestLengthName = on.stockSymbol.length();
        }

        /*Default the number of places for the price to 4*/
        int places = 4;
        /*Get the price of the stock on for this iteration*/
        double price = this->m->getStock(on.stockSymbol)->getPrice();
        /*Calculate the number of places in the price for this iteration*/
        while (price >= 1.0) {
            price *= .1;
            places += 1;
        }
        /*Replace as the new longest if applicable*/
        if (places > longestLengthPrice) {
            longestLengthPrice = places;
        }

        /*Default the number of places for the number of shares for this portEnt*/
        places = 1;
        /*Get the number of shares owned for this portEnt*/
        int sharesOwned = on.amountOwned;
        /*Calculate the number of places for the amountOwned*/
        while (sharesOwned >= 1.0) {
            sharesOwned *= .1;
            places += 1;
        }
        /*Update the longest column length if applicable*/
        if (places > longestLengthShares) {
            longestLengthShares = places;
        }

        /*Get the last change for the stock on this iteration*/
        double lastChange = this->m->getStock(on.stockSymbol)->getLastChange();
        /*Default the number of places to 4 for the last change*/
        places = 4;
        /*Calculate the number of places in the last change*/
        while (lastChange >= 1.0) {
            lastChange *= .1;
            places += 1;
        }
        /*Replace as the new longest column length if applicable*/
        if (places > longestLastChange) {
            longestLastChange = places;
        }

        /*Default as 4 places for the value of the stock on this iteration*/
        places = 4;
        /*Calculate the value of this stock for the number of shares and price*/
        price = (this->m->getStock(on.stockSymbol)->getPrice() * on.amountOwned);
        /*Calculate the number of places in the value*/
        while (price >= 1.0) {
            price *= .1;
            places += 1;
        }
        /*Replace as the new longest column length if applicable*/
        if (places > longestStockShares) {
            longestStockShares = places;
        }
    }

    /*Create the seperator for the table*/
    string sep = "";

    /*Create a market for using the methods associated with it*/
    Market m;

    /*Create the seperator based off the longest length calculated above*/
    sep += "+";
    sep += m.get_seperator(longestLengthName);
    sep += "+";
    sep += m.get_seperator(longestLastChange);
    sep += "+";
    sep += m.get_seperator(longestLengthPrice);
    sep += "+";
    sep += m.get_seperator(longestLengthShares);
    sep += "+";
    sep += m.get_seperator(longestStockShares);
    sep += "+";
    sep += "\n";

    /*Add the seperator to the retval*/
    retVal += sep;

    /*Add the column titles to the retval table*/
    retVal += "|";
    retVal += m.get_spacedWord(symbolTitle, longestLengthName);
    retVal += "|";
    retVal += m.get_spacedWord(changeTitle, longestLastChange);
    retVal += "|";
    retVal += m.get_spacedWord(priceTitle, longestLengthPrice);
    retVal += "|";
    retVal += m.get_spacedWord(sharesTitle, longestLengthShares);
    retVal += "|";
    retVal += m.get_spacedWord(stockSharesTitle, longestStockShares);
    retVal += "|";
    retVal += "\n";

    /*Add another seperator to the retval table*/
    retVal += sep;

    /*Iterate over all the stocks in the allStocks vector.*/
    for (int i = 0; i < this->portEnts.size(); i++) {
        /*Get the portEnt on this iteration*/
        on = portEnts.at(i);

        /*Add the stock symbol for the portEnt on this iteration*/
        retVal += "|";
        retVal += m.get_spacedWord(on.stockSymbol, longestLengthName);

        /*Add the last change to to the retVal table*/
        retVal += "|";
        /*Use a string stream for getting correct decimal display format*/
        stringstream ss;
        /*Get the last change for the stock on this iteration*/
        double lastChange = this->m->getStock(on.stockSymbol)->getLastChange();
        /*Get the change symbol for the last change this stock underwent*/
        char changeSym = this->m->getStock(on.stockSymbol)->getGrowthSymbol();
        /*Check if negative and get rid of it if so, since will display with symbol*/
        if (changeSym == '-') {
            changeSym = ' ';
        }
        /*Put the last change into the string stream*/
        ss << fixed << setprecision(2) << (lastChange*100);
        /*Get the fixed value out of the string stream*/
        string fixedChange = changeSym + ss.str() + "%";
        /*Add the fixed value to the retval table*/
        retVal += m.get_spacedWord(fixedChange, longestLastChange);

        /*Put the price of the stock on this iteration into the string stream to format decimals*/
        retVal += "|";
        ss.str("");
        ss << fixed << setprecision(2) << this->m->getStock(on.stockSymbol)->getPrice();
        /*Get the formatted price out of the string stream and add the "$" symbol*/
        string fixedPrice = "$" + ss.str();
        /*Get the spaced word and add it to the retval table*/
        retVal += m.get_spacedWord(fixedPrice, longestLengthPrice);

        /*Add the space padded number of shares owned to the retval table*/
        retVal += "|";
        retVal += m.get_spacedWord(to_string(on.amountOwned), longestLengthShares);

        /*Add the formatted value of the stock on this iteration to the retval table*/
        retVal += "|";
        ss.str("");
        /*Fix the precision to only two decimal places*/
        ss << fixed << setprecision(2) << (this->m->getStock(on.stockSymbol)->getPrice()*on.amountOwned);
        fixedPrice = "$" + ss.str();
        retVal += m.get_spacedWord(fixedPrice, longestStockShares);

        /*Add a new line to the retval table*/
        retVal += "|";
        retVal += "\n";
    }

    /*Add the bottom seperator to the retval table*/
    retVal += sep;

    /*Return the created retval string*/
    return retVal;

}