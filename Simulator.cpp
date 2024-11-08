#include "Trader.h"
#include <iostream>
#include <string>

using namespace std;

Simulator::Simulator(){
    this->market = Market();
}

void Simulator::loginScreen(){

}

bool Simulator::hydrateFile(string filename){

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
