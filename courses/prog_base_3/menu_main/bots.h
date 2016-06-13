#ifndef BOTS_H_INCLUDED
#define BOTS_H_INCLUDED

#define n 64
#define m 64

#define TS 10

enum step_mode{MP, AI_DUMB, AI_EVIL, AI_SMART};

enum guns{CLAW = 0, HAMMER, MORTAR, MLRS, MISSILE, MINIGUN, LASER, PLASMA, CANNON, FLAMETHROWER};

typedef enum model{TANK, CHARGER, SEEKER, TROOPER}model;

typedef struct blueprint{
    model mod;
    int gun1;
    int gun2;
}blueprint;

#endif // BOTS_H_INCLUDED

