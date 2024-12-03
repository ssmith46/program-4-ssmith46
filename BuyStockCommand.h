/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 3, 2024
 *
 * File: BuyStockCommand.h
 * Purpose: Contains the declaration of the abstract 'BuyStockCommand' class.
*/

#ifndef BuyStockCommand_H
#define BuyStockCommand_H

/*Forward declare class so it will compile.*/
class BuyStockCommand;

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
 * - string whichStock() -> Returns the stock name the user would like to purchase.
 * - int howMany(string stockName) -> Returns an int for the number of shares of a specific
 *   stock a user would like to purchase.
 *
 * Class Usage:
 * - This class is used to allow users to buy stocks by specifying their symbol and amount.
*/
class BuyStockCommand : public Command {
public:
    /**
     * The constructor for a Buy Stock Command object.
     *
     * @param args -> The arguments that lead to the mistake command.
     * @param m -> The market that the command can influence.
     * @param s -> The simulator that the command can influence.
     */
    BuyStockCommand(vector<string> args, Market* m, Simulator* s, CommandFactory *cf);
    /**
     * This method overrides the base Command class's execute method.
     */
    void execute();
    /**
    * Get the name of the stock the user would like to purchase.
    * 
    * @return -> A string for the stock the user would like to purchase.
    */
    string whichStock();
    /**
    * Get the number of shares of a stock the user would like to purchase.
    * 
    * @return -> An int for the number of shares the user would like to purchase.
    */
    int howMany(string stockName);
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
