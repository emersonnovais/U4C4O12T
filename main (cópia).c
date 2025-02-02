#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "bitdoglab.h"  // Biblioteca específica para o BitDogLab

// Definindo os pinos para os LEDs e botões
#define LED_WS2812_PIN     7
#define LED_RGB_R_PIN      11
#define LED_RGB_G_PIN      12
#define LED_RGB_B_PIN      13
#define BUTTON_A_PIN       5
#define BUTTON_B_PIN       6

// Variáveis globais
volatile int number = 0;  // Número a ser exibido na matriz
volatile bool buttonA_pressed = false;
volatile bool buttonB_pressed = false;
unsigned long lastButtonPressA = 0;
unsigned long lastButtonPressB = 0;
const unsigned long debounceDelay = 200;  // Delay para debouncing em milissegundos

// Funções
void initLEDs();
void blinkRed();
void displayNumber(int num);
void incrementNumber();
void decrementNumber();
void buttonAPressed();
void buttonBPressed();

// Função principal
int main(void) {
    // Inicializa o BitDogLab
    bitdoglab_init();
    
    // Configura os LEDs e botões
    initLEDs();
    
    // Configura interrupções para os botões
    attachInterrupt(BUTTON_A_PIN, buttonAPressed, FALLING);
    attachInterrupt(BUTTON_B_PIN, buttonBPressed, FALLING);
    
    while (1) {
        // Pisca o LED vermelho
        blinkRed();
        
        // Verifica e executa as ações dos botões
        if (buttonA_pressed) {
            buttonA_pressed = false;
            incrementNumber();
        }
        if (buttonB_pressed) {
            buttonB_pressed = false;
            decrementNumber();
        }
        
        // Exibe o número na matriz de LEDs
        displayNumber(number);
        
        // Delay para evitar sobrecarga
        delay(100);
    }
    
    return 0;
}

// Inicializa os LEDs
void initLEDs() {
    pinMode(LED_RGB_R_PIN, OUTPUT);
    pinMode(LED_RGB_G_PIN, OUTPUT);
    pinMode(LED_RGB_B_PIN, OUTPUT);
    pinMode(LED_WS2812_PIN, OUTPUT);
    // Inicializa a matriz WS2812, se necessário, com a biblioteca específica
    ws2812_init(LED_WS2812_PIN, 25); // Exemplo de inicialização, adaptar conforme necessário
}

// Função para piscar o LED vermelho
void blinkRed() {
    static unsigned long lastTime = 0;
    static bool ledState = false;
    unsigned long currentTime = millis();
    
    if (currentTime - lastTime >= 200) {  // Piscar a cada 200ms (5 vezes por segundo)
        lastTime = currentTime;
        ledState = !ledState;
        
        if (ledState) {
            digitalWrite(LED_RGB_R_PIN, HIGH);
        } else {
            digitalWrite(LED_RGB_R_PIN, LOW);
        }
    }
}

// Função para incrementar o número
void incrementNumber() {
    if (number < 9) {
        number++;
    }
}

// Função para decrementar o número
void decrementNumber() {
    if (number > 0) {
        number--;
    }
}

// Função para exibir um número na matriz de LEDs
void displayNumber(int num) {
    // Aqui você implementa a exibição do número na matriz 5x5 de LEDs,
    // por exemplo, um número "0" pode ser representado por acender certos LEDs na matriz.
    // Exemplo simples:
    ws2812_clear();  // Limpar todos os LEDs
    
    // Este código é apenas ilustrativo para mapeamento simples de números
    switch (num) {
        case 0:
            ws2812_setPixel(0, 255, 0, 0);
            ws2812_setPixel(1, 255, 0, 0);
            ws2812_setPixel(2, 255, 0, 0);
            ws2812_setPixel(5, 255, 0, 0);
            ws2812_setPixel(10, 255, 0, 0);
            ws2812_setPixel(15, 255, 0, 0);
            ws2812_setPixel(20, 255, 0, 0);
            ws2812_setPixel(21, 255, 0, 0);
            ws2812_setPixel(22, 255, 0, 0);
            break;
        case 1:
            ws2812_setPixel(2, 0, 255, 0);
            ws2812_setPixel(7, 0, 255, 0);
            ws2812_setPixel(12, 0, 255, 0);
            ws2812_setPixel(17, 0, 255, 0);
            ws2812_setPixel(22, 0, 255, 0);
            break;
        case 2:
            // Exibir o número 2...
            break;
        // Adicionar os outros números 3-9 de forma semelhante
    }
    
    ws2812_show();  // Atualiza os LEDs com os valores definidos
}

// Função de interrupção para o botão A
void buttonAPressed() {
    if (millis() - lastButtonPressA > debounceDelay) {
        lastButtonPressA = millis();
        buttonA_pressed = true;
    }
}

// Função de interrupção para o botão B
void buttonBPressed() {
    if (millis() - lastButtonPressB > debounceDelay) {
        lastButtonPressB = millis();
        buttonB_pressed = true;
    }
}
