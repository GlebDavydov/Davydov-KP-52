#include <windows.h>
#include <SFML/Graphics.hpp>

#include "menus.h"

using namespace sf;

typedef int (*battlefield)(RenderWindow& window);

enum holdStatus{NOTHING, EXIT, BATTLE};

int singleplayer_menu(RenderWindow &window, Sprite menu_back){
    battlefield bf = NULL;
    HINSTANCE hLib = LoadLibrary("battlefield.dll");
    if(!hLib)
        return 1;
    bf = (battlefield)GetProcAddress(hLib, "battlefield");
    Texture battle_1, battle_2, ex_1, ex_2;
    ex_1.loadFromFile("BACK_SMALL.PNG");
    ex_2.loadFromFile("BACK_BIG.PNG");
    battle_1.loadFromFile("BATTLE_SMALL.PNG");
    battle_2.loadFromFile("BATTLE_BIG.PNG");

    Sprite menu_exit(ex_1), menu_battle(battle_1);

    menu_exit.setPosition(580, 460);
    menu_battle.setPosition(570, 360);

    Event event;
    int holdStatus = NOTHING;
    while (window.isOpen()){
        while (window.pollEvent(event)){
        window.clear(Color::White);
        menu_exit.setTexture(ex_1);
        menu_battle.setTexture(battle_1);
            switch(event.type){
                case Event::MouseMoved:
                    if(IntRect(580, 460, 155, 60).contains(Mouse::getPosition(window))){
                        menu_exit.setTexture(ex_2);
                        holdStatus = EXIT;
                    } else if(IntRect(570, 360, 175, 60).contains(Mouse::getPosition(window))){
                        menu_battle.setTexture(battle_2);
                        holdStatus = BATTLE;
                    } else {
                        holdStatus = NOTHING;
                    }
                break;
                case Event::MouseButtonPressed:
                    if(event.mouseButton.button == Mouse::Left)
                    switch(holdStatus){
                        case EXIT:
                            return 0;
                        case BATTLE:
                            //bf(window);
                            break;
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
            window.draw(menu_exit);
            window.draw(menu_battle);

            window.display();
        }
    }
    FreeLibrary(hLib);
    return 0;
}
