#ifndef TASK1_VILLAGEGAME_H
#define TASK1_VILLAGEGAME_H

#include <iostream>
#include <cmath>


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
    int tbuildings;      //amount of troop-training buildings owned
    int rbuildings;      //amount of resource buildings owned
    int troops;         //amount of troops available
    bool ptype;      //AI or real player
};

class Resource
{
public:
    string player;        //resource owner
    string type;        //type of resource - tools/spinach/money
    int amount;        //amount of resources owned
};

class Troops
{
public:
    int village;        //troop location
    int cost;           //cost of training
    int health;
    int attack;         //strength
    int carrycap;       //carrying capacity
    int speed;          //marching speed
    string status;      //status of troop - defending/offending/stationed/dead
    string type;        //type of troop - untrained/rookie/expert/master
    int tools;          //amount of tools taken from village after attack
    int spinach;        //amount of spinach taken from village after attack
    int money;          //amount of money taken from village after attack
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
