#include "io.hh" 
#include "actors.hh"


void draw_bird(){

    mvwaddch(GameConfig.win, bird.position_y, bird.position_x, bird.symbol);
}


int  gameSpeedReader(){

    FILE *fptr;

    fptr = fopen("config.txt", "r");

    char buffor[100];

    fgets(buffor, 100, fptr);


    fclose(fptr);
    

    return atoi(buffor);
    
}