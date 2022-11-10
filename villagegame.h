#ifndef TASK1_VILLAGEGAME_H
#define TASK1_VILLAGEGAME_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <curses.h>
#include <clocale>

using namespace std;

#define mapx 13
#define mapy 13
#define maxhealth 100
#define maxplay 15
#define maxtroops 50
#define maxarmy 5
#define maxrbuild 50
#define maxtbuild 3
#define texty 26
#define erry 37


extern WINDOW *win;

class Map{
public:
    string status = "     ";
};
extern Map map[mapx][mapy];


class Village {
public:
    int loc[2] = {0, 0};          //(x,y)
    int health = maxhealth;               //village health
    int tbuildings = 0;                   //amount of troop-training buildings owned
    int rbuildings = 0;                   //amount of resource buildings owned
    int troops = maxtroops;               //amount of troops available
    int army = 0;                         //amount of armies
    bool preal = true;                    //AI or real player

    Village()= default;

    Village(const int a[2], int b, int c, int d, int e, int f, bool g) {
        loc[0] = a[0];
        loc[1] = a[1];
        health = b;
        tbuildings = c;
        rbuildings = d;
        troops = e;
        army = f;
        preal = g;
    }
};
extern Village village[maxplay];


class Resource
{
public:
    string type;
    int amount{};

    Resource()= default;

    Resource(string a, int b){
        type = a;           //tools/food/money/elixir
        amount = b;
    }
};
extern Resource resource[maxplay][4];

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
    int loc[2]{};           //troop location

    Troops() = default;

    Troops(int a, int b, int c, int d, int e, string f, string g, int h[2]){
        cost = a;           //cost of training
        health = b;
        attack = c;         //strength
        carrycap = d;       //carrying capacity
        speed = e;          //marching speed
        status = f;        //status of troop - army/stationed/dead
        type = g;          //type of troop - untrained/rookie/expert/master
        loc[0] = h[0];             //troop location
        loc[1] = h[1];
    }
};
extern Troops troops[maxplay][maxtroops];


class Army{

public:

    int troops{};             //no. of troops in the army
    int loc[2]{};           //army locations
    int speed{};            //army speed
    int attack{};           //total attack of army
    int health{};           //total health of army
    int carrycap{};         //total carrying capacity of army
    int resource[3]{};      //amount of resources taken from village after attack
    int target{};           //target village no.

    Troops trps[maxtroops]{};

    Army() = default;

    Army(int n, Troops a[n], const int b[3], int c){

        for(int i=0; i<n; i++){

            trps[i] = a[i];
            attack += a[i].attack;
            health += a[i].health;
            carrycap += a[i].carrycap;

            if(a[i].status != "dead"){
                loc[0] = a[i].loc[0];
                loc[1] = a[i].loc[1];

                if(a[i].type == "rookie"){
                    speed = 10;
                }else if(a[i].type == "expert"){
                    speed=15;
                }else if(a[i].type == "master"){
                    speed = 25;
                }
            }
        }

        troops = n;
        resource[0] = b[0];
        resource[1] = b[1];
        resource[2] = b[2];
        target = c;
    }
};
extern Army army[maxplay][maxarmy];


class ResourceBuildings
{
public:
    string type;            //type of resource generated
    int level{};
    int cost{};             //cost of upgrading

    ResourceBuildings() = default;

    ResourceBuildings(string a, int b, int c){
        type = a;
        level = b;
        cost = c;
    }
};
extern ResourceBuildings rbuild[maxplay][maxrbuild];


class TroopBuildings
{
public:
    string type;          //type of resource required

    TroopBuildings() = default;

    explicit TroopBuildings(string a){
        type = std::move(a);
    }
};
extern TroopBuildings tbuild[maxplay][maxtbuild];



//main
int options(int n, string choices[n],int y, int x, bool sameline);
void gameloop();

//setup
int *gamesetup();

//roundphases
int turnphase(int playno, int totplay, int round);
bool marching(int playno, int armyno, int target, int mspeed);
int endround(int playno);
void startround(int playno);

//turnphases
void friendtroop(int playno, int totplay);
int enemytroop(int playno, int totplay);
void earnres(int playno);
int actions(int playno, int totplay, int round);

//actions
int build(int playno);
int upgrade(int playno);
int train(int playno);
int attack(int playno, int totplay);
int resurrect(int playno);

//cli
void mapcli(int playno);
void villagecli(int playno);
void refreshcli(int playno);

#endif //TASK1_VILLAGEGAME_H
