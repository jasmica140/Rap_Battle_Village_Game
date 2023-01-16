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
#define maxrbuild 12
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
    string type;        //connections/grub/dollaz
    int amount{};

    Resource()= default;

    Resource(string type, int amount) : type(std::move(type)), amount(amount) {}
};

class Troops
{
public:
    int health{};
    int attack{};
    int carryCap{};       //carrying capacity
    int cost{};
    string type;          //snoopdawgz/biggies/tupacs

    Troops() = default;

    explicit Troops(string type){
        if(type=="snoopdawgz"){
            health = 70;
            attack = 10;
            cost = 5;
            carryCap = 10;
        }else if(type=="biggies"){
            health = 10;
            attack = 35;
            cost = 10;
            carryCap = 30;
        }else if(type=="tupacs"){
            health = 35;
            attack = 70;
            cost = 15;
            carryCap = 20;
        }
        this->type = std::move(type);
    }
};


class Army{

public:
    int loc[2]{};           //army locations
    int speed{};            //army speed
    int attack{};           //total attack of army
    int health{};           //total health of army
    int carryCap{};         //total carrying capacity of army
    int resource[3]{};      //amount of resources taken from village after attack
    int target{};           //target village id
    bool comeHome{};        //coming home

    vector<shared_ptr<Troops>> troops;

    Army() = default;

    void refresharmy(){

        int r=0, e=0;

        attack=0;
        health=0;
        carryCap=0;

        for(auto & troop : troops){

            attack += troop->attack;
            health += troop->health;
            carryCap += troop->carryCap;

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
    int level{};            //level 1-5
    int cost{};             //cost of upgrading
    int resOutput{};        //amount of resources to produce
    int troopCost{};        //cost of training troop

    Building() = default;

    Building(string type, int level, int cost) : type(std::move(type)), level(level), cost(cost) {}

    void refreshbuild(){

        if(type == "connections" || type == "grub" || type == "dollaz"){ //resource
            if(level == 1){
                resOutput = 50;
            }else if(level == 2){
                resOutput = 75;
            }else if(level == 3){
                resOutput = 120;
            }else if(level == 4){
                resOutput = 175;
            }else if(level == 4){
                resOutput = 250;
            }

        }else{ //troops
            troopCost = Troops(type).cost*(6-level);
        }
    }
};

class Village {

public:
    int id{};             //player index
    int loc[2]{};         //(x,y) - village location
    int health{};         //village health
    bool attack{};        //under attack
    bool real{};          //AI or real player

    vector<shared_ptr<Troops>> troops;
    vector<shared_ptr<Resource>> resource;
    vector<shared_ptr<Building>> rbuild;
    vector<shared_ptr<Building>> tbuild;
    vector<shared_ptr<Army>> army;

    Village()= default;

    Village(int id, const int loc[2], int health, bool attack, bool real) {
        this->id = id;
        this->loc[0] = loc[0];
        this->loc[1] = loc[1];
        this->health = health;
        this->attack = attack;
        this->real = real;
    }

    virtual ~Village() {

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
int startcli();
void refreshcli(int playno);

//other
int options(int n, string choices[],int y, int x, bool sameline);
void deleteplayer(int playno);

#endif //TASK1_VILLAGEGAME_H
