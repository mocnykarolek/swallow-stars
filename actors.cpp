#include "actors.hh"

Bird bird;

void init_bird(GameConfig *cfg){

    bird.position_x = cfg->width /2;
    bird.position_y = cfg->height /2;
    bird.symbol = '>';
}

