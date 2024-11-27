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
 * 
 * Member Functions:
 * - Command() -> A default constructor so the compiler doesn't complain.
 * - Command(vector<string> args, Market *m, Simulator *s)
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
         * A default constructor for the command class, so compile is happy.
         */
        Command();
        /**
         * Constructor for the the Command class.
         * 
         * @param args -> The arguments to execute the Command.
         * @param m -> The Market the command manipulates upon execution.
         * @param s -> The Simulator the command manipulates upon execution.
         */
        Command(vector<string> args, Market *m, Simulator *s);

        /**
         * The execute method for the command. Virtual, and will be overrided
         * by child classes that inherit from it.
         */
        virtual void execute();
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
         * The arguements associated with executing this command 
         */
        vector<string> args;
};
#endif
