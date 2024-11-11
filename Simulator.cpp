#include "Trader.h"
#include "Market.h"
#include "Simulator.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void Simulator::setSimulatorName(string name){
    this->simulatorName = name;
}

string Simulator::getSimulatorName(){
    return this->simulatorName;
}

Simulator::Simulator(){
    this->market = Market();
    this->simulatorName = "";
}

void Simulator::loginScreen(){

}

bool Simulator::hydrateFile(string filename){

    ifstream in;
    in.open(filename, ios_base::in);
    string line;

    //Read in simulator name
    if (getline(in, line)){
        this->setSimulatorName(line);
    } else {
        return false;
    }

    //Read in '***' delimiter
    if (getline(in, line)){
        if (line.compare("***") != 0){
            return false;
        }
    } else {
        return false;
    } 

    //Read in 'Stocks:' delimiter
    if (getline(in, line)){
        if (line.compare("Stocks:") != 0){
            return false;
        }
    } else {
        return false;
    }

    //At this point will be hydrating stocks 
    //Need to pass to the ifstream to the market to read in and build/store stocks
    this->market.hydrateStocks(in);

    //At this point the file cursor should be ready to read the line containing 'Traders:'
    //Read this in now
    if (getline(in, line)){
        if (line.compare("Traders:") != 0){
            return false;
        }
    } else {
        return false;
    }

    string name;
    string username;
    double accountBalance;
    while ((getline(in, line)) && (line.compare("***") != 0)){
        //Can now go through and hydrate all of the traders
        //Reading them in with line that look like:
        //      Tony;tonyusername;10345.86
        //      NAME;USERNAME;ACCOUNT BALANCE
        //      String;String;double
        stringstream traderInfo(line);
        string part;
        vector<string> parts;
        while (getline(traderInfo, part, ';')){
            parts.push_back(part);
        }

        if (parts.size() != 3){
            return false;
        }
        
        name = parts.at(0);
        username = parts.at(1);
        //Need to convert this to a double
        accountBalance = stod(parts.at(2));

        Trader newTrader = Trader(name, username, accountBalance);
        this->traders.push_back(newTrader);
    }

    //At this point, onto the portfolios
    //START HERE
    //Need to convert the read in values for account balance, price, and shares to integers/doubles
    //Need to continue hydrating from this point in the file. Onto the portfolios with stocks in the market
    return true;    
}

int main(int argc, char* argv[]){
    //First need to check if correct amount of arguments given
    if (argc != 2){
        cout << "Error: Incorrect number of arguments passed. Should be 2." << endl;
        return 1;
    }
    //argv[1] should be the filename to hydrate
    //Can pass this to the declaration of string to convert from char* to string
    string filename(argv[1]);

    Simulator s = Simulator();
    
    if (s.hydrateFile(filename)){
        cout << "It says it worked!" << endl;

    } else { //Means that the hydration failed
        cout << "Nah." << endl;
        return 1;
    } 


    return 0;
    
}
