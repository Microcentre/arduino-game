#include "Health.h"

Health::Health()
{
    show();
}

void Health::show()
{

}

void Health::adjust()
{
    health--;
    if (health == GAME_OVER_HEALTH)
    {
        resetFunc();
    }
    show();
}