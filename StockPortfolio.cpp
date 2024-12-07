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

StockPortfolio::StockPortfolio() { 
    this->totalVal = 0;
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
        if (pe.stock->getSymbol().compare(symbol) == 0){
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
string StockPortfolio::sellStock(string symbol, int amount){


    /*Calculate the size of the portfolio.*/
    int entries = this->portEnts.size();
    /*Create a variable for the currently on portEnt.*/
    struct PortfolioEntry pe;
    /*Iterate through all the portEnts in the portfolio.*/
    for (int i = 0; i<entries; i++){
        /*Get the currently on portEnt.*/
        pe = this->portEnts.at(i);
        /*Check if the symbol of this stock matches what is trying to be sold, and
          ensure that the trader actually owns some of that stock.*/
        if ((pe.stock->getSymbol().compare(symbol) == 0) && (pe.amountOwned != 0)){
            /*Check if they are trying to sell more than they have.*/
            if (pe.amountOwned < amount){

                /*Since they have less than they are trying to sell, see if they
                  would just like to sell all the stock that they currently have.*/
                cout << "Hmm, it seems that you only own : ";
                cout << pe.amountOwned << " shares. would you like to sell them all?" << endl;
                cout << "[yes, no] > ";

                /*Get the trader's answer*/
                string answer;
                cin >> answer;

                /*Check that they entered yes or no, loop if not*/
                while ((answer.compare("yes") != 0) && (answer.compare("no") != 0)){
                    cout << "That wasn't an option. Please try again." << endl;
                    cout << "[yes, no] > ";
                    cin >> answer;
                }
                /*Handle the case that they entered yes.*/
                if (answer.compare("yes") == 0) {
                    /*Update the correct spots:*/
                        /*The stock shares left for sale*/
                        /*The trader's account balance*/
                        /*The portfolio entry*/
                    return "Selling all shares of that stock.";
                } else { /*answer == "no"*/
                    /*Indicate that no stocks are being sold then.*/
                    return "Confirmed. Not selling any stocks.";
                }
            } else { /*They own more stocks than they want to sell. Sell them.*/
                return "Stocks sold successfully.";
            }
        }
    }
    /*If making it to here, they do not have any of that stock in their portfolio.*/
    return "Hmm, it seems that you don't own any of that stock. Please try selling a different stock that you own.";
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
    PortfolioEntry on;
    int posFound = -1;
    string onSymbol;
    string symbolLookingFor = s->getSymbol();
    for (int i = 0; i < this->portEnts.size(); i++) {
        on = this->portEnts.at(i);
        onSymbol = on.stock->getSymbol();

        if (onSymbol.compare(symbolLookingFor) == 0) {
            posFound = i;
        }
    }

    /*This means need to create a new entry for that stock.*/
    if (posFound == -1) {
        PortfolioEntry newEnt;
        newEnt.stock = s;
        newEnt.amountOwned = amount;
        this->portEnts.push_back(newEnt);

        return "Successful Purchase.";
    }
    else {
        PortfolioEntry* updating = &(this->portEnts.at(posFound));
        updating->amountOwned += amount;
        return "Successful Purchase.";
    }

    return "Fail.";

}

/**
* Convert all of the currently owned stocks into human readable format, and return them. 
* 
* @return -> The human readable format of the worth of each stock. 
*/
string StockPortfolio::stocks_toString(){

    if (this->portEnts.size() == 0) {
        return "There are currently no stocks in your portfolio.\n";
    }

    string retVal = "";

    double totalValue = 0.00;
    /*Calculate the size of the portfolio.*/
    int entries = this->portEnts.size();
    /*Create a variable for the currently on portEnt.*/
    struct PortfolioEntry pe;
    for (int i = 0; i < entries; i++) {
        pe = this->portEnts.at(i);
        totalValue += (pe.stock->getPrice()*pe.amountOwned);
    }
    
    stringstream ss;
    ss << fixed << setprecision(2) << totalValue;

    retVal += "Total portfolio worth: $" + ss.str() + "\n";

    string symbolTitle = "Symbols";
    string changeTitle = "Last Value Change";
    string priceTitle = "Stock Prices";
    string sharesTitle = "Shares Own";
    string stockSharesTitle = "Stock Shares Worth";



    int longestLengthName = symbolTitle.length() + 1;
    int longestLengthPrice = priceTitle.length() + 1;
    int longestLengthShares = sharesTitle.length() + 1;
    int longestLastChange = changeTitle.length() + 1;
    int longestStockShares = stockSharesTitle.length() + 1;

    PortfolioEntry on;
    for (int i = 0; i < this->portEnts.size(); i++) {
        on = this->portEnts.at(i);
        if (on.stock->getSymbol().length() > longestLengthName) {
            longestLengthName = on.stock->getSymbol().length();
        }
        int places = 4;
        double price = on.stock->getPrice();
        while (price >= 1.0) {
            price *= .1;
            places += 1;
        }
        if (places > longestLengthPrice) {
            longestLengthPrice = places;
        }
        places = 1;
        int sharesOwned = on.amountOwned;
        while (sharesOwned >= 1.0) {
            sharesOwned *= .1;
            places += 1;
        }
        if (places > longestLengthShares) {
            longestLengthShares = places;
        }
        double lastChange = (on.stock->getLastChange()*100);
        places = 4;
        while (lastChange >= 1.0) {
            lastChange *= .1;
            places += 1;
        }
        if (places > longestLastChange) {
            longestLastChange = places;
        }
        places = 4;
        price = (on.stock->getPrice() * on.amountOwned);
        while (price >= 1.0) {
            price *= .1;
            places += 1;
        }
        if (places > longestStockShares) {
            longestStockShares = places;
        }
    }


    string sep = "";

    Market m;

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

    retVal += sep;

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

    retVal += sep;


    /*Iterate over all the stocks in the allStocks vector.*/
    for (int i = 0; i < this->portEnts.size(); i++) {
        /*Go through all the stocks in the simulation and get their 'to_string()' equivalents.*/
        /*This 'if' is to help format the string correctly with a '\n' character*/
        on = portEnts.at(i);
        retVal += "|";
        retVal += m.get_spacedWord(on.stock->getSymbol(), longestLengthName);
        retVal += "|";
        stringstream ss;
        double lastChange = on.stock->getLastChange();
        char changeSym = on.stock->getGrowthSymbol();
        if (changeSym == '-') {
            changeSym = ' ';
        }
        ss << fixed << setprecision(2) << lastChange;
        string fixedChange = changeSym + ss.str() + "%";
        retVal += m.get_spacedWord(fixedChange, longestLastChange);
        retVal += "|";
        ss.str("");
        ss << fixed << setprecision(2) << on.stock->getPrice();
        string fixedPrice = "$" + ss.str();
        retVal += m.get_spacedWord(fixedPrice, longestLengthPrice);
        retVal += "|";
        retVal += m.get_spacedWord(to_string(on.amountOwned), longestLengthShares);
        retVal += "|";
        ss.str("");
        ss << fixed << setprecision(2) << (on.stock->getPrice()*on.amountOwned);
        fixedPrice = "$" + ss.str();
        retVal += m.get_spacedWord(fixedPrice, longestStockShares);
        retVal += "|";
        retVal += "\n";
    }

    retVal += sep;

    return retVal;

}