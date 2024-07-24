#include "State.hpp"

State::State(TrafficLight* context, HardwareHandler* hardware) noexcept : context_(context), hardware_(hardware) { }
