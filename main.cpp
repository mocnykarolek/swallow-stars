
#include "defs.hh"   // Żeby main znał struktury (Bird, Star)
#include "actors.hh" // Żeby main mógł wywołać init_bird()
#include "io.hh"     // Żeby main mógł wywołać draw_screen()
#include "logic.hh"


int main()
{   
    GameConfig gamecfg;

    screenInitialization(&gamecfg);
    gameLoop(&gamecfg);

    deleteWindow(&gamecfg);

    // gameSpeedReader(&gamecfg);

  return 0;
}