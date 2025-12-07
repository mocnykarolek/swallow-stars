#ifndef LOGIC_H
#define LOGIC_H

#include <ncurses.h>
#include "defs.hh" 
#include "actors.hh"
#include "io.hh"

void gameLoop(GameConfig *cfg, Bird *bird);

void hunterBehaviour(GameConfig *cfg, hunter *hunters, Bird* bird ,h_size* templates, int*count);

void firstLevelInits(GameConfig *cfg, Levels* levels);

void starBehaviour(GameConfig *cfg, Bird* bird, STARS* s, MenuCongif* menu);

void HandleUserInput(GameConfig *cfg, Bird *bird, int *gameStart, int *input,gs* gamespeed,int *delay );

void updateHunterPosition(hunter* h, GameConfig *cfg);

void gameTimer(int *fps, int *timer, MenuCongif* menu);
// void changeHunterDirection(hunter* h);
void detectHunterBorderCollision(hunter* h, GameConfig *cfg);

void detectBirdHunterCollision(Bird *b, hunter* h, GameConfig* cfg);

void didHunterEnter(hunter* h, GameConfig *cfg);

void nextLevel(GameConfig *cfg, Bird *bird, STARS *stars, hunter *hunters, MenuCongif *menu, Levels* l, int*lnum);

void starOutsideBorder(STARS* star, GameConfig *cfg);

void changeBirdDirection(Bird *bird);

void detectBorderColission(GameConfig *cfg, Bird *bird);

STARS* star_array(GameConfig *cfg);

void move_star(STARS *star);

gs* init_gs(GameConfig *cfg);

void changeGameSpeed(gs* gamespeed, char input, int *delay);

void deallocate(Levels* levels, gs* gamespeed,h_size* templates, hunter* hunters, STARS* s, MenuCongif* menu);
void birdStarCollision(Bird* bird, STARS *star, MenuCongif* menu, GameConfig* cfg);

void mainLoop(GameConfig* cfg, Bird* bird, Levels* levels, gs* gamespeed, h_size* templates, hunter* hunters, STARS* s, MenuCongif* menu, 
              int* tcount, int* levels_num, int* gameStart, int* input, int* delay, int* fps, int* timer);


#endif
