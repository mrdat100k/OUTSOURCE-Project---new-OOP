/******************************************************************************
 *
 * Copyright (c) October 2017,
 *
 *
 *****************************************************************************/
/**
 * @file INAReader.h
 * @author
 * @brief Configuration and Reading data from INA module, uses the hadware I2C available
 * 	  in the Maple to interact with I2C slave (INA module).
 */
/*
 * Library created to use with ARM cores.
 * users easy interaction with the I2C Hardware in a familiar method.
 */

#ifndef _INAREADER_H_
#define _INAREADER_H_
#include <var.h>
/** Class for configuration and Reading data from INA module  */
class INAReader{
public:
    /**
    *@param current_out_of_range alarm when current out of range
    *@param voltage_out_of_range alarm when voltage out of range
    */
    bool current_out_of_range;
    bool voltage_out_of_range;
    //************************************
    //@brief Construct a new INAReader instance.
    // Method:    INAReader::INAReader
    // Description:   INAReader constructor
    // Access:    public
    // Returns:
    // Qualifier:
    //***********************************
    INAReader(INA219* _bat_ina_ptr, INA219* _pv_ina_ptr)
    {
        ina_batmeasure_object_ptr = _bat_ina_ptr;
        ina_pvmeasure_object_ptr = _pv_ina_ptr;
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
    void Calibration(float _shunt_value, float _max_current, float _max_voltage);
    /*
    Reading voltage value and current value from INA module
    */
    void Scan();
    float GetBattVolt();
    float GetBattCurr();
    float GetBattPower();
    float GetPVVolt();
    float GetPVCurr();
    float GetPVPower();
private:
    INA219* ina_batmeasure_object_ptr;
    INA219* ina_pvmeasure_object_ptr;
    float pv_volt;
    float pv_curr;
    float pv_power;
    float battery_volt;
    float battery_curr;
    float battery_power;
    float max_current;
    float max_voltage;

};
    //************************************
    // Method:    INAReader::Calibration
    // Description:  Adjust measurement range
    // Access:    public
    // Returns:
    // Qualifier:
    //***********************************
void INAReader::Calibration(float _shunt_value, float _max_current, float _max_voltage)
{
    ina_batmeasure_object_ptr -> calibrate(_shunt_value, _max_current, _max_voltage);
    ina_pvmeasure_object_ptr -> calibrate(_shunt_value, _max_current, _max_voltage);
    max_current = _max_current;
    max_voltage = _max_voltage;
}
    //************************************
    // Method:    INAReader::Scan
    // Description:     Reading current value, voltage value, energy value form INA module
    // Access:    public
    // Returns:
    // Qualifier:
    //***********************************
void INAReader::Scan()
{
    pv_volt = ina_pvmeasure_object_ptr -> read_bus_voltage();
    pv_curr = ina_pvmeasure_object_ptr -> read_current_mA();
    pv_power = ina_pvmeasure_object_ptr -> read_power_mW();
    battery_volt = ina_batmeasure_object_ptr -> read_bus_voltage();
    battery_curr = ina_batmeasure_object_ptr -> read_current_mA();
    battery_power = ina_batmeasure_object_ptr -> read_power_mW();
    if( (pv_volt >= max_voltage) || (battery_volt >= max_voltage) )
    {
        voltage_out_of_range = true;
    }
    else
    {
        voltage_out_of_range = false;
    }
    if( (pv_curr >= max_current) || (battery_curr >= max_current) )
    {
        current_out_of_range = true;
    }
    else
    {
        current_out_of_range = false;
    }
}
    //************************************
    // Method:    INAReader::GetBattVolt
    // Description:    Reading battery voltage value
    // Access:    public
    // Returns:    battery_volt
    // Qualifier:
    //***********************************
float INAReader::GetBattVolt()
{
    return battery_volt;
}
    //************************************
    // Method:    INAReader::GetBattCurr
    // Description:     Reading battery current value
    // Access:    public
    // Returns:    battery_curr
    // Qualifier:
    //***********************************
float INAReader::GetBattCurr()
{
    return battery_curr;
}
    //************************************
    // Method:    INAReader::GetBattPower
    // Description:    Reading battery energy value
    // Access:    public
    // Returns:    battery_power
    // Qualifier:
    //***********************************
float INAReader::GetBattPower()
{
    return battery_power;
}
    //************************************
    // Method:    INAReader::GetPVVolt
    // Description:    Reading PV voltage value
    // Access:    public
    // Returns:    pv_volt
    // Qualifier:
    //***********************************
float INAReader::GetPVVolt()
{
    return pv_volt;
}
    //************************************
    // Method:    INAReader::GetPVCurr
    // Description:    Reading PV current value
    // Access:    public
    // Returns:    pv_curr
    // Qualifier:
    //***********************************
float INAReader::GetPVCurr()
{
    return pv_curr;
}
    //************************************
    // Method:    INAReader::GetPVPower
    // Description:    Reading PV current value
    // Access:    public
    // Returns: pv_power
    // Qualifier:
    //***********************************
float INAReader::GetPVPower()
{
    return pv_power;
}
#endif /*_INAREADER_H_*/
