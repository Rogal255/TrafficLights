#pragma once

#include "pico/stdlib.h"
#include <functional>

class TrafficLight;

namespace HardwareHelpers {
int64_t callback_transition(alarm_id_t id, void* usr_data) noexcept;
bool callback_repeating(repeating_timer_t* timer) noexcept;
}

class HardwareHandler {
public:
    void set_traffic_lights(TrafficLight* lights);
    static void init() noexcept;
    static void red_light(bool illuminate) noexcept;
    static void yellow_light(bool illuminate) noexcept;
    static void green_light(bool illuminate) noexcept;
    void set_transition(uint32_t ms, std::function<void(void)>&& transitionFunction) noexcept;
    void set_repeating_timer(int32_t ms, std::function<void(void)>&& serviceFunction) noexcept;
    void set_service_exit(std::function<void(void)>&& servExit) noexcept;
    void on_update() noexcept;
    friend int64_t HardwareHelpers::callback_transition(alarm_id_t id, void* usr_data) noexcept;
    friend bool HardwareHelpers::callback_repeating(repeating_timer_t* timer) noexcept;

private:
    void service_enter() noexcept;
    void service_exit() noexcept;
    constexpr static uint32_t sleep_per_cycle_ms_ {10};
    alarm_id_t next_alarm_id_ {};
    bool serviceMode_ {false};
    struct repeating_timer timer_struct_;
    absolute_time_t last_time_button_pressed_ {0};
    int64_t button_inhibit_time_ {1'000'000};
    std::function<void(void)> transitionFunction_;
    std::function<void(void)> serviceFunction_;
    std::function<void(void)> serviceExit_;
    TrafficLight* lights_;
};
