/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: November 26, 2024
 * 
 * File: MistakeCommand.cpp
 * Purpose: Contains the implementation of the abstract 'MistakeCommand' class.
*/
#include "Command.h"
#include "MistakeCommand.h"
#include "Market.h"
#include "CommandFactory.h"
#include "Simulator.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/**
* The constructor for a Mistake Command object.
* 
* @param args -> The arguments that lead to the mistake command.
* @param m -> The market that the command can influence.
* @param s -> The simulator that the command can influence.
*/
MistakeCommand::MistakeCommand(vector<string> args, Market *m, Simulator *s, CommandFactory *cf){
    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}

/**
* This method overrides the base Command class's execute method.
* In this case, an error message is displayed to the user to indicate
* that their input wasn't understood.
*/
void MistakeCommand::execute(){
    /*Indicate that their input wasn't understood and give nudge towards help*/
    cout << endl << "Hmm, I don't know how to do that." << endl;
    cout << "For help on what I can do, enter: options" << endl;
}