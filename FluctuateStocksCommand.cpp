/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 6, 2024
 *
 * File: FluctuateStocksCommand.cpp
 * Purpose: Contains the implementation of the 'FluctuateStocksCommand' class.
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
* The constructor for a Fluctuate Stocks Command object.
*
* @param args -> The arguments that lead to the creation of a fluctuate stocks command.
* @param m -> The market that the command can influence.
* @param s -> The simulator that the command can influence.
*/
FluctuateStocksCommand::FluctuateStocksCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf) {
    /*Assign the arguments to data members of the object*/

    this->args = args;
    this->m = m;
    this->s = s;
    this->cf = cf;
}
/**
 * This method overrides the base Command class's execute method.
 * In this case, this command randomly fluctuates the prices of the stocks
 * on the stock market in accordance to the number of times specified by
 * the user
 */
void FluctuateStocksCommand::execute() {
    /*The thing to show during price fluctuations*/
    int option = -1;
    /*Format the screen*/
    cout << endl;
    /*A string for getting user input*/
    string line;
    /*The words entered by the user during input collection*/
    vector<string> allParts;
    /*While the user hasn't selected a valid option, loop*/
    while (option == -1) {
        /*Prompt the user for input*/
        cout << "What would you like to look at while the stock prices fluctuate?";
        cout << endl;
        cout << "1. Your Personal Stock Portfolio." << endl;
        cout << "2. All Stocks on the Market." << endl;
        cout << "3. Nothing (faster, but boring)." << endl;
        cout << "> ";
        /*Get the input in from the user*/
        getline(cin, line);
        /*Parse the input that the user entered*/
        allParts = this->cf->parseLine(line);
        /*Check and indicate if the user didn't enter any input*/
        if (allParts.size() == 0) {
            cout << endl;
            cout << "It seems you did not enter anything. ";
            cout << "Please try again." << endl;
        }
        /*Check and indicate if the user wants to cancel the transaction*/
        else if (Command::isCancel(allParts.at(0)) == true) {
            cout << endl;
            cout << "Canceling Fluctuation." << endl;
            return;
        }
        /*Handles when the user only enters one word*/
        else if (allParts.size() == 1) {
            /*Get the word that the user entered*/
            string entered = allParts.at(0);
            /*Handle the case that the user wants to see their portfolio*/
            if (entered.compare("1") == 0) {
                option = 1;
            }
            /*Handles the case that the user wants to see the market*/
            else if (entered.compare("2") == 0) {
                option = 2;
            }
            /*Handles the case that the user wants to see nothing*/
            else if (entered.compare("3") == 0) {
                option = 3;
            }


            /*Handles the same above cases but for other input types*/

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
            /*Handles the case that the input from the user wasn't understood as an option*/
            else {
                cout << endl;
                cout << "Hmm, I don't understand that. Please try again." << endl;
            }
        }
        /*Indicate that the input from the user wasn't understood as an option*/
        else {
            cout << endl;
            cout << "Hmm, I don't understand that. Please try again." << endl;
        }
    }

    /*Format the screen*/
    cout << endl;
    /*The number of cycles to fluctuate the prices for*/
    int cycles = -1;
    /*The number entered by the user*/
    int inputNum;
    /*Keep looping until a valid number cycles is entered by the user*/
    while (cycles == -1) {
        /*Prompt the user for input*/
        cout << "How many cycles would you like to fluctuate the prices for?";
        cout << endl;
        cout << "> ";
        /*Get input from the user*/
        getline(cin, line);
        /*Parse the input from the user*/
        allParts = this->cf->parseLine(line);
        /*Handles the case that the user didn't enter the correct number of arguments*/
        if (allParts.size() != 1) {
            cout << endl;
            cout << "Please make sure you enter only one number." << endl;
        }
        else {
            try {
                /*Attempt to parse the user input into an integer*/
                inputNum = stoi(allParts.at(0));
                /*Check and indicate if the user entered a negative number*/
                if (inputNum < 0) {
                    cout << endl;
                    cout << "Please make sure that the number of cycles is a positive value.";
                    cout << endl;
                }
                /*Check and indicate if the user entered zero*/
                else if (inputNum == 0) {
                    cout << endl;
                    cout << "Why? .....Just..... why?" << endl;
                    return;
                }
                /*Check and indicate if the user entered too large a number*/
                else if (inputNum >= 1000) {
                    cout << endl;
                    cout << "Please enter a number smaller than 1000.";
                    cout << endl;
                }
                /*Collect the number of cycles from the user*/
                else {
                    cycles = inputNum;
                }
            }
            /*Catch exception if user didn't enter a valid number*/
            catch (invalid_argument& e) {
                cout << endl;
                cout << "Please enter a valid number for the number of cycles." << endl;
            }
            /*Catch exception if user enters too large a number for parsing*/
            catch (out_of_range& e) {
                cout << endl;
                cout << "Please enter a smaller number for the number of cycles." << endl;
            }
        }
    }

    /*Options:
    * 1->Portfolio
    * 2->Market
    * 3->Nothing
    */

    /*A pointer to a command to execute based on the user's choice*/
    Command *toExecute;

    /*The case the user want's to look at their portfolio*/
    if (option == 1) {
        /*Create a list portfolio command*/
        toExecute = &(ListPortfolioCommand(this->args, this->m, this->s, this->cf));
        /*Execute the command*/
        toExecute->execute();
        /*Fluctuate the prices for the number of cycles specified by the user*/
        for (int i = 0; i < cycles; i++) {
            /*Fluctuate the prices*/
            this->m->randomlyUpdateStocks();
            /*Put space before next print*/
            cout << endl << endl << endl << endl;
            /*Execute the command to see the portfolio*/
            toExecute->execute();
        }
    }
    /*The case the user wants to look at the market*/
    else if (option == 2) {
        /*Create a list stocks command*/
        toExecute = &(ListStocksCommand(this->args, this->m, this->s, this->cf));
        /*Execute the command*/
        toExecute->execute();
        /*Fluctuate the prices for the number of cycles specified by the user*/
        for (int i = 0; i < cycles; i++) {
            /*Fluctuate the prices*/
            this->m->randomlyUpdateStocks();
            /*Put space before next print*/
            cout << endl << endl << endl << endl;
            /*Execute the command to see the market*/
            toExecute->execute();
        }
    }
    /*The case the user wants to look at nothing*/
    else if (option == 3) {
        /*Fluctuate the prices for the number of cycles specified by the user*/
        for (int i = 0; i < cycles; i++) {
            /*Fluctuate the prices*/
            this->m->randomlyUpdateStocks();
        }
        /*Indicate that the fluctuation is complete*/
        cout << endl;
        cout << "Fluctuating Complete." << endl;
    }
    /*Shouldn't ever happen, but indicate if there was an error fluctuating the prices*/
    else {
        cout << "There was an error fluctuating the prices." << endl;
    }
}