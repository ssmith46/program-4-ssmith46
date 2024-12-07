/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 6, 2024
 *
 * File: DepositCommand.h
 * Purpose: Contains the declaration of the 'DepositCommand' class.
*/

#ifndef DepositCommand_H
#define DepositCommand_H

/*Forward declare class so it will compile.*/
class DepositCommand;

#include <string>
#include <sstream>
#include "Command.h"
#include "Market.h"
#include "Simulator.h"

using namespace std;

/**
 * Purpose:
 * - The purpose of this class is to allow the user to make deposits during the 
 *   run of the simulation.
 *
 * Data Members:
 * - vector<string> args -> The arguments that lead to the creation of the deposit command
 * - Market *m -> The market that the command can influence
 * - Simulator *s -> The simulator the command can influence
 * - CommandFactory *cf -> The command factory the command can use for parsing user input.
 *
 * Member Functions:
 * - DepositCommand(vector<string> args, Market *m, Simulator *s) -> The constructor
 *   for a deposit command.
 * - void execute() -> The override of the base command execute method.
 *
 * Class Usage:
 * - This class is used to allow users to deposit money into their account.
*/
class DepositCommand : public Command {
public:
    /**
     * The constructor for a Deposit Command object.
     *
     * @param args -> The arguments that lead to the deposit command.
     * @param m -> The market that the command can influence.
     * @param s -> The simulator that the command can influence.
     */
    DepositCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf);
    /**
     * This method overrides the base Command class's execute method.
     */
    void execute();

private:
    /*The arguments that lead to the creation of a deposit command.*/
    vector<string> args;
    /*The market that the command can execute.*/
    Market* m;
    /*The Simulator that the command can execute.*/
    Simulator* s;
    /*The CommandFactory that the command can use for parsing user input.*/
    CommandFactory* cf;
};
#endif
