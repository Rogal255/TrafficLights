#pragma once

#include "State.hpp"
#include <cstdint>

class TrafficLight;
class HardwareHandler;

class StopToGo : public State {
public:
    StopToGo(TrafficLight* context, HardwareHandler* hardware) noexcept;
    StopToGo(const StopToGo&) = delete;
    StopToGo(StopToGo&&) = delete;
    StopToGo& operator=(const StopToGo&) = delete;
    StopToGo& operator=(StopToGo&&) = delete;
    ~StopToGo() override = default;
    void on_update() noexcept override;

private:
    void transitionToGo() noexcept;
    constexpr static uint32_t state_period_ {2000};
};
