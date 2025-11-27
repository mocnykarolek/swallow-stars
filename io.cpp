#include "io.hh" 
#include "actors.hh"


void draw_bird(GameConfig *cfg){

    mvwaddch(cfg->win, bird.position_y, bird.position_x, bird.symbol);
}


void  gameSpeedReader(GameConfig *cfg){

    FILE *fptr;

    fptr = fopen("config.txt", "r");

    char buffor[100];

    fgets(buffor, 100, fptr);
    cfg->delay = atoi(buffor);

    fgets(buffor, 100, fptr);
    cfg->width = atoi(buffor);

    fgets(buffor, 100, fptr);
    cfg->height = atoi(buffor);

    fclose(fptr);
    
    printf("%d, %d, %d", cfg->delay, cfg->width, cfg->height);
    // return atoi(buffor);
    
}


void screenInitialization(GameConfig *cfg){


    initscr();
    getmaxyx( stdscr, cfg->height, cfg->width);
    noecho();
    curs_set(0);
    
    keypad( stdscr, TRUE );
    raw();
    noecho();
    int start_y = (cfg->height - 24) / 2;
    int start_x = (cfg->width - 80) / 2;
    cfg->win = newwin(24, 80, start_y, start_x);

    if (cfg->height < 24 || cfg->width < 80){
        endwin();
        printf("Size of terminal is too small for game window initialization\n");
        return;
    }



    nodelay(cfg->win, TRUE);

    keypad(cfg->win, TRUE);



}


void deleteWindow(GameConfig *cfg){
    delwin(cfg->win);
    endwin();
}