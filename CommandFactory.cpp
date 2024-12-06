/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: November 26, 2024
 * 
 * File: CommandFactory.cpp
 * Purpose: Contains the implementation of the 'CommandFactory' class.
*/
#include <string>
#include <sstream>
#include "Market.h"
#include "Simulator.h"
#include "Command.h"
#include "MistakeCommand.h"
#include "BuyStockCommand.h"
#include "ListStocksCommand.h"
#include "LogoutCommand.h"
#include "CommandFactory.h"
#include <vector>

using namespace std;

/** Sets the data member Simulator
* 
* @param s -> The simulator that commands can manipulate
*/
void CommandFactory::setSimulator(Simulator *s){
    this->s = s;
}

/** Access to the Simulator
* 
* @return -> The simulator for this CommandFactory
*/
Simulator* CommandFactory::getSimulator(){
    return this->s;
}

/** Sets the data member Market
* 
* @param s -> The market that commands can manipulate
*/
void CommandFactory::setMarket(Market *m){
    this->m = m;
}

/**
* Access to the Market
* 
* @return -> The Market for this CommandFactory
*/
Market* CommandFactory::getMarket(){
    return this->m;
}

/**
 * Parse a line for the words on that line, getting rid of white space.
 * 
 * @param line -> The string in which the words will be stripped from.
 * @return -> A vector of strings, where each element is one word from the line.
 */
vector<string> CommandFactory::parseLine(string line){
    
    /*The variable to hold all the words in the line*/
    vector<string> allParts;
    /*The string currently being collected. (Chars since last whitespace.)*/
    string word = "";

    /*Iterate through all the chars in the line given as input*/
    for (int i = 0; i<line.length() + 1; i++){

        /*Check if on last char ('\n') and add word if so.*/
        if (i == line.length()){
            /*Only add word if there is content within it.*/
            if (word.compare("") != 0){
                allParts.push_back(word);
            }
        }

        /*Check if the next char is white space, meaning the word on can be added.*/
        else if ((line.substr(i, 1).compare(" ") == 0) || (line.substr(i, 1).compare("\t") == 0)){
            /*Check if the word has content before adding it.*/
            if (word.compare("") != 0){
                allParts.push_back(word);
                /*Reset the word collecting to the empty string.*/
                word = "";
            }
        /*In this case, just on a normal char so add it to the word collecting.*/
        } else {
            word += line.substr(i, 1);
        }
    }

    /*Returns the now complete vector with all the words.*/
    return allParts;
}

/**
* Takes a string as input and returns a command object that will fulfill
* the needs of that line of text.
* 
* @param line -> The line that contains info about the command to create,
* along with the parameters to fulfill that command.
*/
Command* CommandFactory::getCommand(string line) {
    /*Parse the line for all the words in the input*/
    vector<string> allParts;
    allParts = this->parseLine(line);

    /*Create the command pointer for returning*/
    Command* retVal;

    /*This is where the first mistake command check can occur*/
    if (allParts.size() < 1) {
        /*This will create a 'mistake' command for now. In future, branch based on the arguments*/
        retVal = new MistakeCommand(allParts, this->getMarket(), this->getSimulator(), this);
    }
    /*Handle the case that the user wants to execute a "buy" command*/
    else if ((allParts.size() == 2)
        &&
        (
            (allParts.at(0).compare("buy") == 0) ||
            (allParts.at(0).compare("Buy") == 0) ||
            (allParts.at(0).compare("purchase") == 0) ||
            (allParts.at(0).compare("Purchase") == 0)
            )
        &&
        (
            (allParts.at(1).compare("Stocks") == 0) ||
            (allParts.at(1).compare("stocks") == 0) ||
            (allParts.at(1).compare("Stock") == 0) ||
            (allParts.at(1).compare("stock") == 0))
        ) {

        /*Create a BuyStockCommand for the retval*/
        retVal = new BuyStockCommand(allParts, this->getMarket(), this->getSimulator(), this);
    }
    else if ((allParts.size() == 2)
        &&
        (
            (allParts.at(0).compare("see") == 0) ||
            (allParts.at(0).compare("view") == 0) ||
            (allParts.at(0).compare("See") == 0) ||
            (allParts.at(0).compare("View") == 0) ||
            (allParts.at(0).compare("list") == 0) ||
            (allParts.at(0).compare("List") == 0)
            )
        &&
        (
            (allParts.at(1).compare("stock") == 0) ||
            (allParts.at(1).compare("stocks") == 0) ||
            (allParts.at(1).compare("Stock") == 0) ||
            (allParts.at(1).compare("Stocks") == 0) ||
            (allParts.at(1).compare("market") == 0) ||
            (allParts.at(1).compare("Market") == 0)
        )) {
        /*Create a BuyStockCommand for the retval*/
        retVal = new ListStocksCommand(allParts, this->getMarket(), this->getSimulator(), this);
    }
    else if (
        (allParts.size() == 1)
        &&
        (
            (allParts.at(0).compare("logout") == 0) ||
            (allParts.at(0).compare("Logout") == 0)
        )) {
        /*Create a LogoutCommand for the retval*/
        retVal = new LogoutCommand(allParts, this->getMarket(), this->getSimulator(), this);
    }
    else {
        /*This will create a 'mistake' command for now. In future, branch based on the arguments*/
        retVal = new MistakeCommand(allParts, this->getMarket(), this->getSimulator(), this);
    }
    

    /*Return the created command*/
    return retVal;
}

Command CommandFactory::getBaseCommand() {
    vector<string> allParts;
    return Command(allParts, this->getMarket(), this->getSimulator(), this);
}