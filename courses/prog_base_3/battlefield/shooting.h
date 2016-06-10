#ifndef SHOOTING_H_INCLUDED
#define SHOOTING_H_INCLUDED
#include "bf.h"

int eucl_dist_count(int xs, int ys, int xd, int yd);
position track(land bf[n][m], int xs, int ys, int xd, int yd, battle_robot bot[TS], int tm); //returns coords of the first obstacle or coords of destination if no obstacles
position chooseRandom(int x, int y, float deriv);
void destroyRobot(land bf[n][m], battle_robot bot[TS], int botnumber);
float accuracy_count(int x, int y, Weapon *gun);
int damage_count(battle_robot &bot, Weapon *gun);

#endif // SHOOTING_H_INCLUDED
