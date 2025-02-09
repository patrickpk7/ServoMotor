#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22  // GPIO para o servo
#define FREQ_PWM 50 // Frequência do PWM (50Hz)
#define VALOR_WRAP 20000  // Período de 20ms (50Hz)

// Função para configurar o PWM
void config_pwm() {
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM); // Define a GPIO como PWM
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN); // Obtém o slice PWM associado

    pwm_config config = pwm_get_default_config(); 
    pwm_config_set_clkdiv(&config, 125.0);  // Define divisor para obter 50Hz
    pwm_config_set_wrap(&config, VALOR_WRAP); // Define o wrap para 20ms

    pwm_init(slice, &config, true); // Inicializa o PWM
}

// Função para definir o ciclo ativo do PWM (µs)
void flange_config(uint16_t flange_servo) {
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN); // Obtem o slice do Servomotor conectado ao pino 22
    pwm_set_gpio_level(SERVO_PIN, flange_servo); // Define o ciclo ativo
}

int main() {
    stdio_init_all(); // Inicia comunicação serial
    config_pwm(); // Chama função config_pwm para iniciar o pwm configurado

    // Ajuste para 180° (2400µs) e aguarda 5s
    flange_config(2400);
    sleep_ms(5000);

    // Ajuste para 90° (1470µs) e aguarda 5s
    flange_config(1470);
    sleep_ms(5000);

    // Ajuste para 0° (500µs) e aguarda 5s
    flange_config(500);
    sleep_ms(5000);

    // Movimento contínuo suave entre 0° e 180°
    while (true) {
        // Movendo de 0° para 180°
        for (uint16_t pulse = 500; pulse <= 2400; pulse += 5) {
            set_servo_pulse(pulse);
            sleep_ms(10);
        }

        sleep_ms(100); // Aguarda 100ms no fim do movimento

        // Movendo de 180° para 0°
        for (uint16_t pulse = 2400; pulse >= 500; pulse -= 5) {
            set_servo_pulse(pulse);
            sleep_ms(10);
        }

        sleep_ms(100); // Aguarda 100ms no fim do movimento
    }
}
