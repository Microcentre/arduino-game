#ifndef IR_H
#define IR_H

#include <avr/io.h>

#include "Joystick.h"


const uint16_t CARRIER_FREQUENCY = 38000;

const uint8_t DATA_SIZE = 10;
const uint8_t MESSAGE_SIZE = DATA_SIZE + 3; // data + start bit, parity bit, stop bit
const uint8_t PARITY_MASK = 0x02;
const uint16_t DATA_MASK = 0b0111111111100;
const uint8_t START_BIT = 1;
const uint8_t STOP_BIT = 1;

const uint8_t BLINK_DURATION = 211;    // 16000000/38000 = 421/2 = 211
const uint16_t PULSE_DURATION = 9000;  //  562.5µs
const uint16_t ZERO_DURATION = 9000;   //  562.5µs
const uint16_t ONE_DURATION = 27000;   // 1.6875ms
const uint16_t START_DURATION = 54000; // 3.3750ms

const uint16_t SIGNAL_DEVIATION = 2000;

const uint8_t DATA_ARRAY_SIZE = 5;

const uint16_t JOY_MASK_X_AXIS = 0b0011111111;
const uint16_t JOY_MASK_Z_BUTTON = 0b1000000000;
const uint16_t JOY_MASK_C_BUTTON = 0b0100000000;

class IR
{
public:
    enum Flags
    {
        // sending (bit 3 reserved)
        SENDING_MESSAGE = 0b00000001,
        SENDING_START = 0b00000010,
        MESSAGE_PENDING = 0b00000100,

        // receiving
        MESSAGE_RECEIVED = 0b00010000,
        MESSAGE_STARTED = 0b00100000,
    };

    enum DataIndex
    {
        PLAYER_X = 0,
        PLAYER_Y = 1,
        PLAYER_FACING_DIR = 2,
        EVT0 = 3, // event (like bullet-hits-asteroid etc)
        EVT1 = 4
    };

    IR();
    void start_blinking();
    void stop_blinking();
    void start_signal_timer();
    void stop_signal_timer();

    uint16_t get_output_buffer();
    void shift_output_buffer();

    uint8_t get_input_buffer();
    void set_input_buffer(uint8_t);
    void push_input_buffer(uint8_t);

    uint16_t get_timer_start();
    void set_timer_start(uint16_t);

    uint8_t get_received_bits();
    void set_received_bits(uint8_t);
    void inc_received_bits();

    void read_bit();
    void send_bit(uint8_t);

    void read_data();
    void send_joystick(Joystick*);
    void send_data(uint8_t, uint16_t);
    uint16_t interpret_data(uint8_t);
    uint16_t reverse_data(uint16_t);

    uint8_t get_flags();
    void set_flag(uint8_t);
    void clear_flag(uint8_t);

    uint16_t get_received_data(uint8_t);
    void set_received_data(uint8_t, uint16_t);

    void queue_next_message();
    void write_data_to_buffer();

private:
    uint16_t input_buffer;
    uint16_t output_buffer;
    uint16_t timer_start;
    uint8_t received_bits;
    volatile uint8_t flags;
    uint16_t received_data[1];
    uint16_t data_to_send[1];
    uint8_t current_send_index;
    uint8_t current_read_index;
};

#endif