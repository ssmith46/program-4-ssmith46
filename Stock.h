#ifndef Stock_H
#define Stock_H
#include <iostream>
#include <string>
using namespace std;

class Stock {
    public:
        Stock(string symbol, double price, int shares);
        void setSymbol(string symbol);
        string getSymbol();
        void setPrice(double price);
        double getPrice();
        void setShares(int amount);
        int getShares();
        void addShares(int amount);
        void removeShares(int amount);
        void setGrowthSymbol(char Symbol);
        char getGrowthSymbol();
    private:
        string symbol;
        double price;
        int shares;
        char growthSymbol;
};
#endif
