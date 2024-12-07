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

/**
* A default constructor for the command class, so compiler is happy.
*/
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
* Get the symbol of the stock the user would like to interact with.
*
* @return -> A string for the stock the user would like to purchase/sell.
*/
string Command::whichStock(string prompt, string whichUse) {

    /*The string to return to the client code.*/
    string retVal = "";

    /*Create a variable for the line of input from the user.*/
    string line;
    /*Parse the line for the stock that the user would like interact with*/
    vector<string> parts;

    /*Loop exits when user enters valid stock name or cancels*/
    while (1) {
        /*Prompt the user for input using argument passed*/
        cout << endl;
        cout << prompt;
        cout << endl;
        /*Indicate to user where to type.*/
        cout << "> ";
        /*Get a line of input from the user.*/
        getline(cin, line);
        /*Parse the user input for words*/
        parts = this->cf->parseLine(line);

        /*Keep looping until the use enters only one word*/
        while (parts.size() != 1) {
            /*Indicate that the stock symbol should only be one word*/
            cout << endl;
            cout << "A stock's symbol should be only one word long. ";
            cout << "Please try again." << endl;
            /*Re-prompt the user for input*/
            cout << prompt;
            cout << endl;

            /*Indicate to user where to type.*/
            cout << "> ";
            /*Get a line of input from the user.*/
            getline(cin, line);
            /*Parse the user input for words*/
            parts = this->cf->parseLine(line);
        }

        /*Check if the user changed their mind and would like to cancel*/
        if (this->isCancel(parts.at(0))) {
            cout << endl;
            cout << "Transaction canceled." << endl;
            return ";;;";
        }
        /*Check if the user would like to see options for interact choices*/
        if (parts.at(0).compare("l") == 0) {
            cout << endl;
            /*Check whether should display the market*/
            if (whichUse.compare("buy") == 0) {
                /*Convert the market to a string*/
                cout << this->m->stocks_toString();
            }
            /*Or the user's stock portfolio*/
            else if (whichUse.compare("sell") == 0) {
                /*Get the logged in trader's stock portfolio and convert it to a string*/
                cout << this->s->getLoggedInTrader()->getPortfolio()->stocks_toString();
            }
            /*Shouldn't ever happen, but indicate if there's an error*/
            else {
                cout << "There was an issue listing out the stocks.";
            }
            
        }
        /*This means that the user entered a stock symbol*/
        else {
            /*Check that the stock symbol given exists in the market*/
            Stock* s = this->m->getStock(parts.at(0));
            /*This means that the stock doesn't exist in the market*/
            if (s == nullptr) {
                cout << endl;
                cout << "That doesn't seem to be a valid stock name. Please try again.";
            }
            /*Valid stock symbol entered, return the entered stock symbol*/
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
int Command::howManyShares(string stockName, string prompt) {
    /*The number of shares of that stock to buy/sell*/
    int retVal = 0;
    /*Create a variable for the line of input from the user.*/
    string line;
    /*Parse the line for the stock that the user would like buy*/
    vector<string> parts;

    /*Loop until user enters number of shares, or cancels*/
    while (1) {
        /*Prompt the user for input using argument passed*/
        cout << endl;
        cout << prompt;
        cout << endl;
        /*Indicate to user where to type.*/
        cout << "> ";
        /*Get a line of input from the user.*/
        getline(cin, line);
        /*Parse the user entered line for words*/
        parts = this->cf->parseLine(line);

        /*Keep looping until user enters only one word (hopefully integer)*/
        while (parts.size() != 1) {
            /*Indicate that the user entered too many/few arguemnts*/
            cout << endl;
            cout << "There should only be one argument for the number of stocks. ";
            cout << "Please try again." << endl;

            /*Indicate to user where to type.*/
            cout << "> ";
            /*Get a line of input from the user.*/
            getline(cin, line);
            /*Parse the user entered line for words*/
            parts = this->cf->parseLine(line);
        }
        /*Check if the user changed their mind and would like to cancel*/
        if (isCancel(parts.at(0))) {
            cout << endl;
            cout << "Transaction canceled." << endl;
            return -1;
        }
        /*Making it here means that there is only one word, hopefully integer*/
        try {
            /*Try to parse the user input into an integer*/
            int numToBuy = stoi(parts.at(0));
            /*Check that they entered 0*/
            if (numToBuy == 0) {
                cout << endl;
                cout << "I mean sure. I guess you can choose none. Wastes both our times. ";
                cout << endl;
                return -1;
            }
            /*Check that they entered a negative number*/
            else if (numToBuy < 0) {
                cout << endl;
                cout << "The number of stocks has to be a positive number. ";
                cout << "Please try again.";
            }
            /*This case is that they entered a valid number*/
            else {
                /*Need to check that there are that many shares or more left for purchase*/
                int numSharesLeft = this->m->getStock(stockName)->getShares();
                /*Indicate that there aren't that number of shares left to purchase.*/
                if (numSharesLeft < numToBuy) {
                    cout << endl;
                    cout << "There are only " << numSharesLeft << " shares left. " << endl;
                    cout << "Please pick a number less than or equal to this total.";
                }
                else {
                    /*Return the number of shares the user entered*/
                    return numToBuy;
                }
            }
        }
        /*Catch exception if user doesn't entere a valid integer*/
        /*Indicate that they need to enter an integer*/
        catch (const invalid_argument& e) {
            cout << endl;
            cout << "That doesn't seem to be a valid number of shares." << endl;
            cout << "Please enter a valid integer value. ";
        }
        /*Indicate that they entered a number that was way to big to be a C++ integer*/
        catch (const out_of_range& e) {
            cout << endl;
            cout << "That value seems to be too big. Please try a smaller one.";
        }

    }
}