
#include "defs.hh"   // Żeby main znał struktury (Bird, Star)
#include "actors.hh" // Żeby main mógł wywołać init_bird()
#include "io.hh"     // Żeby main mógł wywołać draw_screen()
#include "logic.hh"
// TODO: spowolnic gwiazki
// TODO: dodac kolizje z ptakiem i niszczyc gwizdki
// TODO: dodac przeciwnikow
// TODO: dodac kolory
// TODO: dodac moliwosc zmiany predkosci gry




int main()
{   
    GameConfig gamecfg;
    confReader(&gamecfg);

    screenInitialization(&gamecfg);
    gameLoop(&gamecfg);

    deleteWindow(&gamecfg);


  return 0;
}