#ifndef TASK1_VILLAGEGAME_H
#define TASK1_VILLAGEGAME_H

#include <iostream>

using namespace std;

#define mapsize 10000;
#define maxhealth 100;

class Map
{
public:
    int X;      //horizontal length
    int Y;      //vertical length
};

class Player
{
public:
    string username;
    int village;        //index of village owned
};

class Village
{
public:
    int index;
    int x;
    int y;
    int health;         //village health
    int troopbuildings;      //amount of troop-training buildings owned
    int resbuildings;      //amount of resource buildings owned
    bool ptype;      //AI or real player
};

class Resource
{
public:
    string player;        //resource owner
    string type;        //type of resource - tools/spinach/weights
    int amount;        //amount of resources owned
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
    string status;      //status of troop - defending/offending/stationed
    string type;        //type of troop - untrained/rookies/advanced/masters
};

class ResourceBuidlings
{
public:
    int village;        //building location
    string type;        //type of resource generated
    int level;
};


class TroopBuidlings
{
public:
    int village;        //building location
    int resources;      //amount of resources required to train troops
    string type;        //type of resource required
    int level;
};


string V = "                                          \n"
           "                           _.-^-._    .--.\n"
           "                        .-'   _   '-. |__|\n"
           "                       /     |_|     \\|  |\n"
           "                      /               \\  |\n"
           "                     /|     _____     |\\ |\n"
           "                      |    |==|==|    |  |\n"
           "  |---|---|---|---|---|    |--|--|    |  |\n"
           "  |---|---|---|---|---|    |==|==|    |  |\n"
           " ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";

string map[100][100];


int *gamesetup();

void turnphase();

void wincond();

void marching();

void endround();

void startround();

void gameloop();

#endif //TASK1_VILLAGEGAME_H
