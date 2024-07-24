#pragma once

#include "State.hpp"
#include <cstdint>

class TrafficLight;
class HardwareHandler;

class Go : public State {
public:
    Go(TrafficLight* context, HardwareHandler* hardware) noexcept;
    Go(const Go&) = delete;
    Go(Go&&) = delete;
    Go& operator=(const Go&) = delete;
    Go& operator=(Go&&) = delete;
    ~Go() override = default;
    void on_update() noexcept override;

private:
    void transitionToGoToStop();
    constexpr static uint32_t state_period_ {2000};
};
