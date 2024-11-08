#ifndef Trader_H
#define Trader_H
#include <iostream>
#include <string>
using namespace std;

class Trader {
    public:
        void setName(string name);
        string getName();
        void setBalance(double balance);
        double getBalance();    
    private:
        string name;
        double balance;
};
#endif
