#ifndef Trader_H
#define Trader_H

#include <string>
#include "Stock.h"

using namespace std;

class Trader {
    public:
        Trader(string name, string username, double balance);
        void setName(string name);
        string getName();
        void setBalance(double balance);
        double getBalance();
        void buyStock(Stock stock, int quantity);
    private:
        string name;
        string username;
        double balance;
};
#endif
