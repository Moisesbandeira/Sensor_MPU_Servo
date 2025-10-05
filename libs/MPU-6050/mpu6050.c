#include "mpu6050.h"
#include <stdio.h>
// Endereço I2C do MPU-6050
static const int MPU_ADDR = 0x68;
// Endereços dos registradores importantes
static const int ACCEL_XOUT_H = 0x3B;
static const int PWR_MGMT_1 = 0x6B;
void mpu_setup() {
    // Inicializa a interface I2C com uma velocidade de 100KHz
    i2c_init(I2C_PORT, 100 * 1000);
    // Configura os pinos GPIO para a função I2C
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    // Habilita os resistores de pull-up internos
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);
    // Tira o MPU-6050 do modo de repouso escrevendo 0 o resgistrador PWR_MGMT_1
    uint8_t buf[] = {PWR_MGMT_1, 0X00};
    i2c_write_blocking(I2C_PORT, MPU_ADDR, buf, 2, false);
    printf("MPU-6050 inicializando.\n");
}
void mpu_read_accel_data(int16_t accel[3]) {
    uint8_t buffer[6];
    // Aponta para o registrador do acelerômetro a partir do qual a leitura começará
    uint8_t reg = ACCEL_XOUT_H;
    i2c_write_blocking(I2C_PORT, MPU_ADDR, &reg, 1, true); //-> mantém o controle do barramento
    //Lê 6 bytes de dados (2 bytes para cada eixo: X, Y, Z)
    i2c_read_blocking(I2C_PORT, MPU_ADDR, buffer, 6, false);
    // Combina os bytes alto e baixo para formar um valor de 16 bits para cada eixo
    accel[0] = (buffer[0] << 8) | buffer[1]; // Eixo X
    accel[1] = (buffer[2] << 8) | buffer[3]; // Eixo Y
    accel[2] = (buffer[4] << 8) | buffer[5]; // Eixo Z
}