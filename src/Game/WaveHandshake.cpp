#include "WaveHandshake.h"

WaveHandshake::WaveHandshake()
{
}

void WaveHandshake::update_handshake(bool wave_status_bit)
{
    switch (this->handshake_phase)
    {
    case HandshakePhase::STARTED:
        if (wave_status_bit == 1)
        {
            this->handshake_phase = HandshakePhase::GENERATING_NEW;
            this->bit_to_send = 1;
            break;
        }
        this->bit_to_send = 0;
        break;

    case HandshakePhase::GENERATING_NEW:
        if (wave_status_bit == 0)
        {
            this->handshake_phase = HandshakePhase::FINISHED_GENERATING;
            this->bit_to_send = 0;
            break;
        }
        this->bit_to_send = 1;
        break;

    case HandshakePhase::FINISHED_GENERATING:
        if (wave_status_bit == 0)
        {
            this->handshake_phase = HandshakePhase::STARTED;
        }
        this->bit_to_send = 0;
        break;

    // against warning (IDE cries like a baby 😿)
    default:
        this->bit_to_send = 0;
        break;
    }
}

bool WaveHandshake::get_handshake_bit_to_send()
{
    return this->bit_to_send;
}
