#ifndef LOGIC_H
#define LOGIC_H

#include <ncurses.h>
#include "defs.hh" 
#include "actors.hh"
#include "io.hh"

void gameLoop(GameConfig *cfg);

void changeBirdDirection();

#endif
