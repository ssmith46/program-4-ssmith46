#include "Market.h"
#include "Stock.h"
#include <string>
#include <iostream>

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
    string retVal = "";
    for (int i = 0; i<this->allStocks.size(); i++){
        if (i == this->allStocks.size()-1){
            retVal += (this->allStocks.at(i))->toString();
        } else {
            retVal += (this->allStocks.at(i))->toString() + "\n";
        }
    }
    return retVal;
}

bool Market::addStock(Stock toAdd){
    string uniqueSymbol = toAdd.getSymbol();
    bool unique = true;
    for (int i = 0; i<this->allStocks.size(); i++){
        if ((this->allStocks.at(i))->getSymbol().compare(uniqueSymbol) == 0){
            unique = false;
            break;
        }
    }
    if (!unique){
        return false;
    }

    //At this point, actually add it to the stocks
    this->allStocks.push_back(&toAdd);
    return true;
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
    Stock a("A", 1.0, 1);
    Stock b("B", 2.5, 3);
    Stock c("C", 3.0, 2);
    
    if (!m.addStock(a)){
        cout << "Failed to add A to the stocks." << endl;
    }
    if (!m.addStock(b)){
        cout << "Failed to add B to the stocks." << endl;
    }
    if (!m.addStock(c)){
        cout << "Failed to add C to the stocks." << endl;
    }
    Stock d("B", 2.7, 18);
    if (m.addStock(d)){
        cout << "Should have failed to add d, but it did not." << endl;
    }
    cout << m.stocks_toString() << endl;
    cout << "It works!" << endl;
    return 1;
}
