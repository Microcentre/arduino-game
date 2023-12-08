#include "ResetArduinoOnHurt.h"

ResetArduinoOnHurt::ResetArduinoOnHurt()
{

}

void ResetArduinoOnHurt::update(Player *Player)
{
    if (Player->health == Player->GAME_OVER_HEALTH)
    {
        resetFunc();
    }
}