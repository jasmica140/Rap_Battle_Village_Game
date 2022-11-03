#ifndef TASK1_TROOPS_H
#define TASK1_TROOPS_H

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
    bool army{};
    int loc[2]{};             //troop location
    int resource[3]{};      //amount of resources taken from village after attack

    Troops() = default;

    Troops(int a, int b, int c, int d, int e, string f, string g, bool h, int i[2], int j[3]){
        cost = a;           //cost of training
        health = b;
        attack = c;         //strength
        carrycap = d;       //carrying capacity
        speed = e;          //marching speed
        status = f;        //status of troop - army/stationed/dead
        type = g;          //type of troop - untrained/rookie/expert/master
        army = h;
        loc[0] = i[0];             //troop location
        loc[1] = i[1];
        resource[0] = j[0];      //amount of resources taken from village after attack
        resource[1] = j[1];
        resource[2] = j[2];
    }
};

extern Troops troops[maxplay][maxtroops];


#endif //TASK1_TROOPS_H
