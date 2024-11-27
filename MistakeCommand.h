/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: November 26, 2024
 * 
 * File: MistakeCommand.h
 * Purpose: Contains the declaration of the abstract 'MistakeCommand' class.
*/

#ifndef MistakeCommand_H
#define MistakeCommand_H

/*Forward declare class so it will compile.*/
class MistakeCommand;

#include <string>
#include <sstream>
#include "Command.h"
#include "Market.h"
#include "Simulator.h"

using namespace std;

/**
 * Purpose:
 * - The purpose of this command is to serve as a mistake command that was 
 *   entered by a user.
 * 
 * Data Members:
 * - vector<string> args -> The arguments to explain how the command was wrong
 * - Market *m -> The market that the command can influence
 * - Simulator *s -> The simulator the command can influence
 * 
 * Member Functions:
 * - MistakeCommand(vector<string> args, Market *m, Simulator *s) -> The constructor
 *   for a mistake command. 
 * - void execute() -> The override of the base command execute method.
 * 
 * Class Usage:
 * - This class is used to display an error when a user makes a mistake entering a command. 
*/
class MistakeCommand : public Command {
    public:
        /**
         * The constructor for a Mistake Command object.
         * 
         * @param args -> The arguments that lead to the mistake command.
         * @param m -> The market that the command can influence.
         * @param s -> The simulator that the command can influence.
         */
        MistakeCommand(vector<string> args, Market *m, Simulator *s);
        /**
         * This method overrides the base Command class's execute method.
         */
        void execute();
    private:
        /*The arguments that lead to an error for the command.*/
        vector<string> args;
        /*The market that the command can execute.*/
        Market *m;
        /*The Simulator that the command can execute.*/
        Simulator *s;
};
#endif