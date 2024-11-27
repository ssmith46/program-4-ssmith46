/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: November 26, 2024
 * 
 * File: Stock.cpp
 * Purpose: Contains the implementation of the 'Stock' class.
*/
#include "Stock.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

/**
* Constructor for a stock object
* 
* @param symbol -> The unique symbol for that stock. 
* @param price -> The current price of that stock.
* @param shares -> The number of remaining shares left of that stock.
*/
Stock::Stock(string symbol, double price, int shares){
    /*Initialize all the fields of a stock.*/
    this->symbol = symbol;
    this->price = price;
    this->shares = shares;
    this->growthSymbol = '+';
    this->lastChange = 0.0;
}

/**
* A setter for a stock's symbol
* 
* @param symbol -> The symbol to set as the stock's symbol.
*/
void Stock::setSymbol(string symbol){
    this->symbol = symbol;
}

/**
* A getter for a stock's symbol
* 
* @return -> The symbol of that stock.
*/
string Stock::getSymbol(){
    return this->symbol;
}

/**
* A setter for a stock's price
* 
* @param -> The price to set as the stock's current price.
*/
void Stock::setPrice(double price){
    this->price = price;
}

/**
* A getter for the current price of a stock. 
* 
* @return -> The current price of a stock.
*/
double Stock::getPrice(){
    return this->price;
}

/**
* A setter for the number of shares a stock has left.
* 
* @param amount -> The number of shares to set as how many shares are left.
*/
void Stock::setShares(int amount){
    this->shares = amount;
}

/**
* A getter for the number of shares a stock has left. 
* 
* @return -> The number of shares a stock has left.
*/
int Stock::getShares(){
    return this->shares;
}

/**
* An adder for the number of shares a stock has left.
* 
* @param amount -> The number of shares to add for a stock having left.
*/
void Stock::addShares(int amount){
    this->shares += amount;
}

/**
* A subtractor for the number of shares a stock has left. 
* 
* @param amount -> The number of shares to subtract from a stock having left.
*/
void Stock::removeShares(int amount){
    this->shares -= amount;
}

/**
* A setter for the growth symbol of a stock. 
* 
* @param symbol -> The symbol to change the stock's growth symbol to.
*/
void Stock::setGrowthSymbol(char symbol){
    this->growthSymbol = symbol;
}

/**
* A getter for the growth symbol of a stock. 
* 
* @return -> The growth symbol of a stock based on the last change.
*/
char Stock::getGrowthSymbol(){
    return this->growthSymbol;
}

/**
* A setter for setting the last price change that a stock experienced.
* 
* @param change -> The percent change that the stock underwent.
*/
void Stock::setLastChange(double change){
    this->lastChange = change;
}

/**
* A getter for the last change that a stock underwent. 
* 
* @return -> The percent change that a stock last underwent.
*/
double Stock::getLastChange(){
    return this->lastChange;
}

/**
* An operator that allows a stock to be updated according to a percent change.
* 
* @return -> The new price of the stock.
*/
double Stock::operator*=(double amountToChangeBy){
    /*Calculate the literal change of the stock price.*/
    double change = this->getPrice();
    change *= amountToChangeBy;

    /*Make sure stock price doesn't dip below or to zero, as it can't grow from that point.*/
    if (this->getPrice() - change <= 0){
        this->price = 0.01;
    } else {
        this->price += change;
    }

    /*Update the Growth symbol*/
    if (amountToChangeBy < 0){
        this->setGrowthSymbol('-');
    } else {
        this->setGrowthSymbol('+');
    }

    /*Update the last change amount.*/
    this->setLastChange(amountToChangeBy);

    /*Return the new price.*/
    return this->price;
}

/**
* A toString method that allows a stock to be transformed into a human readable format.
* 
* @return -> The string equivalent of the stock object.
*/
string Stock::toString(){
    /*Create a string that will be returned.*/
    string retVal = "";

    /*Create a stringStream and give the return string as input.*/
    stringstream s(retVal);

    /*Set whitespace for formatting, and add the symbol to the string.*/
    s << setw(7) << this->getSymbol();

    /*Set whitespace for formatting, and add the growth symbol.*/
    s << setw(3);
    if (this->getLastChange() > 0){
        s << this->getGrowthSymbol();
    } else {
        s << " ";
    }

    /*Set the precision, then put the percent change of the last price change.*/
    s << setprecision(2) << fixed << (this->getLastChange()*100) << "%";

    /*Add a space, whitespace, then the current price of the stock.*/
    s << " ";
    s << setw(5) << setprecision(2) << fixed << (this->getPrice());
    
    /*Get all the pieces out of the string stream, and put them in the retVal string.*/
    string piece = "";
    while (s >> piece){
        retVal += piece + " ";
    }

    /*Return the formatted string.*/
    return retVal;
}