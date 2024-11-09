#include "Trader.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void setSimulatorName(string name){
    this->simulatorName = name;
}

string getSimulatorName(){
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
    if (getLine(in, line)){
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
    if (getLine(in, line)){
        if (line.compare("Traders:" != 0){
            return false;
        }
    } else {
        return false;
    }

    string name;
    string username;
    double accountBalance;
    while ((getLine(in, line)) && (line.compare("***") != 0)){
        //Can now go through and hydrate all of the traders
        //Reading them in with line that look like:
        //      Tony;tonyusername;10345.86
        //      NAME;USERNAME;ACCOUNT BALANCE
        //      String;String;double
        stringstream traderInfo(line);
        string part;
        vector<string> parts;
        while (getLine(traderInfo, part, ';')){
            parts.push_back(part);
        }

        if (parts.size() != 3){
            return false;
        }
        
        int start = parts.begin();
        name = parts.at(start);
        username = parts.at(start+1);
        //Need to convert this to a double
        accountBalance = parts.at(start+2);

        Trader newTrader = Trader(name, username, accountBalance);
        this->traders.push_back(newTrader);
    }

    //At this point, onto the portfolios
    //START HERE
    //Need to convert the read in values for account balance, price, and shares to integers/doubles
    //Need to continue hydrating from this point in the file. Onto the portfolios with stocks in the market
    
}

int main(int argc, char* argv[]){
    //First need to check if correct amount of arguments given
    if (argc != 2){
        cout << "Error: Incorrect number of arguments passed. Should be 2.
        return 1;
    }
    //argv[1] should be the filename to hydrate
    //Can pass this to the declaration of string to convert from char* to string
    string filename(argv[1]);

    Simulator s = Simulator();
    
    if (s.hydrateFile(filename)){

    } else { //Means that the hydration failed
        return 1;
    } 


    return 0;
    
}
