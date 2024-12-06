/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 6, 2024
 *
 * File: ListPortfolioCommand.cpp
 * Purpose: Contains the implementation of the abstract 'ListPortfolioCommand' class.
*/
#include "Command.h"
#include "CommandFactory.h"
#include "FluctuateStocksCommand.h"
#include "ListPortfolioCommand.h"
#include "ListStocksCommand.h"
#include "Market.h"
#include "Simulator.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

/**
* The constructor for a List Stocks Command object.
*
* @param args -> The arguments that lead to the mistake command.
* @param m -> The market that the command can influence.
* @param s -> The simulator that the command can influence.
*/
FluctuateStocksCommand::FluctuateStocksCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf) {
    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}
/**
 * This method overrides the base Command class's execute method.
 */
void FluctuateStocksCommand::execute() {

    int option = -1;

    string line;
    vector<string> allParts;
    while (option == -1) {
        cout << "What would you like to look at while the stock prices fluctuate?";
        cout << endl;
        cout << "1. Your Personal Stock Portfolio." << endl;
        cout << "2. All Stocks on the Market." << endl;
        cout << "3. Nothing (faster, but boring)." << endl;
        cout << "> ";
        getline(cin, line);
        allParts = this->cf->parseLine(line);
        if (allParts.size() == 0) {
            cout << endl;
            cout << "It seems you did not enter anything. ";
            cout << "Please try again." << endl;
        }
        else if (allParts.size() == 1) {
            string entered = allParts.at(0);
            if (entered.compare("1") == 0) {
                option = 1;
            }
            else if (entered.compare("2") == 0) {
                option = 2;
            }
            else if (entered.compare("3") == 0) {
                option = 3;
            }
            else if (entered.compare("portfolio") == 0) {
                option = 1;
            }
            else if (entered.compare("Portfolio") == 0) {
                option = 1;
            }
            else if (entered.compare("Market") == 0) {
                option = 2;
            }
            else if (entered.compare("market") == 0) {
                option = 2;
            }
            else if (entered.compare("nothing") == 0) {
                option = 3;
            }
            else if (entered.compare("Nothing") == 0) {
                option = 3;
            }
            else {
                cout << endl;
                cout << "Hmm, I don't understand that. Please try again." << endl;
            }
        }
        else {
            cout << endl;
            cout << "Hmm, I don't understand that. Please try again." << endl;
        }
    }


    
    int cycles = -1;
    int inputNum;
    while (cycles == -1) {
        cout << "How many cycles would you like to fluctuate the prices for?";
        cout << endl;
        cout << "> ";
        getline(cin, line);
        allParts = this->cf->parseLine(line);

        if (allParts.size() != 1) {
            cout << endl;
            cout << "Please make sure you enter only one number." << endl;
        }
        else {
            try {
                inputNum = stoi(allParts.at(0));
                if (inputNum < 0) {
                    cout << "Please make sure that the number of cycles is a positive value.";
                    cout << endl;
                }
                else if (inputNum == 0) {
                    cout << "Why? .....Just..... why?" << endl;
                    cycles = inputNum;
                }
                else if (inputNum > 100) {
                    cout << "Please enter a number smaller than 101.";
                    cout << endl;
                }
                else {
                    cycles = inputNum;
                }
            }
            catch (invalid_argument& e) {
                cout << endl;
                cout << "Please enter a valid number for the number of cycles." << endl;
            }
            catch (out_of_range& e) {
                cout << endl;
                cout << "Please enter a smaller number for the number of cycles." << endl;
            }
        }
    }

    if (cycles == 0) {
        return;
    }

    /*Options:
    * 1->Portfolio
    * 2->Market
    * 3->Nothing
    */
    Command *toExecute;
    if (option == 1) {
        toExecute = &(ListPortfolioCommand(this->args, this->m, this->s, this->cf));
        toExecute->execute();
        for (int i = 0; i < cycles; i++) {
            this->m->randomlyUpdateStocks();
            cout << endl << endl << endl << endl;
            toExecute->execute();
            for (int wait = 0; wait < 100000000; wait++) {}
        }
    }
    else if (option == 2) {
        toExecute = &(ListStocksCommand(this->args, this->m, this->s, this->cf));
        toExecute->execute();
        for (int i = 0; i < cycles; i++) {
            this->m->randomlyUpdateStocks();
            cout << endl << endl << endl << endl;
            toExecute->execute();
            
            
        }
    }
    else if (option == 3) {
        for (int i = 0; i < cycles; i++) {
            this->m->randomlyUpdateStocks();
        }
        cout << endl;
        cout << "Fluctuating Complete." << endl;
    }
    else {
        cout << "There was an error fluctuating the prices." << endl;
    }
}