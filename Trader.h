#ifndef Trader_H
#define Trader_H

#include <string>
#include "Stock.h"

using namespace std;

class Trader {
    public:
        Trader(string name, string username, double accountBalance);
        double getBalance();
        void setBalance(double balance);
        void setName(string name);
        string getName();
        void setUsername(string username);
        string getUsername();
        void buyStock(Stock stock, int quantity);
    private:
        string name;
        string username;
        double balance;
};
#endif
