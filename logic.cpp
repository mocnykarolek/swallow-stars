#include "logic.hh"



void changeBirdDirection(){
    bird.position_y += bird.dy;
    bird.position_x += bird.dx;


}




void detectBorderColission(GameConfig *cfg){

    if (bird.position_x <= 0 || bird.position_x >= cfg->width){
        bird.dx *=-1;
    }
    if (bird.position_y <= 0 || bird.position_y >= cfg->height){
        bird.dy *=-1;
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



void gameLoop(GameConfig *cfg){
    
    srand(time(NULL));
    int delay = cfg->delay;
    bird.symbol = '>';



    box(cfg->win, 0, 0);
    wrefresh(cfg->win);


    int gameStart = true;

    int input;

    init_bird(cfg);
    
    STARS* s = star_array(cfg);
    MenuCongif* menu = InitMenuconf(cfg);

    drawMenu(cfg ,menu);
    


    while(gameStart){
        
        
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
            if(s[i].alive == 1){
                updateStarPosition(cfg , &s[i]);
            }
        }
    
        

        wrefresh(cfg->win);

        input = wgetch(cfg->win);

        switch(input){
            case UP:
                bird.dx = 0;
                bird.dy = -game_speed;
                break;
            case DOWN:
                bird.dx = 0;
                bird.dy = game_speed;
                break;

            case LEFT:
                bird.dx = -game_speed;
                bird.dy = 0;
                break;
            case RIGHT:
                bird.dx = game_speed;
                bird.dy = 0;
                break;
            case FASTER:
                break;

            case SLOWER:
                break;
            

            case 'q':
                gameStart = false;
                break;

            default:
                break;

        }
        detectBorderColission(cfg);

        updateBirdPosition(cfg);

        
        box(cfg->win, 0, 0);

        wrefresh(cfg->win);
        usleep(delay);

        
        wrefresh(cfg->win);

    }





}