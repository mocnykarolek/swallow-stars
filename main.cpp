/*
TODO:
1. jaskolka porusza sie po ekranie ze stala predkoscia i ma moliwosc zmieniania kierunku ruchu


*/
#include "defs.hh"   // Żeby main znał struktury (Bird, Star)
#include "actors.hh" // Żeby main mógł wywołać init_bird()
#include "io.hh"     // Żeby main mógł wywołać draw_screen()
#include "logic.hh"






void gameLoop(){
    
    
    int delay = gamecfg.delay;
    bird.symbol = '>';
    bird.position_x = 40;
    bird.position_y = 12;


    box(gamecfg.win, 0, 0);
    wrefresh(gamecfg.win);


    int gameStart = true;

    int input;
    while(gameStart){



        init_bird();
        


        wrefresh(gamecfg.win);

        input = wgetch(gamecfg.win);

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
        mvwaddch(gamecfg.win, bird.position_y, bird.position_x, ' ');
        
        bird.position_y += bird.dy;
        bird.position_x += bird.dx;
        mvwaddch(gamecfg.win, bird.position_y, bird.position_x, bird.symbol);
        
        box(gamecfg.win, 0, 0);

        wrefresh(gamecfg.win);
        usleep(delay);

    }





}


void screenInitialization(){
    gamecfg.delay = 100000;

    int congif_delay = gameSpeedReader();


    initscr();
    getmaxyx( stdscr, mainWindow.height, mainWindow.width);
    noecho();
    curs_set(0);
    
    keypad( stdscr, TRUE );
    raw();
    noecho();
    int start_y = (mainWindow.height - 24) / 2;
    int start_x = (mainWindow.width - 80) / 2;
    gamecfg.win = newwin(24, 80, start_y, start_x);

    if (mainWindow.height < 24 || mainWindow.width < 80){
        endwin();
        printf("Size of terminal is too small for game window initialization\n");
        return;
    }



    nodelay(gamecfg.win, TRUE);

    keypad(gamecfg.win, TRUE);



}


int main()
{   
    GameConfig gamecfg;
    screenInitialization();
    gameLoop();

    delwin(gamecfg.win);
    endwin();

  return 0;
}