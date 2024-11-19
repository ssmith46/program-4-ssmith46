#include "Market.h"
#include "Stock.h"
#include <string>

using namespace std;

bool Market::hydrateStocks(ifstream& in){
/*
    string symbol;
    double price;
    int shares;
    while ((getLine(in, line)) && (line.compare("***") != 0)){
        //Means that the line read in contains info about a stock
        //in format: SYMBOL;PRICE;SHARES
        //           STRING;DOUBLE;INTEGER
        stringstream stockInfo(line);
        string part;
        vector<string> parts;
        
        while (getLine(stockInfo, part, ';')){
            parts.push_back(part);
        }

        //Wrong info on a line, or missing something
        if (parts.size() != 3){
            return false;
        }

        int start = parts.begin();
        symbol = parts.at(start);
        //Need to convert these to int/double
        price = stod(parts.at(start+1));
        shares = stoi(parts.at(start+2));

        Stock newStock = Stock(symbol, price, shares);
        this->stocks.push_back(newStock);
    }
    //If made it to here, then the file was in the correct format
*/
    return false;
}

string Market::stocks_toString(){
    return "";
}

bool Market::addStock(Stock toAdd){
    return false;
}

Stock Market::getStock(string symbol){
    string str = "ssds";
    Stock s(str, 2.1, 1);
    return s;
}

void Market::setMarketSeed(int seed){

}

void Market::setMarketViolence(int violence){

}

void Market::randomlyUpdateStocks(){

}

int main(){
    Market m = Market();
    return 1;
}
