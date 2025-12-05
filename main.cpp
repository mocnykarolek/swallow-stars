
#include "defs.hh"   
#include "actors.hh" 
#include "io.hh"     
#include "logic.hh"



// TODO: speed bound and damage rules


// TODO: rozwinac hunter template o speed



int main()
{   

    GameConfig gamecfg;
    Bird bird;

    load_config(&gamecfg);
    // return 0;
    // confReader(&gamecfg);

    screenInitialization(&gamecfg);
    gameLoop(&gamecfg, &bird);

    deleteWindow(&gamecfg);


  return 0;
}