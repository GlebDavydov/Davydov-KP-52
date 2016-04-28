#include <windows.h>
#include <SFML/Graphics.hpp>
#include <time.h>
#define DC 4 //"D"istance "C"onstant

#include "main.h"

enum direction{N, NE, E, SE, S, SW, W, NW};

using namespace sf;

class map_point{
    public:
        int x;
        int y;
        int occupied;
        Sprite sp;
        map_point(){
            x = 0;
            y = 0;
            occupied = 1;
        }
        map_point(int xc, int yc, int isocc){
            if(x >= 30 || x < 0 || y >= 30 || y < 0){
                x = 0;
                y = 0;
            }
            x = xc;
            y = yc;
            occupied = isocc;
            sp.setPosition(307 + 30*x, 8 + 30*y);
        }
        void textureSet(Texture txt){
            sp.setTexture(txt);
        }
};

/*class battle_robot{
    public:
        int maxAp;
        int currAp;
        int dir;
        map_point position;
};*/

//int star_distance_count(map bf, map_point start, map_point dest);

int DLL_EXPORT battlefield(RenderWindow& window){
    window.clear(Color::Black);
    Texture land, obst; // allowed, restricted, pers, bn, bne, be, bse, bs, bsw, bw, bnw;
    land.loadFromFile("land.png");
    obst.loadFromFile("obst.png");
    /*allowed.loadFromFile("allowed.png");
    restricted.loadFromFile("restricted.png");
    pers.loadFromFile("personel.png");
    bn.loadFromFile("bot_n.png");
    bne.loadFromFile("bot_ne.png");
    be.loadFromFile("bot_e.png");
    bse.loadFromFile("bot_se.png");
    bs.loadFromFile("bot_s.png");
    bsw.loadFromFile("bot_sw.png");
    bw.loadFromFile("bot_w.png");
    bnw.loadFromFile("bot_nw.png");*/
    map_point point[30][30];
    for(int i = 0; i < 30*30; i++){
        if(i % 43 != 0 && i != 0){
                point[i/30][i%30] = *(new map_point(i/30, i%30, 0));
                point[i/30][i%30].textureSet(land);
        } else {
                point[i/30][i%30] = *(new map_point(i/30, i%30, 1));
                point[i/30][i%30].textureSet(obst);
        }
    }
    Event event;
    while(window.pollEvent(event)){
        for(int i = 0; i < 30*30; i++){
            window.draw(point[i/30][i%30].sp);
        }
        if (event.type == Event::KeyPressed){
            if (event.key.code == sf::Keyboard::Escape){
                return 0;
            }
        }
        window.display();
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
