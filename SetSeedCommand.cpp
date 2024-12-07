/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 7, 2024
 *
 * File: SetSeedCommand.cpp
 * Purpose: Contains the implementation of the abstract 'SetSeedCommand' class.
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
* The constructor for a Add Stock Command object.
*
* @param args -> The arguments that lead to the mistake command.
* @param m -> The market that the command can influence.
* @param s -> The simulator that the command can influence.
*/
SetSeedCommand::SetSeedCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf) {
    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}

/**
* This method overrides the base Command class's execute method.
*/
void SetSeedCommand::execute() {
    string line;
    vector<string> allParts;
    int whichSeedSet = -1;
    cout << endl;
    while (whichSeedSet == -1) {
        cout << "Which seed would you like to set?" << endl;
        cout << "1. Random Seed" << endl;
        cout << "2. Market Violence" << endl;
        cout << "> ";
        getline(cin, line);
        allParts = this->cf->parseLine(line);
        if (allParts.size() == 0) {
            cout << endl;
            cout << "It seems you didn't enter anything, please try again." << endl;
        }
        else if (allParts.size() == 1) {
            string choice = allParts.at(0);
            if (Command::isCancel(choice)) {
                cout << endl;
                cout << "Canceling seed set.";
                cout << endl;
                return;
            }
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
            else {
                cout << endl;
                cout << "Hmm, I don't understand. Please enter [1, 2] for your choice.";
                cout << endl;
            }
        }
        else {
            cout << endl;
            cout << "Hmm, I don't understand. Please enter '1' or '2' for your choice.";
            cout << endl;
        }
    }

    cout << endl;

    int setSeedTo = -1;
    while (setSeedTo == -1) {
        cout << "What would you like to set the seed to?";
        cout << endl;
        cout << "> ";
        getline(cin, line);
        allParts = this->cf->parseLine(line);

        if (allParts.size() != 1) {
            cout << endl;
            cout << "Please enter just one number.";
            cout << endl;
        }
        else if (Command::isCancel(allParts.at(0))) {
            cout << endl;
            cout << "Canceling seed set.";
            cout << endl;
            return;
        }
        else {
            try {
                int entered = stoi(allParts.at(0));
                if (entered < 0) {
                    cout << endl;
                    cout << "Please enter a positive value for the seed.";
                    cout << endl;
                }
                else if (entered >= 1000000) {
                    cout << endl;
                    cout << "Please make sure the number is less than 1 million.";
                    cout << endl;
                }
                else {
                    setSeedTo = entered;
                }
            }
            catch (...) {
                cout << endl;
                cout << "Please ensure you enter a valid positive number.";
                cout << endl;
            }
        }
    }

    /*Setting random seed*/
    if (whichSeedSet == 1) {
        cout << "Setting Random Seed to: " << setSeedTo << "...";
        this->m->setMarketSeed(setSeedTo);
        cout << " Seed Set!";
        cout << endl;
    }
    else if (whichSeedSet == 2) { /*Setting violence*/
        cout << "Setting Violence Seed to: " << setSeedTo << "...";
        this->m->setMarketViolence(setSeedTo);
        cout << " Seed Set!";
        cout << endl;
    }
    else {
        cout << endl;
        cout << "There was an issue setting the seed.";
        cout << endl;
    }

    return;
}