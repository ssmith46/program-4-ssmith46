/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 7, 2024
 *
 * File: AddStockCommand.cpp
 * Purpose: Contains the implementation of the 'AddStockCommand' class.
*/
#include "Command.h"
#include "CommandFactory.h"
#include "AddStockCommand.h"
#include "Market.h"
#include "Simulator.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

using namespace std;

/**
* The constructor for an Add Stock Command object.
*
* @param args -> The arguments that lead to the add stock command creation.
* @param m -> The market that the command can influence.
* @param s -> The simulator that the command can influence.
*/
AddStockCommand::AddStockCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf) {
    /*Assign given arguments to object data members*/

    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}

/**
* This method overrides the base Command class's execute method.
* This method prompts a user for attributes of a stock, and creates that stock
* adding it to the market.
*/
void AddStockCommand::execute() {

    /*The new stock symbol entered by the user*/
    string strStockSymbol = "";
    /*The new stock price entered by the user*/
    double currPrice = -1.0;
    /*The new stock number of shares, entered by the user*/
    int numShares = -1;

    /*First get the name of the stock that would like to created*/

    /*The string for getting input from the user*/
    string line;
    /*The words of the input gotten from the user*/
    vector<string> allParts;

    /*Format screen*/
    std::cout << endl;

    /*Keep looping until the new stock symbol has been collected*/
    while (strStockSymbol.compare("") == 0) {
        /*Prompt the user for input*/
        std::cout << "What would you like the symbol of this stock to be?" << endl;
        std::cout << "> ";
        getline(cin, line);
        /*Parse the input from the user*/
        allParts = this->cf->parseLine(line);
        /*Check and indicate if user gives no input.*/
        if (allParts.size() == 0) {
            std::cout << endl;
            std::cout << "Your stock symbol must be at least one character long.";
            std::cout << endl;
        }
        /*Check and indicate if the user entered too many words*/
        else if (allParts.size() > 1) {
            std::cout << endl;
            std::cout << "Please ensure the stock symbol is only one word long. (no spaces)";
            std::cout << endl;
        }
        /*Check and exit if user wants to cancel*/
        else if (Command::isCancel(allParts.at(0))) {
            std::cout << endl;
            std::cout << "Canceling stock creation.";
            std::cout << endl;
            return;
        }
        /*Check and indicate if using invalid stock name*/
        else if ((allParts.at(0).compare(";;;") == 0) ||
                (allParts.at(0).compare("l") == 0))
        {
            std::cout << endl;
            std::cout << "Hmm, please pick a different name for your stock.";
            std::cout << endl;
        }
        /*This is the case that the user has entered a symbol for a stock*/
        else {
            
            /*Check if that stock already exists*/
            if (this->m->getStock(allParts.at(0)) == nullptr) {
                /*This means the stock doesn't exist*/
                /*Collect the symbol*/
                strStockSymbol = allParts.at(0);
            }
            /*Indiciate that a stock already using that symbol exists.*/
            else {
                std::cout << endl;
                std::cout << "It seems that a stock already exists with that symbol. ";
                std::cout << "Please try a different stock symbol.";
                std::cout << endl;
            }
        } 
    }

    /*Format screen*/
    std::cout << endl;


    /*Figure out how many shares would like to be added*/

    /*Keep looping until the number of shares has been collected*/
    while (numShares == -1) {
        /*Prompt the user for input*/
        std::cout << "How many shares would you like for the ";
        std::cout << strStockSymbol << " stock to have?" << endl;
        std::cout << "> ";
        /*Get input from the user*/
        getline(cin, line);
        /*Parse the line for arguments*/
        allParts = this->cf->parseLine(line);
        /*Check and indicate if use didn't enter any arguments.*/
        if (allParts.size() != 1) {
            std::cout << endl;
            std::cout << "Please ensure you enter one number." << endl;
        }
        /*Check and exit if user wants to cancel*/
        else if (Command::isCancel(allParts.at(0))) {
            std::cout << endl;
            std::cout << "Canceling stock creation.";
            std::cout << endl;
            return;
        }
        /*Correct number of words given by user*/
        else {
            try {
                /*Attempt to parse string to integer*/
                int trialNum = stoi(allParts.at(0));
                /*Check and indicate if the entered number of shares is negative*/
                if (trialNum < 0) {
                    std::cout << endl;
                    std::cout << "The number of shares must be a positive value." << endl;
                }
                /*Check and indicate if the entered number is too large*/
                else if (trialNum > 99999999) {
                    std::cout << endl;
                    std::cout << "Please ensure the number of shares is less than 1 billion.";
                    std::cout << endl;
                }
                /*Collect valid number of shares*/
                else {
                    numShares = trialNum;
                }
            }
            /*Catch exception if user didn't enter a valid integer*/
            catch (...) {
                std::cout << endl;
                std::cout << "Please enter a valid integer for the number of shares.";
                std::cout << endl;
                
            }
        }

    }
    
    /*Format screen*/
    std::cout << endl;


    /*Figure out current price*/

    /*Keep looping until the stock's starting price has been collected*/
    while (currPrice < 0) {
        /*Prompt the user for input*/
        std::cout << "What would you like the starting price of ";
        std::cout << strStockSymbol << " stock to be?" << endl;
        std::cout << "> ";
        /*Get input from user*/
        getline(cin, line);
        /*Get the parts of the entered user input*/
        allParts = this->cf->parseLine(line);
        /*Check and indicate if user didn't enter any words.*/
        if (allParts.size() == 0) {
            std::cout << endl;
            std::cout << "Please enter at least one number for the price of the stock.";
            std::cout << endl;
        }
        /*Indicate if the user entered too many words in input*/
        else if (allParts.size() > 1) {
            std::cout << endl;
            std::cout << "Please enter only one number for the price of the stock.";
            std::cout << endl;
        }
        /*Indicate and exit if user wants to cancel*/
        else if (Command::isCancel(allParts.at(0))) {
            std::cout << endl;
            std::cout << "Canceling stock creation.";
            std::cout << endl;
            return;
        }
        /*Valid number of words in input*/
        else {
            try {
                /*Get the first word from the arguments (the price)*/
                string strPrice = allParts.at(0);
                /*Check and trim for '$' if applicable*/
                if (strPrice.substr(0, 1).compare("$") == 0) {
                    strPrice = strPrice.substr(1, strPrice.length() - 1);
                }
                /*Attempt to parse the user input into double*/
                double entered = stod(strPrice);
                /*Check that the double meets a minimum value of one penny*/
                if (round(entered / 0.01) * 0.01 < .01) {
                    std::cout << endl;
                    std::cout << "Please start the price at at least one penny.";
                    std::cout << endl;
                }
                /*Store the user input as the new stock price*/
                else {
                    currPrice = entered;
                }
            }
            /*Catch exception if user input wasn't a valid double*/
            catch (...) {
                std::cout << endl;
                std::cout << "Please enter a valid decimal value for the price of the stock.";
                std::cout << endl;
            }
        }
    }

    /*Format screen*/
    std::cout << endl;
    /*Indicate to the user that the stock creation process has begun*/
    std::cout << "Creating stock... ";

    /*Create a new stock object with the data given by the user*/
    Stock newStock(strStockSymbol, currPrice, numShares);
    /*Add this stock to the market of the simulation*/
    this->m->addStock(newStock);

    /*Indicate that the stock was created successfully*/
    std::cout << "Stock created!" << endl;

    return;

}