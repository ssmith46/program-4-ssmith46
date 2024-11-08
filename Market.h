#ifndef Market_H
#define Market_H
#include <iostream>
#include <string>
#include <vector>
#include <ifstream>

using namespace std;

class Market {
    public:
        bool hydrateStocks(ifstream in);
        void printAllStocks();
        void addStock(Stock toAdd);
        Stock getStock(string symbol);
    private:
        vector allStocks;
        
}
#endif
