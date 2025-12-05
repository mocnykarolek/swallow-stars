#include "io.hh" 
#include "actors.hh"
#include "logic.hh"

void draw_bird(GameConfig *cfg, Bird *bird){
    switch(bird->lives_remaining){
        case 5:
            wattron(cfg->win, COLOR_PAIR(3));
            mvwaddch(cfg->win, bird->position_y, bird->position_x, bird->symbol);
            wattroff(cfg->win, COLOR_PAIR(3));
            break;
        case 4:
            wattron(cfg->win, COLOR_PAIR(5));
            mvwaddch(cfg->win, bird->position_y, bird->position_x, bird->symbol);
            wattroff(cfg->win, COLOR_PAIR(5));
            break;
        case 3:
            wattron(cfg->win, COLOR_PAIR(6));
            mvwaddch(cfg->win, bird->position_y, bird->position_x, bird->symbol);
            wattroff(cfg->win, COLOR_PAIR(6));
            break;
        case 2:
            wattron(cfg->win, COLOR_PAIR(2));
            mvwaddch(cfg->win, bird->position_y, bird->position_x, bird->symbol);
            wattroff(cfg->win, COLOR_PAIR(2));
            break;
        case 1:
            wattron(cfg->win, COLOR_PAIR(1));
            mvwaddch(cfg->win, bird->position_y, bird->position_x, bird->symbol);
            wattroff(cfg->win, COLOR_PAIR(1));
            break;

        default:
            mvwaddch(cfg->win, bird->position_y, bird->position_x, bird->symbol);
            break;
    }

    
}

void clearHunter(hunter* h, GameConfig *cfg){

    for (int i = 0; i <h->size.x; i++)
    {
        for (int j = 0; j < h->size.y; j++)
        {
            mvwaddch(cfg->win, h->position_y+j, h->position_x+i, ' ');
        }
        
    }
}

void drawHunter(GameConfig *cfg, hunter* h){
    for (int i = 0; i <h->size.x; i++)
    {
        for (int j = 0; j < h->size.y; j++)
        {
            switch(h->type)
            {
                case 1:
                    wattron(cfg->win, COLOR_PAIR(1) | A_BOLD);
                    mvwaddch(cfg->win, h->position_y+j, h->position_x+i, h->symbol);
                    wattroff(cfg->win, COLOR_PAIR(1) | A_BOLD);
                    break;
                case 2:
                    wattron(cfg->win, COLOR_PAIR(6) | A_BOLD);
                    mvwaddch(cfg->win, h->position_y+j, h->position_x+i, h->symbol);
                    wattroff(cfg->win, COLOR_PAIR(6) | A_BOLD);
                    break;
                case 3:
                    wattron(cfg->win, COLOR_PAIR(5) | A_BOLD);
                    mvwaddch(cfg->win, h->position_y+j, h->position_x+i, h->symbol);
                    wattroff(cfg->win, COLOR_PAIR(5) | A_BOLD);
                    break;
                default:
                    mvwaddch(cfg->win, h->position_y+j, h->position_x+i, h->symbol);
                    break;

            }
            
        }
        
    }
    

}




void updateBirdPosition(GameConfig *cfg, Bird *bird){

    mvwaddch(cfg->win, bird->position_y, bird->position_x, ' ');
        
    changeBirdDirection(bird);
    draw_bird(cfg, bird);
        
    // mvwaddch(cfg->win, bird->position_y, bird->position_x, bird->symbol);
}

void  confReader(GameConfig *cfg){

    FILE *fptr;

    fptr = fopen("config.txt", "r");

    char buffor[100];
    fgets(buffor, 100, fptr);
    int parameters = atoi(buffor);

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
    // max opps
    fgets(buffor, 100, fptr);
    cfg->max_opps = atoi(buffor);
    // time left
    fgets(buffor, 100, fptr);
    cfg->time = atoi(buffor);
    // level
    fgets(buffor, 100, fptr);
    cfg->level = atoi(buffor);
    



    fclose(fptr);
    
    printf("%d, %d, %d\n", cfg->delay, cfg->width, cfg->height);
    // return atoi(buffor);
    
}


void screenInitialization(GameConfig *cfg){

    int max_height;
    int max_width;

    initscr();
    start_color();
    getmaxyx( stdscr, max_height, max_width);
    printf("%d %d\n", max_height, max_width);
    noecho();
    curs_set(0);
    init_pair(1, COLOR_RED, COLOR_BLACK);   
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    
    keypad( stdscr, TRUE );
    raw();
    noecho();

    int start_y = ((max_height - cfg->height) / 2) - 10;
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
    wattron(cfg->win, COLOR_PAIR(2));
    mvwaddch(cfg->win, s->position_y, s->position_x, s->symbol);
    wattroff(cfg->win, COLOR_PAIR(2));

}

void updateStarPosition(GameConfig *cfg, STARS *s){
    mvwaddch(cfg->win, s->position_y, s->position_x, ' ');
    move_star(s);
    wattron(cfg->win, COLOR_PAIR(2));
    mvwaddch(cfg->win, s->position_y, s->position_x, s->symbol);
    wattroff(cfg->win, COLOR_PAIR(2));
}

void drawMenu(MenuCongif* menu, Bird *bird){
    
    werase(menu->menu_win);
    wattron(menu->menu_win, COLOR_PAIR(4));
    box(menu->menu_win, 0,0);
    wattroff(menu->menu_win, COLOR_PAIR(4));
    mvwprintw(menu->menu_win, 2, 1, "TIME: %d DIRECTIONS [W,A,S,D] CHANGE SPEED [o/p] EXIT [q] POINTS: %d LIVES: %d",menu->time_left, menu->points, bird->lives_remaining);

    wrefresh(menu->menu_win);
}

void gameover(GameConfig *cfg){
    
    nodelay(cfg->win, FALSE);
    mvwprintw(cfg->win, cfg->height/2, (cfg->width/2) - 4, "GAMEOVER");
    char input;
    do{
        input = wgetch(cfg->win);
    } while(input != 'q');
}
void drawBox(GameConfig *cfg){
    wattron(cfg->win, COLOR_PAIR(4));
    box(cfg->win, 0, 0);
    wattroff(cfg->win, COLOR_PAIR(4));
}

MenuCongif* InitMenuconf(GameConfig *cfg){

    MenuCongif* menu = new MenuCongif;
    
    menu->height = 5;
    menu->width = cfg->width;
    menu->points = 0;
    menu->time_left = cfg->time;


    int main_x;
    int main_y;
    getbegyx(cfg->win, main_y, main_x);

    int menu_y = main_y + cfg->height;
    int menu_x = main_x;



    menu->menu_win = newwin(menu->height, menu->width, menu_y, menu_x);

    return menu;
}


void deleteWindow(GameConfig *cfg){
    delwin(cfg->win);
    endwin();
}