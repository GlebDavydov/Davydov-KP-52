#include <windows.h>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>

#include "main.h"
#include "bf.h"
//#include "view.h"
#include "shooting.h"
#include "main_functs.h"

enum guns{CLAW = 0, HAMMER, MORTAR, MLRS, MISSILE, MINIGUN, LASER, PLASMA, CANNON, FLAMETHROWER};

using namespace sf;

//enum message_type{ALERT, WIN, LOOSE};

    Texture bfbg,
    grass, stone, ruin,
    allowed, restricted, pers, enemy, that,
    botblue, botred,
    mybot, icon[4]; //!0=seeker 1=trooper 2=charger 3=tank
    Texture gunicon[10];
    Texture punch, bang, flares, firing, badabum, spell;
    Texture mapframe, maptmp;
    Texture nextturn_t;
    Texture nextturn_p;

    Sprite bfback;
    Sprite botsprite[TS];
    Sprite mystats, enemystats, myicon, enemyicon, mywp1, mywp2, hiswp1, hiswp2;
    Sprite frame, tmp;
    Sprite selectedSprite;
    Sprite selectedGun;
    Sprite strike;
    Sprite shooting;
    Sprite explosion;
    Sprite destruction;
    Sprite flames[25];
    Sprite smallbang[9];
    Sprite shell;
    Sprite mouseCurrSprite;
    Sprite bfsprite[n][m];
    Sprite nextturn;
    Text tdist;
    Text myhp, myap, hishp, hisap;
    Font font;


Weapon *claw = new Weapon(MELEE, 30.0, 1, 0, 1.0, 0.75, 0, 0.25, 0);
Weapon *hammer = new Weapon(MELEE, 45.0, 1, 0, 1.0, 0.9, 0, 0.33, 0);
Weapon *mortar = new Weapon(ART, 35.0, 16, 0, 0.94, 0.67, 0.33, 0.35, 0);
Weapon *mlrs = new Weapon(ART, 40.0, 32, 3, 0.89, 0.67, 0.25, 0.25, 0.55);
Weapon *missile = new Weapon(ART, 60.0, 28, 0, 0.99, 0.75, 0, 0.55, 0.0);
Weapon *minigun = new Weapon(PROJ, 20.0, 20, 4, 0.9, 0.85, 0, 0.2, 0.45);
Weapon *laser = new Weapon(PROJ, 25.0, 100, 0, 0.999, 0.95, 0, 0.35, 0);
Weapon *plasma = new Weapon(PROJ, 35.0, 24, 2, 0.96, 0.75, 0, 0.35, 0.55);
Weapon *cannon = new Weapon(PROJ, 45.0, 32, 0, 0.98, 0.85, 0.2, 0.33, 0);
Weapon *flamer = new Weapon(FLAMER, 30.0, 8, 0, 0, 1, 0, 0.45, 0);

typedef int(*step_callback)(RenderWindow &window, land battlefield[n][m], battle_robot bot[TS], int &currFaction);

static int shiftx;
static int shifty;

int DLL_EXPORT battlefield(RenderWindow& window, int stepMode, blueprint botset[TS]){
    shiftx = 48;
    shifty = 48;
    step_callback step = NULL;
    switch(stepMode){
    case MP:
        step = player_step;
        break;
    case AI_DUMB:
        step = ai_step_dumb;
        break;
    case AI_EVIL:
        step = ai_step_agressive;
        break;
    case AI_SMART:
    default:
        step = ai_step_alert;
        break;
    }
    shiftx = 48;
    shifty = 48;
    Clock clock;
    srand(time(NULL));

    Image micromap;
    micromap.loadFromFile("textures/micromap.png");
    land battlefield[n][m];
    battle_robot bot[TS];
    for(int i = 0; i < TS; i++){
        bot[i] = *(new battle_robot());
        bot[i].pos.x = -1;
        bot[i].pos.y = -1;
        bot[i].destroyed = 1;
    }
    int rbc = 0;
    int bbc = 0;
    for(int i = 0; i < n*m; i++){
        if(micromap.getPixel(i/n, i%m) == Color::White){
            battlefield[i/n][i%m] = GRSS;
        } else if(micromap.getPixel(i/n, i%m) == Color::Red){
            battlefield[i/n][i%m] = GRSS;
            if(rbc < TS/2){
                bot[rbc*2] = *(new battle_robot(botset[rbc].mod, NULL, NULL));
                gunChoose(botset[rbc].gun1, 0, bot[rbc*2]);
                gunChoose(botset[rbc].gun2, 1, bot[rbc*2]);
                bot[rbc*2].pos.x = i/n;
                bot[rbc*2].pos.y = i%n;
                rbc++;
            }
        } else if(micromap.getPixel(i/n, i%m) == Color::Blue){
            battlefield[i/n][i%m] = GRSS;
            if(bbc < TS/2){
                Weapon *gun1;
                Weapon *gun2;
                bot[bbc*2 + 1] = *(new battle_robot(botset[bbc+TS/2].mod, gun1, gun2));
                gunChoose(botset[bbc + TS/2].gun1, 0, bot[bbc*2+1]);
                gunChoose(botset[bbc + TS/2].gun2, 1, bot[bbc*2+1]);
                bot[bbc*2 + 1].pos.x = i/n;
                bot[bbc*2 + 1].pos.y = i%n;
                bot[bbc*2 + 1].dir = N;
                bbc++;
            }
        } else{
            battlefield[i/n][i%m] = WALL;
        }
    }


    window.clear(Color::Black);

    //objects preparing
    int selected = 0;
    int moves = 0;
    int aim_status = 0;
    Weapon *theGun = NULL;
    direction seq[225] = {NODIR};
    int curr_faction = RED;



    //all graphics stuff preparing
    initSprites(battlefield, bot, shiftx, shifty);

    if(bbc == 0 || rbc == 0){
        message_show(window, "NOWHERE TO PLACE!!!",0);
        return 1;
    }

    for(int i = 0; i < TS; i++){
        bot[i].tm = curr_faction+i%2;
        if(i%2){
            botsprite[i].setTexture(botblue);
        }else{
            botsprite[i].setTexture(botred);
        }
    }

    //Main loop
    while(window.isOpen()){
        int xcoord;
        int ycoord;
        Event event;
        nextturn.setTexture(nextturn_t);
        float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time/200;

        //map shift
        if(Mouse::getPosition(window).x < 16 || Mouse::getPosition(window).y < 16 || Mouse::getPosition(window).x > 1366 - 16 || Mouse::getPosition(window).y > 768 - 16){
                window.clear(Color::Black);
                window.draw(bfback);
                if(Mouse::getPosition(window).x > 1366 - 16){
                    if(shiftx > -(64 + 32*n - 1366))
                        shiftx -= 0.025 * time;
                }
                if(Mouse::getPosition(window).x < 16){
                    if(shiftx < 48)
                        shiftx += 0.025 * time;
                }
                if(Mouse::getPosition(window).y > 768 - 16){
                    if(shifty > -(64 + 32*m - 768))
                        shifty -= 0.025 * time;
                }
                if(Mouse::getPosition(window).y < 16){
                    if(shifty < 48)
                        shifty += 0.025 * time;
                }
                draw_everything(window, battlefield, bot, selected, shiftx, shifty);
                draw_stats(window, bot[selected], icon, gunicon, mystats, myicon, mywp1, mywp2, myhp, myap);
                window.display();
            }


        while(moves){
            bot_walk(bot[selected], moves - 1, seq);
            moves++;
            if(moves > 255)
                moves = 0;
            if(seq[moves - 1] == NODIR)
                moves = 0;
            Sleep(100);
            draw_everything(window, battlefield, bot, selected, shiftx, shifty);
            draw_stats(window, bot[selected], icon, gunicon, mystats, myicon, mywp1, mywp2, myhp, myap);
            window.draw(nextturn);
            window.display();
        }

        while(window.pollEvent(event)){
            //initial drawing

            window.clear(Color::Black);
            window.draw(bfback);
            nextturn.setTexture(nextturn_t);
            draw_everything(window, battlefield, bot, selected, shiftx, shifty);
            draw_stats(window, bot[selected], icon, gunicon, mystats, myicon, mywp1, mywp2, myhp, myap);


                //polling events
            if(!aim_status){
                switch(event.type){
                case Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape){
                    return 0;
                    }
                    break;
                case Event::MouseMoved:{
                    if(IntRect(20, 490, 256, 256).contains((Mouse::getPosition(window))) ||  IntRect(1093+15, 191+15, 63, 63).contains(Mouse::getPosition(window))|| IntRect(1093+95, 191+53, 32, 32).contains(Mouse::getPosition(window)) || IntRect(1093+131, 191+53, 32, 32).contains(Mouse::getPosition(window))){
                        break;
                    }
                    if(IntRect(1136, 728, 100, 30).contains(Mouse::getPosition(window))){
                        nextturn.setTexture(nextturn_p);
                    }else {
                        xcoord = ((int)Mouse::getPosition(window).x - shiftx)/32;
                        ycoord = ((int)Mouse::getPosition(window).y - shifty)/32;
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
                                tdist.setPosition(5 + 32*xcoord + shiftx, 5 + 32 *ycoord + shifty);
                                window.draw(tdist);
                                mouseCurrSprite.setTexture(allowed);
                            } else {
                                mouseCurrSprite.setTexture(restricted);
                            }
                        }else if (c == BOT_ALLY){
                            mouseCurrSprite.setTexture(pers);
                        }else if(c == BOT_ENEMY){
                            mouseCurrSprite.setTexture(enemy);
                            battle_robot curr;
                            for(int i = 0; i < TS; i++){
                                if(bot[i].pos.x == xcoord && bot[i].pos.y == ycoord){
                                    curr = bot[i];
                                    break;
                                }
                            }
                            draw_stats(window, curr, icon, gunicon, enemystats, enemyicon, hiswp1, hiswp2, hishp, hisap);
                        }else{
                            mouseCurrSprite.setTexture(restricted);
                        }
                        mouseCurrSprite.setPosition(32*xcoord + shiftx, 32*ycoord + shifty);
                        window.draw(mouseCurrSprite);
                    }
                    break;
                }
                case Event::MouseButtonPressed:{
                    if(event.mouseButton.button == Mouse::Left){
                        if(IntRect(1093+15, 191+15, 63, 63).contains(Mouse::getPosition(window))){
                            camera_center(bot[selected].pos.x, bot[selected].pos.y);
                        }else if(IntRect(20, 490, 256, 256).contains((Mouse::getPosition(window)))){
                            camera_center((Mouse::getPosition(window).x - 20)/4, (Mouse::getPosition(window).y - 490)/4);
                        }else if(IntRect(1093+95, 191+53, 32, 32).contains(Mouse::getPosition(window))){
                            aim_status = 1;
                            theGun = bot[selected].gun1;
                            selectedGun.setPosition(1093+95, 191+53);
                            selectedGun.setTexture(allowed);
                        }else if(IntRect(1093+131, 191+53, 32, 32).contains(Mouse::getPosition(window))){
                            aim_status = 1;
                            theGun = bot[selected].gun2;
                            selectedGun.setPosition(1093+131, 191+53);
                            selectedGun.setTexture(allowed);
                        }else if(IntRect(1136, 728, 100, 30).contains(Mouse::getPosition(window))){
                            for(int i = 0; i < TS; i++){
                                bot[i].currAp = bot[i].maxAp;
                            }

                            if(step(window, battlefield, bot, curr_faction))
                                return 1;
                            for(int i = 0; i < TS; i++){
                                if(bot[i].tm == curr_faction && !bot[i].destroyed){
                                    selected = i;
                                    camera_center(bot[i].pos.x, bot[i].pos.y);
                                    break;
                                }
                            }
                        } else {
                        xcoord = ((int)Mouse::getPosition(window).x - shiftx)/32;
                        ycoord = ((int)Mouse::getPosition(window).y - shifty)/32;
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
                            aim_status = 1;
                            theGun = bot[selected].gun1;
                            selectedGun.setPosition(1093+95, 191+53);
                            selectedGun.setTexture(allowed);
                        }else if (c==FREE){
                                std::string route = pathFind(bot[selected].pos.x, bot[selected].pos.y, xcoord, ycoord, battlefield, bot);
                                root_to_direction(route, seq);
                            if(walk_distance_count(bot[selected].dir, bot[selected].pos.x, bot[selected].pos.y, xcoord, ycoord, 0, seq) <= bot[selected].currAp){
                                moves = 1;
                            }else{
                                window.draw(nextturn);
                                message_show(window, "INSUFFICIENT AP!", 0);
                            }
                        } else {
                            window.draw(nextturn);
                            message_show(window, "UNWALKABLE TERRAIN", 0);
                        }
                    }} else if(event.mouseButton.button == Mouse::Right){
                        xcoord = ((int)Mouse::getPosition(window).x - shiftx)/32;
                        ycoord = ((int)Mouse::getPosition(window).y - shifty)/32;
                        if(xcoord < 0 || xcoord >= m || ycoord < 0 || ycoord >= n)
                            break;
                        //cell c;
                        if(!bot_turn(bot[selected], xcoord, ycoord)){
                            message_show(window, "INSUFFICIENT AP!", 0);
                        }
                    }
                    break;
                }
                default:
                    break;
                }
            //window.setView(view);
            window.draw(nextturn);
            window.display();
            } else {
                window.draw(selectedGun);
                switch(event.type){
                case Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape){
                    return 0;
                    }
                    break;
                case Event::MouseMoved:
                    if(IntRect(20, 490, 256, 256).contains((Mouse::getPosition(window))) || IntRect(1093+15, 191+15, 63, 63).contains(Mouse::getPosition(window)) || IntRect(1093+95, 191+53, 32, 32).contains(Mouse::getPosition(window)) || IntRect(1093+131, 191+53, 32, 32).contains(Mouse::getPosition(window))){
                        break;
                    }
                    if(IntRect(1136, 728, 100, 30).contains(Mouse::getPosition(window))){
                        nextturn.setTexture(nextturn_p);
                    }else {
                    xcoord = ((int)Mouse::getPosition(window).x - shiftx)/32;
                    ycoord = ((int)Mouse::getPosition(window).y - shifty)/32;
                    if(xcoord < 0 || xcoord > m || ycoord < 0 || ycoord > n)
                        break;
                    cell c = check_walkable(battlefield, xcoord, ycoord, bot, TS, curr_faction);
                    mouseCurrSprite.setTexture(restricted);
                    if(c == FREE || c == BOT_ENEMY){
                        if(eucl_dist_count(bot[selected].pos.x, bot[selected].pos.y, xcoord, ycoord) <= theGun->radius){
                            position pos = *(new position());
                            pos = track(battlefield, bot[selected].pos.x, bot[selected].pos.y, xcoord, ycoord, bot);
                            if((pos.x != xcoord || pos.y != ycoord) && theGun->type != ART){
                                mouseCurrSprite.setPosition(32*xcoord + shiftx, 32*ycoord + shifty);
                                window.draw(mouseCurrSprite);
                                break;
                            }
                            mouseCurrSprite.setTexture(enemy);
                            direction dir = belongs_to_sector(bot[selected], xcoord, ycoord);
                            int diff = abs(dir - bot[selected].dir);
                            if(diff != 4)
                                diff %= 4;
                            int ap;
                            if(aim_status == 1 || theGun->burst == 0){
                                ap = diff + (int)(theGun->apPerStrike * (double)bot[selected].maxAp);
                            } else {
                                ap = diff + (int)(theGun->apPerBurst * (double)bot[selected].maxAp);
                            }
                            char str[10];
                            sprintf(str, "%d", ap);
                            tdist.setString(str);
                            tdist.setPosition(5 + 32*xcoord + shiftx, 37 + 32 *ycoord + shifty);
                            window.draw(tdist);
                        }
                        battle_robot curr;
                        for(int i = 0; i < TS; i++){
                            if(bot[i].pos.x == xcoord && bot[i].pos.y == ycoord){
                                curr = bot[i];
                                break;
                            }
                        }
                        if(c == BOT_ENEMY)
                            draw_stats(window, curr, icon, gunicon, enemystats, enemyicon, hiswp1, hiswp2, hishp, hisap);
                    }else if (c == BOT_ALLY){
                        mouseCurrSprite.setTexture(pers);
                    }
                    mouseCurrSprite.setPosition(32*xcoord+shiftx, 32*ycoord+shifty);
                    window.draw(mouseCurrSprite);
                    }
                    break;
                    case Event::MouseButtonPressed:{
                    if(event.mouseButton.button == Mouse::Left){
                        if(IntRect(1093+15, 191+15, 63, 63).contains(Mouse::getPosition(window))){
                            camera_center(bot[selected].pos.x, bot[selected].pos.y);
                        }else if(IntRect(20, 490, 256, 256).contains((Mouse::getPosition(window)))){
                            camera_center((Mouse::getPosition(window).x - 20)/4, (Mouse::getPosition(window).y - 490)/4);
                        }else if(IntRect(1136, 728, 100, 30).contains(Mouse::getPosition(window))){
                            aim_status = 0;
                            for(int i = 0; i < TS; i++){
                                bot[i].currAp = bot[i].maxAp;
                            }
                            window.display();
                            if(step(window, battlefield, bot, curr_faction))
                                return 1;

                            for(int i = 0; i < TS; i++){
                                if(bot[i].tm == curr_faction && !bot[i].destroyed){
                                    selected = i;
                                camera_center(bot[i].pos.x, bot[i].pos.y);
                                    break;
                                }
                            }
                        }else if(IntRect(1093+95, 191+53, 32, 32).contains(Mouse::getPosition(window))){
                            if(theGun == bot[selected].gun1){
                                if(aim_status == 2){
                                    aim_status = 0;
                                } else {
                                    aim_status = 2;
                                    selectedGun.setTexture(that);
                                }
                            } else {
                                aim_status = 1;
                                theGun = bot[selected].gun1;
                                selectedGun.setPosition(1093+95, 191+53);
                                selectedGun.setTexture(allowed);
                            }
                        }else if(IntRect(1093+131, 191+53, 32, 32).contains(Mouse::getPosition(window))){
                            if(theGun == bot[selected].gun2){
                                if(aim_status == 2){
                                    aim_status = 0;
                                } else {
                                    aim_status = 2;
                                    selectedGun.setTexture(that);
                                }
                            } else {
                                aim_status = 1;
                                theGun = bot[selected].gun2;
                                selectedGun.setPosition(1093+131, 191+53);
                                selectedGun.setTexture(allowed);
                            }
                        } else {
                        xcoord = ((int)Mouse::getPosition(window).x - shiftx)/32;
                        ycoord = ((int)Mouse::getPosition(window).y - shifty)/32;
                        if(xcoord < 0 || xcoord > m || ycoord < 0 || ycoord > n)
                            break;
                        cell c;
                        c = check_walkable(battlefield, xcoord, ycoord, bot, TS, curr_faction);
                        if(c == BOT_ALLY){
                            aim_status = 0;
                            for(int i = 0; i < TS; i++){
                                if(bot[i].pos.x == xcoord && bot[i].pos.y == ycoord){
                                    selected = i;
                                    break;
                                }
                            }
                            break;
                        }
                        shoot(window, battlefield, bot, selected, xcoord, ycoord, theGun, aim_status);
                        if(bot[selected].destroyed){
                            for(int i = 0; i < TS; i++){
                                if(bot[i].tm == curr_faction && !bot[i].destroyed)
                                    selected = i;
                            }
                        }
                        int fc1 = 0;
                        int fc2 = 0;
                        for(int i = 0; i < TS; i++){
                            if(bot[i].destroyed == 0){
                                if(bot[i].tm == RED){
                                    fc1++;
                                } else {
                                    fc2++;
                                }
                            }
                        }
                        if(!fc1 || !fc2){
                            if(!fc1 && !fc2){
                                message_show(window,"DRAW. IMPOSSIBLE!", 1);
                            } else if(!fc2){
                                message_show(window,"YOU WIN! CONGRATS!", 1);
                            }else{
                                message_show(window,"YOU LOOSE. PITY.", 0);
                            }
                            window.clear(Color::Black);
                            return 1;
                        }
                    }
                    } else if(event.mouseButton.button == Mouse::Right){
                        aim_status = 0;
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

void draw_stats(RenderWindow &window, battle_robot bot, Texture *icons,
                Texture *gunicons, Sprite stats, Sprite boticon, Sprite wp1, Sprite wp2, Text hp, Text ap){
    switch(bot.rm){
        case SEEKER:
        boticon.setTexture(icons[0]);
        break;
        case CHARGER:
        boticon.setTexture(icons[2]);
        break;
        case TANK:
        boticon.setTexture(icons[3]);
        break;
        default:
        case TROOPER:
        boticon.setTexture(icons[1]);
        break;
    }
    Weapon *gun = bot.gun1;
    if(gun == claw){
        wp1.setTexture(gunicons[CLAW]);
    }else if(gun == hammer){
        wp1.setTexture(gunicons[HAMMER]);
    } else if(gun == mortar){
        wp1.setTexture(gunicons[MORTAR]);
    } else if(gun == mlrs){
        wp1.setTexture(gunicons[MLRS]);
    } else if(gun == missile){
        wp1.setTexture(gunicons[MISSILE]);
    } else if(gun == minigun){
        wp1.setTexture(gunicons[MINIGUN]);
    } else if(gun == laser){
        wp1.setTexture(gunicons[LASER]);
    } else if(gun == cannon){
        wp1.setTexture(gunicons[CANNON]);
    } else if(gun == plasma){
        wp1.setTexture(gunicons[PLASMA]);
    } else if(gun == flamer){
        wp1.setTexture(gunicons[FLAMETHROWER]);
    }
    gun = bot.gun2;
    if(gun == claw){
        wp2.setTexture(gunicons[CLAW]);
    }else if(gun == hammer){
        wp2.setTexture(gunicons[HAMMER]);
    } else if(gun == mortar){
        wp2.setTexture(gunicons[MORTAR]);
    } else if(gun == mlrs){
        wp2.setTexture(gunicons[MLRS]);
    } else if(gun == missile){
        wp2.setTexture(gunicons[MISSILE]);
    } else if(gun == minigun){
        wp2.setTexture(gunicons[MINIGUN]);
    } else if(gun == laser){
        wp2.setTexture(gunicons[LASER]);
    } else if(gun == cannon){
        wp2.setTexture(gunicons[CANNON]);
    } else if(gun == plasma){
        wp2.setTexture(gunicons[PLASMA]);
    } else if(gun == flamer){
        wp2.setTexture(gunicons[FLAMETHROWER]);
    }
    char buff[20];
    sprintf(buff, "%d / %d", bot.currAp, bot.maxAp);
    ap.setString(buff);
    sprintf(buff, "%d / %d", bot.hp, bot.maxhp);
    hp.setString(buff);
    window.draw(stats);
    window.draw(boticon);
    window.draw(wp1);
    window.draw(wp2);
    window.draw(ap);
    window.draw(hp);
}

int shoot(RenderWindow &window, land battlefield[n][m], battle_robot *bot, int selected, int targx, int targy, Weapon *wp, int shotmode){

    if(eucl_dist_count(bot[selected].pos.x, bot[selected].pos.y, targx, targy) > wp->radius){
        message_show(window, "NOT IN RANGE", 0);
        return 1;
    }
    position pos = *(new position());
    pos = track(battlefield, bot[selected].pos.x, bot[selected].pos.y, targx, targy, bot);
    if((pos.x != targx || pos.y != targy) && wp->type != ART){
        message_show(window, "TRAJECTORY BLOCKED", 0);
        return 1;
    }
    direction dir = belongs_to_sector(bot[selected], targx, targy);
    int diff = abs(dir - bot[selected].dir);
    if(diff != 4)
    diff %= 4;
    int ap;
    if(shotmode == 1 || wp->burst == 0){
        ap = diff + (int)(wp->apPerStrike * (double)bot[selected].maxAp);
    } else {
        ap = diff + (int)(wp->apPerBurst * (double)bot[selected].maxAp);
    }
    if(ap > bot[selected].currAp){
        if(bot_turn(bot[selected], targx, targy));
        message_show(window, "INSUFFICIENT AP!", 0);
        return 1;
    } else {
        ap -= diff;
        bot_turn(bot[selected], targx, targy);
        bot[selected].currAp -= ap;
    }
    if(wp->type == MELEE){

        animation_strike(window, targx, targy, battlefield, bot, selected);

        battle_robot curr;
        for(int i = 0; i < TS; i++){
            if(bot[i].pos.x == targx && bot[i].pos.y == targy){
                int dmg = damage_count(curr, wp, 1);
                bot[i].hp -= dmg;
                if(bot[i].hp <= 0){
                    bot[i].destroyed = 1;
                    bot[i].pos.x = -1;
                    bot[i].pos.y = -1;
                    animation_destroyed(window, targx, targy, battlefield, bot, selected);
                }
                return 0;
            }
        }
        if(battlefield[targx][targy] == WALL){
            battlefield[pos.x][pos.y] = RUIN;
            bfsprite[pos.x][pos.y].setTexture(ruin);
        }
        return 0;
    }else{

        animation_shooting(window, targx, targy, selected, battlefield, bot);

        if(wp->type == FLAMER){
            int cx;
            int cy;
            for(int i = 0; i < 25; i++){
                flames[i].setPosition(targx * 32 + shiftx, targy * 32 + shifty);
            }
            int flc = 0;
            for(int i = -2; i <= 2; i++){
                for(int j = -2; j <= 2; j++){
                    cx = targx + j;
                    cy = targy + i;
                    if(cx >= 0 && cx < n && cy >= 0 && cy < m){
                        if((rand()%10) - 4 >= 0){
                            flames[flc].setPosition(32*cx+shiftx, 32*cy+shifty);
                            for(int k = 0; k < TS; k++){
                                if(bot[k].pos.x == cx && bot[k].pos.y == cy){
                                    int dmg = damage_count(bot[k], wp, 1);
                                    bot[k].hp -= dmg;
                                }
                            }
                        }
                    }
                    flc++;
                }
            }

            animation_flames(window, battlefield, bot, selected);

            for(int i = 0; i < TS; i++){
                if(bot[i].hp <= 0&& !bot[i].destroyed){
                    bot[i].destroyed = 1;
                    int cx = bot[i].pos.x;
                    int cy = bot[i].pos.y;
                    bot[i].pos.x = -1;
                    bot[i].pos.y = -1;
                    animation_destroyed(window, cx, cy, battlefield, bot, selected);
                }
            }

            return 0;
        } else {
            double acc;
            acc = accuracy_count(eucl_dist_count(bot[selected].pos.x, bot[selected].pos.y, targx, targy), wp);
            if(shotmode == 2 && wp->burst != 0){
            acc *= 0.75;
                for(int i = 0; i < wp->burst; i++){
                    pos = chooseRandom(battlefield, targx, targy, acc);
                    if(wp->type != ART)
                        pos = track(battlefield, bot[selected].pos.x, bot[selected].pos.y, pos.x, pos.y, bot);

                    animation_explode(window, pos.x, pos.y, battlefield, bot, selected);

                    for(int j = 0; j < TS; j++){
                        if(bot[j].pos.x == pos.x && bot[j].pos.y == pos.y){
                            int dmg = damage_count(bot[j], wp, eucl_dist_count(bot[selected].pos.x, bot[selected].pos.y, pos.x, pos.y));
                            bot[j].hp -= dmg;
                            if(bot[j].hp <= 0){
                                bot[j].destroyed = 1;
                                bot[j].pos.x = -1;
                                bot[j].pos.y = -1;
                                animation_destroyed(window, pos.x, pos.y, battlefield, bot, selected);
                            }
                        }
                    }
                    if(wp->splash > 0){
                        for(int i = 0; i < 9; i++){
                            smallbang[i].setPosition(32*pos.x+shiftx, 32*pos.y+shifty);
                        }
                        int cx;
                        int cy;
                        int flc = 0;
                        for(int u = -1; u <= 1; u++){
                            for(int v = -1; v <= 1; v++){
                                if(!u && !v)
                                    continue;
                                cx = pos.x + v;
                                cy = pos.y + u;
                                smallbang[flc].setPosition(32*cx+shiftx, 32*cy+shifty);
                                for(int j = 0; j < TS && cx >= 0 && cx < n && cy >= 0 && cy < m; j++){
                                    if(bot[j].pos.x == cx && bot[j].pos.y == cy){
                                        bot[j].hp -= wp->splash*damage_count(bot[j], wp, 1);
                                    }
                                }
                            flc++;
                            }
                        }

                        animation_smallbangs(window, battlefield, bot, selected);
                        for(int i = 0; i < TS; i++){
                            if(bot[i].hp <= 0 && !bot[i].destroyed){
                                bot[i].destroyed = 1;
                                int cx = bot[i].pos.x;
                                int cy = bot[i].pos.y;
                                bot[i].pos.x = -1;
                                bot[i].pos.y = -1;
                                animation_destroyed(window, cx, cy, battlefield, bot, selected);
                            }
                        }
                    }

                    if(battlefield[pos.x][pos.y] == WALL){
                        battlefield[pos.x][pos.y] = RUIN;
                        bfsprite[pos.x][pos.y].setTexture(ruin);
                    }
                }
                return 0;
            } else {
                if(wp->type == ART){
                    pos = track(battlefield, bot[selected].pos.x, bot[selected].pos.y, targx, targy, bot);
                    if(pos.x != targx || pos.y != targy)
                        acc *= 0.75;
                }
                pos = chooseRandom(battlefield, targx, targy, acc);
                if(wp->type != ART){
                    pos = track(battlefield, bot[selected].pos.x, bot[selected].pos.y, pos.x, pos.y, bot);
                }
                animation_explode(window, pos.x, pos.y, battlefield, bot, selected);

                for(int j = 0; j < TS; j++){
                    if(bot[j].pos.x == pos.x && bot[j].pos.y == pos.y){
                        int dmg = damage_count(bot[j], wp, eucl_dist_count(bot[selected].pos.x, bot[selected].pos.y, pos.x, pos.y));
                        bot[j].hp -= dmg;
                        if(bot[j].hp <= 0){
                            bot[j].destroyed = 1;
                            bot[j].pos.x = -1;
                            bot[j].pos.y = -1;
                            animation_destroyed(window, pos.x, pos.y, battlefield, bot, selected);
                        }
                    }
                }
                if(wp->splash > 0){
                        for(int i = 0; i < 9; i++){
                            smallbang[i].setPosition(32*pos.x+shiftx, 32*pos.y+shifty);
                        }
                        int cx;
                        int cy;
                        int flc = 0;
                        for(int u = -1; u <= 1; u++){
                            for(int v = -1; v <= 1; v++){
                                if(!u && !v)
                                    continue;
                                cx = pos.x + v;
                                cy = pos.y + u;
                                smallbang[flc].setPosition(32*cx+shiftx, 32*cy+shifty);
                                for(int j = 0; j < TS && cx >= 0 && cx < n && cy >= 0 && cy < m; j++){
                                    if(bot[j].pos.x == cx && bot[j].pos.y == cy){
                                        bot[j].hp -= wp->splash*damage_count(bot[j], wp, 1);
                                    }
                                }
                            flc++;
                            }
                        }

                        animation_smallbangs(window, battlefield, bot, selected);
                        for(int i = 0; i < TS; i++){
                            if(bot[i].hp <= 0 && !bot[i].destroyed){
                                bot[i].destroyed = 1;
                                int cx = bot[i].pos.x;
                                int cy = bot[i].pos.y;
                                bot[i].pos.x = -1;
                                bot[i].pos.y = -1;
                                animation_destroyed(window, cx, cy, battlefield, bot, selected);
                            }
                        }
                    }
                    if(battlefield[pos.x][pos.y] == WALL){
                        battlefield[pos.x][pos.y] = RUIN;
                        bfsprite[pos.x][pos.y].setTexture(ruin);
                    }
                }
            }
        }
        return 0;
    }

void initSprites(land battlefield[n][m], battle_robot bot[TS], int shiftx, int shifty){

    botblue.loadFromFile("textures/botblue.png");
    botred.loadFromFile("textures/botred.png");
    bfbg.loadFromFile("bfbg.jpg");
    grass.loadFromFile("textures/land_grass.png");
    ruin.loadFromFile("textures/land_ruin.png");
    stone.loadFromFile("textures/wall_brick.png");
    allowed.loadFromFile("textures/allowed.png");
    restricted.loadFromFile("textures/restricted.png");
    enemy.loadFromFile("textures/enemy.png");
    pers.loadFromFile("textures/personel.png");
    that.loadFromFile("textures/chosen.png");
    mybot.loadFromFile("textures/mystats.png");
    for(int i = 0; i < 4; i++){
        icon[i].loadFromFile("textures/icons.png", IntRect(64*i, 0, 64, 64));
    }
    gunicon[CLAW].loadFromFile("textures/guns/claw.png");
    gunicon[HAMMER].loadFromFile("textures/guns/hammer.png");
    gunicon[MORTAR].loadFromFile("textures/guns/mortar.png");
    gunicon[MLRS].loadFromFile("textures/guns/mlrs.png");
    gunicon[MISSILE].loadFromFile("textures/guns/missile.png");
    gunicon[MINIGUN].loadFromFile("textures/guns/minigun.png");
    gunicon[LASER].loadFromFile("textures/guns/laser.png");
    gunicon[PLASMA].loadFromFile("textures/guns/plasmagun.png");
    gunicon[CANNON].loadFromFile("textures/guns/cannon.png");
    gunicon[FLAMETHROWER].loadFromFile("textures/guns/flamethrower.png");
    punch.loadFromFile("textures/strike.png");
    bang.loadFromFile("textures/bang1.png");
    flares.loadFromFile("textures/flames.png");
    firing.loadFromFile("textures/firing.png");
    badabum.loadFromFile("textures/BombExploding.png");
    spell.loadFromFile("textures/shell.png");
    mapframe.loadFromFile("textures/mapframe.png");
    maptmp.loadFromFile("textures/maptext.png");
    nextturn_t.loadFromFile("textures/nextturn.png");
    nextturn_p.loadFromFile("textures/nextturnpressed.png");
    bfback.setTexture(bfbg);

    bfback.setPosition(0,0);

    font.loadFromFile("arial.ttf");

    selectedSprite.setTexture(that);

    tdist.setCharacterSize(20);
    tdist.setColor(Color::Magenta);
    tdist.setFont(font);

    mystats.setTexture(mybot); mystats.setPosition(1093, 191);
    myicon.setPosition(1093+15, 191+15);
    myhp.setCharacterSize(12); myhp.setColor(Color::Red); myhp.setFont(font); myhp.setPosition(1093+127, 191+17);
    myap.setCharacterSize(12); myap.setColor(Color::Green); myap.setFont(font); myap.setPosition(1093+127, 191+36);
    mywp1.setPosition(1093+95, 191+53); mywp2.setPosition(1093+131, 191+53);

    enemystats.setTexture(mybot); enemystats.setPosition(554, 15);
    enemyicon.setPosition(554+15, 15+15);
    hishp.setCharacterSize(12); hishp.setColor(Color::Red); hishp.setFont(font); hishp.setPosition(554+127, 15+17);
    hisap.setCharacterSize(12); hisap.setColor(Color::Green); hisap.setFont(font); hisap.setPosition(554+127, 15+36);
    hiswp1.setPosition(554+95, 15+53); hiswp2.setPosition(554+131, 15+53);

    nextturn.setPosition(1136, 728);
    nextturn.setTexture(nextturn_t);

    frame.setTexture(mapframe);
    frame.setPosition(0, 471);
    tmp.setTexture(maptmp);

    for(int i = 0; i < n*m; i++){
        bfsprite[i/n][i%m].setPosition(shiftx+32*(i/n), shifty+32*(i%m));
        switch(battlefield[i/n][i%m]){
        case WALL:
            bfsprite[i/n][i%m].setTexture(stone);
            break;
        case RUIN:
            bfsprite[i/n][i%m].setTexture(ruin);
        case GRSS:
        default:
            bfsprite[i/n][i%m].setTexture(grass);
        }
    }

    strike.setTexture(punch);
    shooting.setTexture(firing);
    explosion.setTexture(bang);
    destruction.setTexture(badabum);
    for(int i = 0; i < 25; i++){
        flames[i].setTexture(flares);
    }
    for(int i = 0; i < 9; i++){
        smallbang[i].setTexture(bang);
    }
    shell.setTexture(spell);
}

void draw_everything(RenderWindow &window, land battlefield[n][m], battle_robot bot[TS], int selected, int shiftx, int shifty){
    window.clear(Color::Black);
    window.draw(bfback);

    for(int i = 0; i < n*m; i++){
        bfsprite[i/n][i%m].setPosition(32*(i/n) + shiftx, 32*(i%m) + shifty);
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
    botsprite[i].setPosition(32*bot[i].pos.x + hs + shiftx, 32 * bot[i].pos.y + vs + shifty);
    window.draw(botsprite[i]);
    if(i == selected)
        selectedSprite.setPosition( 32*bot[i].pos.x + shiftx, 32 * bot[i].pos.y + shifty);
    }
    draw_minimap(window, battlefield, bot, selected);
    window.draw(nextturn);
    window.draw(selectedSprite);
}

void animation_strike(RenderWindow &window, int px, int py, land battlefield[n][m], battle_robot bot[TS], int selected){
    Clock clock;
    window.display();
    window.clear(Color::Black);
    strike.setPosition(32 * px + shiftx, 32 * py + shifty);
    double cf;
    clock.restart();
    for(cf = 2; cf >= 0; ){
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;
        cf -= 0.005*time;
        strike.setTextureRect(IntRect(32*(int)cf, 0, 32, 32));
        draw_everything(window, battlefield, bot, selected, shiftx, shifty);
        window.draw(strike);
        window.display();
    }
}

void animation_shooting(RenderWindow &window, int px, int py, int selected, land battlefield[n][m], battle_robot bot[TS]){
        Clock clock;
        double curr;
        int vs;
        int hs;
        switch(bot[selected].dir){
        case N:
            curr = 270.0;
            vs = 0;
            hs = 0;
            break;
        case NE:
            curr = 315.0;
            vs = -16;
            hs = 32;
            break;
        case E:
            curr = 0.0;
            vs = 0;
            hs = 32;
            break;
        case SE:
            curr = 45.0;
            vs = 32;
            hs = 48;
            break;
        case SW:
            curr = 135.0;
            vs = 48;
            hs = 0;
            break;
        case W:
            curr = 180.0;
            hs = 0;
            vs = 32;
            break;
        case NW:
            curr = 225.0;
            vs = 0;
            hs = -16;
            break;
        case S:
        default:
            curr = 90.0;
            vs = 32;
            hs = 32;
            break;
    }
    shooting.setRotation(curr);
    shooting.setPosition(32*bot[selected].pos.x + hs + shiftx, 32 * bot[selected].pos.y + vs + shifty);
    window.display();
    window.clear(Color::Black);
    double cf;
    clock.restart();
    for(cf = 5; cf >= 0; ){
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;
        cf -= 0.005*time;
        shooting.setTextureRect(IntRect(32*((int)cf%2), 0, 32, 32));
        draw_everything(window, battlefield, bot, selected, shiftx, shifty);
        window.draw(shooting);
        window.display();
    }
}

void animation_explode(RenderWindow &window, int px, int py, land battlefield[n][m], battle_robot bot[TS], int selected){
    Clock clock;
    window.display();
    window.clear(Color::Black);
    double cf;
    clock.restart();
    explosion.setPosition(32*px + shiftx, 32*py + shifty);
    for(cf = 0; cf <= 5; ){
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;
        cf += 0.005*time;
        explosion.setTextureRect(IntRect(32*(int)cf, 0, 32, 32));
        draw_everything(window, battlefield, bot, selected, shiftx, shifty);
        window.draw(explosion);
        window.display();
    }
}

void animation_destroyed(RenderWindow &window, int px, int py, land battlefield[n][m], battle_robot bot[TS], int selected){
    Clock clock;
    window.display();
    window.clear(Color::Black);
    double cf;
    destruction.setPosition(32*px + shiftx, 32*py-32 + shifty);
    for(cf = 7; cf <= 12; ){
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;
        cf += 0.005*time;
        destruction.setTextureRect(IntRect(32*(int)cf, 0, 32, 64));
        draw_everything(window, battlefield, bot, selected, shiftx, shifty);
        window.draw(destruction);
        window.display();
    }
}

void animation_flames(RenderWindow &window, land battlefield[n][m], battle_robot bot[TS], int selected){
        Clock clock;
        window.display();
        window.clear(Color::Black);
        double cf;
        clock.restart();
        for(cf = 25; cf >= 0; ){
        float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time/800;
            cf -= 0.005*time;
        for(int i = 0; i < 25; i++)
            flames[i].setTextureRect(IntRect(32*((int)cf%5), 0, 32, 32));
        draw_everything(window, battlefield, bot, selected, shiftx, shifty);
        for(int i = 0; i < 25; i++)
            window.draw(flames[i]);
        window.display();
    }
}


void animation_smallbangs(RenderWindow &window, land battlefield[n][m], battle_robot bot[TS], int selected){
    Clock clock;
    window.display();
    window.clear(Color::Black);
    double cf;
    clock.restart();
    for(cf = 0; cf < 2.0; ){
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;
        cf += 0.005*time;
        for(int i = 0; i < 9 && cf < 2.0; i++)
            smallbang[i].setTextureRect(IntRect(32*4*((int)cf%2), 0, 32, 32));
        draw_everything(window, battlefield, bot, selected, shiftx, shifty);
        for(int i = 0; i < 9; i++)
            window.draw(smallbang[i]);
        window.display();
    }
}

void draw_minimap(RenderWindow &window, land battlefield[n][m], battle_robot bot[TS], int selected){
    window.draw(frame);
    for(int i = 0; i < n*m; i++){
        if(battlefield[i/n][i%m] < WALL){
            tmp.setTextureRect(IntRect(32, 4, 4, 4));
        }else{
            tmp.setTextureRect(IntRect(36, 4, 4, 4));
        }
        tmp.setPosition(20 + (i/n)*4, 490+(i%m)*4);
        window.draw(tmp);
    }
    for(int i = 0; i < TS; i++){
        if(bot[i].destroyed)
            continue;
        int dirmult;
        switch(bot[i].dir){
        case NE:
            dirmult = 7;
            break;
        case N:
            dirmult = 6;
            break;
        case NW:
            dirmult = 5;
            break;
        case W:
            dirmult = 4;
            break;
        case SW:
            dirmult = 3;
            break;
        case S:
            dirmult = 2;
            break;
        case SE:
            dirmult = 1;
            break;
        case E:
        default:
            dirmult = 0;
        break;
        }
        if(i == selected){
            tmp.setTextureRect(IntRect(dirmult*4 + 32, 0, 4, 4));
        }else if(bot[i].tm == RED){
            tmp.setTextureRect(IntRect(dirmult*4, 0, 4, 4));
        }else{
            tmp.setTextureRect(IntRect(dirmult*4, 4, 4, 4));
        }
    tmp.setPosition(20 + bot[i].pos.x * 4, 490 + bot[i].pos.y *4);
    window.draw(tmp);
    }
}

void message_show(RenderWindow &window, char *message, int messageType){
    Text txt;
    txt.setCharacterSize(48);
    txt.setFont(font);
    if(messageType){
        txt.setColor(Color::Green);
    } else {
        txt.setColor(Color::Red);
    }
    txt.setPosition(539, 360);
    txt.setString(message);
    window.draw(txt);
    window.draw(nextturn);
    window.display();
    Sleep(1500);
}

void camera_center(int px, int py){
    shiftx = 618- 32*px;
    if(shiftx < -(64 + 32*n - 1366))
        shiftx = -(63+32*n-1366);
    if(shiftx > 48)
        shiftx = 47;
    shifty = 319 - 32*py;
    if(shifty < -(64 + 32*n - 768))
        shifty = -(63+32*n-768);
    if(shifty > 48)
        shifty = 47;
}

int ai_step_agressive(RenderWindow &window, land battlefield[n][m], battle_robot bot[TS], int &currFaction){
    currFaction = ((currFaction+1)%2);
    shiftx = 0;
    shifty = 0;
    window.clear(Color::Black);
    int selected;
    int moves = 0;
    direction seq[255];
    for(int i = 0; i < TS; i++){
        if(bot[i].tm == currFaction && bot[i].destroyed == 0){
            window.clear(Color::Black);
            selected = i;
            camera_center(bot[selected].pos.x, bot[selected].pos.y);
            draw_everything(window, battlefield, bot, selected, shiftx, shifty);
            window.display();
            position b1 = *(new position());
            int minHP = 0;
            int gun1Reachable = 0;
            int gun2Reachable = 0;
            int turnValue;
            int minimalShotAP;
            int gun1AP = bot[selected].gun1->apPerStrike * bot[selected].maxAp;
            int gun2AP = bot[selected].gun2->apPerStrike * bot[selected].maxAp;
            if(gun1AP > gun2AP){
                minimalShotAP = gun2AP;
            }else{
                minimalShotAP = gun1AP;
            }
            while(bot[selected].currAp > minimalShotAP){

                //finding most vulnerable target
                for(int j  = 0; j < TS; j++){
                    if(bot[j].tm == (currFaction+1)%2 && bot[j].destroyed == 0){
                        gun1Reachable = 0;
                        gun2Reachable = 0;
                        int dist = eucl_dist_count(bot[selected].pos.x, bot[selected].pos.y, bot[j].pos.x, bot[j].pos.y);
                        direction dir = belongs_to_sector(bot[selected], bot[j].pos.x, bot[j].pos.y);
                        turnValue = abs(dir - bot[selected].dir);
                        if(turnValue != 4)
                            turnValue %= 4;
                        position tmp = *(new position());
                        tmp = track(battlefield, bot[selected].pos.x, bot[selected].pos.y, bot[j].pos.x, bot[j].pos.y, bot);
                        int trc = 0;
                        if(tmp.x != bot[j].pos.x || tmp.y != bot[j].pos.y)
                            trc = 1;
                        gun1Reachable = ((!trc || bot[selected].gun1->type == ART) && (bot[selected].gun1->radius >= dist) && (gun1AP+turnValue < bot[selected].currAp));
                        gun2Reachable = ((!trc || bot[selected].gun2->type == ART) && (bot[selected].gun2->radius >= dist) && (gun2AP+turnValue < bot[selected].currAp));
                        if((gun1Reachable || gun2Reachable)&&(minHP == 0 || minHP > bot[j].hp)){
                            minHP = bot[j].hp;
                            b1.x = bot[j].pos.x;
                            b1.y = bot[j].pos.y;
                        }
                    }
                    int dist = eucl_dist_count(bot[selected].pos.x, bot[selected].pos.y, b1.x, b1.y);
                    direction dir = belongs_to_sector(bot[selected], b1.x, b1.y);
                    turnValue = abs(dir - bot[selected].dir);
                    if(turnValue != 4)
                        turnValue %= 4;
                    position tmp = *(new position());
                    tmp = track(battlefield, bot[selected].pos.x, bot[selected].pos.y, b1.x, b1.y, bot);
                    int trc = 0;
                    if(tmp.x != b1.x || tmp.y != b1.y)
                        trc = 1;
                    gun1Reachable = ((!trc || bot[selected].gun1->type == ART) && (bot[selected].gun1->radius >= dist) && (gun1AP+turnValue < bot[selected].currAp));
                    gun2Reachable = ((!trc || bot[selected].gun2->type == ART) && (bot[selected].gun2->radius >= dist) && (gun2AP+turnValue < bot[selected].currAp));
                }
                if(minHP != 0 && (gun1Reachable || gun2Reachable)){
                //most vulnerable found, destroy
                    window.clear(Color::Black);
                    draw_everything(window, battlefield, bot, selected, shiftx, shifty);
                    if(gun1Reachable && gun2Reachable){
                        int gun1Damage = bot[selected].gun1->damage;
                        int g1ap = gun1AP;
                        int g2ap = gun2AP;
                        int gun2Damage = bot[selected].gun2->damage;
                        if(bot[selected].gun1->burst && bot[selected].gun1->apPerBurst*bot[selected].maxAp + turnValue < bot[selected].currAp){
                            gun1Damage *= bot[selected].gun1->burst;
                            g1ap = bot[selected].gun1->apPerBurst * bot[selected].maxAp;
                        }
                        if(bot[selected].gun2->burst && bot[selected].gun2->apPerBurst*bot[selected].maxAp + turnValue < bot[selected].currAp){
                            gun2Damage *= bot[selected].gun2->burst;
                            g2ap = bot[selected].gun2->apPerBurst * bot[selected].maxAp;
                        }
                        if(gun1Damage > gun2Damage){
                            gun2Reachable = 0;
                        } else if(gun1Damage < gun2Damage){
                            gun1Reachable = 0;
                        } else {
                            if(g1ap>g2ap){
                                gun1Reachable = 0;
                            }else{
                                gun2Reachable = 0;
                            }
                        }
                    }
                    if(gun1Reachable){
                        camera_center(b1.x, b1.y);
                        if(bot[selected].gun1->burst && bot[selected].gun1->apPerBurst*bot[selected].maxAp + turnValue < bot[selected].currAp){
                            if(shoot(window, battlefield, bot, selected, b1.x, b1.y, bot[selected].gun1, 2))
                                break;
                        } else {
                            if(shoot(window, battlefield, bot, selected, b1.x, b1.y, bot[selected].gun1, 1))
                                break;
                        }
                    }
                    if(gun2Reachable){
                        camera_center(b1.x, b1.y);
                        if(bot[selected].gun2->burst && bot[selected].gun2->apPerBurst*bot[selected].maxAp + turnValue < bot[selected].currAp){
                            if(shoot(window, battlefield, bot, selected, b1.x, b1.y, bot[selected].gun2, 2))
                                break;
                        } else {
                            if(shoot(window, battlefield, bot, selected, b1.x, b1.y, bot[selected].gun2, 1))
                                break;
                        }
                    }
                }else{ //no target, moving to nearest enemy bot
                    if(bot[selected].currAp < 4)
                        break;
                    int damnation = 7;
                    if(bot[selected].gun1->type == MELEE || bot[selected].gun2->type == MELEE)
                        damnation = 1;
                    int minDist = 0;
                    battle_robot closeBot;
                    std::string route;
                    position cp = *(new position());
                    cp.x = -1;
                    cp.y = -1;
                    for(int j = 0; j < TS; j++){
                        if(bot[j].tm == (currFaction+1)%2 && bot[j].destroyed == 0){
                            int cd = eucl_dist_count(bot[selected].pos.x, bot[selected].pos.y, bot[j].pos.x, bot[j].pos.y);
                            if(minDist == 0 || cd < minDist){
                                minDist = cd;
                                closeBot = bot[j];
                            }
                        }
                    }
                    minDist = 0;
                    position fp = *(new position());
                    fp.x = -1;
                    fp.y = -1;
                    for(int u  = damnation; u>= -1*damnation; u--){
                        for(int v = damnation; v >= -1*damnation; v--){
                            cp = track(battlefield, closeBot.pos.x+u, closeBot.pos.y+v, closeBot.pos.x, closeBot.pos.y, bot);
                            if(check_walkable(battlefield, closeBot.pos.x+u, closeBot.pos.y+v, bot, TS, BLUE) == FREE
                               && cp.x == closeBot.pos.x && cp.y == closeBot.pos.y){
                                int cd = eucl_dist_count(closeBot.pos.x+u, closeBot.pos.y+v, bot[selected].pos.x, bot[selected].pos.y);
                                if(minDist == 0 || cd < minDist){
                                    minDist = cd;
                                    fp.x = closeBot.pos.x + u;
                                    fp.y = closeBot.pos.y + v;
                                }
                            }
                        }
                    }
                    if(fp.x != -1 && fp.y != -1){
                        route = pathFind(bot[selected].pos.x, bot[selected].pos.y, fp.x, fp.y, battlefield, bot);
                        root_to_direction(route, seq);
                        moves = 1;
                        while(moves){
                            window.clear(Color::Black);
                            if(bot_walk(bot[selected], moves - 1, seq))
                                break;
                            camera_center(bot[selected].pos.x, bot[selected].pos.y);
                            moves++;
                            if(moves > 255)
                                moves = 0;
                            if(seq[moves - 1] == NODIR){
                                moves = 0;
                                break;
                            }
                            Sleep(100);
                            draw_everything(window, battlefield, bot, selected, shiftx, shifty);
                            draw_stats(window, bot[selected], icon, gunicon, mystats, myicon, mywp1, mywp2, myhp, myap);
                            window.display();
                        }
                    }
                }
            }
        }
    }
    window.display();
    currFaction = ((currFaction+1)%2);

    int fc1 = 0;
    int fc2 = 0;
    for(int i = 0; i < TS; i++){
        if(bot[i].destroyed == 0){
            if(bot[i].tm == RED){
                fc1++;
            } else {
                fc2++;
            }
        }
    }
    if(!fc1 || !fc2){
        if(!fc1 && !fc2){
                message_show(window,"DRAW. IMPOSSIBLE!", 1);
        }else if(!fc2){
            message_show(window,"YOU WIN! CONGRATS!", 1);
        }else{
            message_show(window,"YOU LOOSE. PITY.", 0);
        }
        window.clear(Color::Black);
    return 1;
    }
    return 0;
}

int ai_step_dumb(RenderWindow &window, land battlefield[n][m], battle_robot bot[TS], int &currFaction){
    currFaction = ((currFaction+1)%2);
    shiftx = 0;
    shifty = 0;
    position pos = *(new position());
    pos.x = 0;
    pos.y = 0;
    window.clear(Color::Black);
    int selected;
    int moves = 0;
    direction seq[255];
    for(int i = 0; i < TS; i++){
        if(bot[i].tm == currFaction && bot[i].destroyed == 0)
            selected = i;
    }
    camera_center(bot[selected].pos.x, bot[selected].pos.y);
    draw_everything(window, battlefield, bot, selected, shiftx, shifty);
    window.display();
    for(int i = 0; i < TS; i++){
        if(bot[i].tm == currFaction && bot[i].destroyed == 0){
            selected = i;
            do{
                pos.x = bot[selected].pos.x + rand() % 17 - 8;
                pos.y = bot[selected].pos.y + rand() % 17 - 8;
            }while(pos.x < 0 || pos.x >= n || pos.y < 0 && pos.y >= m || check_walkable(battlefield, pos.x, pos.y, bot, TS, currFaction) != FREE);
            std::string route = pathFind(bot[selected].pos.x, bot[selected].pos.y, pos.x, pos.y, battlefield, bot);
                    root_to_direction(route, seq);
            if(walk_distance_count(bot[selected].dir, bot[selected].pos.x, bot[selected].pos.y, pos.x, pos.y, 0, seq) <= bot[selected].currAp){
                    bot[selected].currAp -= walk_distance_count(bot[selected].dir, bot[selected].pos.x, bot[selected].pos.y, pos.x, pos.y, 0, seq);
                    moves = 1;
            }
            while(moves){
                window.clear(Color::Black);
                bot_walk(bot[selected], moves - 1, seq);
                moves++;
                if(moves > 255)
                    moves = 0;
                if(seq[moves - 1] == NODIR)
                    moves = 0;
                Sleep(100);
                draw_everything(window, battlefield, bot, selected, shiftx, shifty);
                draw_stats(window, bot[selected], icon, gunicon, mystats, myicon, mywp1, mywp2, myhp, myap);
                window.display();
            }
        }
    }
    currFaction = ((currFaction+1)%2);
    return 0;
}

int check_probable_damage(land battlefield[n][m], battle_robot bot[TS], int x, int y){
    int dmg = 0;
    for(int i = 0; i < TS; i++){
        if(bot[i].tm == RED && bot[i].destroyed == 0){
            int gun1Reachable = 0;
            int gun2Reachable = 0;
            int dist = eucl_dist_count(x, y, bot[i].pos.x, bot[i].pos.y);
            direction dir = belongs_to_sector(bot[i], x, y);
            position tmp = *(new position());
            tmp = track(battlefield, bot[i].pos.x, bot[i].pos.y, x, y, bot);
            int trc = 0;
            if(tmp.x != x || tmp.y != y)
                trc = 1;
            gun1Reachable = ((!trc || bot[i].gun1->type == ART) && (bot[i].gun1->radius >= dist));
            gun2Reachable = ((!trc || bot[i].gun2->type == ART) && (bot[i].gun2->radius >= dist));
            if(gun1Reachable){
                int gdmg = bot[i].gun1->damage;
                if(bot[i].gun1->burst)
                    gdmg *= bot[i].gun1->burst;
                dmg += gdmg;
            }
            if(gun2Reachable){
                int gdmg = bot[i].gun2->damage;
                if(bot[i].gun2->burst)
                    gdmg *= 0.75*bot[i].gun2->burst;
                dmg += gdmg;
            }
        }
    }
}

int ai_step_alert(RenderWindow &window, land battlefield[n][m], battle_robot bot[TS], int &currFaction){
    currFaction = ((currFaction+1)%2);
    shiftx = 0;
    shifty = 0;
    window.clear(Color::Black);
    int selected;
    int moves = 0;
    direction seq[255];
    for(int i = 0; i < TS; i++){
        if(bot[i].tm == currFaction && bot[i].destroyed == 0){
            window.clear(Color::Black);
            selected = i;
            camera_center(bot[selected].pos.x, bot[selected].pos.y);
            draw_everything(window, battlefield, bot, selected, shiftx, shifty);
            window.display();
            position escapepos = *(new position());
            position b1 = *(new position());
            int escapeAP = 100000;
            int minHP = 0;
            int gun1Reachable = 0;
            int gun2Reachable = 0;
            int turnValue;
            int minimalShotAP;
            int gun1AP = bot[selected].gun1->apPerStrike * bot[selected].maxAp;
            int gun2AP = bot[selected].gun2->apPerStrike * bot[selected].maxAp;
            if(gun1AP > gun2AP){
                minimalShotAP = gun2AP;
            }else{
                minimalShotAP = gun1AP;
            }
            position sp = *(new position());
            sp.x = bot[selected].pos.x;
            sp.y = bot[selected].pos.y;
            int pdamage = check_probable_damage(battlefield, bot, sp.x, sp.y);

            //check for possible damage to come & for AP required to hide

            if(pdamage != 0){
                int minDamage = pdamage;
                position temppos = *(new position());
                escapepos.x = sp.x;
                escapepos.y = sp.y;
                std::string route;
                for(int i = 7; i <= -7; i ++){
                    for(int j = 7; j <= -7; j++){
                        int cd = check_probable_damage(battlefield, bot, sp.x + i, sp.y + j);
                        if(cd < minDamage){
                            escapepos.x = sp.x + i;
                            escapepos.y = sp.y + i;
                            route = pathFind(sp.x, sp.y, escapepos.x, escapepos.y, battlefield, bot);
                            root_to_direction(route, seq);
                            escapeAP = walk_distance_count(bot[selected].dir, sp.x, sp.y, escapepos.x, escapepos.y, 0, seq);
                        }
                    }
                }
                if(escapepos.x != sp.x || escapepos.x != sp.x){
                    for(int i = 5; i <= -5; i++){
                        for(int j = 5; j <= -5; j++){
                            int cd = check_probable_damage(battlefield, bot, sp.x + i, sp.y + j);
                            if(cd < minDamage){
                                temppos.x = escapepos.x + i;
                                temppos.y = escapepos.y + j;
                                route = pathFind(sp.x, sp.y, escapepos.x + i, escapepos.y + j, battlefield, bot);
                                root_to_direction(route, seq);
                                escapeAP = walk_distance_count(bot[selected].dir, sp.x, sp.y, escapepos.x + i, escapepos.y + j, 0, seq);
                            }
                        }
                    }
                    escapepos.x = temppos.x;
                    escapepos.y = temppos.y;
                }
                if(escapeAP == 100000){
                    escapeAP = minimalShotAP;
                    pdamage = 0;
                }
            }
            if(pdamage == 0){
                int damnation = 7;
                if(bot[selected].gun1->type == MELEE || bot[selected].gun2->type == MELEE)
                    damnation = 1;
                int minDist = 0;
                battle_robot closeBot;
                std::string route;
                position cp = *(new position());
                cp.x = -1;
                cp.y = -1;
                for(int j = 0; j < TS; j++){
                    if(bot[j].tm == (currFaction+1)%2 && bot[j].destroyed == 0){
                        int cd = eucl_dist_count(bot[selected].pos.x, bot[selected].pos.y, bot[j].pos.x, bot[j].pos.y);
                        if(minDist == 0 || cd < minDist){
                            minDist = cd;
                            closeBot = bot[j];
                        }
                    }
                }
                int minDamage = 100000;
                position fp = *(new position());
                fp.x = -1;
                fp.y = -1;
                for(int u  = damnation; u>= -damnation; u--){
                    for(int v = damnation; v >= -damnation; v--){
                        cp = track(battlefield, closeBot.pos.x+u, closeBot.pos.y+v, closeBot.pos.x, closeBot.pos.y, bot);
                        if(check_walkable(battlefield, closeBot.pos.x+u, closeBot.pos.y+v, bot, TS, BLUE) == FREE
                        && cp.x == closeBot.pos.x && cp.y == closeBot.pos.y){
                            //choose least vulnerable position among those close to nearest bot
                            int cd = check_probable_damage(battlefield, bot, closeBot.pos.x+u, closeBot.pos.y+v);
                            if(cd < minDamage){
                                minDamage = cd;
                                fp.x = closeBot.pos.x + u;
                                fp.y = closeBot.pos.y + v;
                            }
                        }
                    }
                }
                if(fp.x != -1 && fp.y != -1){
                    route = pathFind(bot[selected].pos.x, bot[selected].pos.y, fp.x, fp.y, battlefield, bot);
                    root_to_direction(route, seq);
                    moves = 1;
                    while(moves){
                        window.clear(Color::Black);
                        if(bot_walk(bot[selected], moves - 1, seq))
                            break;
                        camera_center(bot[selected].pos.x, bot[selected].pos.y);
                        moves++;
                        if(moves > 255)
                            moves = 0;
                        if(seq[moves - 1] == NODIR){
                            moves = 0;
                            break;
                        }
                        Sleep(100);
                        draw_everything(window, battlefield, bot, selected, shiftx, shifty);
                        draw_stats(window, bot[selected], icon, gunicon, mystats, myicon, mywp1, mywp2, myhp, myap);
                        window.display();
                    }
                }
            }
            while(bot[selected].currAp > escapeAP + 4){
                //finding most vulnerable target
                for(int j  = 0; j < TS; j++){
                    if(bot[j].tm == (currFaction+1)%2 && bot[j].destroyed == 0){
                        gun1Reachable = 0;
                        gun2Reachable = 0;
                        int dist = eucl_dist_count(bot[selected].pos.x, bot[selected].pos.y, bot[j].pos.x, bot[j].pos.y);
                        direction dir = belongs_to_sector(bot[selected], bot[j].pos.x, bot[j].pos.y);
                        turnValue = abs(dir - bot[selected].dir);
                        if(turnValue != 4)
                            turnValue %= 4;
                        position tmp = *(new position());
                        tmp = track(battlefield, bot[selected].pos.x, bot[selected].pos.y, bot[j].pos.x, bot[j].pos.y, bot);
                        int trc = 0;
                        if(tmp.x != bot[j].pos.x || tmp.y != bot[j].pos.y)
                            trc = 1;
                        gun1Reachable = ((!trc || bot[selected].gun1->type == ART) && (bot[selected].gun1->radius >= dist) && (gun1AP+turnValue < bot[selected].currAp - (escapeAP + 4)));
                        gun2Reachable = ((!trc || bot[selected].gun2->type == ART) && (bot[selected].gun2->radius >= dist) && (gun2AP+turnValue < bot[selected].currAp - (escapeAP + 4)));
                        if((gun1Reachable || gun2Reachable)&&(minHP == 0 || minHP > bot[j].hp)){
                            minHP = bot[j].hp;
                            b1.x = bot[j].pos.x;
                            b1.y = bot[j].pos.y;
                        }
                    }
                    int dist = eucl_dist_count(bot[selected].pos.x, bot[selected].pos.y, b1.x, b1.y);
                    direction dir = belongs_to_sector(bot[selected], b1.x, b1.y);
                    turnValue = abs(dir - bot[selected].dir);
                    if(turnValue != 4)
                        turnValue %= 4;
                    position tmp = *(new position());
                    tmp = track(battlefield, bot[selected].pos.x, bot[selected].pos.y, b1.x, b1.y, bot);
                    int trc = 0;
                    if(tmp.x != b1.x || tmp.y != b1.y)
                        trc = 1;
                    gun1Reachable = ((!trc || bot[selected].gun1->type == ART) && (bot[selected].gun1->radius >= dist) && (gun1AP+turnValue < bot[selected].currAp));
                    gun2Reachable = ((!trc || bot[selected].gun2->type == ART) && (bot[selected].gun2->radius >= dist) && (gun2AP+turnValue < bot[selected].currAp));
                }
                if(minHP != 0 && (gun1Reachable || gun2Reachable)){
                //most vulnerable found, destroy
                    window.clear(Color::Black);
                    draw_everything(window, battlefield, bot, selected, shiftx, shifty);
                    if(gun1Reachable && gun2Reachable){
                        int gun1Damage = bot[selected].gun1->damage;
                        int g1ap = gun1AP;
                        int g2ap = gun2AP;
                        int gun2Damage = bot[selected].gun2->damage;
                        if(bot[selected].gun1->burst && bot[selected].gun1->apPerBurst*bot[selected].maxAp + turnValue < bot[selected].currAp){
                            gun1Damage *= bot[selected].gun1->burst;
                            g1ap = bot[selected].gun1->apPerBurst * bot[selected].maxAp;
                        }
                        if(bot[selected].gun2->burst && bot[selected].gun2->apPerBurst*bot[selected].maxAp + turnValue < bot[selected].currAp){
                            gun2Damage *= bot[selected].gun2->burst;
                            g2ap = bot[selected].gun2->apPerBurst * bot[selected].maxAp;
                        }
                        if(gun1Damage > gun2Damage){
                            gun2Reachable = 0;
                        } else if(gun1Damage < gun2Damage){
                            gun1Reachable = 0;
                        } else {
                            if(g1ap>g2ap){
                                gun1Reachable = 0;
                            }else{
                                gun2Reachable = 0;
                            }
                        }
                    }
                    if(gun1Reachable){
                        camera_center(b1.x, b1.y);
                        if(bot[selected].gun1->burst && bot[selected].gun1->apPerBurst*bot[selected].maxAp + turnValue < bot[selected].currAp){
                            if(shoot(window, battlefield, bot, selected, b1.x, b1.y, bot[selected].gun1, 2))
                                break;
                        } else {
                            if(shoot(window, battlefield, bot, selected, b1.x, b1.y, bot[selected].gun1, 1))
                                break;
                        }
                    }
                    if(gun2Reachable){
                        camera_center(b1.x, b1.y);
                        if(bot[selected].gun2->burst && bot[selected].gun2->apPerBurst*bot[selected].maxAp + turnValue < bot[selected].currAp){
                            if(shoot(window, battlefield, bot, selected, b1.x, b1.y, bot[selected].gun2, 2))
                                break;
                        } else {
                            if(shoot(window, battlefield, bot, selected, b1.x, b1.y, bot[selected].gun2, 1))
                                break;
                        }
                    }
                }
                else{
                    break;
                }
            }
            if(pdamage != 0){
                std::string route = pathFind(bot[selected].pos.x, bot[selected].pos.y, escapepos.x, escapepos.y, battlefield, bot);
                root_to_direction(route, seq);
                moves = 1;
                while(moves){
                    window.clear(Color::Black);
                    if(bot_walk(bot[selected], moves - 1, seq))
                        break;
                    camera_center(bot[selected].pos.x, bot[selected].pos.y);
                    moves++;
                    if(moves > 255)
                        moves = 0;
                    if(seq[moves - 1] == NODIR){
                        moves = 0;
                        break;
                    }
                    Sleep(100);
                    draw_everything(window, battlefield, bot, selected, shiftx, shifty);
                    draw_stats(window, bot[selected], icon, gunicon, mystats, myicon, mywp1, mywp2, myhp, myap);
                    window.display();
                }
            }
        }
    }
    currFaction = ((currFaction+1)%2);
    window.display();

    int fc1 = 0;
    int fc2 = 0;
    for(int i = 0; i < TS; i++){
        if(bot[i].destroyed == 0){
            if(bot[i].tm == currFaction){
                fc1++;
            } else {
                fc2++;
            }
        }
    }
    if(!fc1 || !fc2){
        if(!fc1 && !fc2){
                message_show(window,"DRAW. IMPOSSIBLE!", 1);
        }else if(!fc2){
            message_show(window,"YOU WIN! CONGRATS!", 1);
        }else{
            message_show(window,"YOU LOOSE. PITY.", 0);
        }
        window.clear(Color::Black);
    return 1;
    }
    return 0;
}

int player_step(RenderWindow &window, land battlefield[n][m], battle_robot bot[10], int &currFaction){
    currFaction = ((currFaction+1)%2);
    return 0;
}

void gunChoose(int t, int c, battle_robot &bot){
    if(c == 0){
        switch(t){
        case CLAW:
            bot.gun1 = claw;
            break;
        case HAMMER:
            bot.gun1 = hammer;
            break;
        case MORTAR:
            bot.gun1 = mortar;
            break;
        case MLRS:
            bot.gun1 = mlrs;
            break;
        case MISSILE:
            bot.gun1 = missile;
            break;
        case MINIGUN:
            bot.gun1 = minigun;
            break;
        case LASER:
            bot.gun1 = laser;
            break;
        case CANNON:
            bot.gun1 = cannon;
            break;
        case FLAMETHROWER:
            bot.gun1 = flamer;
            break;
        default:
            bot.gun1 = NULL;
            break;
        }
    }else{
        switch(t){
        case CLAW:
            bot.gun2 = claw;
            break;
        case HAMMER:
            bot.gun2 = hammer;
            break;
        case MORTAR:
            bot.gun2 = mortar;
            break;
        case MLRS:
            bot.gun2 = mlrs;
            break;
        case MISSILE:
            bot.gun2 = missile;
            break;
        case MINIGUN:
            bot.gun2 = minigun;
            break;
        case LASER:
            bot.gun2 = laser;
            break;
        case CANNON:
            bot.gun2 = cannon;
            break;
        case FLAMETHROWER:
            bot.gun2 = flamer;
            break;
        default:
            bot.gun2 = NULL;
            break;
        }
    }
}
