#include "logic.hh"



void changeBirdDirection(Bird *bird){
    bird->position_y += bird->dy;
    bird->position_x += bird->dx;


}
void updateHunterPosition(hunter* h, GameConfig *cfg){

    for (int i = 0; i <h->size.y; i++)
    {
        for (int j = 0; j < h->size.x; j++)
        {
            mvwaddch(cfg->win, h->position_y+i, h->position_x+i, ' ');
        }
        
    }
    h->position_x += h->dx;
    h->position_y += h->dy;

    drawHunter(cfg, h);
    
    
    


}

void changeHunterDirection(hunter* h){

    h->dx *= -1;
    h->dy *= -1;
}



// void detectHunterBorderCollision(hunter* h, GameConfig *cfg){

//     // if(h->position_x == cfg->width)

// }



void detectBorderColission(GameConfig *cfg, Bird *bird){

    if (bird->position_x <= 1 || bird->position_x >= cfg->width -1){
        bird->dx *=-1;
    }
    if (bird->position_y <= 1 || bird->position_y >= cfg->height-1){
        bird->dy *=-1;
    }
}


// STARS* init_star(){
//     STARS* stars[] = new STARS;
//     star->symbol = '*';
//     star->speed = 1;
//     star->position_y =1;
//     star->position_x =1;
//     star->alive = 1;

//     return star;
// }

STARS* star_array(GameConfig *cfg){
    

    STARS* stars = new STARS[cfg->max_stars];
    for (int i = 0; i < cfg->max_stars; i++)
    {
        stars[i].alive = 0;
        stars[i].symbol = '*';
    }
    

    return stars;
}

void move_star(STARS *star){

    star->position_y +=1;

}


void changeGameSpeed(gs* gamespeed, char input, int *delay){

    if (gamespeed->current_speed > 0 && input == 'o'){
        gamespeed->current_speed --;
 
    }
    if (gamespeed->current_speed < 4 && input == 'p'){
        gamespeed->current_speed ++;
 
    }
    switch(gamespeed->current_speed){
        case 0:
            *delay = gamespeed->very_slow;

            break;
        case 1:
            *delay = gamespeed->slow;
            break;
        case 2:
            *delay = gamespeed->normal;
            break;
        case 3:
            *delay = gamespeed->fast;
            break;
        case 4:
            *delay = gamespeed->very_fast;
            break;


        default:
            break;

    }


}


void birdStarCollision(Bird* bird, STARS *star, MenuCongif* menu, GameConfig* cfg){

    if(abs(bird->position_x - star->position_x) <= 1 && abs(bird->position_y-star->position_y) <=1 && star->alive == 1){
        menu->points++;
        star->alive = 0;
        mvwaddch(cfg->win, star->position_y, star->position_x, ' ');
    }
}


gs* init_gs(GameConfig *cfg){
    gs* gamespeed = new gs;
    gamespeed->normal = cfg->delay;
    gamespeed->current_speed = 2;
    gamespeed->slow = gamespeed->normal*0.9;
    gamespeed->very_slow = gamespeed->normal*0.8;
    gamespeed->fast = gamespeed->normal*1.1;
    gamespeed->very_fast = gamespeed->normal*1.2;
 
    return gamespeed;
}


void gameLoop(GameConfig *cfg, Bird *bird){
    
    int horizontalBirdspeed = (int)(cfg->width/cfg->height);
    int verticalBirdSpeed = 1;
    
    gs* gamespeed = init_gs(cfg);




    srand(time(NULL));

    int delay = gamespeed->normal;
    int *pDelay = &delay;
    bird->symbol = '>';



    box(cfg->win, 0, 0);
    wrefresh(cfg->win);


    int gameStart = true;

    int input;

    init_bird(cfg, bird);
    
    STARS* s = star_array(cfg);
    MenuCongif* menu = InitMenuconf(cfg);

    hunter* hunters = hunters_array(cfg);

    // drawMenu(cfg ,menu);
    int fps = 1000000 / cfg->delay;
    int timer = 0;

    while(gameStart){
        

        if(rand() % 4 == 0){
            for (int i = 0; i < cfg->max_opps; i++)
            {
                if(!hunters[i].alive){

                    init_hunter(&hunters[i],bird ,cfg);

                    break;

                }
                
            }
            
        }

        for (int i = 0; i < cfg->max_opps; i++)
        {
            if(hunters[i].alive){
                updateHunterPosition(&hunters[i], cfg);
            }

            if(hunters[i].bouces_left == 0)
                hunters[i].alive = false;
        }
        


        timer++;
        if (timer >= fps){
            menu->time_left --;
            timer = 0;
        }

        if (menu->time_left == 0) gameStart = false;
        




        if(rand() % 20 == 0){
            for (int i = 0; i < cfg->max_stars; i++)
            {
                if(s[i].alive == 0){
                    s[i].alive =1;
                    s[i].position_x = rand() % (cfg->width -2) +1;
                    s[i].position_y =1;
                    drawStar(cfg, &s[i]);
                    break;
                }
            }
            
        }


        for (int i = 0; i < cfg->max_stars; i++)
        {

            birdStarCollision(bird, &s[i], menu, cfg);

            if(s[i].alive == 1){
                updateStarPosition(cfg , &s[i]);
            }

        }
    
        

        

        wrefresh(cfg->win);

        input = wgetch(cfg->win);

        switch(input){
            case UP:
                bird->dx = 0;
                bird->dy = -verticalBirdSpeed;
                break;
            case DOWN:
                bird->dx = 0;
                bird->dy = verticalBirdSpeed;
                break;

            case LEFT:
                bird->dx = -horizontalBirdspeed;
                bird->dy = 0;
                break;
            case RIGHT:
                bird->dx = horizontalBirdspeed;
                bird->dy = 0;
                break;
            case FASTER:
                changeGameSpeed(gamespeed, input, pDelay);
                break;

            case SLOWER:
                changeGameSpeed(gamespeed, input, pDelay);
                break;
            

            case 'q':
                gameStart = false;
                break;

            default:
                break;

        }
        detectBorderColission(cfg, bird);

        updateBirdPosition(cfg, bird);

        
        box(cfg->win, 0, 0);


        drawMenu(menu, bird);
        wrefresh(cfg->win);
        usleep(delay);

        

        wrefresh(cfg->win);

    }

    gameover(cfg);




    delete[] s;
    delete[] menu;

}