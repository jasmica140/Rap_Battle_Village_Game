#ifndef TASK1_VILLAGEGAME_H
#define TASK1_VILLAGEGAME_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <curses.h>
#include <clocale>
#include <utility>
#include <ctime>
#include <memory>
#include <vector>


using namespace std;

#define mapx 13
#define mapy 13
#define maxhealth 10000
#define maxplay 15
#define maxtroops 100
#define texty 26
#define textx 2
#define erry 38

extern WINDOW *win;

class Map{
public:
    string status = "     ";
};
extern Map map[mapx][mapy];

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

class Troops
{
public:
    int health{};
    int attack{};         //strength
    int carrycap{};       //carrying capacity
    string type;          //type of troop - untrained/rookie/expert/master

    Troops() = default;

    Troops(int b, int c, int d, string f){
        health = b;
        attack = c;         //strength
        carrycap = d;       //carrying capacity
        type = std::move(f);           //type of troop - untrained/rookie/expert/master
    }
};


class Army{

public:

    int loc[2]{};           //army locations
    int speed{};            //army speed
    int attack{};           //total attack of army
    int health{};           //total health of army
    int carrycap{};         //total carrying capacity of army
    int resource[3] = {0,0,0};      //amount of resources taken from village after attack
    int target{};           //target village no.

    vector<shared_ptr<Troops>> troops;

    Army() = default;

    void refresharmy(const Army& army){

        int r=0, e=0;

        attack=0;
        health=0;
        carrycap=0;

        for(auto & troop : troops){

            attack += troop->attack;
            health += troop->health;
            carrycap += troop->carrycap;

            if(troop->type == "rookie"){
                r++;
            }else if(troop->type == "expert"){
                e++;
            }
        }

        if(r>0){
            speed = 1;
        }else if(e>0){
            speed = 2;
        }else{
            speed = 3;
        }
    }

    void addtroops(const Troops& newtroop){
        auto t = make_shared<Troops>(newtroop);
        troops.push_back(std::move(t));
    }
};


class Building{

public:
    string type;            //type of resources/troops to generate
    int level{};
    int cost{};             //cost of upgrading
    int output{};           //amount of resources to produce/ cost to train troop

    Building() = default;

    Building(string a, int b, int c){
        type = std::move(a);
        level = b;
        cost = c;
    }

    void refreshbuild(){

        if(type == "tools" || type == "food" || type == "money"){ //resource
            if(level == 1){
                output = 50;
            }else if(level == 2){
                output = 75;
            }else if(level == 3){
                output = 120;
            }else if(level == 4){
                output = 175;
            }else if(level == 4){
                output = 250;
            }

        }else{ //troops

            if(type == "snoopdawgz"){
                output = 5;
            }else if(type == "biggies"){
                output = 15;
            }else{
                output = 10;
            }

            output *= (6 - level);
        }
    }
};


class Village {

public:
    int idx{};                            //player index
    int loc[2] = {0, 0};         //(x,y) - village location
    int health = maxhealth;               //village health
    bool attack = false;                  //under attack
    bool preal = true;                    //AI or real player

    vector<shared_ptr<Troops>> troops;
    vector<shared_ptr<Resource>> resource;
    vector<shared_ptr<Building>> rbuild;
    vector<shared_ptr<Building>> tbuild;
    vector<shared_ptr<Army>> army;

    Village()= default;

    Village(int i, const int a[2], int b, bool g, bool h) {
        idx = i;
        loc[0] = a[0];
        loc[1] = a[1];
        health = b;
        attack = g;
        preal = h;
    }

    void addtroops(const Troops& newtroop){
        auto t = make_shared<Troops>(newtroop);
        troops.push_back(std::move(t));
    }

    void addarmy(const Army& newarmy){
        auto a = make_shared<Army>(newarmy);
        army.push_back(std::move(a));
    }

    void addres(const Resource& newres){
        auto r = make_shared<Resource>(newres);
        resource.push_back(std::move(r));
    }

    void addrbuild(const Building& newbuild){
        auto rb = make_shared<Building>(newbuild);
        rbuild.push_back(std::move(rb));
    }

    void addtbuild(const Building& newbuild){
        auto tb = make_shared<Building>(newbuild);
        tbuild.push_back(std::move(tb));
    }
};
extern vector<unique_ptr<Village>> village;


//setup
int gamesetup();
void gameloop();

//roundphases
int turnphase(int playno, int roundno);
void marching(int playno, int armyno, int target, int mspeed);
int endround(int roundno);
void startround(int roundno);

//turnphases
void friendtroop(int playno);
int enemytroop(int playno);
void earnres(int playno);
int actions(int playno, int roundno);

//actions
int build(int playno);
int upgrade(int playno);
int train(int playno);
int attack(int playno);

//AI
int AIround1(int playno);
int AIbuild(int playno);
int AIupgrade(int playno);
int AItrain(int playno);
int AIattack(int playno);

//cli
void mapcli(int playno);
void villagecli(int playno);
int alertcli(int playno, const string& type);
void refreshcli(int playno);

//other
int options(int n, string choices[n],int y, int x, bool sameline);
void deleteplayer(int playno);


#endif //TASK1_VILLAGEGAME_H
