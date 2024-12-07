/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 7, 2024
 *
 * File: SellStockCommand.h
 * Purpose: Contains the declaration of the abstract 'SellStockCommand' class.
*/

#ifndef SellStockCommand_H
#define SellStockCommand_H

/*Forward declare class so it will compile.*/
class SellStockCommand;

#include <string>
#include <sstream>
#include "Command.h"
#include "Market.h"
#include "Simulator.h"

using namespace std;

/**
 * Purpose:
 * - The purpose of this command is to allow the user to buy a stock by specifying
 *   it's symbol, as well as how many shares they would like to buy.
 *
 * Data Members:
 * - vector<string> args -> The arguments to explain how the command was wrong
 * - Market *m -> The market that the command can influence
 * - Simulator *s -> The simulator the command can influence
 * - CommandFactory *cf -> The command factory the command can use for parsing user input.
 *
 * Member Functions:
 * - BuyStockCommand(vector<string> args, Market *m, Simulator *s) -> The constructor
 *   for a mistake command.
 * - void execute() -> The override of the base command execute method.
 *
 * Class Usage:
 * - This class is used to allow users to buy stocks by specifying their symbol and amount.
*/
class SellStockCommand : public Command {
public:
    /**
     * The constructor for a Buy Stock Command object.
     *
     * @param args -> The arguments that lead to the mistake command.
     * @param m -> The market that the command can influence.
     * @param s -> The simulator that the command can influence.
     */
    SellStockCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf);
    /**
     * This method overrides the base Command class's execute method.
     */
    void execute();

private:
    /*The arguments that lead to an error for the command.*/
    vector<string> args;
    /*The market that the command can execute.*/
    Market* m;
    /*The Simulator that the command can execute.*/
    Simulator* s;
    /*The CommandFactory that the command can use for parsing user input.*/
    CommandFactory* cf;
};
#endif
