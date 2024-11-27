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
MistakeCommand::MistakeCommand(vector<string> args, Market *m, Simulator *s){
    this->args = args;
    this->m = m;
    this->s = s;
}

/**
* This method overrides the base Command class's execute method.
*/
void MistakeCommand::execute(){
    /*Can change later to be more specific about why command failed.*/
    cout << endl << "Mistake Command Executed." << endl;
}