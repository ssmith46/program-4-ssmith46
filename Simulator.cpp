/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: November 26, 2024
 * 
 * File: Simulator.cpp
 * Purpose: Contains the implementation of the 'Simulator' class.
*/
#include "Trader.h"
#include "Stock.h"
#include "Simulator.h"
#include "CommandFactory.h"
#include "Market.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

/**
* The constructor used to instantiate a Simulator object.
*/
Simulator::Simulator(Market m){
    this->market = m;
    this->simulatorName = "";
}

/**
* A method used to set the CommandFactory of the Simulator. 
* 
* @param cf -> The command factory used for creating commands during the simulation.
*/
void Simulator::setCommandFactory(CommandFactory cf){
    this->cf = cf;
}

/**
* A method used to set the name of the simulation run.
* 
* @param name -> The name to set the simulation run to.
*/
void Simulator::setSimulatorName(string name){
    this->simulatorName = name;
}

/**
* A method used to retreive the name of the simulation run.
* 
* @return -> the name of the simulation run.
*/
string Simulator::getSimulatorName(){
    return this->simulatorName;
}

/**
* The method used to get a user logged in as a particular trader.
*/
void Simulator::loginScreen(){
    /** NOTE: Empty for now, but will add features later. */
}

/**
* This function is used to get a line of input from the user, and convert
* it into a command that can then be executed to do what they want. 
* 
* @return -> A command that can be used to change the simulation. 
*/
Command Simulator::getNextCommand(){

    /** NOTE: This function doesn't do what it actually should yet,
      but this will be changed in future iterations.*/


    /*Create a variable for the line of input from the user.*/
    string line;
    /*Indicate to user where to type.*/
    cout << "> ";
    /*Get a line of input from the user.*/
    getline(cin, line);
    /*Create a variable for all the words in the entered command*/
    vector<string> allParts;
    /*Keep looping until the user enters 'done'*/
    while (line.compare("done") != 0){
        /*Get the words of the line.*/
        allParts = this->cf.parseLine(line);
        /*Iterate through all the words and print them out.*/
        for (int i = 0; i<allParts.size(); i++){
            cout << "Piece " << (i+1) << ": " << allParts.at(i) << endl;
        }
        /*Indicate where the user can type.*/
        cout << endl << "> ";
        /*Get the next line of input from the user.*/
        getline(cin, line);
    }
}

/*The actual execution of the entire simulator.*/
int main(){
    
    /*Create the Market for the Simulation.*/
    Market m = Market();
    /*Create the Simulator for the Simulation.*/
    Simulator s = Simulator(m);
    /*Create the CommandFactory for the Simulation.*/
    CommandFactory cf = CommandFactory();

    /*Finish setting up the CommandFactory with the market and simulator*/
    cf.setMarket(m);
    cf.setSimulator(s);

    /*Set the CommandFactory as the Simulation's Command Factory for the Simulation.*/
    s.setCommandFactory(cf);


    /*Get the next command to execute (will change this later).*/
    s.getNextCommand();


    return 0;
}