#include "Joystick.h"
#include "Player.h"
#include "Display.h"
#include "MovingObject.h"
#include "HardwareSerial.h"
#include "util/delay.h"
#include <avr/interrupt.h>

// time to wait between each frame.
// to minimise redraw flicker.
// 50fps if each frame were to instantly generate.
const uint8_t SCREEN_DELAY_MS = 20;

int main()
{
    // enable global interrupts
    sei();

    Joystick joystick = Joystick();
    Display display = Display();
    Player player = Player(Display::WIDTH_PIXELS / 2, Display::HEIGHT_PIXELS / 2, 100); // start around the centre
    player.wrap_around_display = true;

    // game loop
    while (1)
    {
        // delta in seconds (time since last frame) TODO: get accurate delta?
        double delta = (double)SCREEN_DELAY_MS / 1000;

        // handle user input
        if (joystick.store_state())
        {
            player.rotate(joystick.get_x_axis());
            if (joystick.is_z_pressed())
            {
                player.accelerate();
            }
        }

        // update & draw objects
        player.update(delta);
        player.draw(display);

        _delay_ms(SCREEN_DELAY_MS);
    }
    return (0);
}
