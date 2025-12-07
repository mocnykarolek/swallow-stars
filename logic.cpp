#include "logic.hh"



void changeBirdDirection(Bird *bird){
    bird->position_y += bird->dy;
    bird->position_x += bird->dx;


}

void updateHunterPosition(hunter* h, GameConfig *cfg){

    clearHunter(h, cfg);
    h->position_x += h->dx;
    h->position_y += h->dy;

    didHunterEnter(h, cfg);

    detectHunterBorderCollision(h, cfg);
    if (h->alive)
    drawHunter(cfg, h);
    
    
    


}




void detectHunterBorderCollision(hunter* h, GameConfig *cfg){

    if(h->in == true && h->alive == true){

        int margin = 1;


        int hit_left = (h->position_x <= margin);
        int hit_right = (h->position_x + h->size.x >= cfg->width - margin);

        if(hit_left || hit_right){
            h->dx *=-1;
            h->bouces_left --;
            if (hit_left) h->position_x = margin + 0.1f;
            if (hit_right) h->position_x = cfg->width - margin - h->size.x - 0.1f;
        }


        int hit_top  = (h->position_y <= margin);
        
        int hit_bottom = (h->position_y + h->size.y >= cfg->height - margin);

        if(hit_top || hit_bottom){
            h->dy *=-1;
            h->bouces_left--;

            if (hit_top) h->position_y = margin + 0.1f;
            if (hit_bottom) h->position_y = cfg->height - margin - h->size.y - 0.1f;

        }

        if (h->bouces_left <= 0) {
            h->alive = false;
        }
    }

}


void didHunterEnter(hunter* h, GameConfig *cfg){

    if (h->in) return;

    int margin = 2;

    bool clear_left = (h->position_x > margin);
    bool clear_top  = (h->position_y > margin);
    bool clear_right = (h->position_x + h->size.x < cfg->width - margin);
    bool clear_bottom = (h->position_y + h->size.y < cfg->height - margin);

    if(clear_left && clear_right && clear_top && clear_bottom){
        h->in = true;
    }
    
}

void detectBirdHunterCollision(Bird *b, hunter* h, GameConfig* cfg){

    if (!h->alive) return;
    int birdx = (int)b->position_x;
    int birdy = (int)b->position_y;

    int hunterx = (int)h->position_x;
    int huntery = (int)h->position_y;

    int huntermaxx = (int)(hunterx+h->size.x);
    int huntermaxy = (int)(huntery+h->size.y);

    if(birdx >= hunterx && birdx <= huntermaxx){
        if(birdy >= huntery && birdy <= huntermaxy){
            b->lives_remaining-= cfg->damage_rule;
            return;
        }
    }
    
    


}

void detectBorderColission(GameConfig *cfg, Bird *bird){

    if (bird->position_x <= 1){
        bird->dx *=-1;
        bird->position_x =1;
    }
    if(bird->position_x >= cfg->width -1){
        bird->dx *=-1;
        bird->position_x = cfg->width -1;
    }



    if (bird->position_y <= 1){
        bird->dy *=-1;
        bird->position_y = 1;
    }
    if(bird->position_y >= cfg->height-1){
        bird->dy *=-1;
        bird->position_y = cfg->height-1;
    }
}



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

    star->position_y +=1*star->speed;

}


void changeGameSpeed(gs* gamespeed, char input, int *delay){

    if (gamespeed->current_speed > 0 && input == 'p'){
        gamespeed->current_speed --;
 
    }
    if (gamespeed->current_speed < 4 && input == 'o'){
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

void starOutsideBorder(STARS* star, GameConfig *cfg){

    if(star->position_y > cfg->height)
        star->alive = false;

}



void birdStarCollision(Bird* bird, STARS *star, MenuCongif* menu, GameConfig* cfg){

    if(abs(bird->position_x - star->position_x) <= 1 && abs(bird->position_y-star->position_y) <=1 && star->alive == 1){
        menu->points += 1*cfg->scoringw;
        star->alive = 0;
        mvwaddch(cfg->win, star->position_y, star->position_x, ' ');
    }
}


gs* init_gs(GameConfig *cfg){
    gs* gamespeed = new gs;
    gamespeed->normal = cfg->delay;
    gamespeed->current_speed = 2;
    gamespeed->slow = gamespeed->normal* (1 - cfg->speed_bound);
    gamespeed->very_slow = gamespeed->normal* (1 - 2* cfg->speed_bound);
    gamespeed->fast = gamespeed->normal*(1 + cfg->speed_bound);
    gamespeed->very_fast = gamespeed->normal*(1 + 2*cfg->speed_bound);
 
    return gamespeed;
}

void nextLevel(GameConfig *cfg, Bird *bird, STARS *stars, hunter *hunters, MenuCongif *menu, Levels* l, int*lnum) {
    
    cfg->level ++;
    if(cfg->level< *lnum){
    cfg->max_opps = l[cfg->level-1].max_opps;
    cfg->max_stars = l[cfg->level-1].max_stars;
    cfg->time = l[cfg->level-1].time_limit;
    cfg->max_bounces = l[cfg->level-1].max_bounces;
    cfg->scoringw = l[cfg->level-1].scoring_weights;
    }

    init_bird(cfg, bird);

    for (int i = 0; i < cfg->max_stars; i++)
    {
        stars[i].alive = false;
        mvwaddch(cfg->win, stars[i].position_y, stars[i].position_x, ' ');
    }
    for (int i = 0; i < cfg->max_opps; i++)
    {
        hunters[i].alive = false;
        clearHunter(&hunters[i], cfg);

    }
    
    menu->time_left = cfg->time;

    werase(cfg->win);
    drawBox(cfg);
    mvwprintw(cfg->win, cfg->height/2, cfg->width/2 - 5, "LEVEL %d", cfg->level);
    wrefresh(cfg->win);
    sleep(2);
    mvwaddstr(cfg->win, cfg->height/2, cfg->width/2 - 5, "        ");

}

void HandleUserInput(GameConfig *cfg, Bird *bird, int *gameStart, int *input,gs* gamespeed,int *delay ){
    int horizontalBirdspeed = (int)(cfg->width/cfg->height);
    int verticalBirdSpeed = 1;
    int *pDelay = delay;
    *input = wgetch(cfg->win);
        switch(*input){
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
                changeGameSpeed(gamespeed, *input, pDelay);
                break;

            case SLOWER:
                changeGameSpeed(gamespeed, *input, pDelay);
                break;
            

            case 'q':
                *gameStart = false;
                break;

            default:
                break;

        }


}

void gameTimer(int *fps, int* timer, MenuCongif* menu){
    (*timer)++;
    if (*timer >= *fps){
        menu->time_left --;
        *timer = 0;
    }

}

void hunterBehaviour(GameConfig *cfg, hunter *hunters, Bird* bird, h_size* templates, int*count){
    if(rand() % 25 == 0){
            for (int i = 0; i < cfg->max_opps; i++)
            {
                if(!hunters[i].alive){

                    init_hunter(&hunters[i],bird ,cfg, templates, count);

                    break;

                }
                
            }
            
        }

        for (int i = 0; i < cfg->max_opps; i++)
        {
            if(hunters[i].alive){
                
                updateHunterPosition(&hunters[i], cfg);
                detectBirdHunterCollision(bird, &hunters[i], cfg);
            }

            if(hunters[i].bouces_left == 0)
                hunters[i].alive = false;

        }

}

void starBehaviour(GameConfig *cfg, Bird* bird, STARS* s, MenuCongif* menu){

            if(rand() % 20 == 0){
            for (int i = 0; i < cfg->max_stars; i++)
            {
                if(s[i].alive == 0){
                    s[i].alive =1;
                    s[i].position_x = rand() % (cfg->width -2) +1;
                    s[i].position_y =1;
                    s[i].speed = (rand() % 2) +1;
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

            starOutsideBorder(&s[i], cfg);

        }

}

void firstLevelInits(GameConfig *cfg, Levels* levels){

    cfg->max_opps = levels[0].max_opps;
    cfg->max_stars = levels[0].max_stars;
    cfg->time = levels[0].time_limit;
    cfg->max_bounces = levels[0].max_bounces;
    cfg->scoringw = levels[0].scoring_weights;


}


void deallocate(Levels* levels, gs* gamespeed,h_size* templates, hunter* hunters, STARS* s, MenuCongif* menu){
    delete[] levels;
    delete gamespeed;
    delete[] templates;
    delete[] hunters;
    delete[] s;
    delete menu;


}



void mainLoop(GameConfig* cfg, Bird* bird, Levels* levels, gs* gamespeed, h_size* templates, hunter* hunters, STARS* s, MenuCongif* menu, 
              int* tcount, int* levels_num, int* gameStart, int* input, int* delay, int* fps, int* timer){
    while(*gameStart){
        
        hunterBehaviour(cfg, hunters, bird, templates, tcount);

        starBehaviour(cfg, bird, s, menu);
        
        if(bird->lives_remaining ==0) break;
        
        wrefresh(cfg->win);
        
        HandleUserInput(cfg, bird, gameStart, input, gamespeed, delay);

        gameTimer(fps, timer, menu);

        if (cfg->goal - menu->points <= 0){
            menu->points = 0;
            nextLevel(cfg, bird, s, hunters, menu, levels, levels_num);
            

        }
        if (bird->lives_remaining <= 0 || menu->time_left <=0) break;

        detectBorderColission(cfg, bird);

        updateBirdPosition(cfg, bird);

        drawBox(cfg);

        drawMenu(menu, bird, cfg);

        wrefresh(cfg->win);

        usleep(*delay);

        wrefresh(cfg->win);


    }
}


void gameLoop(GameConfig *cfg, Bird *bird){
    
    
    
    gs* gamespeed = init_gs(cfg);
    
    srand(time(NULL));

    int delay = gamespeed->normal;
    int *pDelay = &delay;


    box(cfg->win, 0, 0);
    wrefresh(cfg->win);
    int tcount;
    int levels_num;
    Levels * levels = loadLevels(&levels_num);
    h_size* templates = hunterTemplates(&tcount);
    
    firstLevelInits(cfg, levels);

    int gameStart = true;
    flushinp();
    int input;

    init_bird(cfg, bird);
    
    STARS* s = star_array(cfg);
    MenuCongif* menu = InitMenuconf(cfg);
    
    hunter* hunters = hunters_array(cfg);


    int fps = 1000000 / cfg->delay;
    int timer = 0;

    mainLoop(cfg, bird, levels, gamespeed, templates, hunters, s, menu, &tcount, &levels_num,&gameStart, &input, &delay, &fps, &timer);

    gameover(cfg);
    deallocate(levels, gamespeed, templates, hunters, s, menu);

}