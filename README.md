Excelente, Moisés 👍
Esse códigomostra a integração entre o **acelerômetro MPU6050** e um **servo contínuo (ou simulado)**, controlando o movimento do servo conforme a **inclinação do sensor**.

---

## 🧠 **Explicação do funcionamento**

### 1. **Inicialização**

```c
stdio_init_all();
sleep_ms(2000);
mpu_setup();
```

* Inicializa a comunicação serial (para `printf` no terminal).
* Dá 2 segundos de pausa para abrir o monitor serial.
* Configura o sensor **MPU6050** via I2C com a função `mpu_setup()` (que define endereços e calibrações básicas).

---

### 2. **Configuração do Servo**

```c
uint32_t rotation_time_ms = 700;
servo_sim_t servo;
servo_sim_init(&servo, SERVO_PIN, (float)rotation_time_ms);
```

* Define o **tempo necessário para o servo girar 90°** (700 ms).
* Configura o pino 2 (GPIO2) para gerar sinal **PWM a 50 Hz** — necessário para controle do servo.
* Define a velocidade de rotação e os limites de 0° a 180°.

---

### 3. **Leitura do Acelerômetro**

```c
mpu_read_accel_data(acceleration);
```

* Lê os valores de aceleração nos eixos X, Y e Z do sensor.

  * `acceleration[0]` → eixo X
  * `acceleration[2]` → eixo Z

---

### 4. **Cálculo do Ângulo**

```c
float angle_rad = atan2f(acceleration[0], acceleration[2]);
float target_angle = angle_rad * 180.0f / M_PI + 90.0f;
```

* Usa a função `atan2f()` para converter a inclinação em radianos.
* Transforma o valor em graus (`×180/π`).
* Soma 90° para centralizar a faixa de 0 a 180°.

  * Sensor plano → ~90°
  * Inclinado para frente → menor que 90°
  * Inclinado para trás → maior que 90°

---

### 5. **Controle do Servo**

```c
servo_sim_set_angle(&servo, target_angle);
```

* Move o servo para o ângulo correspondente à inclinação detectada.
* Se o MPU for girado fisicamente, o servo acompanha o movimento.

---

### 6. **Monitor Serial**

```c
printf("Angulo MPU: %.2f\n", target_angle);
```

* Exibe no terminal o ângulo atual calculado em graus.
* Útil para depuração e calibração.

---

## ✅ **Síntese — Funcionamento Resumido**

> O programa lê continuamente a inclinação do sensor **MPU6050**, converte essa inclinação em um **ângulo de 0° a 180°**, e move um **servo motor** para corresponder a essa posição. Assim, o servo simula fisicamente o ângulo medido pelo acelerômetro.

Quando o módulo MPU é inclinado:

* Inclinação para frente → servo gira para menor ângulo.
* Inclinação para trás → servo gira para ângulo maior.
* Posição neutra (plana) → servo em ~90°.

---

## 📈 **Resultados Esperados**

| Situação Física do MPU6050 | Ângulo Calculado              | Movimento do Servo    |
| -------------------------- | ----------------------------- | --------------------- |
| Sensor na posição plana    | ≈ 90°                         | Servo fica no meio    |
| Sensor inclinado à frente  | 0°–89°                        | Servo gira à esquerda |
| Sensor inclinado para trás | 91°–180°                      | Servo gira à direita  |
| Sensor parado              | Servo parado no último ângulo |                       |

---

