#ifndef WAVEHANDSHAKE_H
#define WAVEHANDSHAKE_H

#include "../Objects/ObjectsContainer.h"

class WaveHandshake
{
public:
    WaveHandshake();

    /// @brief
    /// @param other_player_wave_status_bit
    /// @return new wave_status_bit
    void update_handshake(bool other_player_wave_status_bit);
    bool get_handshake_bit_to_send();

protected:
    enum HandshakePhase
    {
        STARTED,
        GENERATING_NEW,
        FINISHED_GENERATING,
    };

    HandshakePhase handshake_phase = HandshakePhase::STARTED;

private:
    bool bit_to_send = 0;
};

#endif