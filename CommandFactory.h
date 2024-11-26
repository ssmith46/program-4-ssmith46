/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: November 26, 2024
 * 
 * File: CommandFactory.h
 * Purpose: Contains the declaration of the 'CommandFactory' class.
*/
#ifndef CommandFactory_H
#define CommandFactory_H

#include <string>
#include <sstream>
#include "Command.h"
#include "Market.h"
#include "Simulator.h"

using namespace std;

/**
 * Purpose:
 * - This class acts are the factory for creating command objects.
 * - This class will take a string of command line input, and convert it to a
 *   an executable command which 
 * 
 * Data Members:
 * - Market m -> This is the Market that will be passed to created commands
 *   in order to be manipulated when the command executes.
 * - Simulator s -> This is the Simulator that will be passed to created commands
 *   in order to be manipulated when the command executes.
 * 
 * Member Functions:
 * - void setSimulator(Simulator s) -> Setter for the Simulator that commands can
 *   manipulate.
 * - Simulator getSimulator() -> Getter for the Simulator that commands can manipulate.
 * - void setMarket(Market m) -> Setter for the Market that commands can manipulate.
 * - Market getMarket() -> Getter for the Market that commands can manipulate.
 * - vector<string> parseLine(string line) -> Given a user entered line of text,
 *   parse it for all words sepereated by spaces. This will allow the factory to 
 *   create commands specific to the action that the user entered.
 * - Command getCommand(string) -> This will be the method where most of the magic for
 *   this class happens. Calling this with a raw string of input from the user will yield
 *   the coresponding command to execute which will fullfill the request of the user. 
 * 
 * Class Usage:
 * - This class will be a singleton class that is responsible for creating commands
 *   that will make the simulation work.
*/
class CommandFactory {
    public:
        /** Sets the data member Simulator
         * 
         * @param s -> The simulator that commands can manipulate
         */
        void setSimulator(Simulator s);
        /** Access to the Simulator
         * 
         * @return -> The simulator for this CommandFactory
         */
        Simulator getSimulator();
        /** Sets the data member Market
         * 
         * @param s -> The market that commands can manipulate
         */
        void setMarket(Market m);
        /**
         * Access to the Market
         * 
         * @return -> The Market for this CommandFactory
         */
        Market getMarket();
        /**
         * Get all the words out of a line of text.
         * 
         * @param line -> The string to parse for words, ignoring whitespace.
         * @return -> Returns a vector of strings, where each string in the vector 
         * is a word from the line.
         */
        vector<string> parseLine(string line);
        /**
         * Takes a string as input and returns a command object that will fulfill
         * the needs of that line of text.
         * 
         * @param line -> The line that contains info about the command to create,
         * along with the parameters to fulfill that command.
         */
        Command getCommand(string line);
    private:
        /**
        * This is the Market that will be given to commands to manipulate.
        */
        Market m;
        /**
        * This is the Simulator that will be given to commands to manipulate.
        */
        Simulator s;
};
#endif
