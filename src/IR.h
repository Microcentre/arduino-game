#include <avr/io.h>

const uint16_t CARRIER_FREQUENCY = 38000;

const uint8_t MESSAGE_SIZE = 11;
const uint8_t PARITY_MASK = 0x02;
const uint8_t DATA_MASK = 0b01111111100;

const uint8_t  BLINK_DURATION =   211; // 16000000/56000 = 421/2 = 211
const uint16_t PULSE_DURATION =  9000; //  562.5µs 
const uint16_t  ZERO_DURATION  =  9000; //  562.5µs
const uint16_t  ONE_DURATION   = 27000; // 1.6875ms

enum IRFlags {
    IR_FLAG_READY_TO_SEND = 0x01,
    IR_FLAG_SENDING_PULSES = 0x02,
    IR_FLAG_BIT_READY = 0x10,
    IR_FLAG_START_READING = 0x20,
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
        uint8_t flags;
};