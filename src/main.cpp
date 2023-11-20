#include "Joystick.h"
#include "display.h"
#include "HardwareSerial.h"
#include "util/delay.h"

int main(void) {

    Serial.begin(9600);

	Joystick joystick = Joystick();

    Display display = Display();

	// endless loop
	while(1) {
		if(joystick.store_state()){
            uint8_t x = joystick.getX();
            uint8_t y = joystick.getY();
            display.DrawCircle(x,y);
            _delay_ms(50);
            display.ClearCircle(x,y);
        }
	}
	return(0);
}

