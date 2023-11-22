#include "Joystick.h"
#include "Display.h"
#include "Player.h"
#include "HardwareSerial.h"
#include "util/delay.h"

const uint8_t SCREEN_DELAY_MS = 20;

int main(void)
{
    Joystick joystick = Joystick();

    Display display = Display();

    Player player = Player();

    //used for storing and comparing previous player position (reduces display flicker)
    uint16_t prev_x = 0;
    uint8_t prev_y = 0;

    // endless loop
    while (1)
    {
        // store new joystick data in joystick class
        if (joystick.store_state())
        {
            // calculate new player position based on joystick movement
            player.calculate_position(joystick.get_x(), joystick.get_y());

            // if position of player has moved
            if (prev_x != player.get_player_x() || prev_y != player.get_player_y())
            {
                // if z is not pressed, remove previous position of player circle, else draw line by not removing dot.
                // this functionality creates a basic form of pictionary
                if (!joystick.get_z())
                {
                    display.clear_circle(prev_x, prev_y, PLAYER_RADIUS);
                }

                // draw player circle at current position
                display.draw_circle(player.get_player_x(), player.get_player_y(), PLAYER_RADIUS);

                // delay between drawing and clearing, affects speed of player
                _delay_ms(SCREEN_DELAY_MS);
            }

            // store current player position for next iteration of while loop
            prev_x = player.get_player_x();
            prev_y = player.get_player_y();
        }
    }
    return (0);
}
