#include <windows.h>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <string.h>

#include "main.h"
#include "bf.h"
//#include "view.h"
#include "shooting.h"

using namespace sf;

void draw_everything(RenderWindow &window, land battlefield[n][m], Sprite bfsprite[n][m],
Sprite selectedSprite, Sprite botsprite[TS], battle_robot bot[TS], int selected);

Weapon *claw = new Weapon(MELEE, 30, 1, 0, 1.0, 0.67, 0, 0.25, 0);
Weapon *hammer = new Weapon(MELEE, 45, 1, 0, 1.0, 0.9, 0, 0.33, 0);
Weapon *mortar = new Weapon(ART, 35, 16, 0, 0.94, 0.4, 0.33, 0.35, 0);
Weapon *mlrs = new Weapon(ART, 40, 32, 3, 0.92, 0.4, 0.25, 0.25, 0.55);
Weapon *missile = new Weapon(ART, 60, 28, 0, 0.99, 0.67, 0, 0.55, 0.0);
Weapon *minigun = new Weapon(PROJ, 20, 20, 4, 0.9, 0.75, 0, 0.2, 0.45);
Weapon *laser = new Weapon(PROJ, 25, 100, 0, 0.99, 0.95, 0, 0.35, 0);
Weapon *plasma = new Weapon(PROJ, 35, 24, 2, 0.96, 0.67, 0, 0.35, 0.55);
Weapon *cannon = new Weapon(PROJ, 45, 32, 0, 0.98, 0.85, 0.2, 0.4, 0);
Weapon *flamer = new Weapon(FLAMER, 30, 8, 0, 0, 1, 0, 0.25, 0);

int DLL_EXPORT battlefield(RenderWindow& window){
    Clock clock;
     land battlefield[n][m] = {GRSS};
     for(int i = 0; i < n*m; i++){
        if(i/n == 0 ||i%m == 0)
            battlefield[i/n][i%m] = WALL;
     }
        /*{WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL},//1
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//2
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//3
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//4
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//5
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//6
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,WALL,WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//7
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//8
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,WALL,WALL,WALL,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//9
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//10
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//11
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//12
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//13
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//14
        {WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL}//15
    };*/
    window.clear(Color::Black);
    Texture bfbg,
    grass, stone,
    allowed, restricted, pers, enemy, that,
    botblue, botred;

    //Initial sprites&textures&etc load
    botblue.loadFromFile("textures/botblue.png");
    botred.loadFromFile("textures/botred.png");
    bfbg.loadFromFile("bfbg.jpg");
    grass.loadFromFile("textures/land_grass.png");
    stone.loadFromFile("textures/wall_brick.png");
    allowed.loadFromFile("textures/allowed.png");
    restricted.loadFromFile("textures/restricted.png");
    enemy.loadFromFile("textures/enemy.png");
    pers.loadFromFile("textures/personel.png");
    that.loadFromFile("textures/chosen.png");
    Sprite bfback(bfbg);
    Sprite mouseCurrSprite;
    bfback.setPosition(0,0);
    Sprite bfsprite[n][m];
    Text nextturn; //!@todo button
    Text tdist;
    Font font;
    font.loadFromFile("arial.ttf");
    Sprite botsprite[TS];
    Sprite selectedSprite;
    selectedSprite.setTexture(that);
    Vector2i localPosition;

    //objects preparing
    int selected = 0;
    int moves = 0;
    battle_robot bot[TS];
    direction seq[225] = {NODIR};
    tdist.setCharacterSize(20);
    tdist.setColor(Color::Magenta);
    tdist.setFont(font);
    nextturn.setCharacterSize(30);
    nextturn.setFont(font);
    nextturn.setColor(Color::White);
    nextturn.setString("END TURN");
    nextturn.setPosition(1136, 638);
    int curr_faction = RED;
    for(int i = 0; i < TS; i++){
        bot[i] = *(new battle_robot(minigun, plasma));
        bot[i].pos.x = i*2 + 1;
        bot[i].pos.y = i%2 + 1;
        bot[i].tm = curr_faction+i%2;
        if(i%2){
            botsprite[i].setTexture(botblue);
        }else{
            botsprite[i].setTexture(botred);
        }
    }
    for(int i = 0; i < n*m; i++){
        bfsprite[i/n][i%m].setPosition(32*(i/n), 32*(i%m));
        switch(battlefield[i/n][i%m]){
        case WALL:
            bfsprite[i/n][i%m].setTexture(stone);
            break;
        case GRSS:
        default:
            bfsprite[i/n][i%m].setTexture(grass);
        }
    }

    //view.reset(FloatRect(0, 0, screen_width, screen_height));
    //view.setCenter(screen_width/2, screen_height/2);

    //Main loop
    while(window.isOpen()){
        //float time = clock.getElapsedTime().asMicroseconds();
        //clock.restart();
        //time = time/800;
        int xcoord;
        int ycoord;
        Event event;
        nextturn.setColor(Color::Red);

        while(moves){
            window.clear(Color::Black);
            window.draw(bfback);
            bot_walk(bot[selected], moves - 1, seq);
            moves++;
            if(moves > 255)
                moves = 0;
            if(seq[moves - 1] == NODIR)
                moves = 0;
            Sleep(100); //!temp plug until the animation is rdy

            draw_everything(window, battlefield, bfsprite, selectedSprite, botsprite, bot, selected);
            window.draw(nextturn);
            window.display();
        }
        /*localPosition = Mouse::getPosition(window);
        xcoord = ((int)Mouse::getPosition(window).x)/32;
        ycoord = ((int)Mouse::getPosition(window).y)/32;
        if (localPosition.x < 32) { view.move(-0.2*time, 0); }
		if (localPosition.x > window.getSize().x-32) { view.move(0.2*time, 0); }
		if (localPosition.y > window.getSize().y-32) { view.move(0, 0.2*time); }
		if (localPosition.y < 32) {  view.move(0, -0.2*time); }*/
        while(window.pollEvent(event)){
            //initial drawing
            window.clear(Color::Black);
            window.draw(bfback);

            nextturn.setColor(Color::White);
            draw_everything(window, battlefield, bfsprite, selectedSprite, botsprite, bot, selected);


                //polling events
                switch(event.type){
                case Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape){
                    return 0;
                    }
                    break;
                case Event::MouseMoved:{
                    if(IntRect(1136, 638, 100, 30).contains(Mouse::getPosition(window))){
                        nextturn.setColor(Color::Red);
                    }else {
                        xcoord = ((int)Mouse::getPosition(window).x)/32;
                        ycoord = ((int)Mouse::getPosition(window).y)/32;
                        if(xcoord < 0 || xcoord > m || ycoord < 0 || ycoord > n)
                            break;
                        cell c = check_walkable(battlefield, xcoord, ycoord, bot, TS, curr_faction);
                        if(c == FREE){

                            std::string route = pathFind(bot[selected].pos.x, bot[selected].pos.y, xcoord, ycoord, battlefield, bot);
                            root_to_direction(route, seq);
                            /*std::cout << route << std::endl;
                            int i = 0;
                            while(seq[i] != NODIR){
                                std::cout << i << ". " << seq[i] << std::endl;
                                i++;
                            };*/
                            int dist = walk_distance_count(bot[selected].dir, bot[selected].pos.x, bot[selected].pos.y, xcoord, ycoord, 0, seq);
                            if(dist <= bot[selected].currAp){
                                char str[10];
                                sprintf(str, "%d", dist);
                                tdist.setString(str);
                                tdist.setPosition(5 + 32*xcoord, 5 + 32 *ycoord);
                                window.draw(tdist);
                                mouseCurrSprite.setTexture(allowed);
                            } else {
                                mouseCurrSprite.setTexture(restricted);
                            }
                        }else if (c == BOT_ALLY){
                            mouseCurrSprite.setTexture(pers);
                        }else if(c == BOT_ENEMY){
                            //mouseCurrSprite.setTexture(enemy);
                            mouseCurrSprite.setTexture(restricted);
                            position p = track(battlefield, bot[selected].pos.x, bot[selected].pos.y, xcoord, ycoord, bot, curr_faction);
                            char str[10];
                            sprintf(str, "XX");
                            tdist.setString(str);
                            tdist.setPosition(5 + 32*p.x, 5 + 32 *p.y);
                            window.draw(tdist);
                        }else{
                            mouseCurrSprite.setTexture(restricted);
                        }
                        mouseCurrSprite.setPosition(32*xcoord, 32*ycoord);
                        window.draw(mouseCurrSprite);
                    }
                    break;
                }
                case Event::MouseButtonPressed:{
                    if(event.mouseButton.button == Mouse::Left){
                        if(IntRect(1136, 638, 100, 30).contains(Mouse::getPosition(window))){
                            for(int i = 0; i < TS; i++){
                                bot[i].currAp = bot[i].maxAp;
                            }
                            curr_faction = (++curr_faction)%2;
                            for(int i = 0; i < TS; i++){
                                if(bot[i].tm == curr_faction){
                                    selected = i;
                                    break;
                                }
                            }
                        } else {
                        xcoord = ((int)Mouse::getPosition(window).x)/32;
                        ycoord = ((int)Mouse::getPosition(window).y)/32;
                        if(xcoord < 0 || xcoord > m || ycoord < 0 || ycoord > n)
                            break;
                        cell c;
                        c = check_walkable(battlefield, xcoord, ycoord, bot, TS, curr_faction);
                        if(c == BOT_ALLY){
                            for(int i = 0; i < TS; i++){
                                if(bot[i].pos.x == xcoord && bot[i].pos.y == ycoord)
                                    selected = i;
                            }
                        }else if(c == BOT_ENEMY){

                            //!@todo
                        }else if (c==FREE){
                                std::string route = pathFind(bot[selected].pos.x, bot[selected].pos.y, xcoord, ycoord, battlefield, bot);
                                root_to_direction(route, seq);
                            if(walk_distance_count(bot[selected].dir, bot[selected].pos.x, bot[selected].pos.y, xcoord, ycoord, 0, seq) <= bot[selected].currAp){
                                bot[selected].currAp -= walk_distance_count(bot[selected].dir, bot[selected].pos.x, bot[selected].pos.y, xcoord, ycoord, 0, seq);
                                moves = 1;
                            }//!@todo message if insuff AP
                        }
                    }} else if(event.mouseButton.button == Mouse::Right){
                        xcoord = ((int)Mouse::getPosition(window).x)/32;
                        ycoord = ((int)Mouse::getPosition(window).y)/32;
                        if(xcoord < 0 || xcoord >= m || ycoord < 0 || ycoord >= n)
                            break;
                        //cell c;
                        bot_turn(bot[selected], xcoord, ycoord);
                    }
                    break;
                }
                default:
                    break;
                }
            //window.setView(view);
            window.draw(nextturn);
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


void draw_everything(RenderWindow &window, land battlefield[n][m], Sprite bfsprite[n][m],
Sprite selectedSprite, Sprite botsprite[TS], battle_robot bot[TS], int selected){
    for(int i = 0; i < n*m; i++){
        window.draw(bfsprite[i/n][i%m]);
    }
    for(int i = 0; i < TS; i++){
        if(bot[i].destroyed)
            continue;
        float curr;
        int vs;
        int hs;
        switch(bot[i].dir){
        case N:
            curr = 270.0;
            vs = 32;
            hs = 0;
            break;
        case NE:
            curr = 315.0;
            vs = 16;
            hs = 0;
            break;
        case E:
            curr = 0.0;
            vs = 0;
            hs = 0;
            break;
        case SE:
            curr = 45.0;
            vs = 0;
            hs = 16;
            break;
        case SW:
            curr = 135.0;
            vs = 16;
            hs = 32;
            break;
        case W:
            curr = 180.0;
            hs = 32;
            vs = 32;
            break;
        case NW:
            curr = 225.0;
            vs = 32;
            hs = 16;
            break;
        case S:
        default:
            curr = 90.0;
            vs = 0;
            hs = 32;
            break;
        }
    botsprite[i].setRotation(curr);
    botsprite[i].setPosition(32*bot[i].pos.x + hs,32 * bot[i].pos.y + vs);
    window.draw(botsprite[i]);
    if(i == selected)
        selectedSprite.setPosition( 32*bot[i].pos.x, 32 * bot[i].pos.y);
    }
    window.draw(selectedSprite);
}

