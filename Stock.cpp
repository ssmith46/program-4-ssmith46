#include "Stock.h"
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

Stock::Stock(string symbol, double price, int shares){
    this->symbol = symbol;
    this->price = price;
    this->shares = shares;
    this->growthSymbol = '+';
}

void Stock::setSymbol(string symbol){
    this->symbol = symbol;
}

string Stock::getSymbol(){
    return this->symbol;
}

void Stock::setPrice(double price){
    this->price = price;
}

double Stock::getPrice(){
    return this->price;
}

void Stock::setShares(int amount){
    this->shares = amount;
}

int Stock::getShares(){
    return this->shares;
}

void Stock::addShares(int amount){
    this->shares += amount;
}

void Stock::removeShares(int amount){
    this->shares -= amount;
}

void Stock::setGrowthSymbol(char symbol){
    this->growthSymbol = symbol;
}

char Stock::getGrowthSymbol(){
    return this->growthSymbol;
}

double Stock::operator*(double amountToGrowBy){
    this->price *= amountToGrowBy;
    return this->price;
}

int main(){
    Stock s = Stock("TSL", 216.8, 100);
    
    cout << "Should be TSL: " << s.getSymbol() << endl;
    cout << "Should be 216.8: " << s.getPrice() << endl;
    cout << "Should be 100: " << s.getShares() << endl;
    cout << "Should be '+': " << s.getGrowthSymbol() << endl;
    
    cout << endl << endl << endl;
    cout << "New Stock Growth Test:" << endl;

    
    srand(12);

    for (int i = 0; i<3; i++){
        cout << rand()% << endl;
    }





    return 0;
}
