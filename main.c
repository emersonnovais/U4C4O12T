//Embarcatech - curso de sistemas embarcados
//Autor: Emerson Novais Oliveira
//Tarefa: U4C4O12T

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"  // erro na implementação dessa biblioteca no linux

#define LED_RED 11
#define LED_GREEN 12
#define LED_BLUE 13
#define BUTTON_A 5
#define BUTTON_B 6
#define WS2812_PIN 7
#define LED_MATRIX_SIZE 25  // 5x5 = 25 LEDs

volatile int number = 0;
volatile bool update_display = true;

// Padrões dos números (0-9) para a matriz 5x5
const uint8_t number_patterns[10][5] = {
    {1, 1, 1, 1, 1},
    {0, 1, 0, 0, 0},
    {1, 1, 0, 1, 1},
    {1, 1, 1, 0, 1},
    {0, 1, 1, 1, 0},
    {1, 0, 1, 1, 1},
    {1, 0, 1, 1, 1},
    {1, 1, 0, 0, 0},
    {1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0}
};

// Função de debounce para botões
void debounce(uint gpio) {
    sleep_ms(50);
    while (!gpio_get(gpio));
    sleep_ms(50);
}

// Funções de interrupção para botões A e B
void button_a_isr(uint gpio, uint32_t events) {
    debounce(BUTTON_A);
    number = (number + 1) % 10;
    update_display = true;
}

void button_b_isr(uint gpio, uint32_t events) {
    debounce(BUTTON_B);
    number = (number - 1 + 10) % 10;
    update_display = true;
}

// Função para configurar os pinos GPIO e interrupções
void setup_gpio() {
    // Inicializando os pinos dos LEDs RGB
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);

    // Inicializando o botão A e configurando a interrupção
    gpio_init(BUTTON_A);
    gpio_pull_up(BUTTON_A);
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_a_isr);

    // Inicializando o botão B e configurando a interrupção
    gpio_init(BUTTON_B);
    gpio_pull_up(BUTTON_B);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &button_b_isr);
}

// Função para piscar o LED vermelho
void blink_red_led() {
    static absolute_time_t last_toggle;
    static bool led_state = false;
    if (absolute_time_diff_us(last_toggle, get_absolute_time()) > 100000) {
        led_state = !led_state;
        gpio_put(LED_RED, led_state);
        last_toggle = get_absolute_time();
    }
}

// Função para exibir o número na matriz WS2812
void display_number(int num) {
    // Inicialize o PIO para controle da WS2812 (certifique-se de que você tem a biblioteca PIO configurada)
    PIO pio = pio0;
    int sm = 0;  // Estado da máquina de estado

    // Configuração do PIO para enviar dados da WS2812
    ws2812_init(pio, sm, WS2812_PIN);

    // Obtendo o padrão de LEDs do número a ser exibido
    uint8_t *pattern = number_patterns[num];

    // Enviando os dados para a WS2812 (não é implementado na função ws2812_init, será necessário um código específico)
    for (int i = 0; i < LED_MATRIX_SIZE; i++) {
        bool state = pattern[i / 5] & (1 << (i % 5));  // Definindo se o LED está aceso ou apagado
        ws2812_send(pio, sm, state);  // Envia o estado de cada LED
    }
}

int main() {
    stdio_init_all();
    setup_gpio();

    while (1) {
        blink_red_led();
        if (update_display) {
            display_number(number);
            update_display = false;
        }
        sleep_ms(10);
    }

    return 0;
}
