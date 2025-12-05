#ifndef LOGIC_H
#define LOGIC_H

#include <ncurses.h>
#include "defs.hh" 
#include "actors.hh"
#include "io.hh"




void gameLoop(GameConfig *cfg, Bird *bird);

void updateHunterPosition(hunter* h, GameConfig *cfg);

// void changeHunterDirection(hunter* h);
void detectHunterBorderCollision(hunter* h, GameConfig *cfg);

void detectBirdHunterCollision(Bird *b, hunter* h);
void didHunterEnter(hunter* h, GameConfig *cfg);
void nextLevel(GameConfig *cfg, Bird *bird, STARS *stars, hunter *hunters, MenuCongif *menu);
void starOutsideBorder(STARS* star, GameConfig *cfg);
void changeBirdDirection(Bird *bird);

void detectBorderColission(GameConfig *cfg, Bird *bird);

STARS* star_array(GameConfig *cfg);

void move_star(STARS *star);

gs* init_gs(GameConfig *cfg);
void changeGameSpeed(gs* gamespeed, char input, int *delay);

void changeGameSpeed(gs* gamespeed);

void birdStarCollision(Bird* bird, STARS *star, MenuCongif* menu, GameConfig* cfg);

#endif
