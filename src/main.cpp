#include "Joystick.h"
#include "Display.h"
#include "Player.h"
#include "HardwareSerial.h"
#include "util/delay.h"
#include <avr/interrupt.h>

const uint8_t SCREEN_DELAY_MS = 20;

int main(void)
{
    Joystick joystick = Joystick();
    Display display = Display();
    Player player = Player();

    // enable global interrupts
    sei();

    // used for storing and comparing previous player position (reduces display flicker)
    uint16_t prev_player_pos_x = 0;
    uint8_t prev_player_pos_y = 0;

    // endless loop
    while (1)
    {
        // store new joystick data in joystick class
        if (joystick.store_state())
        {
            // calculate new player position based on joystick movement
            player.calculate_position(joystick.get_x_axis(), joystick.get_y_axis());

            // if position of player has moved
            if (prev_player_pos_x != player.get_pos_x() || prev_player_pos_y != player.get_pos_y())
            {
                // if z is not pressed, remove previous position of player circle, else draw line by not removing dot.
                // this functionality creates a basic form of pictionary
                if (!joystick.is_z_pressed())
                {
                    display.clear_circle(prev_player_pos_x, prev_player_pos_y, PLAYER_RADIUS);
                }

                // draw player circle at current position
                display.draw_circle(player.get_pos_x(), player.get_pos_y(), PLAYER_RADIUS);

                // delay between drawing and clearing, affects speed of player
                _delay_ms(SCREEN_DELAY_MS);
            }

            // store current player position for next iteration of while loop
            prev_player_pos_x = player.get_pos_x();
            prev_player_pos_y = player.get_pos_y();
        }
    }
    return (0);
}
