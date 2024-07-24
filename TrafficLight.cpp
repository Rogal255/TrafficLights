#include "TrafficLight.hpp"
#include "State.hpp"

void TrafficLight::transitionTo(std::unique_ptr<State>&& state) noexcept { state_ = std::move(state); }

void TrafficLight::on_update() noexcept { state_->on_update(); }
