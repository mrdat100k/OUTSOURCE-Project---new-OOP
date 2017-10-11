/******************************************************************************
 * @file    INAReader.h
 * @author
 * @brief    Configuration and Reading data from INA module, uses the hardware I2C 
 * 	     available in the Maple to interact with I2C slave (INA module).
 * @date     Oct. 2017
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/

#ifndef _INAREADER_H_
#define _INAREADER_H_
#include <INA219.hpp>
 
/* Class for configuration and Reading data from INA module
 * If this source file built with example, the <mbed.h> and <INAReader> library 
 * must be included
 */
/*
 * Example:
 * @code
 * calibration, reading current, voltage and power
 * #include <mbed.h>
 * #include <INAReader>
 * INAReader measurement_object;
 *
 * int main() {
 *     float volt_mV;
 *     float curr_mA;
 *     float power_mW;
 *     //calibrating with shunt resistor 0.1 ohm, max current 3.2A, max voltage 16V
 *     measurement_object.calibrate(0.1, 3.2, 16);
 *     while(1) {
 *          measurement_object.Scan();
 *          if(measurement_object.current_out_of_range == true)
 *          {
 *              printf("current out of range!!!");
 *          }
 *          else
 *          {
 *              curr_mA = measurement_object.GetCurr();
 *          }
 *          if(measurement_object.voltage_out_of_range == true)
 *          {
 *              printf("voltage out of range!!!")
 *          }
 *          else
 *          {
 *          volt_mV = measurement_object.GetVolt();
 *          }
 *          power_mW = measurement_object.GetPower();
 *         }
 *     }
 * }
 * @endcode
 * @ingroup module
 */
class INAReader: private INA219{
public:
    /**
    *@param current_out_of_range alarm when current out of range
    *@param voltage_out_of_range alarm when voltage out of range
    */
    bool current_out_of_range;
    bool voltage_out_of_range;
    /************************************
    * @brief Construct a new INAReader instance.
    * Method:    INAReader::INAReader
    * Description:   INAReader constructor
    * Access:    public
    * Returns:
    * Qualifier:
    /***********************************
    INAReader(PinName sda, PinName scl, int addr=0x40, int freq=100000, resolution_t res=RES_12BITS):
    INA219(sda, scl, addr, freq, res)
    {
        volt = 0;
        curr = 0;
        power = 0;
        max_current = 0;
        max_voltage = 0;
    }
    /**
    *@brief
    *@param pv_volt PV Voltage value is read from INA module
	            This will depend on voltage input from PV
    *@param pv_curr PV Current value is read from INA module
	            This will depend on current input from PV
    *@param pv_power Power value of PV that is measured by INA module
    *@param battery_volt batterry Voltage value  is read from INA module
	             This will depend on batterry voltage
    *@param battery_curr batterry Current value is read from INA module
	             This will depend on batterry current
    *@param battery_power Batterry power value is measured by INA module
    */
    /*
    Adjust measurement range
    */
    void Calibrate(float _shunt_value, float _max_current, float _max_voltage);
    /*
    Reading voltage value and current value from INA module
    */
    void Scan();
    float GetVolt();
    float GetCurr();
    float GetPower();
private:
    float volt;
    float curr;
    float power;
    float max_current;
    float max_voltage;
    float current_lsb;
    float power_lsb;
    float voltage_lsb;
    /** Reads the current raw value of current from the INA219.
     *
     *  @see read_current_mA
     *
     *  @returns
     *      A value between -32768 and +32768. Depending on the current calibration and configuration register values, the corresponding current can be calculated.
     */
    int16_t read_current_raw();
    /** Reads the current from the INA219 and calculates the actual value in mA.
     *
     *  @see read_current_raw
     *
     *  @returns
     *      A floating point value corresponding to the current flowing through the current shunt, in mA.
     */
    float read_current_mA();

    /** Reads the raw power value from the INA219.
     *
     *  @see read_power_mW
     *
     *  @returns
     *      A value between -32768 and +32768. Depending on the calibration and configuration register values, the actual power can be calculated.
     */
    int16_t read_power_raw();
    /** Reads the power from the INA219 and calculates the actual value in mW.
     *
     *  @see read_power_raw
     *
     *  @returns
     *      A floating point value corresponding to the power being used in the circuit, in mW.
     */
    float read_power_mW();
    /** Reads the raw bus voltage.
     *
     *  @see read_bus_voltage
     *
     *  @returns
     *      A value between -32768 and +32768 corresponding to the bus voltage.
     */
    int16_t read_bus_voltage_raw();
    /** Reads the bus voltage and uses it to calculate the actual bus voltage.
     *
     *  @see read_bus_voltage_raw
     *
     *  @returns
     *      A floating point value corresponding to the voltage of V+ (in V).
     */
    float read_bus_voltage();

};
    //************************************
    // Method:    INAReader::Calibration
    // Description:  Adjust measurement range
    // Access:    public
    // Returns:
    // Qualifier:
    //***********************************
void INAReader::Calibrate(float _shunt_value, float _max_current, float _max_voltage)
{
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
int16_t INAReader::read_current_raw()
{
    return (int16_t)read_register_u16(INA219_REG_CURRENT);
}
/** Reads the current from the INA219 and calculates the actual value in mA.
 *
 *  @see read_current_raw
 *
 *  @returns
 *      A floating point value corresponding to the current flowing through the current shunt, in mA.
 */
float INAReader::read_current_mA()
{
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
int16_t INAReader::read_power_raw()
{
    return (int16_t)read_register_u16(INA219_REG_POWER);
}
/** Reads the power from the INA219 and calculates the actual value in mW.
 *
 *  @see read_power_raw
 *
 *  @returns
 *      A floating point value corresponding to the power being used in the circuit, in mW.
 */
float INAReader::read_power_mW()
{
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
int16_t INAReader::read_bus_voltage_raw()
{
    return (int16_t)read_register_u16(INA219_REG_BUSVOLTAGE)>>3;
}
/** Reads the bus voltage and uses it to calculate the actual bus voltage.
 *
 *  @see read_bus_voltage_raw
 *
 *  @returns
 *      A floating point value corresponding to the voltage of V+ (in V).
 */
float INAReader::read_bus_voltage()
{
    float raw_volt = read_bus_voltage_raw();
    return raw_volt * voltage_lsb;
}
   /************************************
    * Method:    INAReader::Scan
    * Description:     Reading current value, voltage value, energy value form INA module
    * Access:    public
    * Returns:
    * Qualifier:
    /***********************************
void INAReader::Scan()
{
    volt = read_bus_voltage();
    curr = read_current_mA();
    power = read_power_mW();
    if ( volt >= max_voltage )
    {
        voltage_out_of_range = true;
    }
    else
    {
        voltage_out_of_range = false;
    }
    if ( curr >= max_current )
    {
        current_out_of_range = true;
    }
    else
    {
        current_out_of_range = false;
    }
}

   /************************************
    * Method:    INAReader::GetPVVolt
    * Description:    Reading PV voltage value
    * Access:    public
    * Returns:    pv_volt
    * Qualifier:
    /***********************************
float INAReader::GetVolt()
{
    return volt;
}
   /************************************
    * Method:    INAReader::GetPVCurr
    * Description:    Reading PV current value
    * Access:    public
    * Returns:    pv_curr
    * Qualifier:
    /***********************************
float INAReader::GetCurr()
{
    return curr;
}
   /************************************
    * Method:    INAReader::GetPVPower
    * Description:    Reading PV current value
    * Access:    public
    * Returns: pv_power
    * Qualifier:
    /***********************************
float INAReader::GetPower()
{
    return power;
}
#endif /*_INAREADER_H_*/

/*Use case
 *Name : Calibration 
 *ID : 01
 *Description : when user want to change shunt resistor value, range current and voltage   
 *              measurement to match with desiring range.
 *Actors : user  
 *Triggers:  The user set measurement range 
 *Main course :  1.The system reads  _shunt_value, _max_current, _max_voltage value
 *	         2. Changing calibration register value according to max current value and shunt resistor value.
 *		 3. choosing voltage range (16Volt or 32 Volt) from max voltage value
 *Exceptions:  _shunt_value, _max_current value or _max_voltage value is out of permissive range.
 */
/*Use case
 *Name : Getting current value, voltage value and power value
 *ID : 02
 *Description : User wanna get current value, voltage value and power value from the INA219 module 
 *Actors : user  
 *Triggers:  The user call the function 
 *Main course :  The system reads  _shunt_value, _max_current, _max_voltage value
 *		 from corresponding register of INA219.
*Exceptions:  INA219 module is not connected.
*/


