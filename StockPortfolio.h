#ifndef StockPortfolio_H
#define StockPortfolio_H

#include <string>
#include <iostream>
#include <vector>
#include "Stock.h"
#include "Trader.h"

using namespace std;
struct PortfolioEntry {
    Stock stock;
    int amountOwned;
};

class StockPortfolio {
    public:
        //See if some of that stock is already owned by the trader
        //Show how many of that stock the trader owns
        //Will be 0 if none owned
        int howMuchStockOwned(string symbol);
        //Need to update the Portfolio entry, the trader balance, make sure not selling more than have, make sure they own that stock
        void sellStock(string symbol, int amount);
        void printStocks();
    private:
        //For definition see above struct
        vector<PortfolioEntry> portEnts;
        //The total value of all stocks in the portfolio
        double totalVal;
        Trader owner;
};
#endif
