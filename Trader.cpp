#include "Trader.h"
#include <iostream>
#include <string>

using namespace std;

Trader::Trader(string name, string username, double accountBalance){
    this->name = name;
    this->username = username;
    this->accountBalance = accountBalance;
}

void Trader::setName(string name){
    this->name = name;
}

string Trader::getName(){
    return this->name;
}

void Trader::setBalance(double balance){
    this->balance = balance;
}

double Trader::getBalance(){
    return this->balance;
}

void Trader::buyStock(Stock stock, int amount){
    
}

int main(){
    Trader t = Trader();
    t.setName("Tony");
    cout << "Should be Tony: " << t.getName() << endl;
    t.setBalance(129.8);
    cout << "Should be 129.8: " << t.getBalance() << endl;
    return 0;
}
