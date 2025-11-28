#include "logic.hh"



void changeBirdDirection(){
    bird.position_y += bird.dy;
    bird.position_x += bird.dx;


}



void gameLoop(GameConfig *cfg){
    
    
    int delay = cfg->delay;
    bird.symbol = '>';
    bird.position_x = 40;
    bird.position_y = 12;


    box(cfg->win, 0, 0);
    wrefresh(cfg->win);


    int gameStart = true;

    int input;

    init_bird();


    while(gameStart){


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

            case 'q':
                gameStart = false;
                break;

            default:
                break;

        }

        updateBirdPosition(cfg);

        
        box(cfg->win, 0, 0);

        wrefresh(cfg->win);
        usleep(delay);

    }





}