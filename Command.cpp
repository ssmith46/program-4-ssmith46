/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: November 26, 2024
 * 
 * File: Command.cpp
 * Purpose: Contains the implementation of the abstract 'Command' class.
*/
#include "Command.h"
#include "Market.h"
#include "Simulator.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Command::Command(){ }

/**
* Constructor for the the Command class.
* 
* @param args -> The arguments to execute the Command.
* @param m -> The Market the command manipulates upon execution.
* @param s -> The Simulator the command manipulates upon execution.
*/
Command::Command(vector<string> args, Market *m, Simulator *s, CommandFactory *cf){
    this->m = m;
    this->s = s;
    this->cf = cf;
    this->args = args;
}

/**
* The execute method for the command. Virtual, and will be overrided
* by child classes that inherit from it.
*/
void Command::execute(){ cout << "Parent" << endl; /*Override in children*/ }

/**
* Checks whether the user's entered command is "cancel" or some variant.
*
* @param word -> The word to check whether it's a cancel or not.
* @return -> A boolean on whether the user wishes to cancel the transaction or not.
*/
bool Command::isCancel(string word) {
    /*If it's a cancel word, return true*/
    if ((word.compare("cancel") == 0) ||
        (word.compare("Cancel") == 0) ||
        (word.compare("c") == 0) ||
        (word.compare("C") == 0) ||
        (word.compare("stop") == 0)) {
        return true;
    }
    return false;
}

/**
* Get the name of the stock the user would like to purchase.
*
* @return -> A string for the stock the user would like to purchase/sell.
*/
string Command::whichStock() {

    /*The string to return to the client code.*/
    string retVal = "";

    /*Create a variable for the line of input from the user.*/
    string line;
    /*Parse the line for the stock that the user would like buy*/
    vector<string> parts;

    while (1) {
        cout << endl;
        cout << "Which stock would you like to buy shares of? ('l' to list options)";
        cout << endl;
        /*Indicate to user where to type.*/
        cout << "> ";
        /*Get a line of input from the user.*/
        getline(cin, line);
        parts = this->cf->parseLine(line);

        while (parts.size() != 1) {

            cout << endl;
            cout << "A stock's symbol should be only one word long. ";
            cout << "Please try again." << endl;
            cout << "Which stock would you like to buy shares of? ('l' to list options)";
            cout << endl;

            /*Indicate to user where to type.*/
            cout << "> ";
            /*Get a line of input from the user.*/
            getline(cin, line);

            parts = this->cf->parseLine(line);
        }

        /*Check if the user changed their mind and would like to cancel*/
        if (this->isCancel(parts.at(0))) {
            cout << endl;
            cout << "Transaction canceled." << endl;
            return ";;;";
        }

        if (parts.at(0).compare("l") == 0) {
            cout << endl;
            cout << "Listing stocks...";
        }
        else {

            Stock* s = this->m->getStock(parts.at(0));
            if (s == nullptr) {
                cout << endl;
                cout << "That doesn't seem to be a valid stock name. Please try again.";
            }
            else {
                return parts.at(0);
            }
        }
    }
}

/**
* Get the number of shares of a stock the user would like to purchase/sell.
*
* @return -> An int for the number of shares the user would like to purchase/sell.
*/
int Command::howMany(string stockName) {
    /*The number of shares of that stock to buy*/
    int retVal = 0;

    /*Create a variable for the line of input from the user.*/
    string line;
    /*Parse the line for the stock that the user would like buy*/
    vector<string> parts;

    while (1) {
        cout << endl;
        cout << "How many shares of " << stockName << " stock would you like to buy?";
        cout << endl;
        /*Indicate to user where to type.*/
        cout << "> ";
        /*Get a line of input from the user.*/
        getline(cin, line);
        parts = this->cf->parseLine(line);
        while (parts.size() != 1) {
            cout << endl;
            cout << "There should only be one argument for the number of stocks to buy. ";
            cout << "Please try again." << endl;

            /*Indicate to user where to type.*/
            cout << "> ";
            /*Get a line of input from the user.*/
            getline(cin, line);

            parts = this->cf->parseLine(line);
        }
        /*Check if the user changed their mind and would like to cancel*/
        if (isCancel(parts.at(0))) {
            cout << endl;
            cout << "Transaction canceled." << endl;
            return -1;
        }

        try {
            int numToBuy = stoi(parts.at(0));
            if (numToBuy == 0) {
                cout << endl;
                cout << "I mean sure. I guess you can buy none. Waste of both our times. ";
                cout << endl;
                return -1;
            }
            else if (numToBuy < 0) {
                cout << endl;
                cout << "The number of stocks to buy has to be a positive number. ";
                cout << "Please try again.";
            }
            else {
                /*Need to check that there are that many shares or more left for purchase*/
                int numSharesLeft = this->m->getStock(stockName)->getShares();
                if (numSharesLeft < numToBuy) {
                    cout << endl;
                    cout << "There are only " << numSharesLeft << " shares left. " << endl;
                    cout << "Please pick a number less than or equal to this total.";
                }
                else {
                    return numToBuy;
                }
            }
        }
        catch (const invalid_argument& e) {
            cout << endl;
            cout << "That doesn't seem to be a valid number of shares to buy." << endl;
            cout << "Please enter a valid integer value. ";
        }
        catch (const out_of_range& e) {
            cout << endl;
            cout << "That value seems to be too big. Please try a smaller one.";
        }

    }
}