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
#define maxhealth 5000
#define maxplay 15
#define texty 25
#define erry 37

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
    int cost{};           //cost of training
    int health{};
    int attack{};         //strength
    int carrycap{};       //carrying capacity
    string type;          //type of troop - untrained/rookie/expert/master

    Troops() = default;

    Troops(int a, int b, int c, int d, string f){
        cost = a;           //cost of training
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
    int resource[3]{};      //amount of resources taken from village after attack
    int target{};           //target village no.

    vector<shared_ptr<Troops>> troops;

    Army() = default;

    void refresharmy(const Army& army, const int b[3], int c){

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

        resource[0] = b[0];
        resource[1] = b[1];
        resource[2] = b[2];
        target = c;
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

    Building() = default;

    Building(string a, int b, int c){
        type = std::move(a);
        level = b;
        cost = c;
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
void turnphase(int playno, int roundno);
void marching(int playno, int armyno, int target, int mspeed);
int endround(int roundno);
void startround(int playno);

//turnphases
void friendtroop(int playno);
void enemytroop(int playno);
void earnres(int playno);
void actions(int playno, int roundno);

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
