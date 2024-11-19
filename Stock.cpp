#include "Stock.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

Stock::Stock(string symbol, double price, int shares){
    this->symbol = symbol;
    this->price = price;
    this->shares = shares;
    this->growthSymbol = '+';
    this->lastChange = 0.0;
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

void Stock::setLastChange(double change){
    this->lastChange = change;
}

double Stock::getLastChange(){
    return this->lastChange;
}

double Stock::operator*=(double amountToChangeBy){
    double change = this->getPrice();
    change *= amountToChangeBy;
    this->price += change;
    if (amountToChangeBy < 0){
        this->setGrowthSymbol('-');
    } else {
        this->setGrowthSymbol('+');
    }
    this->setLastChange(amountToChangeBy);
    return this->price;
}

string Stock::toString(){
    string retVal = "";
    stringstream s(retVal);
    s << setw(7) << this->getSymbol();
    s << setw(3);
    if (this->getLastChange() > 0){
        s << this->getGrowthSymbol();
    } else {
        s << " ";
    }
    s << setprecision(2) << fixed << (this->getLastChange()*100) << "%";
    s << " ";
    s << setw(5) << setprecision(2) << fixed << (this->getPrice());
    
    string piece = "";
    while (s >> piece){
        retVal += piece + " ";
    }

    return retVal;
}

int stockTest(){
    Stock s = Stock("TSL", 216.8, 100);
    
    cout << "Should be TSL: " << s.getSymbol() << endl;
    cout << "Should be 216.8: " << s.getPrice() << endl;
    cout << "Should be 100: " << s.getShares() << endl;
    cout << "Should be '+': " << s.getGrowthSymbol() << endl;
    
    cout << endl << endl << endl;
    cout << "New Stock Growth Test:" << endl;

    
    srand(12);
    int randNum;
    double growth;
    for (int i = 0; i<5; i++){
        randNum = rand() % 10;
        if (randNum % 2 == 0){
            growth = -1;
        } else {
            growth = 1;
        }
        growth *= (randNum/(double) 10);

        cout << i << ": growth is: " << growth << endl;
        s *= growth;
        cout << s.toString() << endl << endl;
    }




    return 0;
}
