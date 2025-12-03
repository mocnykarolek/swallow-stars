#include "actors.hh"


void init_bird(GameConfig *cfg, Bird *bird){

    bird->position_x = (double)cfg->width /2;
    bird->position_y = (double)cfg->height /2;
    bird->symbol = '#';
    bird->lives_remaining = 5;
    bird->speed = 15.0f;
    bird->dx = 0;
    bird->dy = 0;
}



hunter* hunters_array(GameConfig *cfg){
    
    hunter* hunters = new hunter[cfg->max_opps];

    return hunters;
}

hunter* init_hunter(hunter* hunter, Bird *bird ,GameConfig *cfg){

    h_size rozmiary[] = {{2,1}, {1,2}, {2,2}};

    int size = sizeof(rozmiary) / sizeof(rozmiary[0]);

    int rand_size = rand() % size;

    hunter->size.x = rozmiary[rand_size].x;
    hunter->size.y = rozmiary[rand_size].y;


    hunter->bouces_left = 5;
    int side = rand() % 4;
    switch(side){

        case 0:
            hunter->position_x = cfg->height / 2;
            hunter->position_y = cfg->width -3;
        case 1:
            hunter->position_x = cfg->height + 3;
            hunter->position_y = cfg->width /2;
        case 2:
            hunter->position_x = cfg->height / 2;
            hunter->position_y = cfg->width +3;
        case 3:
            hunter->position_x = cfg->height - 3;
            hunter->position_y = cfg->width /2;

        default:
            break;
    }
    hunter->dx = bird->dx;
    hunter->dy = bird->dy;
    


    return hunter;

    // hunter size random from tab list


}