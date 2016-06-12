#ifndef BOTS_H_INCLUDED
#define BOTS_H_INCLUDED

#define n 64
#define m 64

#define TS 10

enum step_mode{MP, AI_DUMB, AI_EVIL, AI_SMART};

typedef enum land_type_s{
    GRSS = 1,
    RUIN,
    WALL
}land;

typedef struct position{
    int x;
    int y;
}position;


typedef enum guntype{MELEE, ART, FLAMER, PROJ}guntype;

typedef enum model{TANK, CHARGER, SEEKER, TROOPER}model;

#endif // BOTS_H_INCLUDED

