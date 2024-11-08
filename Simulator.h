#ifndef Simulator_H
#define Simulator_H

#include <iostream>
#include <string>
#include <vector>
#include "Trader.h"

using namespace std;

class Simulator {
    public:
        Simulator();
        void loginScreen();
        void hydrateFile();
    private:
        Market market;
        vector<Trader> traders;
        Trader loggedIn;
}
#endif
