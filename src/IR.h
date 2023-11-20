#include <avr/io.h>

const int CARRIER_FREQUENCY = 56000;

class IR 
{
    public:
        IR();
        void startBlinking();
    private:
        int frequency;
        uint8_t pin;
};