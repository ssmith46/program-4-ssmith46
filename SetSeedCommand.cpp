/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 7, 2024
 *
 * File: SetSeedCommand.cpp
 * Purpose: Contains the implementation of the 'SetSeedCommand' class.
*/
#include "Command.h"
#include "CommandFactory.h"
#include "SetSeedCommand.h"
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
* The constructor for a Set Seed Command object.
*
* @param args -> The arguments that lead to the set seed command.
* @param m -> The market that the command can influence.
* @param s -> The simulator that the command can influence.
*/
SetSeedCommand::SetSeedCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf) {
    /*Assign the arguments to the data members of the object*/

    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}

/**
* This method overrides the base Command class's execute method.
* In this case, the user is prompted for the seeds they would like to set
* the market to, and the market is changed accordingly
*/
void SetSeedCommand::execute() {
    /*Create a line for getting user input*/
    string line;
    /*Create a vector for getting user commands from input*/
    vector<string> allParts;
    /*Variable for the seed that the user would like to set*/
    int whichSeedSet = -1;
    /*Format the screen*/
    cout << endl;
    /*Keep looping until the user indicates which seed to set*/
    while (whichSeedSet == -1) {
        /*Prompt the user for which seed they would like to change*/
        cout << "Which seed would you like to set?" << endl;
        cout << "1. Random Seed" << endl;
        cout << "2. Market Violence" << endl;
        cout << "> ";
        /*Get the user input*/
        getline(cin, line);
        /*Parse the input for arguments*/
        allParts = this->cf->parseLine(line);
        /*Handles the case that the user didn't enter any arguments*/
        if (allParts.size() == 0) {
            cout << endl;
            cout << "It seems you didn't enter anything, please try again." << endl;
        }
        /*Handles the case the user entered one word*/
        else if (allParts.size() == 1) {
            /*Get the choice the user made*/
            string choice = allParts.at(0);
            /*Check and indicate if user wants to cancel*/
            if (Command::isCancel(choice)) {
                cout << endl;
                cout << "Canceling seed set.";
                cout << endl;
                return;
            }

            /*Handles the case that the user wants to change the random seed*/
            if (choice.compare("1") == 0) {
                whichSeedSet = 1;
            }
            else if (choice.compare("random") == 0) {
                whichSeedSet = 1;
            }
            else if (choice.compare("Random") == 0) {
                whichSeedSet = 1;
            }
            else if (choice.compare("seed") == 0) {
                whichSeedSet = 1;
            }
            else if (choice.compare("Seed") == 0) {
                whichSeedSet = 1;
            }

            /*Handles the case that the user wants to change the violence*/
            else if (choice.compare("2") == 0) {
                whichSeedSet = 2;
            }
            else if (choice.compare("violence") == 0) {
                whichSeedSet = 2;
            }
            else if (choice.compare("Violence") == 0) {
                whichSeedSet = 2;
            }
            else if (choice.compare("v") == 0) {
                whichSeedSet = 2;
            }
            else if (choice.compare("V") == 0) {
                whichSeedSet = 2;
            }
            /*Handles the case the user input wasn't understood*/
            else {
                cout << endl;
                cout << "Hmm, I don't understand. Please enter [1, 2] for your choice.";
                cout << endl;
            }
        }
        /*Indicate that only one argument should be given*/
        else {
            cout << endl;
            cout << "Hmm, I don't understand. Please enter '1' or '2' for your choice.";
            cout << endl;
        }
    }

    /*Format the screen*/
    cout << endl;

    /*The number the user would like to change the seed to*/
    int setSeedTo = -1;

    /*Loop until user gives a valid number to set the seed to*/
    while (setSeedTo == -1) {
        /*Prompt the user for input*/
        cout << "What would you like to set the seed to?";
        cout << endl;
        cout << "> ";
        /*Get the input from the user*/
        getline(cin, line);
        /*Parse the input form the user*/
        allParts = this->cf->parseLine(line);

        /*Handles the case that the wrong number of args were given*/
        if (allParts.size() != 1) {
            cout << endl;
            cout << "Please enter just one number.";
            cout << endl;
        }
        /*Handles the case the user cancels*/
        else if (Command::isCancel(allParts.at(0))) {
            cout << endl;
            cout << "Canceling seed set.";
            cout << endl;
            return;
        }
        else {
            try {
                /*Attempt to parse the user input to an integer*/
                int entered = stoi(allParts.at(0));
                /*Handle the case they entered a negative value*/
                if (entered < 0) {
                    cout << endl;
                    cout << "Please enter a positive value for the seed.";
                    cout << endl;
                }
                /*Handle the case they entered too large a value*/
                else if (entered >= 1000000) {
                    cout << endl;
                    cout << "Please make sure the number is less than 1 million.";
                    cout << endl;
                }
                /*Collect the seed they entered*/
                else {
                    setSeedTo = entered;
                }
            }
            /*Catch exception and indicate if they don't enter a valid number*/
            catch (...) {
                cout << endl;
                cout << "Please ensure you enter a valid positive number.";
                cout << endl;
            }
        }
    }

    /*Setting random seed*/

    /*Handles the case the user wants to change the random seed*/
    if (whichSeedSet == 1) {
        cout << endl;
        cout << "Setting Random Seed to: " << setSeedTo << "...";
        this->m->setMarketSeed(setSeedTo);
        cout << " Seed Set!";
        cout << endl;
    }
    /*Handles the case the user wants to change the violence seed*/
    else if (whichSeedSet == 2) { /*Setting violence*/
        cout << endl;
        cout << "Setting Violence Seed to: " << setSeedTo << "...";
        this->m->setMarketViolence(setSeedTo);
        cout << " Seed Set!";
        cout << endl;
    }
    /*Should never occur, but indicate error if so*/
    else {
        cout << endl;
        cout << "There was an issue setting the seed.";
        cout << endl;
    }

    return;
}