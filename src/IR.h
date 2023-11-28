#include <avr/io.h>

const uint16_t CARRIER_FREQUENCY = 38000;

const uint8_t MESSAGE_SIZE = 11;
const uint8_t PARITY_MASK = 0x02;
const uint16_t DATA_MASK = 0b01111111100;

const uint8_t  BLINK_DURATION =   211; // 16000000/56000 = 421/2 = 211
const uint16_t PULSE_DURATION =  9000; //  562.5µs 
const uint16_t  ZERO_DURATION  =  9000; //  562.5µs
const uint16_t  ONE_DURATION   = 27000; // 1.6875ms

enum IRFlags {
    // sending
    IR_FLAG_READY_TO_SEND = 0x01,
    IR_FLAG_SENDING_PULSES = 0x02,
    // receiving
    IR_FLAG_BIT_READY = 0x10,
    IR_FLAG_START_READING = 0x20,
    IR_FLAG_MESSAGE_RECEIVED = 0x40,
};

const uint8_t START_BIT = 1;
const uint8_t STOP_BIT = 1;

class IR 
{
    public:
        IR();
        void start_blinking();
        void stop_blinking();
        void start_signal_timer();
        void stop_signal_timer();

        uint16_t get_output_buffer();
        void shift_output_buffer();

        uint8_t get_input_buffer();
        void write_to_input_buffer(uint8_t);

        uint16_t get_timer_start();
        void set_timer_start(uint16_t);

        uint8_t get_received_bits();
        void set_received_bits(uint8_t);
        void inc_received_bits();
    
        void read_bit();
        void send_bit(uint8_t);
    
        void read_data();
        void send_data(uint8_t);
        void interpret_data();
        
        uint8_t get_flags();
        void set_flag(uint8_t);
        void clear_flag(uint8_t);
        
    private:
        uint16_t input_buffer;
        uint16_t output_buffer;
        uint16_t timer_start;
        uint8_t received_bits;
        uint8_t flags;
        uint8_t data[];
};