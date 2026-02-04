#include "hts221.h"
#include "stm32l47xx_i2c_driver.h"  // tu driver

/* Para simplificar: vamos a fijar que usamos I2C2 */
static I2C_Handle_t g_i2c2;

/* Función interna: leo un registro de 1 byte del HTS221 */
static uint8_t hts221_read_u8(uint8_t reg)
{
    uint8_t val = 0;

    // 1) mando el registro a leer (escritura sin STOP final)
    //    -> Usamos Sr = 1 para repeated start
    I2C_MasterSendData(g_i2c2.pI2Cx,
                       &reg,
                       1,
                       HTS221_ADDR_7BIT,
                       /*Sr=*/1);

    // 2) leo 1 byte del esclavo, Sr=0 (stop al final)
    I2C_MasterReceiveData(g_i2c2.pI2Cx,
                          &val,
                          1,
                          HTS221_ADDR_7BIT,
                          /*Sr=*/0);

    return val;
}

/* lo mismo pero escritura de un byte: reg <- data */
static void hts221_write_u8(uint8_t reg, uint8_t data)
{
    uint8_t buf[2];
    buf[0] = reg;
    buf[1] = data;

    // write de 2 bytes con STOP al final (Sr=0)
    I2C_MasterSendData(g_i2c2.pI2Cx,
                       buf,
                       2,
                       HTS221_ADDR_7BIT,
                       /*Sr=*/0);
}

/* Inicialización del HTS221 */
bool HTS221_Init(void)
{
    // 0. Preparar handle I2C2 y configurar periférico si no está inicializado
    g_i2c2.pI2Cx = I2C2;
    I2C_Init(&g_i2c2);

    // 1. Leer WHO_AM_I
    uint8_t who = hts221_read_u8(HTS221_REG_WHO_AM_I);
    if (who != HTS221_WHO_AM_I_VAL)
    {
        return false;
    }

    // 2. Encender el sensor: CTRL1
    //    PD=1 (bit7), BDU=1 (bit2), ODR1:0=01 (bit1=0, bit0=1) -> 1 Hz
    //    CTRL1 = 1<<7 | 1<<2 | 1<<0 = 0b10000101 = 0x85
    hts221_write_u8(HTS221_REG_CTRL1, 0x85);

    return true;
}

bool HTS221_ReadWhoAmI(uint8_t *out_val)
{
    if (!out_val) return false;
    *out_val = hts221_read_u8(HTS221_REG_WHO_AM_I);
    return true;
}

/* Por ahora devolvemos fakes, mañana metemos fórmula de calibración */
float HTS221_ReadTemperatureC(void)
{
    return 25.0f;
}

float HTS221_ReadHumidityPerc(void)
{
    return 40.0f;
}
