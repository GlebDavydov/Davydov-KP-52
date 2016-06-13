#include <windows.h>
#include <SFML/Graphics.hpp>

#include "menus.h"
#include "bots.h"

using namespace sf;


int ai_settings(RenderWindow &window, Sprite background, int &ai_mode){
    window.clear(Color::Black);

    Texture exit_s, exit_b;
    exit_b.loadFromFile("textures/menu/BACK_BIG.png");
    exit_s.loadFromFile("textures/menu/BACK_SMALL.png");

    Font font;
    font.loadFromFile("arial.ttf");

    Text param("AI MODE", font, 32);
    param.setColor(Color::Red);
    param.setPosition(540, 300);
    Text value(" ", font, 32);
    value.setColor(Color::Red);
    value.setPosition(760, 300);

    Sprite exit;
    exit.setPosition(580, 660);
    while(window.isOpen()){
            Event event;
        while(window.pollEvent(event)){
            window.clear(Color::White);
            window.draw(background);
            exit.setTexture(exit_s);
            if(event.type == Event::KeyPressed){
                if(event.key.code == Keyboard::Escape){
                    return 0;
                }
            } else if(event.type == Event::MouseMoved){
                if(IntRect(600, 680, 165, 60).contains(Mouse::getPosition(window))){
                    exit.setTexture(exit_b);
                }
            } else if(event.type == Event::MouseButtonPressed){
                if(event.mouseButton.button == Mouse::Left){
                    if(IntRect(600, 680, 165, 60).contains(Mouse::getPosition(window))){
                        return 0;
                    } else if(IntRect(760, 300, 220, 32).contains(Mouse::getPosition(window))){
                        switch(ai_mode){
                        case AI_DUMB:
                            ai_mode = AI_EVIL;
                            break;
                        case AI_EVIL:
                            ai_mode = AI_SMART;
                            break;
                        case AI_SMART:
                            ai_mode = AI_DUMB;
                            break;
                        }
                    }
                }
            }
            switch(ai_mode){
            case AI_DUMB:
                value.setString("DUMMY");
                break;
            case AI_EVIL:
                value.setString("AGRESSIVE");
                break;
            case AI_SMART:
                value.setString("ALERT");
                break;
            }
            window.draw(param);
            window.draw(value);
            window.draw(exit);
            window.display();
        }
    }
    return 1;
}
