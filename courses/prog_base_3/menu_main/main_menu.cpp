#include <windows.h>
#include <SFML/Graphics.hpp>

#include "bots.h"
#include "menus.h"

#define USW 1366
#define USH 768

enum holdStatus{NOTHING, EXIT, SINLEPLAYER, MULTIPLAYER, SETTINGS};

using namespace sf;

int main_menu(void){
    int ai_mode = AI_DUMB;
    Texture bckgrnd, ex_1, ex_2, singl_1, singl_2, mult_b, mult_s, set_b, set_s;
    bckgrnd.loadFromFile("textures/menu/background.JPG");
    ex_1.loadFromFile("textures/menu/EXIT_SMALL.PNG");
    ex_2.loadFromFile("textures/menu/EXIT_BIG.PNG");
    singl_1.loadFromFile("textures/menu/SP_SMALL.PNG");
    singl_2.loadFromFile("textures/menu/SP_BIG.PNG");
    mult_s.loadFromFile("textures/menu/MP_SMALL.PNG");
    mult_b.loadFromFile("textures/menu/MP_BIG.PNG");
    set_s.loadFromFile("textures/menu/SETTINGS_SMALL.PNG");
    set_b.loadFromFile("textures/menu/SETTINGS_BIG.PNG");

    Sprite menu_back(bckgrnd), menu_exit(ex_1), menu_singleplayer(singl_1);
    Sprite mp(mult_s);
    Sprite settings(set_s);


    menu_back.setPosition(0, 0);
    menu_exit.setPosition(580, 540);
    menu_singleplayer.setPosition(440, 240);
    mp.setPosition(455, 340);
    settings.setPosition(540, 440);

    RenderWindow window(VideoMode(USW, USH), "Fury of Steel", Style::Fullscreen);
    Event event;
    int holdStatus = NOTHING;
    while (window.isOpen()){
        while (window.pollEvent(event)){
        window.clear(Color::White);
        menu_exit.setTexture(ex_1);
        menu_singleplayer.setTexture(singl_1);
        mp.setTexture(mult_s);
        settings.setTexture(set_s);
        switch(event.type){
                case Event::MouseMoved:
                    if(IntRect(580, 540, 155, 60).contains(Mouse::getPosition(window))){
                        menu_exit.setTexture(ex_2);
                        holdStatus = EXIT;
                    } else if(IntRect(440, 240, 455, 60).contains(Mouse::getPosition(window))){
                        menu_singleplayer.setTexture(singl_2);
                        holdStatus = SINLEPLAYER;
                    } else if(IntRect(455, 340, 390, 60).contains(Mouse::getPosition(window))){
                        mp.setTexture(mult_b);
                        holdStatus = MULTIPLAYER;
                    } else if(IntRect(540, 440, 265, 60).contains(Mouse::getPosition(window))){
                        settings.setTexture(set_b);
                        holdStatus = SETTINGS;
                    } else {
                        holdStatus = NOTHING;
                    }
                break;
                case Event::MouseButtonPressed:
                    if(event.mouseButton.button == Mouse::Left)
                    switch(holdStatus){
                        case EXIT:
                            window.close();
                            break;
                        case SINLEPLAYER:
                            battle_start(window, menu_back, ai_mode);
                            break;
                        case MULTIPLAYER:
                            battle_start(window, menu_back, MP);
                            break;
                        case SETTINGS:
                            ai_settings(window, menu_back, ai_mode);
                        default:
                            break;
                    }
                break;
                case Event::Closed:
                    window.close();
                default:
                break;
            }
            window.draw(menu_back);
            window.draw(mp);
            window.draw(settings);
            window.draw(menu_exit);
            window.draw(menu_singleplayer);

            window.display();
        }
    }
    return 0;
}
