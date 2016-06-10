#ifndef SHOOTING_H_INCLUDED
#define SHOOTING_H_INCLUDED
#include "bf.h"

int eucl_dist_count(int xs, int ys, int xd, int yd);
position track(land bf[n][m], int xs, int ys, int xd, int yd, battle_robot bot[TS], int tm); //returns coords of the first obstacle or coords of destination if no obstacles
position chooseRandom(land bf[n][m], int x, int y, double acc);
//void destroyRobot(land bf[n][m], battle_robot bot[TS], int botnumber);
double accuracy_count(int distance, Weapon *gun);
int damage_count(battle_robot &bot, Weapon *gun, int distance);

#endif // SHOOTING_H_INCLUDED
