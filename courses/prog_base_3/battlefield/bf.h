#ifndef BF_H_INCLUDED
#define BF_H_INCLUDED

#include "guns.h"

#define DC 4 //"D"istance "C"onstant

#define TS 6 //"T"eam "S"ize

#define n 25
#define m 25

enum faction{RED, BLUE};

typedef enum direction{NODIR = 0, N = 1, NE, E, SE, S, SW, W, NW}direction;

typedef enum cell{REST = 0, FREE, BOT_ALLY, BOT_ENEMY}cell;

typedef enum model{TANK, CHARGER, SEEKER, TROOPER}model;

typedef enum land_type_s{
    GRSS = 1,
    WALL
}land;

typedef struct position{
    int x;
    int y;
}position;


class battle_robot{
    public:
        int destroyed;
        int maxAp;
        int currAp;
        int hp;
        int maxhp;
        int armor;
        Weapon *gun1;
        Weapon *gun2;
        model rm;
        direction dir;
        position pos;
        int tm;
        battle_robot(){
            destroyed = 0;
            rm = TROOPER;
            maxAp = 112;
            currAp = 112;
            armor = 12;
            maxhp = 125;
            hp = 125;
            this->gun1 = NULL;
            this->gun2 = NULL;
            dir = S;
            pos.x = 0;
            pos.y = 0;
        }
        battle_robot(Weapon *gun1, Weapon *gun2){
            destroyed = 0;
            rm = TROOPER;
            maxAp = 112;
            currAp = 112;
            armor = 12;
            maxhp = 125;
            hp = 125;
            this->gun1 = gun1;
            this->gun2 = gun2;
            dir = S;
            pos.x = 0;
            pos.y = 0;
        }
        battle_robot(model rm, Weapon *gun1, Weapon *gun2){
            destroyed = 0;
            this->rm = rm;
            this->gun1 = gun1;
            this->gun2 = gun2;
            switch(m){
            case TANK: //slow but brutal, heavy fire support at any distance
                maxAp = 44;
                armor = 25;
                maxhp = 150;
            break;
            case CHARGER: //fast but unused to long distances
                maxAp = 60;
                armor = 6;
                maxhp = 140;
            break;
            case SEEKER: //performs best at long distances
                maxAp = 52;
                armor = 20;
                maxhp = 100;
            break;
            case TROOPER: //useful in any case
            default:
                maxAp = 56;
                armor = 12;
                maxhp = 125;
            break;
            }
            hp = maxhp;
            currAp = maxAp;
            dir = S;
            pos.x = 0;
            pos.y = 0;
        }
};

int walk_distance_count(direction dsourse, int sx, int sy, int dx, int dy, int count, direction *sequence);
//int dijstra_distance_count(land bf, int px, int py, battle_robot *team, int rcount, battle_robot walker, direction *sequence);
cell check_walkable(land bf[n][m], int px, int py, battle_robot* team, int rcount, int tm);
std::string pathFind( const int & xStart, const int & yStart,
                 const int & xFinish, const int & yFinish, land bf[n][m], battle_robot *bot);
void root_to_direction(std::string &route, direction *sequence);
void bot_walk(battle_robot &bot, int count, direction *sequence);
void bot_turn(battle_robot &bot, int x, int y);
direction belongs_to_sector(battle_robot &bot, int x, int y);


#endif // BF_H_INCLUDED
