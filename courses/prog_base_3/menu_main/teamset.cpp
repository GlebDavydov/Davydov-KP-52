#include <windows.h>
#include <SFML/Graphics.hpp>

#include "menus.h"
#include "bots.h"

using namespace sf;

typedef int (*battlefield)(RenderWindow &window, int battlemode, blueprint botset[TS]);

void draw_bots(RenderWindow &window, blueprint *botset, Texture *icons, Texture *gun_ts, Sprite frame, Sprite bot, Sprite gun1, Sprite gun2, Text textBot, Text textAp, Text textHp);


int battle_start(RenderWindow &window, Sprite background, int battlemode){
    HINSTANCE hLib = LoadLibrary("battlefield.dll");
    if(!hLib)
        return 1;
    battlefield bf = (battlefield)GetProcAddress(hLib, "battlefield");
    window.clear(Color::Black);
    blueprint botset[TS];
    for(int i = 0; i < TS; i++){
        botset[i].mod = TROOPER;
        botset[i].gun1 = 0;
        botset[i].gun2 = 0;
    }
    Texture battle_s, battle_b, exit_s, exit_b, frame_t, red_t, blue_t;
    battle_b.loadFromFile("textures/menu/BATTLE_BIG.png");
    battle_s.loadFromFile("textures/menu/BATTLE_SMALL.png");
    exit_b.loadFromFile("textures/menu/BACK_BIG.png");
    exit_s.loadFromFile("textures/menu/BACK_SMALL.png");
    frame_t.loadFromFile("textures/mystats.png");
    red_t.loadFromFile("textures/red.png");
    blue_t.loadFromFile("textures/blue.png");

    Texture bot_t[4];
    Texture gun_t[10];

    for(int i = 0; i < 4; i++){
        bot_t[i].loadFromFile("textures/icons.png", IntRect(64*i, 0, 64, 64));
    }
    gun_t[CLAW].loadFromFile("textures/guns/claw.png");
    gun_t[HAMMER].loadFromFile("textures/guns/hammer.png");
    gun_t[MORTAR].loadFromFile("textures/guns/mortar.png");
    gun_t[MLRS].loadFromFile("textures/guns/mlrs.png");
    gun_t[MISSILE].loadFromFile("textures/guns/missile.png");
    gun_t[MINIGUN].loadFromFile("textures/guns/minigun.png");
    gun_t[LASER].loadFromFile("textures/guns/laser.png");
    gun_t[PLASMA].loadFromFile("textures/guns/plasmagun.png");
    gun_t[CANNON].loadFromFile("textures/guns/cannon.png");
    gun_t[FLAMETHROWER].loadFromFile("textures/guns/flamethrower.png");

    Font font;
    font.loadFromFile("arial.ttf");
    Text textBot(" ", font, 12);
    textBot.setColor(Color::Black);
    Text textAp(" ", font, 12);
    textAp.setColor(Color::Green);
    Text textHp(" ", font, 12);
    textHp.setColor(Color::Red);

    Sprite battle, exit, frame, bot, gun1, gun2, red, blue;
    battle.setPosition(538, 560);
    exit.setPosition(580, 660);
    frame.setTexture(frame_t);
    red.setTexture(red_t);
    red.setPosition(213, 143);
    blue.setTexture(blue_t);
    blue.setPosition(883, 143);
    while(window.isOpen()){
            Event event;
        while(window.pollEvent(event)){
            window.clear(Color::White);
            window.draw(background);
            battle.setTexture(battle_s);
            exit.setTexture(exit_s);
            window.draw(red);
            window.draw(blue);
            if(event.type == Event::KeyPressed){
                if(event.key.code == Keyboard::Escape){
                    FreeLibrary(hLib);
                    return 0;
                }
            } else if(event.type == Event::MouseMoved){
                if(IntRect(558, 580, 245, 60).contains(Mouse::getPosition(window))){
                    battle.setTexture(battle_b);
                }else if(IntRect(600, 680, 165, 60).contains(Mouse::getPosition(window))){
                    exit.setTexture(exit_b);
                }
            } else if(event.type == Event::MouseButtonPressed){
                if(event.mouseButton.button == Mouse::Left){
                    if(IntRect(558, 580, 245, 60).contains(Mouse::getPosition(window))){
                        bf(window, battlemode, botset);
                        FreeLibrary(hLib);
                        return 0;
                    }else if(IntRect(600, 680, 165, 60).contains(Mouse::getPosition(window))){
                        FreeLibrary(hLib);
                        return 0;
                    } else if(IntRect(213, 239, 256, 480).contains(Mouse::getPosition(window))){
                        int x = Mouse::getPosition(window).x - 214;
                        int y = Mouse::getPosition(window).y - 240;
                        int i = y/96;
                        y -= 96*i;
                        if(x > 15 && x < 64+15 && y > 15 && y < 64+15){
                            switch(botset[i].mod){
                            case SEEKER:
                                botset[i].mod = CHARGER;
                                break;
                            case CHARGER:
                                botset[i].mod = TROOPER;
                                break;
                            case TANK:
                                botset[i].mod = SEEKER;
                                break;
                            default:
                            case TROOPER:
                                botset[i].mod = TANK;
                                break;
                            }
                        } else if (x > 95 && x < 95+32 && y > 53 && y < 53+32){
                            botset[i].gun1 = (botset[i].gun1+1)%10;
                        } else if (x > 131 && x < 131+32 && y > 53 && y < 53+32){
                            botset[i].gun2 = (botset[i].gun2+1)%10;
                        }
                    } else if(IntRect(883, 239, 256, 480).contains(Mouse::getPosition(window))){
                        int x = Mouse::getPosition(window).x - 214 - 670;
                        int y = Mouse::getPosition(window).y - 240;
                        int i = y/96;
                        y -= 96*i;
                        i += 5;
                        if(x > 15 && x < 64+15 && y > 15 && y < 64+15){
                            switch(botset[i].mod){
                            case SEEKER:
                                botset[i].mod = CHARGER;
                                break;
                            case CHARGER:
                                botset[i].mod = TROOPER;
                                break;
                            case TANK:
                                botset[i].mod = SEEKER;
                                break;
                            default:
                            case TROOPER:
                                botset[i].mod = TANK;
                                break;
                            }
                        } else if (x > 95 && x < 95+32 && y > 53 && y < 53+32){
                            botset[i].gun1 = (botset[i].gun1+1)%10;
                        } else if (x > 131 && x < 131+32 && y > 53 && y < 53+32){
                            botset[i].gun2 = (botset[i].gun2+1)%10;
                        }
                    }
                }
            }
            draw_bots(window, botset, bot_t, gun_t, frame, bot, gun1, gun2, textBot, textAp, textHp);
            window.draw(battle);
            window.draw(exit);
            window.display();
        }
    }
    FreeLibrary(hLib);
    return 1;
}

void draw_bots(RenderWindow &window, blueprint *botset, Texture *icons,
                Texture *gun_ts, Sprite frame, Sprite bot, Sprite gun1, Sprite gun2, Text textBot, Text textAp, Text textHp){
    for(int i = 0; i < TS; i++){
        int px = 213 + (i/5)*670;
        int py = 239 + (i%5)*96;
        switch(botset[i].mod){
            case SEEKER:
                bot.setTexture(icons[0]);
                textBot.setString("Seeker");
                textAp.setString("104");
                textHp.setString("100");
                break;
            case CHARGER:
                bot.setTexture(icons[2]);
                textBot.setString("Charger");
                textAp.setString("120");
                textHp.setString("140");
                break;
            case TANK:
                bot.setTexture(icons[3]);
                textBot.setString("Tank");
                textAp.setString("88");
                textHp.setString("150");
            break;
            default:
            case TROOPER:
                bot.setTexture(icons[1]);
                textBot.setString("Trooper");
                textAp.setString("112");
                textHp.setString("125");
            break;
        }
        frame.setPosition(px, py);

        gun1.setTexture(gun_ts[botset[i].gun1]);
        gun2.setTexture(gun_ts[botset[i].gun2]);

        bot.setPosition(px+15, py+15);
        gun1.setPosition(px+95, py+53);
        gun2.setPosition(px+131, py+53);
        textHp.setPosition(px+127, py+17);
        textAp.setPosition(px+127, py+36);
        textBot.setPosition(px+26, py+78);
        window.draw(frame);
        window.draw(bot);
        window.draw(gun1);
        window.draw(gun2);
        window.draw(textBot);
        window.draw(textAp);
        window.draw(textHp);
    }
}
