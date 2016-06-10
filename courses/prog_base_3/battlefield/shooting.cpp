#include <windows.h>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <math.h>

#include "shooting.h"

int my_round(double fx){
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

position track(land bf[n][m], int xs, int ys, int xd, int yd, battle_robot bot[TS]){
    double cx = (double)xs;
    double cy = (double)ys;
    double dx = (double)(xd - xs);
    double dy = (double)(yd - ys);
    while(my_round(cx) != xd || my_round(cy) != yd){
        cx += dx/sqrt(dx*dx + dy*dy);
        cy += dy/sqrt(dx*dx + dy*dy);
        if ((my_round(cx) == xd && my_round(cy) == yd) || (check_walkable(bf, my_round(cx), my_round(cy), bot, TS, RED) != FREE)){
            position newPos = *(new position());
            newPos.x = my_round(cx);
            newPos.y = my_round(cy);
            return newPos;
        }
    }
    position newPos = *(new position());
    newPos.x = xd;
    newPos.y = yd;
    return newPos;
}

position chooseRandom(land bf[n][m], int x, int y, double acc){
    printf("\naccuracy: %.2f", acc);
    int d = floor(1/acc);
    position pos = *(new position());
    pos.x = x;
    pos.y = y;
    do{pos.x += rand() % (2*d+1) - d;}while(pos.x < 0 || pos.x > n);
    do{pos.y += rand() % (2*d+1) - d;}while(pos.y < 0 || pos.y > m);
    return pos;
}

/*void destroyRobot(land bf[n][m], battle_robot bot[TS], int botnumber){

}*/

double accuracy_count(int distance, Weapon *gun){
    return pow(gun->accuracy, 1+log2(distance));
}

int damage_count(battle_robot &bot, Weapon *gun, int distance){
    if(gun->type == FLAMER){
        return my_round((double)(1.0 + (rand() % 201 - 100)/300.0) * gun->damage);
    }
    double pierce;
    if(gun->type == ART || gun->type == MELEE){
        pierce = (1.0 + (rand() % 201 - 100)/500.0) * gun->pierce;
    } else if(gun->type == PROJ){
        pierce = (1.0 + (rand() % 201 - 100)/500.0) * pow(gun->pierce, 1+log10(distance));
    }
    if(pierce < 0)
            pierce = -pierce;
    if(gun->damage * pierce > bot.armor){
        return my_round((double)(1.0 + (rand() % 201 - 100)/300.0) * gun->damage);
    } else {
        double tdm =  (1.0 + (rand() % 201 - 100)/300.0) * gun->damage;
        double mlt = (6*pierce)/bot.armor;
        tdm *= mlt;
        return my_round(tdm);
    }
}
