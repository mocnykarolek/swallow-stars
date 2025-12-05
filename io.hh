
#include <ncurses.h>

#include "actors.hh"

void clearHunter(hunter* h, GameConfig *cfg);

void draw_bird(GameConfig *cfg, Bird *bird);

void drawHunter(GameConfig *cfg, hunter* h);

void screenInitialization(GameConfig *cfg);

void deleteWindow(GameConfig *cfg);

void confReader(GameConfig *cfg);

void updateBirdPosition(GameConfig *cfg, Bird *bird);

void drawStar(GameConfig *cfg, STARS *s);

void updateStarPosition(GameConfig *cfg, STARS *s);

void drawBox(GameConfig *cfg);
MenuCongif* InitMenuconf(GameConfig *cfg);

void drawMenu(MenuCongif *menu, Bird *bird);

void gameover(GameConfig *cfg);




