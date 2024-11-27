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

class MistakeCommand : public Command {
    public:
        MistakeCommand(vector<string> args, Market *m, Simulator *s);
        void execute();
    private:
        vector<string> args;
        Market *m;
        Simulator *s;

};

#endif