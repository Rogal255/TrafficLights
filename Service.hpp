#pragma once

#include "State.hpp"
#include <cstdint>

class TrafficLight;
class HardwareHandler;

class Service : public State {
public:
    Service(TrafficLight* context, HardwareHandler* hardware) noexcept;
    Service(const Service&) = delete;
    Service(Service&&) = delete;
    Service& operator=(const Service&) = delete;
    Service& operator=(Service&&) = delete;
    ~Service() override = default;
    void on_update() noexcept override;

private:
    void transitionToStop() noexcept;
    void transitionToBlink() noexcept;
    bool isBlink_ {true};
    constexpr static uint32_t blink_time_ {500};
};
