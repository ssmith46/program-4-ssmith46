/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 7, 2024
 *
 * File: SellStockCommand.h
 * Purpose: Contains the declaration of the 'SellStockCommand' class.
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
 * - The purpose of this command is to allow the user to sell a stock by specifying
 *   it's symbol, as well as how many shares they would like to sell.
 *
 * Data Members:
 * - vector<string> args -> The arguments to explain how the command was created
 * - Market *m -> The market that the command can influence
 * - Simulator *s -> The simulator the command can influence
 * - CommandFactory *cf -> The command factory the command can use for parsing user input.
 *
 * Member Functions:
 * - SellStockCommand(vector<string> args, Market *m, Simulator *s) -> The constructor
 *   for a sell stock command.
 * - void execute() -> The override of the base command execute method.
 *
 * Class Usage:
 * - This class is used to allow users to sell stocks by specifying their symbol and amount.
*/
class SellStockCommand : public Command {
public:
    /**
     * The constructor for a Sell Stock Command object.
     *
     * @param args -> The arguments that lead to the sell stock command.
     * @param m -> The market that the command can influence.
     * @param s -> The simulator that the command can influence.
     */
    SellStockCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf);
    /**
     * This method overrides the base Command class's execute method.
     */
    void execute();

private:
    /*The arguments that lead to sell stocks command.*/
    vector<string> args;
    /*The market that the command can manipulate.*/
    Market* m;
    /*The Simulator that the command can manipulate.*/
    Simulator* s;
    /*The CommandFactory that the command can use for parsing user input.*/
    CommandFactory* cf;
};
#endif
