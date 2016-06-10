#include <windows.h>
#include <SFML/Graphics.hpp>
#include <math.h>

#include "shooting.h"

int round(float fx){
    int ix;
    if(fx < 0){
        ix = floor(fx - 0.5);
    }else{
        ix = floor(fx + 0.5);
    }
    return ix;
}

int eucl_dist_count(int xs, int ys, int xd, int yd){
    int dx = xd - xs;
    int dy = yd - ys;
    return (int)sqrt(dx*dx + dy*dy);
}

position track(land bf[n][m], int xs, int ys, int xd, int yd, battle_robot bot[TS], int tm){
    double cx = (double)xs;
    double cy = (double)ys;
    double dx = (double)(xd - xs);
    double dy = (double)(yd - ys);
    while(round(cx) != xd || round(cy) != yd){
        cx += dx/sqrt(dx*dx + dy*dy);
        cy += dy/sqrt(dx*dx + dy*dy);
        printf("\nx %.2f, y %.2f", cx, cy);
        if((round(cx) == xd && round(cy) == yd) || check_walkable(bf, round(cx), round(cy), bot, TS, tm) != FREE){
            position newPos = *(new position());
            newPos.x = round(cx);
            newPos.y = round(cy);
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
