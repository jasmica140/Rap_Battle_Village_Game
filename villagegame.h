#ifndef TASK1_VILLAGEGAME_H
#define TASK1_VILLAGEGAME_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <curses.h>
#include <clocale>
#include <utility>
#include <random>

using namespace std;

#define mapx 13
#define mapy 13
#define maxhealth 10000
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
    int idx{};                              //player index
    int loc[2] = {0, 0};         //(x,y)
    int health = maxhealth;               //village health
    int tbuildings = 0;                   //amount of troop-training buildings owned
    int rbuildings = 0;                   //amount of resource buildings owned
    int troops = maxtroops;               //amount of troops available
    int army = 0;                         //amount of armies
    bool attack = false;                  //under attack
    bool preal = true;                    //AI or real player

    Village()= default;

    Village(int i, const int a[2], int b, int c, int d, int e, int f, bool g, bool h) {
        idx = i;
        loc[0] = a[0];
        loc[1] = a[1];
        health = b;
        tbuildings = c;
        rbuildings = d;
        troops = e;
        army = f;
        attack = g;
        preal = h;
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
        type = std::move(a);           //tools/food/money/elixir
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
    string type;          //type of troop - untrained/rookie/expert/master
    int loc[2]{};         //troop location

    Troops() = default;

    Troops(int a, int b, int c, int d, int e, string f, const int g[2]){
        cost = a;           //cost of training
        health = b;
        attack = c;         //strength
        carrycap = d;       //carrying capacity
        speed = e;          //marching speed
        type = std::move(f);           //type of troop - untrained/rookie/expert/master
        loc[0] = g[0];             //troop location
        loc[1] = g[1];
    }
};
extern Troops troops[maxplay][maxtroops];


class Army{

public:

    int troops{};           //no. of troops in the army
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

        int r=0,e=0;

        for(int i=0; i<n; i++){

            trps[i] = a[i];
            attack += a[i].attack;
            health += a[i].health;
            carrycap += a[i].carrycap;

            loc[0] = a[i].loc[0];
            loc[1] = a[i].loc[1];

            if(a[i].type == "rookie"){
                r++;
            }else if(a[i].type == "expert"){
                e++;
            }
        }

        if(r>0){
            speed = 10;
        }else if(e>0){
            speed = 15;
        }else{
            speed = 25;
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
        type = std::move(a);
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
int gamesetup();
void deleteplayer(int playno, int totplay);

//roundphases
int turnphase(int playno, int totplay, int roundno);
bool marching(int playno, int armyno, int target, int mspeed);
int endround(int playno, int totplay);
void startround(int playno);

//turnphases
void friendtroop(int playno);
int enemytroop(int playno, int totplay);
void earnres(int playno);
int actions(int playno, int totplay, int roundno);

//actions
int build(int playno);
int upgrade(int playno);
int train(int playno);
int attack(int playno, int totplay);
int resurrect(int playno);

//AI
int AIround1(int playno);
int AIbuild(int playno);
int AIupgrade(int playno);
int AItrain(int playno);
int AIattack(int playno, int totplay);
void AIresurrect(int playno, int dead);

//cli
void mapcli(int playno);
void villagecli(int playno);
void refreshcli(int playno);

#endif //TASK1_VILLAGEGAME_H
