/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: November 26, 2024
 * 
 * File: Command.h
 * Purpose: Contains the declaration of the abstract 'Command' class.
*/

#ifndef Command_H
#define Command_H

/*Forward declare class so it will compile.*/
class Command;

#include <string>
#include <sstream>
#include "Market.h"
#include "Simulator.h"

using namespace std;

/**
 * Purpose:
 * - Manipulate the state of the Stock Simulation based on input provided by the user.
 * - This is the base class that will be inherited by more specific commands,
 *   such as "BuyStockCommand".
 * 
 * Data Members:
 * - Simulator s -> The simulator that the command will be able to manipulate.
 * - Market m -> The market that the command will be able to manipulate.
 * - vector<string> args -> Arguments needed to execute the command.
 * - CommandFactory *cf -> The command factory the command can use for parsing user input.
 * 
 * Member Functions:
 * - Command() -> A default constructor so the compiler doesn't complain.
 * - Command(vector<string> args, Market *m, Simulator *s)
 *      -> The constructor for the command object. 
 * - void execute() -> A void abstract method that is overidden by child commands
 * - boolean isCancel(string word) -> Returns whether a user is trying to cancel a transaction.
 * - string whichStock() -> Returns the stock name the user would like to purchase.
 * - int howMany(string stockName) -> Returns an int for the number of shares of a specific
 *   stock a user would like to purchase.
 * 
 * Class Usage:
 * - This class is used to manipulate the simulation based off of
 *   user entered strings to specify arguments. 
*/
class Command {
    public:
        /**
         * A default constructor for the command class, so compile is happy.
         */
        Command();
        /**
         * Constructor for the the Command class.
         * 
         * @param args -> The arguments to execute the Command.
         * @param m -> The Market the command manipulates upon execution.
         * @param s -> The Simulator the command manipulates upon execution.
         * @param f -> The CommandFactory that can be used for parsing user input.
         */
        Command(vector<string> args, Market *m, Simulator *s, CommandFactory *cf);

        /**
         * The execute method for the command. Virtual, and will be overrided
         * by child classes that inherit from it.
         */
        virtual void execute();

        /**
        * Checks whether the user's entered command is "cancel" or some variant.
        * 
        * @param word -> The word to check whether it's a cancel or not.
        * @return -> A boolean on whether the user wishes to cancel the transaction or not.
        */
        bool isCancel(string word);

        /**
        * Get the name of the stock the user would like to purchase.
        *
        * @return -> A string for the stock the user would like to purchase.
        */
        string whichStock(string prompt);
        /**
        * Get the number of shares of a stock the user would like to purchase.
        *
        * @return -> An int for the number of shares the user would like to purchase.
        */
        int howManyShares(string stockName, string prompt);
    private:
        /**
         * This is the Simulator that the command is able to manipulate
         * during execution.
         */
        Simulator *s;
        /**
         * This is the Market that the command is able to manipulate
         * during execution.
         */
        Market *m;
        /**
        *This is the Command Factory that can be used for parsing user input.
        */
        CommandFactory* cf;
        /**
         * The arguements associated with executing this command 
         */
        vector<string> args;
};
#endif
