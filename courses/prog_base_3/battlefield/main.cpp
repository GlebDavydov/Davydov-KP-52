#include <windows.h>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <string.h>

#include "main.h"
#include "bf.h"
//#include "view.h"
#include "shooting.h"

//!MYSPRITE COORDS:
//!ENEMYSPRITE COORDS:

using namespace sf;

void draw_everything(RenderWindow &window, land battlefield[n][m], Sprite bfsprite[n][m],
Sprite selectedSprite, Sprite botsprite[TS], battle_robot bot[TS], int selected);

void draw_stats(RenderWindow &window, battle_robot bot, Texture *icons,
Texture *gunicons, Sprite stats, Sprite icon, Sprite wp1, Sprite wp2, Text hp, Text ap);

void shoot(RenderWindow &window, land battlefield[n][m], Sprite bfsprite[n][m], battle_robot *bot, Sprite *botsprite,
int selected, int targx, int targy, Weapon *wp, int shotmode,
Sprite strike, Sprite shooting, Sprite explosion, Sprite destruction, Sprite flames[36], Sprite smallbang[9], Sprite shell, Sprite selectedSprite);

Weapon *claw = new Weapon(MELEE, 30.0, 1, 0, 1.0, 0.67, 0, 0.25, 0);
Weapon *hammer = new Weapon(MELEE, 45.0, 1, 0, 1.0, 0.9, 0, 0.33, 0);
Weapon *mortar = new Weapon(ART, 35.0, 16, 0, 0.94, 0.4, 0.33, 0.35, 0);
Weapon *mlrs = new Weapon(ART, 40.0, 32, 3, 0.92, 0.4, 0.25, 0.25, 0.55);
Weapon *missile = new Weapon(ART, 60.0, 28, 0, 0.99, 0.67, 0, 0.55, 0.0);
Weapon *minigun = new Weapon(PROJ, 20.0, 20, 4, 0.9, 0.75, 0, 0.2, 0.45);
Weapon *laser = new Weapon(PROJ, 25.0, 100, 0, 0.99, 0.95, 0, 0.35, 0);
Weapon *plasma = new Weapon(PROJ, 35.0, 24, 2, 0.96, 0.67, 0, 0.35, 0.55);
Weapon *cannon = new Weapon(PROJ, 45.0, 32, 0, 0.98, 0.85, 0.2, 0.4, 0);
Weapon *flamer = new Weapon(FLAMER, 30.0, 8, 0, 0, 1, 0, 0.25, 0);

Sprite bfback;

enum guns{CLAW = 0, HAMMER, MORTAR, MLRS, MISSILE, MINIGUN, LASER, PLASMA, CANNON, FLAMETHROWER};

int DLL_EXPORT battlefield(RenderWindow& window){
    Clock clock;
    srand(time(NULL));
     land battlefield[n][m] = {GRSS};
     for(int i = 0; i < n*m; i++){
        if(i/n == 0 || i%m == 0)
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
    botblue, botred,
    mybot, icon[4]; //!0=seeker 1=trooper 2=charger 3=tank
    Texture gunicon[10];
    Texture punch, bang, flares, firing, badabum, spell;


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
    spell.loadFromFile("textures/shell");
    bfback.setTexture(bfbg);
    Sprite mouseCurrSprite;
    bfback.setPosition(0,0);
    Sprite bfsprite[n][m];
    Text nextturn; //!@todo button
    Text tdist;
    Text myhp, myap, hishp, hisap;
    Font font;
    font.loadFromFile("arial.ttf");
    Sprite botsprite[TS];
    Sprite mystats, enemystats, myicon, enemyicon, mywp1, mywp2, hiswp1, hiswp2;
    Sprite selectedSprite;
    Sprite selectedGun;
    Sprite strike;
    Sprite shooting;
    Sprite explosion;
    Sprite destruction;
    Sprite flames[36];
    Sprite smallbang[9];
    Sprite shell;
    selectedSprite.setTexture(that);
    Vector2i localPosition;

    //objects preparing
    int selected = 0;
    int moves = 0;
    int aim_status = 0;
    Weapon *theGun = NULL;
    battle_robot bot[TS];
    direction seq[225] = {NODIR};
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

    nextturn.setCharacterSize(30);
    nextturn.setFont(font);
    nextturn.setColor(Color::White);
    nextturn.setString("END TURN");
    nextturn.setPosition(1136, 638);
    int curr_faction = RED;
    for(int i = 0; i < TS; i++){
        bot[i] = *(new battle_robot(TANK, hammer, flamer));
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

    strike.setTexture(punch);
    shooting.setTexture(firing);
    explosion.setTexture(bang);
    destruction.setTexture(badabum);
    for(int i = 0; i < 36; i++){
        flames[i].setTexture(flares);
    }
    for(int i = 0; i < 9; i++){
        smallbang[i].setTexture(bang);
    }
    shell.setTexture(spell);
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
            bot_walk(bot[selected], moves - 1, seq);
            moves++;
            if(moves > 255)
                moves = 0;
            if(seq[moves - 1] == NODIR)
                moves = 0;
            Sleep(100); //!temp plug until the animation is rdy

            draw_everything(window, battlefield, bfsprite, selectedSprite, botsprite, bot, selected);
            draw_stats(window, bot[selected], icon, gunicon, mystats, myicon, mywp1, mywp2, myhp, myap);
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
                        mouseCurrSprite.setPosition(32*xcoord, 32*ycoord);
                        window.draw(mouseCurrSprite);
                    }
                    break;
                }
                case Event::MouseButtonPressed:{
                    if(event.mouseButton.button == Mouse::Left){
                        if(IntRect(1093+95, 191+53, 32, 32).contains(Mouse::getPosition(window))){
                            aim_status = 1;
                            theGun = bot[selected].gun1;
                            selectedGun.setPosition(1093+95, 191+53);
                            selectedGun.setTexture(allowed);
                        }else if(IntRect(1093+131, 191+53, 32, 32).contains(Mouse::getPosition(window))){
                            aim_status = 1;
                            theGun = bot[selected].gun2;
                            selectedGun.setPosition(1093+131, 191+53);
                            selectedGun.setTexture(allowed);
                        }else if(IntRect(1136, 638, 100, 30).contains(Mouse::getPosition(window))){
                            for(int i = 0; i < TS; i++){
                                bot[i].currAp = bot[i].maxAp;
                            }
                            curr_faction = (++curr_faction)%2;
                            for(int i = 0; i < TS; i++){
                                if(bot[i].tm == curr_faction && !bot[i].destroyed){
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
                            aim_status = 1;
                            theGun = bot[selected].gun1;
                            selectedGun.setPosition(1093+95, 191+53);
                            selectedGun.setTexture(allowed);
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
            } else {
                window.draw(selectedGun);
                switch(event.type){
                case Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape){
                    return 0;
                    }
                    break;
                case Event::MouseMoved:{
                    xcoord = ((int)Mouse::getPosition(window).x)/32;
                    ycoord = ((int)Mouse::getPosition(window).y)/32;
                    if(xcoord < 0 || xcoord > m || ycoord < 0 || ycoord > n)
                        break;
                    cell c = check_walkable(battlefield, xcoord, ycoord, bot, TS, curr_faction);
                    mouseCurrSprite.setTexture(restricted);
                    if(c == FREE || c == BOT_ENEMY){
                        if(eucl_dist_count(bot[selected].pos.x, bot[selected].pos.y, xcoord, ycoord) <= theGun->radius){
                            position pos = *(new position());
                            pos = track(battlefield, bot[selected].pos.x, bot[selected].pos.y, xcoord, ycoord, bot);
                            if((pos.x != xcoord || pos.y != ycoord) && theGun->type != ART){
                                mouseCurrSprite.setPosition(32*xcoord, 32*ycoord);
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
                            tdist.setPosition(5 + 32*xcoord, 37 + 32 *ycoord);
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
                    mouseCurrSprite.setPosition(32*xcoord, 32*ycoord);
                    window.draw(mouseCurrSprite);
                    break;
                    }
                    case Event::MouseButtonPressed:{
                    if(event.mouseButton.button == Mouse::Left){
                        if(IntRect(1093+95, 191+53, 32, 32).contains(Mouse::getPosition(window))){
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
                        xcoord = ((int)Mouse::getPosition(window).x)/32;
                        ycoord = ((int)Mouse::getPosition(window).y)/32;
                        if(xcoord < 0 || xcoord > m || ycoord < 0 || ycoord > n)
                            break;
                        cell c;
                        c = check_walkable(battlefield, xcoord, ycoord, bot, TS, curr_faction);
                        if(c == BOT_ALLY){
                            break;
                        }
                        shoot(window, battlefield, bfsprite, bot, botsprite, selected, xcoord, ycoord, theGun, aim_status,
                              strike, shooting, explosion, destruction, flames, smallbang, shell, selectedSprite);
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
                            //!@todo message & record
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


void draw_everything(RenderWindow &window, land battlefield[n][m], Sprite bfsprite[n][m],
Sprite selectedSprite, Sprite botsprite[TS], battle_robot bot[TS], int selected){
    window.clear(Color::Black);
    window.draw(bfback);
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

void draw_stats(RenderWindow &window, battle_robot bot, Texture *icons,
                Texture *gunicons, Sprite stats, Sprite icon, Sprite wp1,Sprite wp2, Text hp, Text ap){
    switch(bot.rm){
        case SEEKER:
        icon.setTexture(icons[0]);
        break;
        case CHARGER:
        icon.setTexture(icons[2]);
        break;
        case TANK:
        icon.setTexture(icons[3]);
        break;
        default:
        case TROOPER:
        icon.setTexture(icons[1]);
        break;
    }
    if(bot.gun1 == claw){
        wp1.setTexture(gunicons[CLAW]);
    }else if(bot.gun1 == hammer){
        wp1.setTexture(gunicons[HAMMER]);
    } else if(bot.gun1 == mortar){
        wp1.setTexture(gunicons[MORTAR]);
    } else if(bot.gun1 == mlrs){
        wp1.setTexture(gunicons[MLRS]);
    } else if(bot.gun1 == missile){
        wp1.setTexture(gunicons[MISSILE]);
    } else if(bot.gun1 == minigun){
        wp1.setTexture(gunicons[MINIGUN]);
    } else if(bot.gun1 == laser){
        wp1.setTexture(gunicons[LASER]);
    } else if(bot.gun1 == plasma){
        wp1.setTexture(gunicons[PLASMA]);
    } else if(bot.gun1 == cannon){
        wp1.setTexture(gunicons[CANNON]);
    } else if(bot.gun1 == flamer){
        wp1.setTexture(gunicons[FLAMETHROWER]);
    }
    if(bot.gun2 == claw){
        wp2.setTexture(gunicons[CLAW]);
    }else if(bot.gun2 == hammer){
        wp2.setTexture(gunicons[HAMMER]);
    } else if(bot.gun2 == mortar){
        wp2.setTexture(gunicons[MORTAR]);
    } else if(bot.gun2 == mlrs){
        wp2.setTexture(gunicons[MLRS]);
    } else if(bot.gun2 == missile){
        wp2.setTexture(gunicons[MISSILE]);
    } else if(bot.gun2 == minigun){
        wp2.setTexture(gunicons[MINIGUN]);
    } else if(bot.gun2 == laser){
        wp2.setTexture(gunicons[LASER]);
    } else if(bot.gun2 == plasma){
        wp2.setTexture(gunicons[PLASMA]);
    } else if(bot.gun2 == cannon){
        wp2.setTexture(gunicons[CANNON]);
    } else if(bot.gun2 == flamer){
        wp2.setTexture(gunicons[FLAMETHROWER]);
    }
    char buff[20];
    sprintf(buff, "%d / %d", bot.currAp, bot.maxAp);
    ap.setString(buff);
    sprintf(buff, "%d / %d", bot.hp, bot.maxhp);
    hp.setString(buff);
    window.draw(stats);
    window.draw(icon);
    window.draw(wp1);
    window.draw(wp2);
    window.draw(ap);
    window.draw(hp);
}

void shoot(RenderWindow &window, land battlefield[n][m], Sprite bfsprite[n][m], battle_robot *bot, Sprite *botsprite,
int selected, int targx, int targy, Weapon *wp, int shotmode,
Sprite strike, Sprite shooting, Sprite explosion, Sprite destruction, Sprite flames[36], Sprite smallbang[9], Sprite shell, Sprite selectedSprite){
    Clock clock;

    if(eucl_dist_count(bot[selected].pos.x, bot[selected].pos.y, targx, targy) > wp->radius){
        //!@todo message;
        return;
    }
    position pos = *(new position());
    pos = track(battlefield, bot[selected].pos.x, bot[selected].pos.y, targx, targy, bot);
    if((pos.x != targx || pos.y != targy) && wp->type != ART){
        //!@todo message;
        return;
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
        bot_turn(bot[selected], targx, targy);
        //!@todo message;
        return;
    } else {
        ap -= diff;
        bot_turn(bot[selected], targx, targy);
        bot[selected].currAp -= ap;
    }
    if(wp->type == MELEE){

        {
            window.display();
            window.clear(Color::Black);
            strike.setPosition(32 * targx, 32 * targy);
            double cf;
            clock.restart();
            for(cf = 2; cf >= 0; cf--){
                float time = clock.getElapsedTime().asMicroseconds();
                clock.restart();
                time = time/800;
                cf += 0.0005*time;
                strike.setTextureRect(IntRect(32*(int)cf, 0, 32, 32));
                draw_everything(window, battlefield, bfsprite, selectedSprite, botsprite, bot, selected);
                window.draw(strike);
                window.display();
            }
        }

        battle_robot curr;
        for(int i = 0; i < TS; i++){
            if(bot[i].pos.x == targx && bot[i].pos.y == targy){
                int dmg = damage_count(curr, wp, 1);
                bot[i].hp -= dmg;
                if(bot[i].hp <= 0){
                    bot[i].destroyed = 1;
                    bot[i].pos.x = -1;
                    bot[i].pos.y = -1;
                }
                //!@todo animation;
                return;
            }
        }
        if(battlefield[targx][targy] == WALL){
            battlefield[targx][targy] = GRSS;
            //!@todo ruins&animation;
        }
        return;
    }else{
        if(wp->type == FLAMER){
            int cx;
            int cy;
            for(int i = -2; i <= 2; i++){
                for(int j = -2; j <= 2; j++){
                    cx = targx + j;
                    cy = targy + i;
                    if(cx >= 0 && cx < n && cy >= 0 && cy < m){
                        if((rand()%10) - 4 >= 0){
                            //!@todo animation;
                            for(int k = 0; k < TS; k++){
                                if(bot[k].pos.x == cx && bot[k].pos.y == cy){
                                    int dmg = damage_count(bot[k], wp, 1);
                                    bot[k].hp -= dmg;
                                    if(bot[k].hp <= 0){
                                        bot[k].destroyed = 1;
                                        bot[k].pos.x = -1;
                                        bot[k].pos.y = -1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            return;
        } else {
            double acc;
            acc = accuracy_count(eucl_dist_count(bot[selected].pos.x, bot[selected].pos.y, targx, targy), wp);
            if(shotmode == 2 && wp->burst != 0){
            acc *= 0.75;
                for(int i = 0; i < wp->burst; i++){
                    pos = chooseRandom(battlefield, targx, targy, acc);
                    if(wp->type != ART)
                        pos = track(battlefield, bot[selected].pos.x, bot[selected].pos.y, pos.x, pos.y, bot);
                    for(int j = 0; j < TS; j++){
                        if(bot[j].pos.x == pos.x && bot[j].pos.y == pos.y){
                            int dmg = damage_count(bot[j], wp, eucl_dist_count(bot[selected].pos.x, bot[selected].pos.y, pos.x, pos.y));
                            bot[j].hp -= dmg;
                            if(bot[j].hp <= 0){
                                bot[j].destroyed = 1;
                                bot[j].pos.x = -1;
                                bot[j].pos.y = -1;
                            }
                        }
                    }
                    if(wp->splash > 0){
                        int cx;
                        int cy;
                        for(int u = -1; u < 1; u++){
                            for(int v = -1; v < 1; v++){
                                if(!u && !v)
                                    continue;
                                cx = pos.x + v;
                                cy = pos.y + v;
                                for(int j = 0; j < TS && cx >= 0 && cx < n && cy >= 0 && cy < m; j++){
                                    if(bot[j].pos.x == cx && bot[j].pos.y == cy){
                                        bot[j].hp -= wp->splash*damage_count(bot[j], wp, 1);
                                        if(bot[j].hp <= 0){
                                            bot[j].destroyed = 1;
                                            bot[j].pos.x = -1;
                                            bot[j].pos.y = -1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if(battlefield[pos.x][pos.y] == WALL){
                        battlefield[pos.x][pos.y] = GRSS;
                    }
                }
                return;
            } else {
                pos = chooseRandom(battlefield, targx, targy, acc);
                if(wp->type != ART)
                    pos = track(battlefield, bot[selected].pos.x, bot[selected].pos.y, pos.x, pos.y, bot);
                for(int j = 0; j < TS; j++){
                    if(bot[j].pos.x == pos.x && bot[j].pos.y == pos.y){
                        int dmg = damage_count(bot[j], wp, eucl_dist_count(bot[selected].pos.x, bot[selected].pos.y, pos.x, pos.y));
                        bot[j].hp -= dmg;
                        if(bot[j].hp <= 0){
                            bot[j].destroyed = 1;
                            bot[j].pos.x = -1;
                            bot[j].pos.y = -1;
                        }
                    }
                }
                if(wp->splash > 0){
                    int cx;
                    int cy;
                    for(int u = -1; u < 1; u++){
                        for(int v = -1; v < 1; v++){
                            if(!u && !v)
                                continue;
                            cx = pos.x + v;
                            cy = pos.y + v;
                            for(int j = 0; j < TS && cx >= 0 && cx < n && cy >= 0 && cy < m; j++){
                                if(bot[j].pos.x == cx && bot[j].pos.y == cy){
                                    bot[j].hp -= wp->splash*damage_count(bot[j], wp, 1);
                                    if(bot[j].hp <= 0){
                                        bot[j].destroyed = 1;
                                        bot[j].pos.x = -1;
                                        bot[j].pos.y = -1;
                                    }
                                }
                            }
                        }
                    }
                }
                if(battlefield[pos.x][pos.y] == WALL){
                    battlefield[pos.x][pos.y] = GRSS;
                }
                return;
            }
        }
    }
}
