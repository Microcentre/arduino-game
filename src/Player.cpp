#include "Player.h" 


Player::Player(){

    //center position on display
    player_x = 170;
    player_y = 120;
}

void Player::calculate_position(uint8_t joysitck_x, uint8_t joystick_y){
        
        //5 move speeds
        uint8_t move_x;
        uint8_t move_y;

        
}

uint8_t Player::get_player_x(){
    return player_x;
}

uint8_t Player::get_player_y(){
    return player_y;
}

