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
#include "CommandFactory.h"
#include <vector>

using namespace std;

/** Sets the data member Simulator
* 
* @param s -> The simulator that commands can manipulate
*/
void CommandFactory::setSimulator(Simulator s){
    this->s = s;
}

/** Access to the Simulator
* 
* @return -> The simulator for this CommandFactory
*/
Simulator CommandFactory::getSimulator(){
    return this->s;
}

/** Sets the data member Market
* 
* @param s -> The market that commands can manipulate
*/
void CommandFactory::setMarket(Market m){
    this->m = m;
}

/**
* Access to the Market
* 
* @return -> The Market for this CommandFactory
*/
Market CommandFactory::getMarket(){
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