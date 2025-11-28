#include "io.hh" 
#include "actors.hh"
#include "logic.cpp"

void draw_bird(GameConfig *cfg){

    mvwaddch(cfg->win, bird.position_y, bird.position_x, bird.symbol);
}

void updateBirdPosition(GameConfig *cfg){

    mvwaddch(cfg->win, bird.position_y, bird.position_x, ' ');
        
    changeBirdDirection();
        
    mvwaddch(cfg->win, bird.position_y, bird.position_x, bird.symbol);
}

void  confReader(GameConfig *cfg){

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
    
    printf("%d, %d, %d\n", cfg->delay, cfg->width, cfg->height);
    // return atoi(buffor);
    
}


void screenInitialization(GameConfig *cfg){

    int max_height;
    int max_width;

    initscr();
    getmaxyx( stdscr, max_height, max_width);
    printf("%d %d\n", max_height, max_width);
    noecho();
    curs_set(0);
    
    keypad( stdscr, TRUE );
    raw();
    noecho();

    int start_y = (max_height - cfg->height) / 2;
    int start_x = (max_width - cfg->width) / 2;
    cfg->win = newwin(cfg->height, cfg->width, start_y, start_x);

    if (max_height < cfg->height || max_width < cfg->width){
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