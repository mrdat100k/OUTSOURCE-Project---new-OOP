/******************************************************************************
 * @file    INAReader.h
 * @author   Dua Nguyen
 * @brief    Configuration and Reading data from INA module, uses the hardware I2C
 * 	         available in the Maple to interact with I2C slave (INA module).
 * @date     Oct. 2017
 * @date modified 2017/10/13
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
 /*Use case
  *Name : Calibration
  *ID : 01
  *Description : when user want to change shunt resistor value, range current and voltage
  *              measurement to match with desiring range.
  *Actors : user
  *Triggers:  The user set measurement range
  *Main course :  1.The system reads  _shunt_value, _max_current, _max_voltage value
  *	              2. Changing calibration register value according to max current value and shunt resistor value.
  *		             3. choosing voltage range (16Volt or 32 Volt) from max voltage value
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
#ifndef LIB_INA_INAREADER_H_
#define LIB_INA_INAREADER_H_
#include <INA219.hpp>
#include <mbed.h>

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
 * // I2C address of INA219 = 0x40
 * INAReader measurement_object(I2C_SDA, I2C_SCL, 0x40);
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
    * Method: INAReader::INAReader
    * @brief: INAReader constructor
    * Description: initialized INAReader object
    * @param sda data pin of i2c communication
    * @param scl clock pin of i2c communication
    * @param addr INA219 i2c address
    * i2c permissive addresses:
    *    A1    |    A0    |    address
    *   GND    |   GND    |    0x40
    *   GND    |   Vs+    |    0x41
    *   Vs+    |   GND    |    0x44
    *   Vs+    |   GND    |    0x45
    * @param freq i2c frequency communication
    * @param res INA219 ADC resolution
    * Access: public
    * Returns:
    * Qualifier:
    ***********************************/
    INAReader(PinName sda, PinName scl, int addr = 0x40, int freq = 100000,
    resolution_t res = RES_12BITS):
    INA219(sda, scl, addr, freq, res) {
        /*throw an exception when user set a wrong address*/
        if ((0x40 != addr)&&(0x41 != addr)&&(0x44 != addr)&&(0x45 !=addr)) {
            throw "exception - unavailable address!";
        } else {
             /*do nothing*/
        }
        volt = 0;
        curr = 0;
        power = 0;
        max_current = 0;
        max_voltage = 0;
    }

    /************************************
    * Method: INAReader::Calibrate
    * Description: Calibrating INA219 according to shunt resistor value, max current value, max voltage value
    * @brief: INA219 Calibration
    * @param _shunt_value shunt resistor value
    * @param _max_current max current value that is set by user
    * @param _max_voltage max voltage value that is set by user
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
    void Calibrate(float _shunt_value, float _max_current, float _max_voltage);
    /*
    *Reading voltage value, current value and power value from INA module
    *Exceptions: 1.when measurement value out of permissive range. the display always show max value
    *@TODO show to user a notification by a text on LCD
    */
    void Scan();
    float GetVolt();
    float GetCurr();
    float GetPower();

 protected:
   /**
   *@brief
   *@param volt Voltage value is read from INA module
           This will depend on bus voltage (V+ pin) of INA219
   *@param curr Current value is read from INA module
           This will depend on current through the shunt resistor
   *@param power Power value of PV that is measured by INA module
   *@param max_current the maximum of current set by operator
   *@param max_voltage the maximum of voltage set by operator
   *@param current_lsb the minimum current value that INA219 can sense in mA, to calculate the actual current value
   *@param voltage_lsb the minimum voltage value that INA219 can sense in mV, to calculate the actual voltage value
   *@param power_lsb  the minimum power value that INA219 can sense in mW, to calculate the actual power value
   */
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
#endif /*LIB_INA_INAREADER_H_*/
