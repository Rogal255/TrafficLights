#include "HardwareHandler.hpp"
#include "Enums.hpp"
#include "Service.hpp"
#include "TrafficLight.hpp"
#include <memory>

void HardwareHandler::set_traffic_lights(TrafficLight* lights) { this->lights_ = lights; }

void HardwareHandler::init() noexcept {
    stdio_usb_init();

    gpio_init(LED::GREEN);
    gpio_init(LED::YELLOW);
    gpio_init(LED::RED);
    gpio_set_dir(LED::GREEN, GPIO_OUT);
    gpio_set_dir(LED::YELLOW, GPIO_OUT);
    gpio_set_dir(LED::RED, GPIO_OUT);
    gpio_put(LED::GREEN, false);
    gpio_put(LED::YELLOW, false);
    gpio_put(LED::RED, false);

    gpio_init(OTHER::SW);
    gpio_set_dir(OTHER::SW, GPIO_IN);
    gpio_pull_up(OTHER::SW);
}

void HardwareHandler::red_light(bool illuminate) noexcept { gpio_put(LED::RED, illuminate); }

void HardwareHandler::yellow_light(bool illuminate) noexcept { gpio_put(LED::YELLOW, illuminate); }

void HardwareHandler::green_light(bool illuminate) noexcept { gpio_put(LED::GREEN, illuminate); }

void HardwareHandler::set_transition(uint32_t ms, std::function<void(void)>&& transitionFunction) noexcept {
    next_alarm_id_ = add_alarm_in_ms(ms, HardwareHelpers::callback_transition, this, false);
    this->transitionFunction_ = transitionFunction;
}

void HardwareHandler::set_repeating_timer(int32_t ms, std::function<void()>&& serviceFunction) noexcept {
    this->serviceFunction_ = serviceFunction;
    add_repeating_timer_ms(ms, HardwareHelpers::callback_repeating, this, &this->timer_struct_);
}

void HardwareHandler::service_enter() noexcept {
    this->serviceMode_ = true;
    if (this->next_alarm_id_) {
        cancel_alarm(this->next_alarm_id_);
    }
    this->next_alarm_id_ = 0;
    this->lights_->transitionTo(std::make_unique<Service>(this->lights_, this));
}

void HardwareHandler::service_exit() noexcept {
    this->serviceMode_ = false;
    this->serviceExit_();
}

void HardwareHandler::set_service_exit(std::function<void()>&& servExit) noexcept { this->serviceExit_ = servExit; }

void HardwareHandler::on_update() noexcept {
    if (!gpio_get(OTHER::SW)) {
        if (absolute_time_diff_us(this->last_time_button_pressed_, get_absolute_time()) > this->button_inhibit_time_) {
            if (this->serviceMode_) {
                this->service_exit();
            } else {
                this->service_enter();
            }
            last_time_button_pressed_ = get_absolute_time();
        }
    }
    sleep_ms(HardwareHandler::sleep_per_cycle_ms_);
}

int64_t HardwareHelpers::callback_transition([[maybe_unused]] alarm_id_t id, void* usr_data) noexcept {
    auto handler = static_cast<HardwareHandler*>(usr_data);
    handler->transitionFunction_();
    return 0;
}

bool HardwareHelpers::callback_repeating(repeating_timer_t* timer) noexcept {
    auto handler = static_cast<HardwareHandler*>(timer->user_data);
    if (handler->serviceMode_) {
        handler->serviceFunction_();
    }
    return handler->serviceMode_;
}
