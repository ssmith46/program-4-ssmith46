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

using namespace std;

/**
* Constructor for the the Command class.
* 
* @param args -> The arguments to execute the Command.
* @param m -> The Market the command manipulates upon execution.
* @param s -> The Simulator the command manipulates upon execution.
*/
Command::Command(vector<string> args, Market *m, Simulator *s){
    this->m = m;
    this->s = s;
    this->args = args;
}

/**
* The execute method for the command. Virtual, and will be overrided
* by child classes that inherit from it.
*/
void Command::execute(){ /*Override in children*/ }