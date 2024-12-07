/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 7, 2024
 *
 * File: DoneCommand.h
 * Purpose: Contains the declaration of the 'DoneCommand' class.
*/

#ifndef DoneCommand_H
#define DoneCommand_H

/*Forward declare class so it will compile.*/
class DoneCommand;

#include <string>
#include <sstream>
#include "Command.h"
#include "Market.h"
#include "Simulator.h"
#include "CommandFactory.h"

using namespace std;

/**
 * Purpose:
 * - The purpose of this command is to serve as the final command executed in the simulation.
 *
 * Data Members:
 * - vector<string> args -> The arguments to explain how the command was created
 * - Market *m -> The market that the command can influence
 * - Simulator *s -> The simulator the command can influence
 * - CommandFactory *cf -> The command factory the command can use for parsing user input.
 *
 * Member Functions:
 * - MistakeCommand(vector<string> args, Market *m, Simulator *s) -> The constructor
 *   for a mistake command.
 * - void execute() -> The override of the base command execute method.
 *
 * Class Usage:
 * - This class is used to end the run of the simulation that is active
*/
class DoneCommand : public Command {
public:
    /**
     * The constructor for a Done Command object.
     *
     * @param args -> The arguments that lead to the creation of the Done command.
     * @param m -> The market that the command can influence.
     * @param s -> The simulator that the command can influence.
     */
    DoneCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf);
    /**
     * This method overrides the base Command class's execute method.
     */
    void execute();
private:
    /*The arguments that lead to the done command creation.*/
    vector<string> args;
    /*The market that the command can manipulate.*/
    Market* m;
    /*The Simulator that the command can manipulate.*/
    Simulator* s;
    /*The command factory that can be used for parsing user input.*/
    CommandFactory* cf;
};
#endif
