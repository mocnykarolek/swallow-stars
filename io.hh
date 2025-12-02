
#include <ncurses.h>

#include "actors.hh"



void draw_bird(GameConfig *cfg, Bird *bird);

void screenInitialization(GameConfig *cfg);

void deleteWindow(GameConfig *cfg);

void confReader(GameConfig *cfg);

void updateBirdPosition(GameConfig *cfg, Bird *bird);

void drawStar(GameConfig *cfg, STARS *s);

void updateStarPosition(GameConfig *cfg, STARS *s);


MenuCongif* InitMenuconf(GameConfig *cfg);

void drawMenu(MenuCongif *menu, Bird *bird);

void gameover(GameConfig *cfg);




