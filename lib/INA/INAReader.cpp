/******************************************************************************
 * @file    INAReader.cpp
 * @author   Dua Nguyen
 * @brief   Contains IO Pins map using for the demo
 * @date     Oct. 2017
 * @date modified 2017/10/13
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
#include "INAReader.h"
    /************************************
    * Method: INAReader::Calibrate
    * Description: Calibrating INA219 according to shunt resistor value, max current value, max voltage value
    * @brief: INA219 Calibration
    * @param _shunt_value shunt resistor value
    * @param _max_current max current value that is set by user
    * @param _max_voltage max voltage value that is set by user
    *        _max_voltage must be 16V or 32V.
    * Access: public
    * Returns:
    * Qualifier:
    * @Date modified 2017/10/13
    * @author Dua Nguyen
    * Exceptions:
    * 1. Setting max current value or max voltage value out of range
    *  Max current value of system equal 320/(shunt resistor value) mA
    *  Max current value (unit: Ampere) set by user have to in persissive range ( smaller than max current  of system)
    * @TODO show a notification for user when user compile
    ***********************************/
void INAReader::Calibrate(float _shunt_value, float _max_current, float _max_voltage) {
    /*throw an exception when _max_voltage value is not 16V or 32V*/
    /*INA219 just allow set two max voltage values. threre are 16 volt and 32 volt*/
    if ((16 != _max_voltage)&&(32 != _max_voltage)) {
        throw "exception - max voltage must be 16V or 32V";
    } else {
        /*do nothing*/
    }
    /*throw an exception when _max_current exceed the bounds of INA219 */
    /*max shunt drop voltage is 320mV */
    if ((_max_current * _shunt_value) >= 0.32) {
        throw "exception - max current exceed the bounds of the device!";
    } else {
        /*do nothing*/
    }
    uint16_t calibrating_value;
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
    else  /* resolution == RES_9BITS*/
        resolution_mask = INA219_CONFIG_BADCRES_9BIT | INA219_CONFIG_SADCRES_9BIT_1S_84US;
    if (_max_voltage < 16) {
        write_register_u16(INA219_REG_CONFIG, INA219_CONFIG_BVOLTAGERANGE_16V |
                           INA219_CONFIG_GAIN_8_320MV |
                           resolution_mask |
                           INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS);
    } else {
        write_register_u16(INA219_REG_CONFIG, INA219_CONFIG_BVOLTAGERANGE_32V |
                           INA219_CONFIG_GAIN_8_320MV |
                           resolution_mask |
                           INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS);
    }
    /* Set power_lsb */
    power_lsb = 20* current_lsb;
    voltage_lsb = 4;
    max_current = _max_current;
    max_voltage = _max_voltage;
}
    /** Reads the current raw value of current from the INA219.
    *
    *  @see read_current_mA
    *
    *  @returns
    *      A value between -32768 and +32768. Depending on the current calibration and configuration register values, the corresponding current can be calculated.
    */
    int16_t INAReader::read_current_raw() {
         return (int16_t)read_register_u16(INA219_REG_CURRENT);
    }
    /** Reads the current from the INA219 and calculates the actual value in mA.
    *
    *  @see read_current_raw
    *
    *  @returns
    *      A floating point value corresponding to the current flowing through the current shunt, in mA.
    */
float INAReader::read_current_mA() {
    float raw_current = read_current_raw();
    return raw_current * current_lsb;
}
    /** Reads the raw power value from the INA219.
    *
    *  @see read_power_mW
    *
    *  @returns
    *      A value between -32768 and +32768. Depending on the calibration and configuration register values, the actual power can be calculated.
    */
int16_t INAReader::read_power_raw() {
    return (int16_t)read_register_u16(INA219_REG_POWER);
}
    /** Reads the power from the INA219 and calculates the actual value in mW.
    *
    *  @see read_power_raw
    *
    *  @returns
    *      A floating point value corresponding to the power being used in the circuit, in mW.
    */
float INAReader::read_power_mW() {
    float raw_power = read_power_raw();
    return raw_power * power_lsb;
}
    /** Reads the raw bus voltage.
    *
    *  @see read_bus_voltage
    *
    *  @returns
    *      A value between -32768 and +32768 corresponding to the bus voltage.
    */
int16_t INAReader::read_bus_voltage_raw() {
    return (int16_t)read_register_u16(INA219_REG_BUSVOLTAGE)>>3;
}
    /** Reads the bus voltage and uses it to calculate the actual bus voltage.
    *
    *  @see read_bus_voltage_raw
    *
    *  @returns
    *      A floating point value corresponding to the voltage of V+ (in V).
    */
float INAReader::read_bus_voltage() {
    float raw_volt = read_bus_voltage_raw();
    return raw_volt * voltage_lsb;
}
    /************************************
    * Method:    INAReader::Scan
    * Description:     Reading current value, voltage value, energy value form INA module
    * Access:    public
    * Returns:
    * Qualifier:
    ***********************************/
void INAReader::Scan() {
    volt = read_bus_voltage();
    curr = read_current_mA();
    power = read_power_mW();
    if ( volt >= max_voltage ) {
        voltage_out_of_range = true;
    } else {
        voltage_out_of_range = false;
    }
    if ( curr >= max_current ) {
        current_out_of_range = true;
    } else {
        current_out_of_range = false;
    }
}
    /************************************
    * Method:    INAReader::GetPVVolt
    * Description:    Reading PV voltage value
    * Access:    public
    * Returns:    voltage
    * Qualifier:
    ***********************************/
float INAReader::GetVolt() {
    return volt;
}
    /************************************
    * Method:    INAReader::GetPVCurr
    * Description:    Reading PV current value
    * Access:    public
    * Returns:   current
    * Qualifier:
    ***********************************/
float INAReader::GetCurr() {
    return curr;
}
    /************************************
    * Method:    INAReader::GetPVPower
    * Description:    Reading PV current value
    * Access:    public
    * Returns:    power
    * Qualifier:
    ***********************************/
float INAReader::GetPower() {
    return power;
}

bool TestINAReader::Get_voltage_out_of_range() {
    return voltage_out_of_range;
}
bool TestINAReader::Get_current_out_of_range() {
    return current_out_of_range;
}
void TestINAReader::SetVolt(float value) {
    volt = value;
}
void TestINAReader::SetCurr(float value) {
    curr = value;
}
void TestINAReader::TestScanning() {
    if ( volt >= max_voltage ) {
        voltage_out_of_range = true;
    } else {
        voltage_out_of_range = false;
    }
    if ( curr >= max_current ) {
        current_out_of_range = true;
    } else {
        current_out_of_range = false;
    }
}
