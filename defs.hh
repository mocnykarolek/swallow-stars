#ifndef DEFS_HH
#define DEFS_HH

#include <ncurses.h>
#include <unistd.h> 
#include <stdio.h>
#include <string.h> 

#include <cstdio> 
#include <cstdlib>



#define QUIT 'q'

#define UP 'w'
#define RIGHT 'd'
#define DOWN 's'
#define LEFT 'a'
#define FASTER 'p'
#define SLOWER 'o'


struct GameConfig {
    int width;
    int height;
    int delay;    
    int max_stars;
    int min_stars;
    int max_opps;
    int min_opps;
    
    int time;
    

    WINDOW *win;  
};

struct MenuCongif{
    int width;
    int height;
    int time_left;
    int points;

    WINDOW *menu_win;
};


struct Bird {
    int position_x;
    int position_y;
    int dx, dy;
    char symbol;
    int lives_remaining;
};

struct STARS {
    char symbol;
    int speed;
    int position_x;
    int position_y;
    int alive;


};

struct gs{
    int very_slow;
    int slow;
    int normal;
    int fast;
    int very_fast;
    int current_speed;

};



#endif