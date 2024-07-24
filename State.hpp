#pragma once

class TrafficLight;
class HardwareHandler;

class State {
public:
    State(TrafficLight* context, HardwareHandler* hardware) noexcept;
    State(const State&) = delete;
    State(State&&) = delete;
    State& operator=(const State&) = delete;
    State& operator=(State&&) = delete;
    virtual ~State() = default;
    virtual void on_update() noexcept = 0;

protected:
    TrafficLight* context_;
    HardwareHandler* hardware_;
};
