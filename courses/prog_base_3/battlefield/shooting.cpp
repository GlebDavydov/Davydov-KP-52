#include <windows.h>
#include <SFML/Graphics.hpp>
#include <math.h>

#include "shooting.h"

int eucl_dist_count(int xs, int ys, int xd, int yd){
    int dx = xd - xs;
    int dy = yd - ys;
    return (int)sqrt(dx*dx + dy*dy);
}

position track(land bf[n][m], int xs, int ys, int xd, int yd, battle_robot bot[TS], int tm){
    int cx = xs;
    int cy = ys;
    float dx = (float)(xd - xs);
    float dy = (float)(yd - ys);
    cx += (int)ceil(dx/sqrt(dx*dx + dy*dy));
    cy += (int)ceil(dy/sqrt(dx*dx + dy*dy));
    while(cx != xd || cy != yd){
    cx += (int)ceil(dx/sqrt(dx*dx + dy*dy));
    cy += (int)ceil(dy/sqrt(dx*dx + dy*dy));
        if((cx == xd && cy == yd) || check_walkable(bf, cx, cy, bot, TS, tm) != FREE){
            position newPos = *(new position());
            newPos.x = cx;
            newPos.y = cy;
            return newPos;
        }
    }
    position newPos = *(new position());
    newPos.x = xd;
    newPos.y = yd;
    return newPos;
}

position chooseRandom(int x, int y, float deriv);
void destroyRobot(land bf[n][m], battle_robot bot[TS], int botnumber);
float accuracy_count(int x, int y, Weapon *gun);
int damage_count(battle_robot &bot, Weapon *gun);
