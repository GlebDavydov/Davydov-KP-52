#include <windows.h>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdio.h>
#include <string.h>
#define DC 4 //"D"istance "C"onstant

#include "main.h"

typedef enum direction{N, NE, E, SE, S, SW, W, NW}direction;

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
};

//int star_distance_count(map bf, map_point start, map_point dest);

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
    Texture grass, stone, bfbg, allowed, restricted, pers, bn, bne, be, bse, bs, bsw, bw, bnw;

    //Initial sprites&textures&etc load
    bfbg.loadFromFile("bfbg.jpg");
    grass.loadFromFile("land.png");
    stone.loadFromFile("obst.png");
    allowed.loadFromFile("allowed.png");
    restricted.loadFromFile("restricted.png");
    /*pers.loadFromFile("personel.png");
    bn.loadFromFile("bot_n.png");
    bne.loadFromFile("bot_ne.png");
    be.loadFromFile("bot_e.png");
    bse.loadFromFile("bot_se.png");
    bs.loadFromFile("bot_s.png");
    bsw.loadFromFile("bot_sw.png");
    bw.loadFromFile("bot_w.png");
    bnw.loadFromFile("bot_nw.png");*/
    Sprite bfback(bfbg);
    Sprite mouseCurrSprite;
    bfback.setPosition(0,0);
    Sprite bfsprite[15][15];
    Font font;
    font.loadFromFile("arial.ttf");

    //Drawing&preparing
    //battle_robot robot_team[6];
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
        int st;
        int xcoord;
        int ycoord;
        Event event;
        while(window.pollEvent(event)){
            window.clear(Color::Black);
            st = 0;
            window.draw(bfback);
            for(int i = 0; i < 15*15; i++){
                window.draw(bfsprite[i/15][i%15]);
            }
            switch(event.type){
            case Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape){
                    return 0;
                }
                break;
            case Event::MouseMoved:
                if(IntRect(433, 133, 450, 450).contains(Mouse::getPosition(window))){
                    xcoord = ((int)Mouse::getPosition(window).x-433)/30;
                    ycoord = ((int)Mouse::getPosition(window).y-133)/30;
                    /*char buf[100];
                    sprintf(buf, "X:%d\tY:%d", xcoord, ycoord);
                    Text text(buf, font, 24);
                    text.setPosition(100, 100);
                    window.draw(text);*/
                    st = 1;
                    if(battlefield[xcoord][ycoord] == GRSS){
                        mouseCurrSprite.setTexture(allowed);
                    }else if(battlefield[xcoord][ycoord] == WALL){
                        mouseCurrSprite.setTexture(restricted);
                    } else {
                        mouseCurrSprite.setColor(Color::Transparent);
                    }
                }
                break;
            default:
                break;
            }
            if(st){
                mouseCurrSprite.setPosition(433+30*xcoord, 133+30*ycoord);
                window.draw(mouseCurrSprite);
            }
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
