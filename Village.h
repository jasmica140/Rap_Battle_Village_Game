#ifndef TASK1_VILLAGE_H
#define TASK1_VILLAGE_H

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

class Village {
public:
    int loc[2] = {0, 0};          //(x,y)
    int health = maxhealth;               //village health
    int tbuildings = 0;                   //amount of troop-training buildings owned
    int rbuildings = 0;                   //amount of resource buildings owned
    int troops = maxtroops;               //amount of troops available
    bool ptype = true;                    //AI or real player

    Village()= default;

    Village(const int a[2], int b, int c, int d, int e, bool f) {
        loc[0] = a[0];
        loc[1] = a[1];
        health = b;
        tbuildings = c;
        rbuildings = d;
        troops = e;
        ptype = f;
    }
};

extern Village village[maxplay];


#endif //TASK1_VILLAGE_H
