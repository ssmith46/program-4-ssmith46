#include <string>
#include <sstream>
#include "Market.h"
#include "Simulator.h"
#include "Command.h"
#include "CommandFactory.h"
#include <vector>

using namespace std;

vector<string> CommandFactory::parseLine(string line){
    
    vector<string> allParts;
    string part;

    string word = "";
    for (int i = 0; i<line.length() + 1; i++){
        //Do this so that the last word gets added still.
        //Doesn't end in ' ', it ends in '\n'
        if (i == line.length()){
            allParts.push_back(word);
        }
        else if ((line.substr(i, 1).compare(" ") == 0) || (line.substr(i, 1).compare("\t") == 0)){
            if (word.compare("") != 0){
                allParts.push_back(word);
                word = "";
            }
        } else {
            word += line.substr(i, 1);
        }
    }

    return allParts;
}

/*
int traderTest(){
    Trader t = Trader();
    t.setName("Tony");
    cout << "Should be Tony: " << t.getName() << endl;
    t.setBalance(129.8);
    cout << "Should be 129.8: " << t.getBalance() << endl;
    return 0;
}
*/
