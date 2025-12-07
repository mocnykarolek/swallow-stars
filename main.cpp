
#include "defs.hh"   
#include "actors.hh" 
#include "io.hh"     
#include "logic.hh"



int main()
{   

    GameConfig gamecfg;
    Bird bird;

    load_config(&gamecfg);

    screenInitialization(&gamecfg);
    gameLoop(&gamecfg, &bird);

    deleteWindow(&gamecfg);


  return 0;
}