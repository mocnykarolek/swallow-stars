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
    for(int i=0; i<cfg->max_opps; i++) {
        hunters[i].alive = false;
        hunters[i].bouces_left = 0;
    }

    return hunters;
}

hunter* init_hunter(hunter* hunter, Bird *bird ,GameConfig *cfg,h_size* templates, int*count){


       
    int type = (rand() % *count); 
    hunter->alive = true;
    hunter->size.x = templates[type].x;
    hunter->size.y = templates[type].y;

    

    hunter->bouces_left = cfg->max_bounces;
    int side = rand() % 4;
    switch(side){

        case 0:
            hunter->position_y = cfg->height / 2;
            hunter->position_x = cfg->width -3;
            break;
        case 1:
            hunter->position_y = cfg->height /2;
            hunter->position_x = 1;
            break;
        case 2:
            hunter->position_y = 1;
            hunter->position_x = cfg->width /2;
            break;
        case 3:
            hunter->position_y = cfg->height - 3;
            hunter->position_x = cfg->width /2;
            break;

        default:
            break;
    }
    float diff_x = bird->position_x - hunter->position_x;
    float diff_y = bird->position_y - hunter->position_y;
    

    float length = sqrt(diff_x * diff_x + diff_y * diff_y);
    if(length == 0){
        length =1;
        diff_x=1;
    }
    float speed = 0.5f;
    switch((type % 3) +1){
        case 1:
            speed = 0.7f;
            break;
        case 2:
            speed = 0.6f;
            break;
        case 3:
            speed = 0.5f;
            break;
        default:
            speed = 0.5f;
            break;

    }
    hunter->type = type;
    
    hunter->dx = (diff_x / length) * speed;
    hunter->dy = (diff_y / length) * speed;

    hunter->in = false;
    return hunter;




}