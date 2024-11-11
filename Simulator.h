#ifndef Simulator_H
#define Simulator_H

#include <string>
#include "Trader.h"
#include "Market.h"
#include <vector>

using namespace std;

class Simulator {
    public:
        Simulator();
        void loginScreen();
        bool hydrateFile(string filename);
        void setSimulatorName(string name);
        string getSimulatorName();
    private:
        Market market;
        vector<Trader*> traders;
        string simulatorName;
};
#endif
