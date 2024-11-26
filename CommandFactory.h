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
 * - CommandFactory(Market m, Simulator s) -> The constructor for the CommandFactory
 *   object.
 * - vector<string> parseLine(string line) -> Given a user entered line of text,
 *   parse it for all words sepereated by spaces. This will allow the factory to 
 *   create commands specific to the action that the user entered.
 * - Command getCommand(string) -> This will be the method where most of the magic for
 *   this class happens. Calling this with a raw string of input from the user will yield
 *   the coresponding command to execute which will fullfill the request of the user. 
 * 
 * Class Usage:
 * - 
*/
class CommandFactory {
    public:
        CommandFactory(Market m, Simulator s);
        //Get all the parts of the line in a vector
        vector<string> parseLine(string line);
        //Actually create and return the command
        Command getCommand(string);
    private:
    Market m;
    Simulator s;
};
#endif
