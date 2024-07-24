#include "Stop.hpp"
#include "StopToGo.hpp"
#include <memory>

Stop::Stop(TrafficLight* context, HardwareHandler* hardware) noexcept : State(context, hardware) {
    HardwareHandler::red_light(true);
    HardwareHandler::yellow_light(false);
    HardwareHandler::green_light(false);
    hardware->set_transition(2000, [&]() { this->transitionToStopToGo(); });
}

void Stop::transitionToStopToGo() noexcept { context_->transitionTo(std::make_unique<StopToGo>(context_, hardware_)); }

void Stop::on_update() noexcept { }
