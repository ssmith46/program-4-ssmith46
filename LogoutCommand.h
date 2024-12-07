/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 6, 2024
 *
 * File: LogoutCommand.h
 * Purpose: Contains the declaration of the 'LogoutCommand' class.
*/

#ifndef LogoutCommand_H
#define LogoutCommand_H

/*Forward declare class so it will compile.*/
class LogoutCommand;

#include <string>
#include <sstream>
#include "Command.h"
#include "Market.h"
#include "Simulator.h"

using namespace std;


/**
 * Purpose:
 * - The purpose of this class is to allow the user to logout and login as a
 *   different trader.
 *
 * Data Members:
 * - vector<string> args -> The arguments to explain how the command came to be
 * - Market *m -> The market that the command can influence
 * - Simulator *s -> The simulator the command can influence
 * - CommandFactory *cf -> The command factory the command can use for parsing user input.
 *
 * Member Functions:
 * - LogoutCommand(vector<string> args, Market *m, Simulator *s) -> The constructor
 *   for a logout command.
 * - void execute() -> The override of the base command execute method.
 *
 * Class Usage:
 * - This class is used to allow users to login as a different trader
 *   than was selected at startup of the simulation.
*/
class LogoutCommand : public Command {
public:
    /**
     * The constructor for a Logout Command object.
     *
     * @param args -> The arguments that lead to the creation of this command
     * @param m -> The market that the command can influence.
     * @param s -> The simulator that the command can influence.
     */
    LogoutCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf);
    /**
     * This method overrides the base Command class's execute method.
     */
    void execute();

private:
    /*The arguments that lead to the creation of this command.*/
    vector<string> args;
    /*The market that the command can manipulate.*/
    Market* m;
    /*The Simulator that the command can manipulate.*/
    Simulator* s;
    /*The CommandFactory that the command can use for parsing user input.*/
    CommandFactory* cf;
};
#endif
