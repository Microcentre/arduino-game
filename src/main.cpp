#include "Joystick.h"

int main(void) {

	Joystick joystick = Joystick();

	// endless loop
	while(1) {
		joystick.show_info();
	}
	return(0);
}
