#ifndef BF_H_INCLUDED
#define BF_H_INCLUDED

#define DC 4 //"D"istance "C"onstant

#define TS 6 //"T"eam "S"ize

#define RDP 1000 //"R"obot "D"is"p"osition

#define n 20

enum faction{RED, BLUE};

typedef enum direction{NODIR = 0, N = 1, NE, E, SE, S, SW, W, NW}direction;

typedef enum cell{REST = 0, FREE, BOT_ALLY, BOT_ENEMY}cell;

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
        int maxAp;
        int currAp;
        direction dir;
        position pos;
        int tm;
        battle_robot(){
            maxAp = 100;
            currAp = 100;
            dir = S;
            pos.x = 0;
            pos.y = 0;
        }
};

int walk_distance_count(direction dsourse, int sx, int sy, int dx, int dy, int count, direction *sequence);
//int dijstra_distance_count(land bf, int px, int py, battle_robot *team, int rcount, battle_robot walker, direction *sequence);
cell check_walkable(land bf[n][n], int px, int py, battle_robot* team, int rcount, int tm);
std::string pathFind( const int & xStart, const int & yStart,
                 const int & xFinish, const int & yFinish, land bf[n][n], battle_robot *bot);
void root_to_direction(std::string &route, direction *sequence);
void bot_walk(battle_robot &bot, int count, direction *sequence);
void bot_turn(battle_robot &bot, int x, int y);
direction belongs_to_sector(battle_robot &bot, int x, int y);


#endif // BF_H_INCLUDED
