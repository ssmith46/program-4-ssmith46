#ifndef Market_H
#define Market_H

#include <string>
#include "Stock.h"
#include <vector>

using namespace std;

class Market {
    public:
        string stocks_toString();
        bool addStock(Stock toAdd);
        Stock getStock(string symbol);
        void setMarketSeed(int seed);
        void setMarketViolence(int violence);
        void randomlyUpdateStocks();
        

        bool hydrateStocks(ifstream& in);
    private:
        vector<Stock*> allStocks;
        int randSeed;
        int marketViolence;
        
};
#endif
