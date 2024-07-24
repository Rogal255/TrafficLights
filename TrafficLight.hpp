#pragma once

#include "State.hpp"
#include <memory>

class TrafficLight {
public:
    void transitionTo(std::unique_ptr<State>&& state) noexcept;
    void on_update() noexcept;

private:
    std::unique_ptr<State> state_ {nullptr};
};
