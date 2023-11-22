#include <avr/io.h>

const uint16_t CARRIER_FREQUENCY = 38000;

const uint8_t  BLINK_DURATION =   211; // 16000000/56000 = 421/2 = 211
const uint16_t PULSE_DURATION =  9000; //  562.5µs 
const uint16_t  ZERO_DURATION  =  9000; //  562.5µs
const uint16_t  ONE_DURATION   = 27000; // 1.6875ms
class IR 
{
    public:
        IR();
        void start_blinking();
        void start_signal_timer();
    
        void read_bit();
        void send_bit();
    
        void read_data();
        void send_data(uint8_t);
        
        uint8_t is_communicating();
        void set_communicating(uint8_t);
        
        uint8_t is_bit_ready();
        void set_bit_ready(uint8_t);
    
    private:
        uint8_t communicating;
        uint16_t input_buffer;
        uint8_t bit_ready;
};