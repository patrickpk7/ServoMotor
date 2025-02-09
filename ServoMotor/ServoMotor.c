#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22  // GPIO para o servo
#define PWM_FREQUENCY 50 // Frequência do PWM (50Hz)
#define WRAP_VALUE 20000  // Período de 20ms (50Hz)

// Função para configurar o PWM
void pwm_setup() {
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM); // Define a GPIO como PWM
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN); // Obtém o slice PWM associado

    pwm_config config = pwm_get_default_config(); 
    pwm_config_set_clkdiv(&config, 125.0);  // Define divisor para obter 50Hz
    pwm_config_set_wrap(&config, WRAP_VALUE); // Define o wrap para 20ms

    pwm_init(slice, &config, true); // Inicializa o PWM
}

// Função para definir o ciclo ativo do PWM (µs)
void set_servo_pulse(uint16_t pulse_width) {
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN);
    pwm_set_gpio_level(SERVO_PIN, pulse_width); // Define o ciclo ativo
}

int main() {
    stdio_init_all();
    pwm_setup();

    // Ajuste para 180° (2400µs) e aguarda 5s
    set_servo_pulse(2400);
    sleep_ms(5000);

    // Ajuste para 90° (1470µs) e aguarda 5s
    set_servo_pulse(1470);
    sleep_ms(5000);

    // Ajuste para 0° (500µs) e aguarda 5s
    set_servo_pulse(500);
    sleep_ms(5000);

    // Movimento contínuo suave entre 0° e 180°
    while (true) {
        // Movendo de 0° para 180°
        for (uint16_t pulse = 500; pulse <= 2400; pulse += 5) {
            set_servo_pulse(pulse);
            sleep_ms(10);
        }

        sleep_ms(100); // Aguarda 1s no final do movimento

        // Movendo de 180° para 0°
        for (uint16_t pulse = 2400; pulse >= 500; pulse -= 5) {
            set_servo_pulse(pulse);
            sleep_ms(10);
        }

        sleep_ms(100); // Aguarda 1s no final do movimento
    }
}
