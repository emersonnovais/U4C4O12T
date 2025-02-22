# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)
set(PICO_SDK_PATH "/home/emerson/.pico-sdk/sdk/2.1.0")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

# Definição do projeto
project(U4C4O12T C CXX ASM)

# Inicializa o Raspberry Pi Pico SDK
pico_sdk_init()

# Adiciona o executável com o único arquivo do projeto
add_executable(U4C4O12T main.c)

pico_set_program_name(U4C4O12T "U4C4O12T")
pico_set_program_version(U4C4O12T "0.1")

# Configura saída UART e USB
pico_enable_stdio_uart(U4C4O12T 1)
pico_enable_stdio_usb(U4C4O12T 0)

# Vincula bibliotecas padrão
target_link_libraries(U4C4O12T pico_stdlib)

# Adiciona bibliotecas necessárias
target_link_libraries(U4C4O12T 
    hardware_pio
    pico_cyw43_arch_none
    hardware_clocks
)

# Aqui você inclui a biblioteca WS2812
add_subdirectory(Pico_WS2812)

# Vincula a biblioteca WS2812
target_link_libraries(U4C4O12T Pico_WS2812)

# Gera os arquivos de saída, incluindo .UF2
pico_add_extra_outputs(U4C4O12T)
