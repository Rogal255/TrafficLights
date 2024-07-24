#pragma once

#include "HardwareHandler.hpp"
#include "State.hpp"
#include "TrafficLight.hpp"

class Stop : public State {
public:
    Stop(TrafficLight* context, HardwareHandler* hardware) noexcept;
    Stop(const Stop&) = delete;
    Stop(Stop&&) = delete;
    Stop& operator=(const Stop&) = delete;
    Stop& operator=(Stop&&) = delete;
    ~Stop() override = default;
    void on_update() noexcept override;

private:
    void transitionToStopToGo() noexcept;
};
