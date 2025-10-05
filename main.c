#include <stdio.h>
#include "pico/stdlib.h"
#include <math.h>
// Inclui os novos headers dos módulos
#include "mpu6050.h"
#include "servo.h"
// Define o pino do servo
#define SERVO_PIN   2       // GPIO do servo contínuo (360° )    
int main() {  
    // Inicializa a E/S padrão (para printf)
    stdio_init_all();
    sleep_ms(2000); // Pausa para dar tempo de abrir o monitor serial
    // Chama as funções de configuração dos módulos
    mpu_setup();
     // Servo: usa 700ms padrão
    uint32_t rotation_time_ms = 700;// tempo para 90°
    servo_sim_t servo;
    servo_sim_init(&servo, SERVO_PIN, (float)rotation_time_ms);
    int16_t acceleration[3];
    float current_angle;  

while (1) {
    mpu_read_accel_data(acceleration);
    // Calcula ângulo em graus a partir do MPU
    float angle_rad = atan2f(acceleration[0], acceleration[2]);
    float target_angle = angle_rad * 180.0f / M_PI + 90.0f;

    if (target_angle < 0) target_angle = 0;
    if (target_angle > 180) target_angle = 180;
    // Move o servo diretamente para o ângulo desejado
    servo_sim_set_angle(&servo, target_angle);
    printf("Angulo MPU: %.2f\n", target_angle);
    sleep_ms(100);
}
    return 0;
}