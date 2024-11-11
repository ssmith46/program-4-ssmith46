#include "StockPortfolio.h"
#include "Stock.h"
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

int StockPortfolio::howMuchStockOwned(string symbol){
    int entries = this->portEnts.size();
    Struct PortfolioEntry pe;
    for (int i = 0; i<entries; i++){
        pe = this->portEnts.at(this->portEnts.begin()+i);
        //If this is true, then found that stock
        if (pe.stock.getSymbol().compare(symbol) == 0){
            return pe.amountOwned;
        }
    }
    //None of that stock is currently owned by the trader
    return 0;
}

void StockPortfolio::sellStock(string symbol, int amount){
    int entries = this->portEnts.size();
    Struct PortfolioEntry pe;
    for (int i = 0; i<entries; i++){
        pe = this->portEnts.at(this->portEnts.begin()+i);
        //Check if symbol name matches, and the trader actually owns shares for that stock
        if ((pe.stock.getSymbol().compare(symbol) == 0) && (pe.amountOwned != 0)){
            if (pe.amountOwned < amount){
                cout << "Hmm, it seems that you only own : " << pe.amountOwned << " shares. would you like to sell them all?" << endl;
                cout << "[yes, no] > ";
                string answer;
                cin >> answer;
                while ((answer.compare("yes") != 0) && (answer.compare("no") != 0)){
                    cout << "That wasn't an option. Please try again." << endl;
                    cout << "[yes, no] > ";
                    cin >> answer;
                }
                if (answer.compare("yes") == 0) {
                    //Will need to update in all correct spots:
                        //The stock shares left for sale
                        //The trader's account balance
                        //The portfolio entry
                } else { //answer == "no"
                    //May want to print a confirmation that stocks haven't been sold here
                    return;
                }
            } else { //They own more stocks than they want to sell. Should probably sell them.

            }
        }
    }
    //Since returning if stocks get sold, can presume that they don't own any of that stock if they make it here
    cout << "Hmm, it seems that you don't own any of that stock. Please try selling a different stock that you own." << endl;
}


void printStocks(){
    int entries = this->portEnts.size();
    Struct PortfolioEntry pe;
    string symbol;
    int amount;
    double price;
    int ws = 4
    cout << set(ws) << "Symbol" << set(ws) << "Shares" << set(ws) << "Value" << endl;

    for (int i = 0; i<entries; i++){
        pe = this->portEnts.at(this->portEnts.begin()+i);
        symbol = pe.stock.getSymbol();
        amount = pe.amountOwned;
        price = pe.stock.getPrice();
        cout << set(ws) << symbol << set(ws) << amount << set(ws) << setprecision(2) << (price*amount) << endl;
    }
}


