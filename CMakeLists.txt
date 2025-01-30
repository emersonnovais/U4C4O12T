# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Matriz_Led_PIO C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(Matriz_Led_PIO
    src/Matriz_Led_PIO.c
    src/util/drawing.c
    src/util/keypad.c
    src/util/matrizLedControl.c
)

pico_set_program_name(Matriz_Led_PIO "Matriz_Led_PIO")
pico_set_program_version(Matriz_Led_PIO "0.1")

# Generate PIO header
pico_generate_pio_header(Matriz_Led_PIO ${CMAKE_CURRENT_LIST_DIR}/ws2818b.pio)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Matriz_Led_PIO 1)
pico_enable_stdio_usb(Matriz_Led_PIO 0)

# Add the standard library to the build
target_link_libraries(Matriz_Led_PIO
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(Matriz_Led_PIO PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/src/util
)

# Add any user requested libraries
target_link_libraries(Matriz_Led_PIO 
        hardware_pio
        pico_cyw43_arch_none
        hardware_clocks
        )


pico_add_extra_outputs(Matriz_Led_PIO)