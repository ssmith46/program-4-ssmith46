/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 7, 2024
 *
 * File: AddStockCommand.h
 * Purpose: Contains the declaration of the abstract 'AddStockCommand' class.
*/

#ifndef AddStockCommand_H
#define AddStockCommand_H

/*Forward declare class so it will compile.*/
class AddStockCommand;

#include <string>
#include <sstream>
#include "Command.h"
#include "Market.h"
#include "Simulator.h"

using namespace std;

/**
 * Purpose:
 * - The purpose of this class is to allow the user to add stocks to the simulation.
 *
 * Data Members:
 * - vector<string> args -> The arguments entered to initiate this command creation.
 * - Market *m -> The market that the command can influence
 * - Simulator *s -> The simulator the command can influence
 * - CommandFactory *cf -> The command factory the command can use for parsing user input.
 *
 * Member Functions:
 * - AddStockCommand(vector<string> args, Market *m, Simulator *s) -> The constructor
 *   for a add stock command.
 * - void execute() -> The override of the base command execute method.
 *
 * Class Usage:
 * - This class is used to allow users to add stocks to the market.
*/
class AddStockCommand : public Command {
public:
    /**
     * The constructor for a Add Stock Command object.
     *
     * @param args -> The arguments that lead to the add stock command.
     * @param m -> The market that the command can influence.
     * @param s -> The simulator that the command can influence.
     */
    AddStockCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf);
    /**
     * This method overrides the base Command class's execute method.
     */
    void execute();

private:
    /*The arguments that lead to an add stock command.*/
    vector<string> args;
    /*The market that the command can manipulate.*/
    Market* m;
    /*The Simulator that the command can manipulate.*/
    Simulator* s;
    /*The CommandFactory that the command can use for parsing user input.*/
    CommandFactory* cf;
};
#endif
