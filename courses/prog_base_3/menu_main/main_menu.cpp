#include <windows.h>
#include <SFML/Graphics.hpp>

#include "menus.h"

#define USW 1366
#define USH 768

enum holdStatus{NOTHING, EXIT, SINLEPLAYER};

using namespace sf;

int main_menu(void){
    Texture bckgrnd, ex_1, ex_2, singl_1, singl_2;
    bckgrnd.loadFromFile("background.JPG");
    ex_1.loadFromFile("EXIT_SMALL.PNG");
    ex_2.loadFromFile("EXIT_BIG.PNG");
    singl_1.loadFromFile("SP_SMALL.PNG");
    singl_2.loadFromFile("SP_BIG.PNG");

    Sprite menu_back(bckgrnd), menu_exit(ex_1), menu_singleplayer(singl_1);

    menu_back.setPosition(0, 0);
    menu_exit.setPosition(580, 540);
    menu_singleplayer.setPosition(430, 440);

    RenderWindow window(VideoMode(USW, USH), "Fury of Steel", Style::Fullscreen);
    Event event;
    int holdStatus = NOTHING;
    while (window.isOpen()){
        while (window.pollEvent(event)){
        window.clear(Color::White);
        menu_exit.setTexture(ex_1);
        menu_singleplayer.setTexture(singl_1);
            switch(event.type){
                case Event::MouseMoved:
                    if(IntRect(580, 540, 155, 60).contains(Mouse::getPosition(window))){
                        menu_exit.setTexture(ex_2);
                        holdStatus = EXIT;
                    } else if(IntRect(430, 440, 455, 60).contains(Mouse::getPosition(window))){
                        menu_singleplayer.setTexture(singl_2);
                        holdStatus = SINLEPLAYER;
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
                            singleplayer_menu(window, menu_back);
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
            window.draw(menu_singleplayer);

            window.display();
        }
    }
    return 0;
}
