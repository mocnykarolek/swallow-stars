#include "io.hh" 
#include "actors.hh"
#include "logic.hh"

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
    // width
    fgets(buffor, 100, fptr);
    cfg->delay = atoi(buffor);
    //height
    fgets(buffor, 100, fptr);
    cfg->width = atoi(buffor);
    //delay
    fgets(buffor, 100, fptr);
    cfg->height = atoi(buffor);
    // max stars
    fgets(buffor, 100, fptr);
    cfg->max_stars = atoi(buffor);
    // min stars
    fgets(buffor, 100, fptr);
    cfg->min_stars = atoi(buffor);
    // max opps
    fgets(buffor, 100, fptr);
    cfg->max_opps = atoi(buffor);
    // min opps
    fgets(buffor, 100, fptr);
    cfg->min_stars = atoi(buffor);


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


void drawStar(GameConfig *cfg, STARS *s){
    mvwaddch(cfg->win, s->position_y, s->position_x, s->symbol);
}

void updateStarPosition(GameConfig *cfg, STARS *s){
    mvwaddch(cfg->win, s->position_y, s->position_x, ' ');
    move_star(s);
    mvwaddch(cfg->win, s->position_y, s->position_x, s->symbol);

}


void deleteWindow(GameConfig *cfg){
    delwin(cfg->win);
    endwin();
}