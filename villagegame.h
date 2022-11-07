#ifndef TASK1_VILLAGEGAME_H
#define TASK1_VILLAGEGAME_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <curses.h>

using namespace std;

#define mapx 13
#define mapy 11
#define maxhealth 100
#define maxplay 10
#define maxtroops 50
#define maxrbuild 50
#define maxtbuild 50
#define texty 25

//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


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
    int loc[2]{};           //troop location
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


class ResourceBuidlings
{
public:
    string type;            //type of resource generated
    int level{};
};
extern ResourceBuidlings rbuild[maxplay][maxrbuild];


class TroopBuidlings
{
public:
    string type;          //type of resource required
    int level{};
};
extern TroopBuidlings tbuild[maxplay][maxtbuild];



//main
int options(int n, string choices[n]);
void gameloop();

//setup
int *gamesetup();


//roundphases
int turnphase(int playno, int totplay);
bool marching(int playno, int villno, int mspeed);
int endround(int playno);
void startround(int playno);

//turnphases
void friendtroop(int playno, int totplay);
int enemytroop(int playno, int totplay);
void earnres(int playno);
void actions(int playno, int totplay);

//actions
void build(int playno);
int upgrade(int playno);
int train(int playno);
void attack(int playno, int villno, int totplay);

//cli
void mapcli();
void villagecli(int playno);
void refreshcli(int playno);

void moveTo(int row, int col);

#endif //TASK1_VILLAGEGAME_H
