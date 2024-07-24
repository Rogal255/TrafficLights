#include "GoToStop.hpp"
#include "HardwareHandler.hpp"
#include "Stop.hpp"
#include "TrafficLight.hpp"
#include <memory>

GoToStop::GoToStop(TrafficLight* context, HardwareHandler* hardware) noexcept : State(context, hardware) {
    HardwareHandler::red_light(false);
    HardwareHandler::yellow_light(true);
    HardwareHandler::green_light(false);
    hardware->set_transition(GoToStop::state_period_, [&]() { this->transitionToStop(); });
}

void GoToStop::transitionToStop() noexcept { context_->transitionTo(std::make_unique<Stop>(context_, hardware_)); }

void GoToStop::on_update() noexcept { }
