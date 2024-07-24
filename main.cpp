#include "HardwareHandler.hpp"
#include "Stop.hpp"
#include "TrafficLight.hpp"
#include <memory>

class Application {
public:
    Application() noexcept {
        HardwareHandler::init();
        lights_.transitionTo(std::make_unique<Stop>(&lights_, &hardware_));
        hardware_.set_traffic_lights(&lights_);
    }

    void loop() noexcept {
        while (true) {
            hardware_.on_update();
            lights_.on_update();
        }
    }

private:
    TrafficLight lights_;
    HardwareHandler hardware_;
};

int main() {
    Application app;
    app.loop();
}
