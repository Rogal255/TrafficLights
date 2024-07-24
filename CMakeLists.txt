cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(Trening)

pico_sdk_init()
set(PICO_BOARD pico_w)

add_executable(${PROJECT_NAME} main.cpp State.cpp TrafficLight.cpp HardwareHandler.cpp Stop.cpp StopToGo.cpp Go.cpp GoToStop.cpp Service.cpp)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} pico_stdlib pico_cyw43_arch_none hardware_pwm hardware_adc)
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

## -DPICO_BOARD=pico_w
