#include "INA219.hpp"

INA219::INA219 (PinName sda, PinName scl, int addr, int freq, resolution_t res) : I2C(sda, scl), resolution(res), i2c_addr(addr << 1)
{
    I2C::frequency(freq);

    // by default, calibrate to this level.
    calibrate_16v_400mA();
}

// Private Methods

void INA219::write_register (uint8_t reg, uint8_t* data, int length)
{
    char* transmission = (char*)malloc(length + 1);
    memcpy(transmission + 1, data, length);

    transmission[0] = reg;
    I2C::write(i2c_addr, transmission, length + 1);

    free(transmission);
}

void INA219::write_register_u16 (uint8_t reg, uint16_t data)
{
    char transmission[3];
    transmission[0] = reg;
    transmission[1] = (data >> 8) & 0xff;
    transmission[2] = data & 0xff;

    I2C::write(i2c_addr, transmission, 3);
}

void INA219::write_null(uint8_t reg) {
    I2C::write(i2c_addr, (char*)&reg, 1);
}

uint16_t INA219::read_register_u16 (uint8_t reg)
{
    write_null(reg);

    char data[2];
    I2C::read(i2c_addr, data, 2);

    uint16_t ret_val = data[0] << 8 | data[1];
    return ret_val;
}

// Public Methods

void INA219::calibrate_16v_400mA()
{
    // ASSUMING A 0.1 OHM RESISTOR!
    write_register_u16(INA219_REG_CALIBRATION, 8192);

    // Write to config register

    uint16_t resolution_mask = 0x0000;

    if (resolution == RES_12BITS)
        resolution_mask = INA219_CONFIG_BADCRES_12BIT | INA219_CONFIG_SADCRES_12BIT_1S_532US;
    else if (resolution == RES_11BITS)
        resolution_mask = INA219_CONFIG_BADCRES_11BIT | INA219_CONFIG_SADCRES_11BIT_1S_276US;
    else if (resolution == RES_10BITS)
        resolution_mask = INA219_CONFIG_BADCRES_10BIT | INA219_CONFIG_SADCRES_10BIT_1S_148US;
    else // resolution == RES_9BITS
        resolution_mask = INA219_CONFIG_BADCRES_9BIT | INA219_CONFIG_SADCRES_9BIT_1S_84US;

    write_register_u16(INA219_REG_CONFIG, INA219_CONFIG_BVOLTAGERANGE_16V |
                    INA219_CONFIG_GAIN_1_40MV |
                    resolution_mask |
                    INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS);

    // Set current divider
    current_divider = 20;
    power_divider = 1;
}
void INA219::calibrate_32v_3200mA()
{
  // ASSUMING A 0.1 OHM RESISTOR!
  write_register_u16(INA219_REG_CALIBRATION, 8192);

  // Write to config register

  uint16_t resolution_mask = 0x0000;

  if (resolution == RES_12BITS)
      resolution_mask = INA219_CONFIG_BADCRES_12BIT | INA219_CONFIG_SADCRES_12BIT_1S_532US;
  else if (resolution == RES_11BITS)
      resolution_mask = INA219_CONFIG_BADCRES_11BIT | INA219_CONFIG_SADCRES_11BIT_1S_276US;
  else if (resolution == RES_10BITS)
      resolution_mask = INA219_CONFIG_BADCRES_10BIT | INA219_CONFIG_SADCRES_10BIT_1S_148US;
  else // resolution == RES_9BITS
      resolution_mask = INA219_CONFIG_BADCRES_9BIT | INA219_CONFIG_SADCRES_9BIT_1S_84US;

  write_register_u16(INA219_REG_CONFIG, INA219_CONFIG_BVOLTAGERANGE_32V |
                  INA219_CONFIG_GAIN_8_320MV |
                  resolution_mask |
                  INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS);

  // Set current divider
  current_divider = 20;
  power_divider = 1;
  volt_gain = 4;
}
void INA219::calibrate(float _shunt_value, float _max_current, float _max_voltage)
{
    uint16_t calibrating_value;
    float current_lsb;
    /*Caculate calibration register value*/
    current_lsb = (_max_current * 1000) / 32000;
    calibrating_value = (uint16_t) 40.96 / (current_lsb * _shunt_value);
    /*write calibrating_value to calibration register*/
    write_register_u16(INA219_REG_CALIBRATION, calibrating_value);
    /*write to config register*/
    uint16_t resolution_mask = 0x0000;

    if (resolution == RES_12BITS)
        resolution_mask = INA219_CONFIG_BADCRES_12BIT | INA219_CONFIG_SADCRES_12BIT_1S_532US;
    else if (resolution == RES_11BITS)
        resolution_mask = INA219_CONFIG_BADCRES_11BIT | INA219_CONFIG_SADCRES_11BIT_1S_276US;
    else if (resolution == RES_10BITS)
        resolution_mask = INA219_CONFIG_BADCRES_10BIT | INA219_CONFIG_SADCRES_10BIT_1S_148US;
    else // resolution == RES_9BITS
        resolution_mask = INA219_CONFIG_BADCRES_9BIT | INA219_CONFIG_SADCRES_9BIT_1S_84US;
    if(_max_voltage < 16)
    {
        write_register_u16(INA219_REG_CONFIG, INA219_CONFIG_BVOLTAGERANGE_16V |
                           INA219_CONFIG_GAIN_8_320MV |
                           resolution_mask |
                           INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS);
    }
    else
    {
        write_register_u16(INA219_REG_CONFIG, INA219_CONFIG_BVOLTAGERANGE_32V |
                           INA219_CONFIG_GAIN_8_320MV |
                           resolution_mask |
                           INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS);
    }


    // Set current divider
    current_divider = 1 / current_lsb;
    power_divider = current_divider / 20;
    volt_gain = 4;
}
int16_t INA219::read_current_raw()
{
    return (int16_t)read_register_u16(INA219_REG_CURRENT);
}

float INA219::read_current_mA()
{
    float raw_current = read_current_raw();
    return raw_current / current_divider;
}
int16_t INA219::read_bus_voltage_raw()
{
  return (int16_t)read_register_u16(INA219_REG_BUSVOLTAGE)>>3;
}
float INA219::read_bus_voltage()
{
  float raw_volt = read_bus_voltage_raw();
  return raw_volt*volt_gain;
}
int16_t INA219::read_power_raw()
{
    return (int16_t)read_register_u16(INA219_REG_POWER);
}

float INA219::read_power_mW()
{
    float raw_power = read_power_raw();
    return raw_power / power_divider;
}
