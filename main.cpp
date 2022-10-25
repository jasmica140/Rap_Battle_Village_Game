#include <iostream>

using namespace std;

void villagegame(){

    int rplay;
    int aiplay;

    loop1:
    cout << "Please provide the number of players:" << endl;
    cin >> rplay;
    if(rplay<1){
        cout << "At least one player required!" << endl;
        goto loop1;
    }

    loop2:
    cout << "How many AI players would you like?" << endl;
    cin >> aiplay;

    if(rplay<1){
        cout << "Number must be zero or greater!" << endl;
        goto loop2;
    }
}

int main() {
    return 0;
}
