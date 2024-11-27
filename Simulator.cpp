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
#include "Command.h"
#include "Market.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

/**
* The constructor used to instantiate a Simulator object.
*/
Simulator::Simulator(Market *m){
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
 * Helper function for ensuring a string only has one word (no spaces or tabs)
 * 
 * @param line -> The string of text entered by the user.
 * @return -> A boolean indicating no whitespace (false) or whitespace (true)
 */
bool hasWhiteSpace(string line){
    /*Iterate through each char in the line.*/
    for (int i = 0; i<line.length(); i++){
        /*Check if that char is whitespace. Return false if so.*/
        if ((line.substr(i, 1).compare(" ") == 0) || (line.substr(i, 1).compare("\t") == 0)){
            return true;
        }
    }

    /*Making it to here indicates no whitespace in the line.*/
    return false;
}

/**
* The method used to get a user logged in as a particular trader.
*/
void Simulator::loginScreen(){
    /*Give a welcome message to the user.*/
    cout << "Welcome to the " << this->getSimulatorName() << " stock market." << endl << endl;
    /*Boolean for tracking whether the user has given a successful login yet.*/
    bool loggedIn = false;
    /*A string to track what the user types in.*/
    string line;
    /*Keep looping while the user isn't logged in.*/
    while (!loggedIn){
        /*Give user a message for how to login, or create a new account.*/
        cout << "Enter Username, or 'new user' to create a new account:" << endl;
        cout << "> ";
        /*Get a line of input from the user.*/
        getline(cin, line);
        /*Check if the user is trying to create a new account for a trader.*/
        if (line.compare("new user") == 0){
            /*Variables for tracking user entered information.*/
            string name;
            string username;
            string strBalance;
            double balance;

            /*Code to add a new user here*/
            cout << "Awesome! Just need a few pieces of data on you:" << endl;

            /*Boolean to check that user entered input is valid.*/
            bool validInput = false;
            /*Boolean to check that user input doesn't have any spaces, or already exist.*/
            bool inLoopCheck = true;

            while (!validInput){
                /*Get the name from the user.*/
                cout << "Name: ";
                getline(cin, name);
                /*Make sure only entered one word.*/
                if (hasWhiteSpace()){
                    cout << "Please enter only your first name with no spaces." << endl;
                } else {
                    if (name.compare("") == 0){
                        cout << "Please enter at least one character." << endl;
                    } else {
                        validInput = true;
                    }
                }
            }
            validInput = false;
            while (!validInput){
                cout << "Username: ";
                getline(cin, username);
                /*Make sure only entered one word.*/
                if (hasWhiteSpace(username)){
                    cout << "Please enter only one word as your username." << endl;
                } else {
                    if (name.compare("") == 0){
                        cout << "Please enter at least one character." << endl;
                    } else {
                        Trader *on;
                        for (int i = 0; i<this->traders.size(); i++){
                            on = this->traders.at(i);
                            if (on->getUsername().compare(username) == 0){
                                inLoopCheck = false;
                            }
                        }
                        if (!inLoopCheck){
                            cout << "It seems that username is already taken. ";
                            cout << "Please try another one." << endl;
                            inLoopCheck = true;
                        } else {
                            validInput = true;
                        }
                    }
                }
            }
            validInput = false;
            while (!validInput){
                cout << "Account Balance: ";
                getline(cin, strBalance);
                if (hasWhiteSpace(strBalance)){
                    cout << "Please enter your balance with not spaces." << endl;
                } else {
                    if (strBalance.substr(0, 1).compare("$") == 0){
                        strBalance = strBalance.substr(0, 1);
                    }
                    try {
                        balance = stod(strBalance);
                        if (balance < 0) {
                            cout << "Please ensure that you start with a positive balance." << endl;
                        } else if (round(balance / 0.01) * 0.01 < .01) {
                            cout << "Please ensure that your balance is at least one penny." << endl;
                        } else {
                            balance = round(balance / 0.01) * 0.01;
                            validInput = true;
                        }
                    } catch(invalid_argument) {
                        cout << "Please ensure that your balance is a number." << endl;
                    }
                }
            }

            Trader newT(name, username, balance);
            this->addTrader(newT);
        } else {
            /*Code to login as an existing user here*/
        }
    }
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
    /*Variable for all the words in the entered command*/
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

    Command c = Command(allParts, this->market, this);
    return c;
}

/**
* This function allows additional traders to be added to the simultor. 
* 
* @param t -> The trader to add to the simulator
*/
bool Simulator::addTrader(Trader t){
    /*Calculate the number of traders in teh simulator*/
    int numTraders = this->traders.size();
    /*Variable for keeping track of which trader looking at.*/
    Trader *on;
    /*Iterate through the traders in the simulation.*/
    for (int i = 0; i<numTraders; i++){
        /*Get the trader on for this iteration.*/
        on = this->traders.at(i);
        /*Ensure that the username of the trader on, and the one trying to add do not match.*/
        if (on->getUsername().compare(t.getUsername()) == 0){
            /*Print an error message and return false if usernames match.*/
            cout << "It appears that username already exists, please try again." << endl;
            return false;
        }
    }
    /*Add the trader to the traders vector of the simulation.*/
    this->traders.push_back(&t);
}

/**
 * A function used to add stocks to the Market for an example run of the Simulator
 * 
 * @param m -> The market that the stocks will be added to.
 */
void exampleStockSetup(Market *m){
    /*Create a few stocks as examples in the simulation*/
    Stock s1("TSLA", 330.05, 1000);
    Stock s2("AAPL", 234.20, 1500);
    Stock s3("NVDA", 132.10, 2000);
    Stock s4("S&P 500", 5989.83, 10000);
    Stock s5("DIS", 116.89, 5000);
    Stock s6("BA", 151.91, 1400);

    /*Add the stocks created above to the market.*/
    m->addStock(s1);
    m->addStock(s2);
    m->addStock(s3);
    m->addStock(s4);
    m->addStock(s5);
    m->addStock(s6);
}

/**
 * A function used to add some existent traders with stocks and account balances already. 
 * 
 * @param s -> The simulator to add Traders to.
 */
void exampleTraderSetup(Simulator *s){
    /*Create a few traders as examples in the simulation*/
    Trader t1("Bob", "bobby123", 3765.80);
    Trader t2("Jane", "janeSmith", 14897.63);
    Trader t3("Bill", "bill", 2508.63);
    Trader t4("Karl", "karls", 57.03);

    /*Add the traders to the simulator.*/
    s->addTrader(t1);
    s->addTrader(t2);
    s->addTrader(t3);
    s->addTrader(t4);
}

/*The actual execution of the entire simulator.*/
int main(){
    
    /*Create the Market for the Simulation.*/
    Market m = Market();
    /*Create the Simulator for the Simulation.*/
    Simulator s = Simulator(&m);
    /*Create the CommandFactory for the Simulation.*/
    CommandFactory cf = CommandFactory();

    /*Finish setting up the CommandFactory with the market and simulator*/
    cf.setMarket(&m);
    cf.setSimulator(&s);

    /*Set the CommandFactory as the Simulation's Command Factory for the Simulation.*/
    s.setCommandFactory(cf);

    /*Setup a few stocks in the market.*/
    exampleStockSetup(&m);
    /*Setup a few traders in the simulator.*/
    exampleTraderSetup(&s);

    /*Get the next command to execute (will change this later).*/
    s.getNextCommand();


    return 0;
}