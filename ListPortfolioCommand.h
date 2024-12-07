/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 6, 2024
 *
 * File: ListPortfolioCommand.h
 * Purpose: Contains the declaration of the 'ListPortfolioCommand' class.
*/

#ifndef ListPortfolioCommand_H
#define ListPortfolioCommand_H

/*Forward declare class so it will compile.*/
class ListPortfolioCommand;

#include <string>
#include <sstream>
#include "Command.h"
#include "Market.h"
#include "Simulator.h"

using namespace std;

/**
 * Purpose:
 * - The purpose of this class is to allow the user to see all the available
 *   stocks currently in their portfolio.
 *
 * Data Members:
 * - vector<string> args -> The arguments to explain how the command came to be
 * - Market *m -> The market that the command can influence
 * - Simulator *s -> The simulator the command can influence
 * - CommandFactory *cf -> The command factory the command can use for parsing user input.
 *
 * Member Functions:
 * - ListPortfolioCommand(vector<string> args, Market *m, Simulator *s) -> The constructor
 *   for a list portfolio command.
 * - void execute() -> The override of the base command execute method.
 *
 * Class Usage:
 * - This class is used to allow users to view the stocks in their portfolio.
*/
class ListPortfolioCommand : public Command {
public:
    /**
     * The constructor for a List Portfolio Command object.
     *
     * @param args -> The arguments that lead to the creation of the command
     * @param m -> The market that the command can influence.
     * @param s -> The simulator that the command can influence.
     */
    ListPortfolioCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf);
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
