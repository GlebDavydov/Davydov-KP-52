#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include <SFML/Graphics.hpp>

int main_menu(void);
int battle_start(sf::RenderWindow &window, sf::Sprite background, int battlemode);
int ai_settings(sf::RenderWindow &window, sf::Sprite background, int &battlemode);

#endif // MENUS_H_INCLUDED
