#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define LED_PIN 12  // GPIO para o LED
#define FREQ_PWM 50 // Frequência do PWM (50Hz)
#define VALOR_WRAP 20000  // Período de 20ms (50Hz)

// Função para configurar o PWM
void config_pwm() {
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM); // Define a GPIO como PWM
    uint slice = pwm_gpio_to_slice_num(LED_PIN); // Obtém o slice PWM associado

    pwm_config config = pwm_get_default_config(); 
    pwm_config_set_clkdiv(&config, 125.0);  // Define divisor para obter 50Hz
    pwm_config_set_wrap(&config, VALOR_WRAP); // Define o wrap para 20ms

    pwm_init(slice, &config, true); // Inicializa o PWM
}

// Função para definir o ciclo ativo do PWM (µs)
void intensidade_led(uint16_t intensidade) {
    uint slice = pwm_gpio_to_slice_num(LED_PIN);
    pwm_set_gpio_level(LED_PIN, intensidade); // Define o ciclo ativo
}

int main() {
    stdio_init_all();
    config_pwm();

    // Ajuste para brilho maximo (2400µs) e aguarda 5s
    intensidade_led(2400);
    sleep_ms(5000);

    // Ajuste para brilho médio (1470µs) e aguarda 5s
    intensidade_led(1470);
    sleep_ms(5000);

    // Ajuste para brilho minimo (500µs) e aguarda 5s
    intensidade_led(500);
    sleep_ms(5000);

    // Movimento contínuo suave entre o brilho minimo e maximo
    while (true) {
        // Aumentando a intensidade do LED variando de 500µs a 2400µs, 0% a 100%
        for (uint16_t intensidade = 500; intensidade <= 2400; intensidade += 5) {
            intensidade_led(intensidade);
            sleep_ms(10);
        }

        sleep_ms(100); // Aguarda 100ms ao finalizar o aumento do brilho

        // Diminuindo a intensidade do LED variando de 2400µs a 500µs, 100% a 0%
        for (uint16_t intensidade = 2400; intensidade >= 500; intensidade -= 5) {
            intensidade_led(intensidade);
            sleep_ms(10);
        }

        sleep_ms(100); // Aguarda 100ms no final da diminuição do brilho
    }
}
