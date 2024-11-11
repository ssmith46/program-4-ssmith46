#ifndef Market_H
#define Market_H

#include <string>
#include <vector>


#include <iostream>












#include <fstream>

#include "Stock.h"

using namespace std;

class Market {
    public:
        bool hydrateStocks(const ifstream in);
        void printAllStocks();
        void addStock(Stock toAdd);
        Stock getStock(string symbol);
    private:
        vector<Stock> allStocks;
        
};
#endif
