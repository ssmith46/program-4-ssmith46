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

MistakeCommand::MistakeCommand(vector<string> args, Market *m, Simulator *s){
    this->args = args;
    this->m = m;
    this->s = s;
}

void MistakeCommand::execute(){
    cout << "Command Executed.";
}