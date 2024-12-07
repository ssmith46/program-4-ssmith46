/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 7, 2024
 *
 * File: OptionsCommand.h
 * Purpose: Contains the declaration of the 'OptionsCommand' class.
*/

#ifndef OptionsCommand_H
#define OptionsCommand_H

/*Forward declare class so it will compile.*/
class OptionsCommand;

#include <string>
#include <sstream>
#include "Command.h"
#include "Market.h"
#include "Simulator.h"
#include "CommandFactory.h"

using namespace std;

/**
 * Purpose:
 * - The purpose of this command is to serve as a helpful options page that lists out
 *   what the simultor is capable of doing
 *
 * Data Members:
 * - vector<string> args -> The arguments to explain how the command was created
 * - Market *m -> The market that the command can influence
 * - Simulator *s -> The simulator the command can influence
 * - CommandFactory *cf -> The command factory the command can use for parsing user input.
 *
 * Member Functions:
 * - MistakeCommand(vector<string> args, Market *m, Simulator *s) -> The constructor
 *   for an options command.
 * - void execute() -> The override of the base command execute method.
 *
 * Class Usage:
 * - This class is used to display options that the user can enter to interact with the simulation
*/
class OptionsCommand : public Command {
public:
    /**
     * The constructor for an Options Command object.
     *
     * @param args -> The arguments that lead to the options command.
     * @param m -> The market that the command can influence.
     * @param s -> The simulator that the command can influence.
     */
    OptionsCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf);
    /**
     * This method overrides the base Command class's execute method.
     */
    void execute();
private:
    /*The arguments that lead to the options command.*/
    vector<string> args;
    /*The market that the command can manipulate.*/
    Market* m;
    /*The Simulator that the command can manipulate.*/
    Simulator* s;
    /*The command factory that can be used for parsing user input.*/
    CommandFactory* cf;
};
#endif

