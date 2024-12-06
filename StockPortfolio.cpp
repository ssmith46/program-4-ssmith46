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
#include "Stock.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

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
    /*Calculate the size of the portfolio*/
    int entries = this->portEnts.size();
    /*Create a variable for referring the portfolio entry on.*/
    struct PortfolioEntry pe;
    /*Create a variable for the symbol of a Stock.*/
    string symbol;
    /*Create a variable for the amount of a Stock that is owned.*/
    int amount;
    /*Create a variable for the current price of a Stock.*/
    double price;
    /*Define the shitespace amount to be between each column.*/
    int ws = 4;
    /*Create a string for the return value of the stock portfolio.*/
    string retVal = "";
    /*Create a stringStream and give the return string as input.*/
    stringstream s(retVal);

    /*Add text to the stringStream.*/
    s << setw(ws) << "Symbol" << setw(ws) << "Shares" << setw(ws) << "Value" << endl;

    /*Iterate through all the entries in the portfolio.*/
    for (int i = 0; i<entries; i++){
        /*Get the portfolio entry on.*/
        pe = this->portEnts.at(i);
        /*Get data about the portfolio entry, and fill variables.*/
        symbol = pe.stock->getSymbol();
        amount = pe.amountOwned;
        price = pe.stock->getPrice();
        /*Put the data into the string stream.*/
        s << setw(ws) << symbol;
        s << setw(ws) << amount << setw(ws) << setprecision(2) << (price*amount) << endl;
    }

    /*Get all the pieces out of the string stream, and put them in the retVal string.*/
    string piece = "";
    while (s >> piece){
        retVal += piece + " ";
    }

    /*Return the portfolio string, but get rid of the last new line character.*/
    return retVal.substr(0, retVal.length()-1);
}