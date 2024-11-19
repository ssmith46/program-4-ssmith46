#ifndef Command_H
#define Command_H

#include <string>
#include <sstream>
#include "Market.h"
#include "Simulator.h"

using namespace std;

class Command {
    public:
        Command(string type, vector<string> args, Market m, Simulator s);
        void execute();
    private:
        Simulator s;
        Market m;
};
#endif
