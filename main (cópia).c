//Embarcatech - curso de sistemas embarcados
//Autor: Emerson Novais Oliveira
//Tarefa: U4C4O12T

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
//#include "ws2812.pio.h"

#define LED_RED 11
#define LED_GREEN 12
#define LED_BLUE 13
#define BUTTON_A 5
#define BUTTON_B 6
#define WS2812_PIN 7
#define LED_MATRIX_SIZE 25

volatile int number = 0;
volatile bool update_display = true;

void debounce(uint gpio) {
    sleep_ms(50);
    while (!gpio_get(gpio));
    sleep_ms(50);
}

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

void setup_gpio() {
    //Inicializando os pinos dos LEDs:
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    //Configurando os pinos dos LEDs:
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);

    //Inicializando o botão A e fazendo ajustes:
    gpio_init(BUTTON_A);
    gpio_pull_up(BUTTON_A);
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_a_isr);

    //Inicializando o botão a 
    gpio_init(BUTTON_B);
    gpio_pull_up(BUTTON_B);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &button_b_isr);
}

void blink_red_led() {
    static absolute_time_t last_toggle;
    static bool led_state = false;
    if (absolute_time_diff_us(last_toggle, get_absolute_time()) > 100000) {
        led_state = !led_state;
        gpio_put(LED_RED, led_state);
        last_toggle = get_absolute_time();
    }
}

void display_number(int num) {
    // Aqui deve ser implementada a lógica para exibir números na matriz WS2812
    printf("Exibindo número: %d\n", num);
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
}
