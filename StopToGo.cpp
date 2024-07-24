#include "StopToGo.hpp"
#include "Go.hpp"
#include "HardwareHandler.hpp"
#include "TrafficLight.hpp"
#include <memory>

StopToGo::StopToGo(TrafficLight* context, HardwareHandler* hardware) noexcept : State(context, hardware) {
    HardwareHandler::red_light(true);
    HardwareHandler::yellow_light(true);
    HardwareHandler::green_light(false);
    hardware->set_transition(StopToGo::state_period_, [&]() { this->transitionToGo(); });
}

void StopToGo::transitionToGo() noexcept { context_->transitionTo(std::make_unique<Go>(context_, hardware_)); }

void StopToGo::on_update() noexcept { }
