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
            
            switch((h->type % 3) +1)
            {
                case 1:
                    if(i==0 && j ==0){
                        wattron(cfg->win, COLOR_PAIR(1) | A_BOLD);
                        mvwaddch(cfg->win, h->position_y+j, h->position_x+i, h->bouces_left + '0');
                        wattroff(cfg->win, COLOR_PAIR(1) | A_BOLD);
                    } else {
                    wattron(cfg->win, COLOR_PAIR(1) | A_BOLD);
                    mvwaddch(cfg->win, h->position_y+j, h->position_x+i, h->symbol);
                    wattroff(cfg->win, COLOR_PAIR(1) | A_BOLD);
                    }
                    break;
                case 2:
                    if(i==0 && j ==0){
                        wattron(cfg->win, COLOR_PAIR(6) | A_BOLD);
                        mvwaddch(cfg->win, h->position_y+j, h->position_x+i, h->bouces_left + '0');
                        wattroff(cfg->win, COLOR_PAIR(6) | A_BOLD); 
                    } else {
                    wattron(cfg->win, COLOR_PAIR(6) | A_BOLD);
                    mvwaddch(cfg->win, h->position_y+j, h->position_x+i, h->symbol);
                    wattroff(cfg->win, COLOR_PAIR(6) | A_BOLD);
                    }
                    break;
                case 3:
                    if(i==0 && j ==0){
                        wattron(cfg->win, COLOR_PAIR(5) | A_BOLD);
                        mvwaddch(cfg->win, h->position_y+j, h->position_x+i, h->bouces_left + '0');
                        wattroff(cfg->win, COLOR_PAIR(5) | A_BOLD);

                    } else {
                    wattron(cfg->win, COLOR_PAIR(5) | A_BOLD);
                    mvwaddch(cfg->win, h->position_y+j, h->position_x+i, h->symbol);
                    wattroff(cfg->win, COLOR_PAIR(5) | A_BOLD);
                    }
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

void drawMenu(MenuCongif* menu, Bird *bird, GameConfig *cfg){
    
    werase(menu->menu_win);
    wattron(menu->menu_win, COLOR_PAIR(4));
    box(menu->menu_win, 0,0);
    wattroff(menu->menu_win, COLOR_PAIR(4));
    // mvwprintw(menu->menu_win, 2, 1, "TIME: %d DIRECTIONS [W,A,S,D] CHANGE SPEED [o/p] EXIT [q] POINTS: %d LIVES: %d",menu->time_left, menu->points, bird->lives_remaining);
    mvwprintw(menu->menu_win, 2, 5, "PLAYER: %s TIME: %d POINTS: %d GOAL: %d LIVES: %d LEVEL: %d",cfg->name ,menu->time_left, menu->points,cfg->goal, bird->lives_remaining, cfg->level);
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

h_size* hunterTemplates(int *count)
{
    FILE *fptr;

    fptr = fopen("huntertemplates.txt", "r");
    char buff[100];
    int ht_ammount = 0;

    fscanf(fptr, "%s", buff);
    if (strcmp(buff, "TEMPLATES") == 0)
        fscanf(fptr, "%d", &ht_ammount);

    h_size* templates = new h_size[ht_ammount];
    for (int i = 0; i < ht_ammount; i++)
    {
        fscanf(fptr, "%d", &templates[i].x);
        fscanf(fptr, "%d", &templates[i].y);
    }
    
    fclose(fptr);
    *count = ht_ammount;

    return templates;

}

void load_config(GameConfig *cfg){
    FILE *fptr;

    fptr = fopen("config.txt", "r");





    char buff[100];
    

    while(fscanf(fptr, "%s", buff) != EOF){

        if(strcmp(buff, "DELAY") == 0){
            fscanf(fptr, "%d", &cfg->delay);
        }
        else if(strcmp(buff, "WIDTH") == 0)
        {
            fscanf(fptr, "%d", &cfg->width);
        }
        else if(strcmp(buff, "HEIGHT") == 0)
        {
            fscanf(fptr, "%d", &cfg->height);
        }
        else if(strcmp(buff, "MAX_STARS") == 0)
        {
            fscanf(fptr, "%d", &cfg->max_stars);
        }
        else if(strcmp(buff, "MAX_OPPS") == 0)
        {
            fscanf(fptr, "%d", &cfg->max_opps);
        }
        else if(strcmp(buff, "TIME_LEFT") == 0)
        {
            fscanf(fptr, "%d", &cfg->time);
        }
        else if(strcmp(buff, "LEVEL") == 0)
        {
            fscanf(fptr, "%d", &cfg->level);
        }
        else if(strcmp(buff, "NAME") == 0)
        {
            fscanf(fptr, "%s", &cfg->name);
        }
        else if(strcmp(buff, "GOAL") == 0)
        {
            fscanf(fptr, "%d", &cfg->goal);
        }
        else if(strcmp(buff, "DAMAGE") == 0)
        {
            fscanf(fptr, "%d", &cfg->damage_rule);
        }
        else if(strcmp(buff, "SBOUNDS") == 0)
        {
            fscanf(fptr, "%f", &cfg->speed_bound);
        }

    }

 





    fclose(fptr);

}
Levels* loadLevels(int* count) { // count to wskaźnik, żeby zwrócić rozmiar
    FILE *fptr = fopen("levels.txt", "r");
    
    // BHP: Sprawdź czy plik istnieje
    if (fptr == NULL) {
        *count = 0;
        return NULL;
    }

    char buff[100];
    *count = 0; // Poprawnie: zerujemy WARTOŚĆ pod wskaźnikiem

    // 1. Wczytaj liczbę poziomów
    fscanf(fptr, "%s", buff); // Czyta "LEVELSNUM"
    if (strcmp(buff, "LEVELSNUM") == 0) {
        fscanf(fptr, "%d", count); // Poprawnie: podajemy wskaźnik (bez &)
    }

    // 2. Alokacja
    Levels* levels = new Levels[*count];

    // 3. Pętla wczytująca
    // Plik ma strukturę powtarzalną: LEVEL x, STARS x, TIME x...
    // Czytamy to sekwencyjnie dla każdego poziomu
    for (int i = 0; i < *count; i++) {
        // Czytamy kolejne pary KLUCZ WARTOŚĆ
        // Zakładamy, że w pliku zawsze jest komplet 6 parametrów na poziom
        
        // LEVEL
        fscanf(fptr, "%s", buff); // Czyta "LEVEL"
        fscanf(fptr, "%d", &levels[i].level); // Czyta numer (np. 1)

        // STARS
        fscanf(fptr, "%s", buff); 
        fscanf(fptr, "%d", &levels[i].max_stars);

        // TIME
        fscanf(fptr, "%s", buff); 
        fscanf(fptr, "%d", &levels[i].time_limit);

        // OPPS
        fscanf(fptr, "%s", buff); 
        fscanf(fptr, "%d", &levels[i].max_opps);

        // MAXBOUNCES
        fscanf(fptr, "%s", buff); 
        fscanf(fptr, "%d", &levels[i].max_bounces);

        // SCORINGW
        fscanf(fptr, "%s", buff); 
        fscanf(fptr, "%d", &levels[i].scoring_weights);
    }

    fclose(fptr);
    return levels;
}
