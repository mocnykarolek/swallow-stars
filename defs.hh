#ifndef DEFS_HH
#define DEFS_HH

#include <ncurses.h>
#include <unistd.h> 
#include <stdio.h>
#include <string.h> 

// #include <cstdio> 
// #include <cstdlib>
#include <time.h>
#include <math.h>



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
    int level;

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
    double position_x;
    double position_y;
    double dx, dy;
    char symbol;
    double speed;
    int lives_remaining;
    float dt;
};

struct STARS {
    char symbol;
    int speed;
    double position_x;
    double position_y;
    int alive;
    float dt;


};

struct gs{
    int very_slow;
    int slow;
    int normal;
    int fast;
    int very_fast;
    int current_speed;

};

struct hunter {
    float position_x;
    float position_y;
    float dx;
    float dy;
    int bouces_left;
    struct {int x; int y;} size;
    char symbol = '&';
    int alive;
    int in;
    int type;

};

struct h_size {
    int x;
    int y;
};


#endif