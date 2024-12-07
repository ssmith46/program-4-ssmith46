/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: December 6, 2024
 *
 * File: FluctuateStocksCommand.h
 * Purpose: Contains the declaration of the 'FluctuateStocksCommand' class.
*/

#ifndef FluctuateStocksCommand_H
#define FluctuateStocksCommand_H

/*Forward declare class so it will compile.*/
class FluctuateStocksCommand;

#include <string>
#include <sstream>
#include "Command.h"
#include "Market.h"
#include "Simulator.h"

using namespace std;

/**
 * Purpose:
 * - The purpose of this class is to allow the user to randomly fluctuate
 *   the prices of the stocks on the market.
 *
 * Data Members:
 * - vector<string> args -> The arguments that lead to this command being created
 * - Market *m -> The market that the command can influence
 * - Simulator *s -> The simulator the command can influence
 * - CommandFactory *cf -> The command factory the command can use for parsing user input.
 *
 * Member Functions:
 * - FluctuateStocksCommand(vector<string> args, Market *m, Simulator *s) -> The constructor
 *   for a fluctuate stocks command.
 * - void execute() -> The override of the base command execute method.
 *
 * Class Usage:
 * - This class is used to allow users to fluctuate stock prices on the market.
*/
class FluctuateStocksCommand : public Command {
public:
    /**
     * The constructor for a Fluctuate Stocks Command object.
     *
     * @param args -> The arguments that lead to the creation of the fluctuate stocks command.
     * @param m -> The market that the command can influence.
     * @param s -> The simulator that the command can influence.
     */
    FluctuateStocksCommand(vector<string> args, Market* m, Simulator* s, CommandFactory* cf);
    /**
     * This method overrides the base Command class's execute method.
     */
    void execute();

private:
    /*The arguments that lead to a fluctuate stocks command.*/
    vector<string> args;
    /*The market that the command can execute.*/
    Market* m;
    /*The Simulator that the command can execute.*/
    Simulator* s;
    /*The CommandFactory that the command can use for parsing user input.*/
    CommandFactory* cf;
};
#endif
