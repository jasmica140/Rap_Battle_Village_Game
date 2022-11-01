#ifndef TASK1_VILLAGEGAME_H
#define TASK1_VILLAGEGAME_H

#include <iostream>
#include <cmath>

using namespace std;

#define mapx 100
#define mapy 100
#define maxhealth 100
#define maxplay 10
#define maxtroops 50
#define maxrbuild 50
#define maxtbuild 50

class Map{
public:
    string status;
}map[mapx][mapy];

class Village
{
public:
    int loc[2];          //(x,y)
    int health;          //village health
    int tbuildings;      //amount of troop-training buildings owned
    int rbuildings;      //amount of resource buildings owned
    int troops;          //amount of troops available
    bool ptype;          //AI or real player
}village[maxplay];

class Resource
{
public:
    string type;
    int amount{};
}resource[maxplay][3];

class Troops
{
public:
    int cost{};           //cost of training
    int health{};
    int attack{};         //strength
    int carrycap{};       //carrying capacity
    int speed{};          //marching speed
    string status;        //status of troop - army/stationed/dead
    string type;          //type of troop - untrained/rookie/expert/master
    bool army;
    int loc[2]{};           //troop location
    int resource[3]{};      //amount of resources taken from village after attack
}troops[maxplay][maxtroops];



class ResourceBuidlings
{
public:
    string type;            //type of resource generated
    int level{};
}rbuild[maxplay][maxrbuild];


class TroopBuidlings
{
public:
    int resources{};      //amount of resources required to train troops
    string type;          //type of resource required
    int level{};
}tbuild[maxplay][maxtbuild];


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

//main
void gameloop();

//setup
int *gamesetup();
void villagesetup();
void resourcesetup();
void troopsetup();

//roundphases
int turnphase(int playno, int totplay);
bool marching(int playno, int villno, int mspeed);
int endround(int playno);
void startround(int playno);

//turnphases
void friendtroop(int playno);
int enemytroop(int playno, int totplay);
void earnres(int playno);
void attack(int playno, int villno);
void actions(int playno);


#endif //TASK1_VILLAGEGAME_H
