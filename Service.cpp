#include "Service.hpp"
#include "HardwareHandler.hpp"
#include "Stop.hpp"
#include "TrafficLight.hpp"
#include <memory>

Service::Service(TrafficLight* context, HardwareHandler* hardware) noexcept : State(context, hardware) {
    HardwareHandler::red_light(false);
    HardwareHandler::yellow_light(true);
    HardwareHandler::green_light(false);
    this->hardware_->set_service_exit([&]() { this->transitionToStop(); });
    this->hardware_->set_repeating_timer(Service::blink_time_, [&]() { this->transitionToBlink(); });
}

void Service::on_update() noexcept { }

void Service::transitionToStop() noexcept { context_->transitionTo(std::make_unique<Stop>(context_, hardware_)); }

void Service::transitionToBlink() noexcept {
    this->isBlink_ = !this->isBlink_;
    HardwareHandler::yellow_light(this->isBlink_);
}
