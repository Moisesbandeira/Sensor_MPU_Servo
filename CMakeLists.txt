# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()

set(PICO_BOARD pico_w CACHE STRING "Board type")

# SDK do Pico
include(pico_sdk_import.cmake)

project(Sensor_MPU_Servo C CXX ASM)

pico_sdk_init()

# Arquivos-fonte corrigidos
add_executable(Sensor_MPU_Servo 
    main.c
    libs/MPU-6050/mpu6050.c
    libs/SERVO/servo.c
)

# Bibliotecas do Pico SDK
target_link_libraries(Sensor_MPU_Servo
    pico_stdlib
    hardware_i2c
    hardware_pwm
    
)

# Diretórios de cabeçalhos
target_include_directories(Sensor_MPU_Servo
    PRIVATE 
        ${CMAKE_CURRENT_LIST_DIR}/libs/MPU-6050
        ${CMAKE_CURRENT_LIST_DIR}/libs/SERVO
)

# Ativando USB, desativando UART
pico_enable_stdio_uart(Sensor_MPU_Servo 0)
pico_enable_stdio_usb(Sensor_MPU_Servo 1)

# Geração do .uf2
pico_add_extra_outputs(Sensor_MPU_Servo)