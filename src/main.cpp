#include "Joystick.h"
#include "Player.h"
#include "Display.h"
#include "MovingObject.h"
#include "Bullet.h"
#include "HardwareSerial.h"
#include "util/delay.h"
#include <avr/interrupt.h>

// time to wait between each frame.
// to minimise redraw flicker.
// 50fps if each frame were to instantly generate.
const uint8_t SCREEN_DELAY_MS = 20;
/// @brief approximate delta in seconds (time since last frame)
const double DELTA = (double)SCREEN_DELAY_MS / 1000;

int main()
{
    // enable global interrupts
    sei();

    Joystick joystick = Joystick();
    Display display = Display();
    Player player = Player(Display::WIDTH_PIXELS / 2, Display::HEIGHT_PIXELS / 2, 100); // start around the centre
    player.wrap_around_display = true;

    bool bullet_created = false;
    Bullet *bullet;

    // game loop
    while (1)
    {

        // handle user input
        if (joystick.store_state())
        {
            player.rotate(joystick.get_x_axis());
        }

        if (joystick.is_c_pressed() && !bullet_created)
        {
            bullet = new Bullet(player.get_x_position(), player.get_y_position(), player.direction);
            bullet_created = true;
        }

        // update & draw objects
        player.update(DELTA);
        player.draw(display);

        if (bullet_created)
        {
            bullet->update(DELTA);
            bullet->draw(display);
        }

        _delay_ms(SCREEN_DELAY_MS);
    }
    return (0);
}
