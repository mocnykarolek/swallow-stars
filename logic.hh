#ifndef LOGIC_H
#define LOGIC_H

#include <ncurses.h>
#include "defs.hh" 
#include "actors.hh"
#include "io.hh"

#include <time.h>


void gameLoop(GameConfig *cfg, Bird *bird);

void changeBirdDirection(Bird *bird);

void detectBorderColission(GameConfig *cfg, Bird *bird);

STARS* star_array(GameConfig *cfg);

void move_star(STARS *star);

void changeGameSpeed(gs* gamespeed);


#endif
