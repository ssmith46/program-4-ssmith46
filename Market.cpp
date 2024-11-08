#include "Market.h"

bool Market::hydrateStocks(ifstream in){

    while ((getLine(in, line)) && (line.compare("***") != 0)){
        //Means that the line read in contains info about a stock
        //in format: SYMBOL;PRICE;SHARES
        //           STRING;DOUBLE;INTEGER
        stringstream stockInfo(line);
        string part;
        vector<string> parts;
        
        while (getline(stockInfo, part, ';')){
            parts.push_back(segment);
        }

        //Wrong info on a line, or missing something
        if (parts.size() != 3){
            return false;
        }
    }
    //If made it to here, then the file was in the correct format
    return true;
}

void Market::printAllStocks(){
    
}

void Market::addStock(Stock toAdd){

}

Stock Market::getStock(string symbol){

}

