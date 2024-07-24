#include "Go.hpp"
#include "GoToStop.hpp"
#include "HardwareHandler.hpp"
#include "TrafficLight.hpp"
#include <memory>

Go::Go(TrafficLight* context, HardwareHandler* hardware) noexcept : State(context, hardware) {
    HardwareHandler::red_light(false);
    HardwareHandler::yellow_light(false);
    HardwareHandler::green_light(true);
    hardware->set_transition(Go::state_period_, [&]() { this->transitionToGoToStop(); });
}

void Go::transitionToGoToStop() { context_->transitionTo(std::make_unique<GoToStop>(context_, hardware_)); }

void Go::on_update() noexcept { }
