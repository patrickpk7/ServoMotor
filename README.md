# Controle de Servomotor e LED com Raspberry Pi Pico W

Este repositório contém dois programas escritos em C para a placa Raspberry Pi Pico W, que demonstram o uso do PWM para controlar um servomotor e a intensidade de um LED.

## Requisitos
- Placa Raspberry Pi Pico W
- LED e resistor apropriado
- Servomotor compatível
- Ambiente de desenvolvimento configurado com o SDK do Raspberry Pi Pico
- Simulador Wokwi (caso não utilize hardware físico)

## Instalação e Compilação
1. Clone este repositório:
   ```sh
   git clone https://github.com/patrickpk7/ServoMotor.git
   cd ServoMotor
   ```
2. Configure o ambiente de compilação do Raspberry Pi Pico W (CMake e SDK).
3. Compile os programas:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```
4. Envie o arquivo .uf2 para o Raspberry Pi Pico W.

## Programa 1: Controle de Servomotor
### Descrição
Este programa controla um servomotor usando PWM na GPIO 22. Ele ajusta a posição do servo para 0°, 90° e 180° e depois faz um movimento suave entre esses ângulos.

### Como usar
- O servomotor se moverá automaticamente entre os ângulos definidos.
- Para testes sem hardware, use o simulador Wokwi, onde o arquivo de configuração já está presente.

## Programa 2: Controle de LED com PWM
### Descrição
Este programa ajusta a intensidade de um LED usando PWM na GPIO 12. Ele define três níveis de brilho (máximo, médio e mínimo) e depois faz uma transição suave entre eles.

### Como usar
- O LED piscará automaticamente entre os níveis de brilho definidos.
- Para testes sem hardware, o simulador Wokwi pode ser utilizado.

## Simulação no Wokwi
Caso não possua um Raspberry Pi Pico W, você pode testar os programas no [Wokwi](https://wokwi.com/). O arquivo de configuração já está incluído no repositório.

## AUTOR
- Erick Patrick Pontes Chagas

## LINK DO VIDEO APRESENTAÇÃO
- https://drive.google.com/file/d/1IBU3w3NRinyB0qbTPp7a-mvY58O1v-kw/view?usp=sharing

