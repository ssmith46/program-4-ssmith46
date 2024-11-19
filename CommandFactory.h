#ifndef CommandFactory_H
#define CommandFactory_H

#include <string>
#include <sstream>
#include "Command.h"

using namespace std;

class CommandFactory {
    public:
        //Get all the parts of the line in a vector
        vector<string> parseLine(string line);
        //Actually create and return the command
        Command getCommand(string);
    private:
};
#endif
