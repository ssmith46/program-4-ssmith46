#include <iostream>

using namespace std;

int main(){
    string test = "Testing testing";
    cout << test;
    for (int i = 0; i<4; i++){
        cout << " " << (i+1);
    }
    cout << endl;
    return 0;
}
