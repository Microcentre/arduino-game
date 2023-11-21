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

            Serial.println("---");
            Serial.println(joystick.get_x());
            Serial.println(joystick.get_y());
            Serial.println("---");

            player.calculate_position(joystick.get_x(),joystick.get_y());
            
            display.draw_circle(player.get_player_x(), player.get_player_y(),PLAYER_RADIUS);            

            _delay_ms(20);

            if(!joystick.get_z()){
                display.clear_circle(player.get_player_x(), player.get_player_y(),PLAYER_RADIUS);
            }        
        }
	}
	return(0);
}

