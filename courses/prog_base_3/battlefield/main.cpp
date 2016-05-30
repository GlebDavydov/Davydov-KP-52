#include <windows.h>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#define DC 4 //"D"istance "C"onstant

#define TS 5 //"T"eam "S"ize

#define RDP 1000 //"R"obot "D"is"p"osition

#include "main.h"

typedef enum direction{NODIR = 0, N = 1, NE, E, SE, S, SW, W, NW}direction;

typedef enum cell{REST = 0, FREE, BOT}cell;

using namespace sf;

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
        battle_robot(){
            maxAp = 100;
            currAp = 100;
            dir = S;
            pos.x = 0;
            pos.y = 0;
        }
};

cell check_walkable(land bf[15][15], int px, int py, battle_robot* team, int rcount){
    if(bf[px][py] == WALL){
        return REST;
    } else for(int i = 0; i < rcount; i ++){
        if(team[i].pos.x == px && team[i].pos.y == py)
            return BOT;
    }
    return FREE;
}

int walk_distance_count(direction dsourse, int sx, int sy, int dx, int dy, int count, direction *sequence);

int star_distance_count(land bf, int px, int py, battle_robot *team, int rcount, battle_robot walker, direction *sequence){

}

int DLL_EXPORT battlefield(RenderWindow& window){
     land battlefield[15][15]{
        {WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL},//1
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//2
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//3
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//4
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//5
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//6
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//7
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//8
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL,WALL,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//9
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//10
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//11
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//12
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//13
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//14
        {WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL}//15
    };
    window.clear(Color::Black);
    Texture bfbg,
    grass, stone,
    allowed, restricted, pers, that,
    bn, bne, be, bse, bs, bsw, bw, bnw;

    //Initial sprites&textures&etc load
    bfbg.loadFromFile("bfbg.jpg");
    grass.loadFromFile("land.png");
    stone.loadFromFile("obst.png");
    allowed.loadFromFile("allowed.png");
    restricted.loadFromFile("restricted.png");
    pers.loadFromFile("personel.png");
    bn.loadFromFile("bot_n.png");
    bne.loadFromFile("bot_ne.png");
    be.loadFromFile("bot_e.png");
    bse.loadFromFile("bot_se.png");
    bs.loadFromFile("bot_s.png");
    bsw.loadFromFile("bot_sw.png");
    bw.loadFromFile("bot_w.png");
    bnw.loadFromFile("bot_nw.png");
    that.loadFromFile("chosen.png");
    Sprite bfback(bfbg);
    Sprite mouseCurrSprite;
    bfback.setPosition(0,0);
    Sprite bfsprite[15][15];
    Text tdist;
    Font font;
    font.loadFromFile("arial.ttf");
    Sprite botsprite[TS];
    Sprite selectedSprite;
    selectedSprite.setTexture(that);

    //objects preparing
    int selected = 0;
    battle_robot bot[TS];
    direction seq[225] = {NODIR};
    tdist.setCharacterSize(20);
    tdist.setColor(Color::Magenta);
    tdist.setFont(font);
    for(int i = 0; i < TS; i++){
        bot[i] = *(new battle_robot());
        bot[i].pos.x = i*2 + 1;
        bot[i].pos.y = i%2 + 1;
    }
    for(int i = 0; i < 15*15; i++){
        bfsprite[i/15][i%15].setPosition(433+30*(i/15), 133+30*(i%15));
        switch(battlefield[i/15][i%15]){
        case WALL:
            bfsprite[i/15][i%15].setTexture(stone);
            break;
        case GRSS:
        default:
            bfsprite[i/15][i%15].setTexture(grass);
        }
    }

    //Main loop
    while(window.isOpen()){
        int xcoord;
        int ycoord;
        Event event;
        while(window.pollEvent(event)){

            //initial drawing
            window.clear(Color::Black);
            window.draw(bfback);
            for(int i = 0; i < 15*15; i++){
                window.draw(bfsprite[i/15][i%15]);
            }
            for(int i = 0; i < TS; i++){
                botsprite[i].setPosition(433 + 30*bot[i].pos.x, 133 + 30 * bot[i].pos.y);
                Texture curr;
                switch(bot[i].dir){
                case N:
                    curr = bn;
                    break;
                case NE:
                    curr = bne;
                    break;
                case E:
                    curr = be;
                    break;
                case SE:
                    curr = bse;
                    break;
                case SW:
                    curr = bsw;
                    break;
                case W:
                    curr = bw;
                    break;
                case NW:
                    curr = bnw;
                    break;
                case S:
                default:
                    curr = bs;
                    break;
                }
                botsprite[i].setTexture(curr);
                window.draw(botsprite[i]);
                if(i == selected)
                    selectedSprite.setPosition(433 + 30*bot[i].pos.x, 133 + 30 * bot[i].pos.y);
            }


            //polling events
            switch(event.type){
            case Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape){
                    return 0;
                }
                break;
            case Event::MouseMoved:{
                if(IntRect(433, 133, 450, 450).contains(Mouse::getPosition(window))){
                    xcoord = ((int)Mouse::getPosition(window).x-433)/30;
                    ycoord = ((int)Mouse::getPosition(window).y-133)/30;
                    cell c = check_walkable(battlefield, xcoord, ycoord, bot, TS);
                    if(c == FREE){
                        mouseCurrSprite.setTexture(allowed);
                        int dist = walk_distance_count(bot[selected].dir, bot[selected].pos.x, bot[selected].pos.y, xcoord, ycoord, 0, seq);
                        char str[10];
                        sprintf(str, "%d", dist);
                        tdist.setString(str);
                        tdist.setPosition(438 + 30*xcoord, 138 + 30 *ycoord);
                        window.draw(tdist);
                    }else if (c == BOT){
                        mouseCurrSprite.setTexture(pers);
                    }else {
                        mouseCurrSprite.setTexture(restricted);
                    }
                    mouseCurrSprite.setPosition(433+30*xcoord, 133+30*ycoord);
                    window.draw(mouseCurrSprite);
                }
                break;
            }
            case Event::MouseButtonPressed:{
                if(event.mouseButton.button == Mouse::Left){
                    if(IntRect(433, 133, 450, 450).contains(Mouse::getPosition(window))){
                    xcoord = ((int)Mouse::getPosition(window).x-433)/30;
                    ycoord = ((int)Mouse::getPosition(window).y-133)/30;
                    if(check_walkable(battlefield, xcoord, ycoord, bot, TS) == BOT){
                        for(int i = 0; i < TS; i++){
                            if(bot[i].pos.x == xcoord && bot[i].pos.y == ycoord)
                                selected = i;
                        }
                    }
                }}
                break;
            }
            default:
                break;
            }
            window.draw(selectedSprite);
            window.display();
        }
    }
    return 1;
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}


int walk_distance_count(direction dsourse, int sx, int sy, int dx, int dy, int count, direction *sequence){
    direction newDir;
    int newx, newy;
    if(dx > sx){
        newx = sx + 1;
        if(dy > sy){
            newDir = SE;
            newy = sy + 1;
        }else if(dy < sy){
            newDir = NE;
            newy = sy - 1;
        } else{
            newy = sy;
            newDir = E;
        }
    }else if(dx < sx){
        newx = sx - 1;
        if(dy > sy){
            newDir = SW;
            newy = sy + 1;
        }else if(dy < sy){
            newDir = NW;
            newy = sy - 1;
        }else{
            newy = sy;
            newDir = W;
        }
    }else{
        newx = sx;
        if(dy > sy){
            newDir = S;
            newy = sy + 1;
        }else if(dy < sy){
            newDir = N;
            newy = sy - 1;
        } else
            return 0;
    }
    sequence[count] = newDir;
    int ddf = abs(newDir - dsourse);
    if(ddf != 4)
        ddf %= 4;
    return ddf + 4 + walk_distance_count(newDir, newx, newy, dx, dy, ++count, sequence);
}
