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