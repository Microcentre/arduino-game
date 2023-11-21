#include "Joystick.h"
#include "Display.h"
#include "Player.h"
#include "HardwareSerial.h"
#include "util/delay.h"

const uint8_t SCREEN_DELAY_MS = 20;

int main(void) {
	Joystick joystick = Joystick();

    Display display = Display();

    Player player = Player();

	// endless loop
	while(1) {
		if(joystick.store_state()){

            player.calculate_position(joystick.get_x(),joystick.get_y());
            
            display.draw_circle(player.get_player_x(), player.get_player_y(),PLAYER_RADIUS);            

            _delay_ms(SCREEN_DELAY_MS);

            //if z is not pressed, remove dot, else draw line by not removing dot.
            if(!joystick.get_z()){
                display.clear_circle(player.get_player_x(), player.get_player_y(),PLAYER_RADIUS);
            }        
        }
	}
	return(0);
}

