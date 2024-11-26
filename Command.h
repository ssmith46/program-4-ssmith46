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
 * 
 * - Having access to these two data members will allow the command to change 
 *   anything about the Simulation.
 * 
 * Member Functions:
 * - Command(vector<string> args, Market m, Simulator s)
 *      -> The constructor for the command object. 
 * - void execute() -> A void abstract method that is overidden by child commands
 * 
 * Class Usage:
 * - This class is used to manipulate the simulation based off of
 *   user entered strings to specify arguments. 
*/
class Command {
    public:
        /**
         * Constructor for the the Command class.
         * 
         * @param args -> The arguments to execute the Command.
         * @param m -> The Market the command manipulates upon execution.
         * @param s -> The Simulator the command manipulates upon execution.
         */
        Command(vector<string> args, Market m, Simulator s);

        /**
         * The execute method for the command. Virtual, and will be overrided
         * by child classes that inherit from it.
         */
        void execute();
    private:
        /**
         * This is the Simulator that the command is able to manipulate
         * during execution.
         */
        Simulator s;
        /**
         * This is the Market that the command is able to manipulate
         * during execution.
         */
        Market m;
};
#endif
