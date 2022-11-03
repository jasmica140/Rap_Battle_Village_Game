
#ifndef TASK1_RESOURCE_H
#define TASK1_RESOURCE_H

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

class Resource
{
public:
    string type;
    int amount{};

    Resource()= default;

    Resource(string a, int b){
        type = a;
        amount = b;
    }
};

extern Resource resource[maxplay][3];


#endif //TASK1_RESOURCE_H
