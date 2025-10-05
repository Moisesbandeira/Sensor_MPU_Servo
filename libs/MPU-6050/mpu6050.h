#ifndef MPU6050_H
#define MPU6050_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"

//----CONFIGURAÇÕES DOS PINOS I2C-----
#define I2C_PORT i2c0
#define I2C_SDA_PIN 0
#define I2C_SCL_PIN 1

/**
 * @brief Inicializa a comunicação I2C com o MPU-6050 e o tira do modo de repouso.
 * 
 */
 void mpu_setup();

/**
 * @brief Lê os dados brutos dos 3 eixos do acelerômetro
 * 
 * @param accel Array de 3 posiçoes para armazenar os valores (X, Y, Z).
 */
 
  void mpu_read_accel_data(int16_t accel[3]);
   
#endif 


