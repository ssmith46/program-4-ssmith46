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
#include "MistakeCommand.h"
#include "Market.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

/**
* The constructor used to instantiate a Simulator object.
* 
* @param m -> The market of the simulation
*/
Simulator::Simulator(Market *m){
    this->market = m;
    this->simulatorName = "";
    this->running = true;
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
void
Simulator::loginScreen(){

    this->loggedIn = nullptr;

    /*Give a welcome message to the user.*/
    cout << endl;
    /*Boolean for tracking whether the user has given a successful login yet.*/
    bool loggedIn = false;
    /*A string to track what the user types in.*/
    string line;
    /*Keep looping while the user isn't logged in.*/
    while (!loggedIn){
        /*Give user a message for how to login, or create a new account.*/
        cout << "Enter your username, or 'new user' to create a new account:" << endl;
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

            /*Indicate adding a new user.*/
            cout << endl;
            cout << "Awesome! Just need a few pieces of data on you:" << endl;

            /*Boolean to check that user entered input is valid.*/
            bool validInput = false;
            /*Boolean to check that user input doesn't have any spaces, or already exist.*/
            bool inLoopCheck = true;

            /*Keep looping until they enter valid text for a valid name.*/
            while (!validInput){
                /*Get the name from the user.*/
                cout << "Name: ";
                getline(cin, name);

                /*Make sure only entered one word.*/
                if (hasWhiteSpace(name)){
                    cout << endl;
                    cout << "Please enter only your first name with no spaces." << endl;
                } else {
                    /*Make sure they entered at least one char.*/
                    if (name.compare("") == 0){
                        cout << endl;
                        cout << "Please enter at least one character." << endl;
                    } else {
                        /*Making it to here means they entered a valid name.*/
                        validInput = true;
                    }
                }
            }
            cout << endl;
            /*Reset validInput to false to ensure the user entered a valid username.*/
            validInput = false;
            /*Keep looping until the user enters a valid username.*/
            while (!validInput){
                /*Get the username from the user.*/
                cout << "Username: ";
                getline(cin, username);

                /*Make sure only entered one word.*/
                if (hasWhiteSpace(username)){
                    cout << endl;
                    cout << "Please enter only one word as your username." << endl;
                } else {
                    /*Make sure they entered at least one character.*/
                    if (username.compare("") == 0){
                        cout << endl;
                        cout << "Please enter at least one character." << endl;
                    } else {
                        /*Loop through the traders to make sure it's a new username.*/
                        Trader on(this->market);
                        for (int i = 0; i<this->traders.size(); i++){
                            on = this->traders.at(i);
                            if (on.getUsername().compare(username) == 0){
                                inLoopCheck = false;
                            }
                        }
                        /*If a matching username was found, tell user to enter a new one.*/
                        if (!inLoopCheck){
                            cout << endl;
                            cout << "It seems that username is already taken. ";
                            cout << "Please try another one." << endl;
                            inLoopCheck = true;
                        } else {
                            /*Indicate that the username they entered is valid, and move on.*/
                            validInput = true;
                        }
                    }
                }
            }
            /*Reset validInput to false, so can ensure they enter a valid account balance.*/
            validInput = false;
            cout << endl;
            while (!validInput){
                cout << "Account Balance: ";
                getline(cin, strBalance);
                /*Ensure there are no spaces in the input.*/
                if (hasWhiteSpace(strBalance)){
                    cout << endl;
                    cout << "Please enter your balance without spaces." << endl;
                } else {
                    /*Check if they added the $ before the amount, and remove it if so.*/
                    if (strBalance.substr(0, 1).compare("$") == 0){
                        strBalance = strBalance.substr(1, strBalance.size()-1);
                    }
                    try {
                        /*Attempt to convert the string to a double.*/
                        balance = stod(strBalance);
                        /*Ensure they have entered at least one penny. */
                        if (round(balance / 0.01) * 0.01 < .01) {
                            cout << endl;
                            cout << "Please ensure that your balance is at least one penny.";
                            cout << endl;
                        }
                        /*Ensure the starting balance isn't too large*/
                        else if (balance > 1000000000000){
                            cout << endl;
                            cout << "Please ensure that your balance is less than ";
                            cout << "one trillion dollars." << endl;
                        }
                        else {
                            /*Calculate the balance for rounding to the nearest penny.*/
                            balance = round(balance / 0.01) * 0.01;
                            validInput = true;
                        }
                    } catch(invalid_argument) { /*Catching failed parse from string to double.*/
                        cout << endl;
                        cout << "Please ensure that your balance is a number." << endl;
                    }
                }
            }
            /*Create a new trader with the information obtained from the user.*/
            Trader newT(name, username, balance, this->market);
            /*Add this new trader to the vector of traders.*/
            this->addTrader(newT);
            /*Set this trader as the logged in trader (Will be the last trader in vector).*/
            this->setLoggedInTrader(&(this->traders.at(this->traders.size()-1)));
            /*Indicate to the user that the account was added successfully.*/
            cout << endl;
            cout << "New user added successfully!";

            return;
        } else {/*Code to login as an existing user here*/
            /*Check that the user entered a username with no spaces.*/
            if (hasWhiteSpace(line)){
                cout << endl;
                cout << "Please try again, your username shouldn't contain any spaces." << endl;
            } else if (line.compare("") == 0){ /*Ensure the user entered at least one char.*/
                cout << endl;
                cout << "Please ensure that your username has at least one character in it." << endl;
            } else {
                /*Loop through all the traders and find the one matching the username.*/
                Trader on(this->market);
                for (int i = 0; i<this->traders.size(); i++){
                    on = this->traders.at(i);
                    /*When the usernames, match, this is the logged in user.*/
                    if (on.getUsername().compare(line) == 0){
                        this->setLoggedInTrader(&(this->traders.at(i)));
                        return;
                    }
                }
                /*Making it to here means that the user entered a username that doesn't exist*/
                cout << endl;
                cout << "Hmm, there doesn't seem to be a trader with that username. ";
                cout << "Please try again." << endl;
            }
        }
    }
}

/**
* This function is used to get a line of input from the user, and convert
* it into a command that can then be executed to do what they want. 
* 
* @return -> A command that can be used to change the simulation. 
*/
Command* Simulator::getNextCommand(){
    /*Create a variable for the line of input from the user.*/
    string line;
    /*Indicate to user where to type.*/
    cout << "home> ";
    /*Get a line of input from the user.*/
    getline(cin, line);
    /*Get the command based off the text entered by the user.*/
    return this->cf.getCommand(line);
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
    Trader on(this->market);
    /*Iterate through the traders in the simulation.*/
    for (int i = 0; i<numTraders; i++){
        /*Get the trader on for this iteration.*/
        on = this->traders.at(i);
        /*Ensure that the username of the trader on, and the one trying to add do not match.*/
        if (on.getUsername().compare(t.getUsername()) == 0){
            /*Print an error message and return false if usernames match.*/
            cout << "It appears that username already exists, please try again." << endl;
            return false;
        }
    }
    /*Add the trader to the traders vector of the simulation.*/
    this->traders.push_back(t);
    return true;
}

/**
 * A getter to retrieve the user logged in to the simulator. 
 * 
 * @return -> Returns a pointer to the trader who is logged in.
 */
Trader* Simulator::getLoggedInTrader(){
    return this->loggedIn;
}

/**
 * A setter for the trader logged in to the simulator. 
 * 
 * @param -> The Trader to set as logged in
 */
void Simulator::setLoggedInTrader(Trader *t){
    this->loggedIn = t;
}

Market* Simulator::getMarket() {
    return this->market;
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
    Stock s4("S&P_500", 5989.83, 10000);
    Stock s5("DIS", 116.89, 5000);
    Stock s6("BA", 151.91, 1400);
    //Stock s7("Very_long_stock_name_test", 100000000.99, 9999999999999);

    /*Add the stocks created above to the market.*/
    m->addStock(s1);
    m->addStock(s2);
    m->addStock(s3);
    m->addStock(s4);
    m->addStock(s5);
    m->addStock(s6);
    //m->addStock(s7);
}

/**
 * A function used to add some existent traders with account balances already. 
 * 
 * @param s -> The simulator to add Traders to.
 */
void exampleTraderSetup(Simulator *s){
    /*Create a few traders as examples in the simulation*/
    Trader t1("Bobby", "bobby123", 329719.95, s->getMarket());
    Trader t2("Jane", "janeSmith", 14897.63, s->getMarket());
    Trader t3("Bill", "bill", 2508.63, s->getMarket());
    Trader t4("Karl", "karls", 57.03, s->getMarket());

    /*Add the traders to the simulator.*/
    s->addTrader(t1);
    s->addTrader(t2);
    s->addTrader(t3);
    s->addTrader(t4);
}

/**
 * Function to create an instance of every object just to be sure it works
 */
void createAllObjectTypes(){
    Stock s("E", 12.00, 5);
    //Trader t("Kyle", "kyle123", 125.00);
    CommandFactory cf;
    Market m;
    Simulator sim(&m);
    //StockPortfolio spf;
    Command c;
    vector<string> svec;
    MistakeCommand mc(svec, &m, &sim, &cf);
    cout << "All object types created successfully!" << endl;
}

/**
* A setter for the "running" of the data member
*
* @param state -> The state to change the "running" data member to
*/
void Simulator::setRunning(bool state) {
    /*Set the "running" data member of the simulation*/
    this->running = state;
}

/**
* A getter for the "running" data member of the simulator
*/
bool Simulator::isRunning() {
    /*Return the "running" data mamber of the simulation*/
    return this->running;
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

    /*Set the simulator's name*/
    s.setSimulatorName("Sully Simulation");

    /*Welcome the user to the simulation*/
    cout << "Welcome to the " << s.getSimulatorName() << " Stock Market.";

    /*Have the user login before continuing*/
    s.loginScreen();
    cout << endl;
    cout << "Login Successful, you are logged in as: " << s.getLoggedInTrader()->getName();
    cout << "." << endl;
    cout << "For available commands, enter 'options'." << endl;

    /*Get the next command to execute and execute it.*/
    /*Loop until no longer running*/
    while (s.isRunning()){
        Command *c = s.getNextCommand();
        if (c != nullptr){
            c->execute();
            /*Since dealing with a pointer on free store, delete it after use.*/
            delete c;
        }
    }

    /*Indicate the simulation has ended*/
    cout << endl;
    cout << "Thank you for using the " << s.getSimulatorName() << " Stock Market Tool!";
    cout << endl;

    return 0;
}