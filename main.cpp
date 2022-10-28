#include <iostream>

using namespace std;

class Map
{
public:
    int X;      //horizontal length
    int Y;      //vertical length
};

class Village
{
public:
    int x;
    int y;
    int health;         //village health
    string player;      //village owner
};

class Resource
{
public:
    string player;        //resource owner
    string type;        //type of resource
};

class Troops
{
public:
    int village;        //troop location
    int cost;
    int health;
    int attack;
    int carrycap;
    int speed;
    string type;        //type of troop
};

class ResourceBuidlings
{
public:
    int village;        //building location
    int resource;       //amount of respective resource generated
    string type;        //type of resource generated
};


class TroopBuidlings
{
public:
    int village;        //building location
    int resources;      //amount of resources required to train troops
    string type;        //type of resource required
};


int *gamesetup(){

    int rplay;      //real players
    int aiplay;     //AI players

    //ask user for player amounts
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

    if(aiplay<0){
        cout << "Number must be zero or greater!" << endl;
        goto loop2;
    }

    //one village for each player
    for(int i=1; i<rplay+aiplay+1; i++) {

        Village[i].player =

    }


    int players[] = {rplay,aiplay};

    return players;
}


void gameloop(){

    int *players = gamesetup();
    int rplay = players[0];
    int aiplay = players[1];

    cout << rplay << endl;
    cout << aiplay << endl;


}

int main() {

    gameloop();
    return 0;
}
