/*
TODO:
1. jaskolka porusza sie po ekranie ze stala predkoscia i ma moliwosc zmieniania kierunku ruchu


*/
#include <ncurses.h>
#include <unistd.h> 
#include <stdio.h>
#include <string.h> 

#include <cstdio> 
#include <cstdlib>
#define QUIT 'q'

#define UP 'w'
#define RIGHT 'd'
#define DOWN 's'
#define LEFT 'a'

struct {
    int width;
    int height;

} mainWindow;

struct {
    int position_x;
    int position_y;
    int dx, dy;
    char symbol;
} bird;



int  gameSpeedReader(){

    FILE *fptr;

    fptr = fopen("config.txt", "r");

    char buffor[100];

    fgets(buffor, 100, fptr);



    fclose(fptr);
    


    // printf("%s", buffor);


    
    
    return atoi(buffor);
    
}






void gameLoop(){
    int main_delay = 100000;

    initscr();
    getmaxyx( stdscr, mainWindow.height, mainWindow.width);
    noecho();
    curs_set(0);
    
    keypad( stdscr, TRUE );
    raw();
    noecho();
    int start_y = (mainWindow.height - 24) / 2;
    int start_x = (mainWindow.width - 80) / 2;
    WINDOW *win = newwin(24, 80, start_y, start_x);

    if (mainWindow.height < 24 || mainWindow.width < 80){
        endwin();
        printf("Size of terminal is too small for game window initialization\n");
        return;
    }



    nodelay(win, TRUE);

    keypad(win, TRUE);


    int game_speed = 1;
    double delay_temp = (gameSpeedReader()/100)*main_delay;
    int delay = (int)delay_temp;
    bird.symbol = '*';
    bird.position_x = 40;
    bird.position_y = 12;

        

    
    box(win, 0, 0);
    wrefresh(win);


    int gameStart = true;

    int input;
    while(gameStart){
        mvwaddch(win, bird.position_y, bird.position_x, bird.symbol);
        


        wrefresh(win);

        input = wgetch(win);

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
        mvwaddch(win, bird.position_y, bird.position_x, ' ');
        
        bird.position_y += bird.dy;
        bird.position_x += bird.dx;
        mvwaddch(win, bird.position_y, bird.position_x, bird.symbol);
        
        box(win, 0, 0);

        wrefresh(win);
        usleep(delay);
    }


    delwin(win);
    endwin();


}

int main()
{   

    gameLoop();



  return 0;
}