
#include "defs.hh"   
#include "actors.hh" 
#include "io.hh"     
#include "logic.hh"
// TODO: spowolnic gwiazki
// TODO: dodac kolizje z ptakiem i niszczyc gwizdki
// TODO: dodac przeciwnikow
// TODO: dodac kolory
// TODO: dodac moliwosc zmiany predkosci gry




int main()
{   
    GameConfig gamecfg;
    Bird bird;
    confReader(&gamecfg);

    screenInitialization(&gamecfg);
    gameLoop(&gamecfg, &bird);

    deleteWindow(&gamecfg);


  return 0;
}