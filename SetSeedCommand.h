/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 7, 2024
 *
 * File: SetSeedCommand.h
 * Purpose: Contains the declaration of the 'SetSeedCommand' class.
*/

#ifndef SetSeedCommand_H
#define SetSeedCommand_H

/*Forward declare class so it will compile.*/
class SetSeedCommand;

#include <string>
#include <sstream>
#include "Command.h"
#include "Market.h"
#include "Simulator.h"

using namespace std;

/**
 * Purpose:
 * - The purpose of this class is to allow the user to change the random seed
 *   as well as the violence of the market.
 *
 * Data Members:
 * - vector<string> args -> The arguments to explain how the command was created
 * - Market *m -> The market that the command can influence
 * - Simulator *s -> The simulator the command can influence
 * - CommandFactory *cf -> The command factory the command can use for parsing user input.
 *
 * Member Functions:
 * - SetSeedCommand(vector<string> args, Market *m, Simulator *s) -> The constructor
 *   for a set seed command.
 * - void execute() -> The override of the base command execute method.
 *
 * Class Usage:
 * - This class is used to allow users to view change the seeds of the market.
*/
class SetSeedCommand : public Command {
public:
    /**
     * The constructor for a Set Seed Command object.
     *
     * @param args -> The arguments that lead to the set seed command.
     * @param m -> The market that the command can influence.
     * @param s -> The simulator that the command can influence.
     */
    SetSeedCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf);
    /**
     * This method overrides the base Command class's execute method.
     */
    void execute();

private:
    /*The arguments that lead to the set seed command.*/
    vector<string> args;
    /*The market that the command can manipulate.*/
    Market* m;
    /*The Simulator that the command can manipulate.*/
    Simulator* s;
    /*The CommandFactory that the command can use for parsing user input.*/
    CommandFactory* cf;
};
#endif