#include <windows.h>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <string.h>

#include "main.h"
#include "bf.h"

using namespace sf;

int DLL_EXPORT battlefield(RenderWindow& window){
      land battlefield[n][n]{
        {WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL},//1
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//2
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//3
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//4
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//5
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//6
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//7
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//8
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//9
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//10
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//11
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL,WALL,WALL,WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//12
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//13
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//14
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//15
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//16
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//17
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//18
        {WALL,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,GRSS,WALL},//19
        {WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL}//20
    };
    window.clear(Color::Black);
    Texture bfbg,
    grass, stone,
    allowed, restricted, pers, enemy, that,
    bn, bne, be, bse, bs, bsw, bw, bnw;

    //Initial sprites&textures&etc load
    Image imbn, imbne, imbe, imbse, imbs, imbsw, imbw, imbnw;
    imbn.loadFromFile("iso/robot.png");
    imbne.loadFromFile("iso/robot.png");
    imbe.loadFromFile("iso/robot.png");
    imbse.loadFromFile("iso/robot.png");
    imbs.loadFromFile("iso/robot.png");
    imbnw.loadFromFile("iso/robot.png");
    imbnw.flipHorizontally();
    imbw.loadFromFile("iso/robot.png");
    imbw.flipHorizontally();
    imbsw.loadFromFile("iso/robot.png");
    imbsw.flipHorizontally();
    imbn.createMaskFromColor(Color(255, 0, 255));
    imbne.createMaskFromColor(Color(255, 0, 255));
    imbe.createMaskFromColor(Color(255, 0, 255));
    imbse.createMaskFromColor(Color(255, 0, 255));
    imbs.createMaskFromColor(Color(255, 0, 255));
    imbsw.createMaskFromColor(Color(255, 0, 255));
    imbw.createMaskFromColor(Color(255, 0, 255));
    imbnw.createMaskFromColor(Color(255, 0, 255));
    bfbg.loadFromFile("bfbg.jpg");
    grass.loadFromFile("iso/land_grass.png");
    stone.loadFromFile("iso/obst_stone.png");
    allowed.loadFromFile("iso/allowed.png");
    restricted.loadFromFile("iso/restricted.png");
    enemy.loadFromFile("iso/enemy.png");
    pers.loadFromFile("iso/personnel.png");
    bn.loadFromImage(imbn, IntRect(1, 7, 25, 33));
    bne.loadFromImage(imbne, IntRect(218, 7, 20, 38));
    be.loadFromImage(imbe, IntRect(419, 7, 17, 41));
    bse.loadFromImage(imbse, IntRect(554, 7, 22, 39));
    bs.loadFromImage(imbs, IntRect(121, 59, 25, 38));
    bsw.loadFromImage(imbsw, IntRect(640-554-22, 7, 22, 39));
    bw.loadFromImage(imbw, IntRect(650-419-17, 7, 17, 41));
    bnw.loadFromImage(imbnw, IntRect(640-218-20, 7, 20, 38));
    that.loadFromFile("iso/selected.png");
    Sprite bfback(bfbg);
    Sprite mouseCurrSprite;
    bfback.setPosition(0,0);
    Sprite bfsprite[n][n];
    Text nextturn;
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
    int curr_faction = RED;
    for(int i = 0; i < TS; i++){
        bot[i] = *(new battle_robot());
        bot[i].pos.x = i*2 + 1;
        bot[i].pos.y = i%2 + 1;
        bot[i].tm = curr_faction+i%2;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= i; j++){
            switch(battlefield[i-j][j]){
            case WALL:
                bfsprite[i-j][j].setTexture(stone);
                bfsprite[i-j][j].setPosition(44+32*(n-1-i)+64*j, 32+16*i);
                break;
            case GRSS:
            default:
                bfsprite[i-j][j].setTexture(grass);
                bfsprite[i-j][j].setPosition(44+32*(n-1-i)+64*j, 64+16*i);
            }
        }
    }
    for(int i = n - 1; i >= 0; i--){
        for(int j = 0; j <= i; j++){
            switch(battlefield[n-1-j][n-1-i+j]){
            case WALL:
                bfsprite[n-1-j][n-1-i+j].setTexture(stone);
                bfsprite[n-1-j][n-1-i+j].setPosition(44+32*(n-1-i)+64*j, 32+16*(2*n-2-i));
                break;
            case GRSS:
            default:
                bfsprite[n-1-j][n-1-i+j].setTexture(grass);
                bfsprite[n-1-j][n-1-i+j].setPosition(44+32*(n-1-i)+64*j, 64+16*(2*n-2-i));
            }
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

        for(int i = 0; i < n*n; i++){
            window.draw(bfsprite[i/n][i%n]);
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
            Sleep(100); //!don't think I'll put it on with the animation
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
            for(int i = 0; i < n*n; i++){
                window.draw(bfsprite[i/n][i%n]);
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
                                tdist.setPosition(438 + 30*xcoord, 138 + 30 *ycoord);
                                window.draw(tdist);
                                mouseCurrSprite.setTexture(allowed);
                            } else {
                                mouseCurrSprite.setTexture(restricted);
                                //!@todo special texture for insuff AP
                            }
                        }else if (c == BOT_ALLY){
                            mouseCurrSprite.setTexture(pers);
                        }else if(c == BOT_ENEMY){
                            mouseCurrSprite.setTexture(enemy);
                        }else{
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
                    }else if(IntRect(1136, 638, 100, 30).contains(Mouse::getPosition(window))){
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
                    }} else if(event.mouseButton.button == Mouse::Right){
                        if(IntRect(433, 133, 450, 450).contains(Mouse::getPosition(window))){
                            xcoord = ((int)Mouse::getPosition(window).x-433)/30;
                            ycoord = ((int)Mouse::getPosition(window).y-133)/30;
                            //cell c;
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
