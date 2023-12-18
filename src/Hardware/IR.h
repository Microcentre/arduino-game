#ifndef IR_H
#define IR_H
#include <avr/io.h>

const uint16_t CARRIER_FREQUENCY = 38000;

const uint8_t DATA_SIZE = 29;
const uint8_t MESSAGE_SIZE = DATA_SIZE + 3;
const uint8_t DATA_POS_X_SIZE = 9;
const uint8_t DATA_POS_Y_SIZE = 8;
const uint8_t DATA_DIR_SIZE = 9;
const uint8_t DATA_FLAGS_SIZE = 3;

const uint8_t PARITY_MASK = 0x02;
const uint32_t RECEIVE_DATA_MASK = 0b01111111111111111111111111111100;
const uint32_t DATA_POS_X_MASK = 0b00011111111100000000000000000000;
const uint32_t DATA_POS_Y_MASK = 0b00000000000011111111000000000000;
const uint32_t DATA_DIR_MASK = 0b00000000000000000000111111111000;

const uint8_t START_BIT = 1;
const uint8_t STOP_BIT = 1;

const uint8_t BLINK_DURATION = 211;    // 16000000/38000 = 421/2 = 211
const uint16_t PULSE_DURATION = 9000;  //  562.5µs
const uint16_t ZERO_DURATION = 9000;   //  562.5µs
const uint16_t ONE_DURATION = 27000;   // 1.6875ms
const uint16_t START_DURATION = 54000; // 3.3750ms

const uint16_t SIGNAL_DEVIATION = 2000;

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
    void send_data(uint32_t);
    void send_player_data(uint16_t, uint8_t, uint16_t, uint8_t);
    void interpret_data();

    uint32_t reverse_data(uint32_t);

    uint8_t get_flags();
    void set_flag(uint8_t);
    void clear_flag(uint8_t);

    void set_received_message_to_input_buffer();

    uint32_t get_received_data();
    void set_received_data(uint32_t);

private:
    uint32_t input_buffer;
    uint32_t output_buffer;
    uint16_t timer_start;
    uint8_t received_bits;
    volatile uint8_t flags;
    uint32_t received_message;
    uint32_t received_data;
};

#endif