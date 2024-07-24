#pragma once

#include "State.hpp"
#include <cstdint>

class TrafficLight;
class HardwareHandler;

class GoToStop : public State {
public:
    GoToStop(TrafficLight* context, HardwareHandler* hardware) noexcept;
    GoToStop(const GoToStop&) = delete;
    GoToStop(GoToStop&&) = delete;
    GoToStop& operator=(const GoToStop&) = delete;
    GoToStop& operator=(GoToStop&&) = delete;
    ~GoToStop() override = default;
    void on_update() noexcept override;

private:
    void transitionToStop() noexcept;
    constexpr static uint32_t state_period_ {2000};
};
