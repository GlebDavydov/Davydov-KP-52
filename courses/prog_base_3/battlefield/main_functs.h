#ifndef MAIN_FUNCTS_H_INCLUDED
#define MAIN_FUNCTS_H_INCLUDED

#include <windows.h>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>

#include "bf.h"
//#include "view.h"
#include "shooting.h"

enum step_mode{MP, AI_DUMB, AI_EVIL, AI_SMART};

using namespace sf;

void initSprites(land battlefield[n][m], battle_robot bot[TS], int shiftx, int shifty);

void draw_everything(RenderWindow &window, land battlefield[n][m], battle_robot bot[TS], int selected, int shiftx, int shifty);


//void draw_gui(RenderWindow &window);

void animation_strike(RenderWindow &window, int px, int py, land battlefield[n][m], battle_robot bot[TS], int selected);
void animation_shooting(RenderWindow &window, int px, int py, int selected, land battlefield[n][m], battle_robot bot[TS]);
void animation_explode(RenderWindow &window, int px, int py, land battlefield[n][m], battle_robot bot[TS], int selected);
void animation_destroyed(RenderWindow &window, int px, int py, land battlefield[n][m], battle_robot bot[TS], int selected);
void animation_flames(RenderWindow &window, land battlefield[n][m], battle_robot bot[TS], int selected);
void animation_smallbangs(RenderWindow &window, land battlefield[n][m], battle_robot bot[TS], int selected);
void message_show(RenderWindow &window, char* msg, int messageType);

void draw_minimap(RenderWindow &window, land battlefield[n][m], battle_robot bot[TS], int selected);

void camera_center(int px, int py);

void draw_stats(RenderWindow &window, battle_robot bot, Texture *icons,
Texture *gunicons, Sprite stats, Sprite boticon, Sprite wp1, Sprite wp2, Text hp, Text ap);

int shoot(RenderWindow &window, land battlefield[n][m], battle_robot bot[TS],
int selected, int targx, int targy, Weapon *wp, int shotmode);

int ai_step_agressive(RenderWindow &window, land battlefield[n][m], battle_robot bot[TS], int &currFaction);
int ai_step_dumb(RenderWindow &window, land battlefield[n][m], battle_robot[TS], int &currFaction);
int ai_step_alert(RenderWindow &window, land battlefield[n][m], battle_robot bot[TS], int &currFaction);
int player_step(RenderWindow &window, land battlefield[n][m], battle_robot bot[TS], int &currFaction);

void gunChoose(int t, int c, battle_robot &bot);

#endif // MAIN_FUNCTS_H_INCLUDED
