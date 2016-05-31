#include <windows.h>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <string.h>

#include "main.h"
#include "bf.h"

using namespace sf;

int DLL_EXPORT battlefield(RenderWindow& window){
     land battlefield[n][m]{
        {WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL},//1
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
    Sprite bfsprite[n][m];
    Text nextturn; //!@todo button
    Text tdist;
    Font font;
    font.loadFromFile("arial.ttf");
    Sprite botsprite[TS];
    Sprite selectedSprite;
    selectedSprite.setTexture(that);

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
    for(int i = 0; i < TS; i++){
        bot[i] = *(new battle_robot());
        bot[i].pos.x = i*2 + 1;
        bot[i].pos.y = i%2 + 1;
    }
    for(int i = 0; i < n*m; i++){
        bfsprite[i/n][i%m].setPosition(433+30*(i/n), 133+30*(i%m));
        switch(battlefield[i/n][i%m]){
        case WALL:
            bfsprite[i/n][i%m].setTexture(stone);
            break;
        case GRSS:
        default:
            bfsprite[i/n][i%m].setTexture(grass);
        }
    }

    //Main loop
    while(window.isOpen()){
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

        for(int i = 0; i < n*m; i++){
            window.draw(bfsprite[i/n][i%m]);
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
            Sleep(100); //!temp plug until the animation is rdy
            if(seq[moves - 1] == NODIR)
                moves = 0;
            window.draw(nextturn);
            window.draw(selectedSprite);
            window.display();
        }
        while(window.pollEvent(event)){
            //initial drawing
            window.clear(Color::Black);
            window.draw(bfback);

            nextturn.setColor(Color::White);
            for(int i = 0; i < n*m; i++){
                window.draw(bfsprite[i/n][i%m]);
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
                                tdist.setPosition(438 + 30*xcoord, 138 + 30 *ycoord);
                                window.draw(tdist);
                                mouseCurrSprite.setTexture(allowed);
                            } else {
                                mouseCurrSprite.setTexture(restricted);
                                //!@todo special texture for insuff AP
                            }
                        }else if (c == BOT){
                            mouseCurrSprite.setTexture(pers);
                        }else {
                            mouseCurrSprite.setTexture(restricted);
                        }
                        mouseCurrSprite.setPosition(433+30*xcoord, 133+30*ycoord);
                        window.draw(mouseCurrSprite);
                    } else if(IntRect(1136, 638, 100, 30).contains(Mouse::getPosition(window)))
                        nextturn.setColor(Color::Red);
                    break;
                }
                case Event::MouseButtonPressed:{
                    if(event.mouseButton.button == Mouse::Left){
                        if(IntRect(433, 133, 450, 450).contains(Mouse::getPosition(window))){
                        xcoord = ((int)Mouse::getPosition(window).x-433)/30;
                        ycoord = ((int)Mouse::getPosition(window).y-133)/30;
                        cell c;
                        c = check_walkable(battlefield, xcoord, ycoord, bot, TS);
                        if(c == BOT){
                            for(int i = 0; i < TS; i++){
                                if(bot[i].pos.x == xcoord && bot[i].pos.y == ycoord)
                                    selected = i;
                            }
                        } else if (c==FREE){
                                std::string route = pathFind(bot[selected].pos.x, bot[selected].pos.y, xcoord, ycoord, battlefield, bot);
                                root_to_direction(route, seq);
                            if(walk_distance_count(bot[selected].dir, bot[selected].pos.x, bot[selected].pos.y, xcoord, ycoord, 0, seq) <= bot[selected].currAp){
                                bot[selected].currAp -= walk_distance_count(bot[selected].dir, bot[selected].pos.x, bot[selected].pos.y, xcoord, ycoord, 0, seq);
                                moves = 1;
                            }//!@todo message if insuff AP
                        }
                    }else if(IntRect(1136, 638, 100, 30).contains(Mouse::getPosition(window))){
                        //!@todo team switch
                        for(int i = 0; i < TS; i++){
                            bot[i].currAp = bot[i].maxAp;
                        }
                    }} else if(event.mouseButton.button == Mouse::Right){
                        if(IntRect(433, 133, 450, 450).contains(Mouse::getPosition(window))){
                            xcoord = ((int)Mouse::getPosition(window).x-433)/30;
                            ycoord = ((int)Mouse::getPosition(window).y-133)/30;
                            cell c;
                            bot_turn(bot[selected], xcoord, ycoord);
                        }
                    }
                    break;
                }
                default:
                    break;
                }
            window.draw(nextturn);
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
