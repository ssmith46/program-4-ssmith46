#ifndef Market_H
#define Market_H

#include <string>
#include "Stock.h"
#include <vector>

using namespace std;

class Market {
    public:
        bool hydrateStocks(ifstream& in);
        void printAllStocks();
        void addStock(Stock toAdd);
        Stock getStock(string symbol);
    private:
        vector<Stock*> stocks;
        
};
#endif
