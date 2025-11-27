#ifndef DEFS_HH
#define DEFS_HH

#include <ncurses.h>
#include <unistd.h> 
#include <stdio.h>
#include <string.h> 

#include <cstdio> 
#include <cstdlib>



#define QUIT 'q'
#define game_speed 1
#define UP 'w'
#define RIGHT 'd'
#define DOWN 's'
#define LEFT 'a'

struct GameConfig {
    int width;
    int height;
    int delay;      // Tu przechowuj main_delay
    WINDOW *win;    // Tu przechowuj wskaźnik na okno!
};


struct Bird {
    int position_x;
    int position_y;
    int dx, dy;
    char symbol;
    int lives_remaining;
};

struct star {
    char symbol;
    int speed;
};


#endif