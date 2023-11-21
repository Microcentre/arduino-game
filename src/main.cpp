#include "Joystick.h"
#include "Display.h"
#include "Player.h"
#include "HardwareSerial.h"
#include "util/delay.h"

int main(void) {

    Serial.begin(9600);

	Joystick joystick = Joystick();

    Display display = Display();

    Player player = Player();

	// endless loop
	while(1) {
		if(joystick.store_state()){

            player.calculate_position(joystick.get_x(),joystick.get_y());

            display.draw_circle(player.get_player_x(), player.get_player_y());

            _delay_ms(20);

            display.clear_circle(player.get_player_x(), player.get_player_y());
        }
	}
	return(0);
}

