#include <windows.h>
#include <SFML/Graphics.hpp>

#define USW 1366
#define USH 768

enum holdStatus{NOTHING, EXIT};

using namespace sf;

int main_menu(void){

    Texture bckgrnd, ex_1, ex_2; //set_1, set_2;
    bckgrnd.loadFromFile("background.JPG");
    ex_1.loadFromFile("EXIT_SMALL.PNG");
    ex_2.loadFromFile("EXIT_BIG.PNG");

    Sprite menu_back(bckgrnd), menu_exit(ex_1);

    menu_back.setPosition(0, 0);
    menu_exit.setPosition(580, 540);

    RenderWindow window(VideoMode(USW, USH), "Fury of Steel", Style::Fullscreen);
    Event event;
    int holdStatus = NOTHING;
    while (window.isOpen()){
        while (window.pollEvent(event)){
        window.clear(Color::White);
        menu_exit.setTexture(ex_1);
        menu_back.setTexture(bckgrnd);
            switch(event.type){
                case Event::MouseMoved:
                    if(IntRect(580, 540, 155, 60).contains(Mouse::getPosition(window))){
                        menu_exit.setTexture(ex_2);
                        holdStatus = EXIT;
                    } else {
                        holdStatus = NOTHING;
                    }
                break;
                case Event::MouseButtonPressed:
                    if(event.mouseButton.button == Mouse::Left && holdStatus == EXIT)
                        window.close();
                break;
                case Event::Closed:
                    window.close();
                default:
                break;
            }
            window.draw(menu_back);
            window.draw(menu_exit);

            window.display();
        }
    }

    return 0;
}
