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
    //************************************
    //@brief Construct a new INAReader instance.
    // Method:    INAReader::INAReader
    // Description:   INAReader constructor
    // Access:    public
    // Returns:
    // Qualifier:
    //***********************************
    INAReader(INA219* batt_INA_ptr, INA219* pv_INA_ptr)
    {
        INA_batmeasure_object_ptr = batt_INA_ptr;
        INA_pvmeasure_object_ptr = pv_INA_ptr;
	Calibration();
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
    /*
    Adjust measurement range
    */
void Calibration();
    /*
    Reading voltage value and current value from INA module
    */
    void Scan();
    float getBattVolt();
    float getBattCurr();
    float getBattPower();
    float getPVVolt();
    float getPVCurr();
    float getPVPower();
private:
    INA219* INA_batmeasure_object_ptr;
    INA219* INA_pvmeasure_object_ptr;
    float pv_volt;
    float pv_curr;
    float pv_power;
    float battery_volt;
    float battery_curr;
    float battery_power;
};
    //************************************
    // Method:    INAReader::Calibration
    // Description:  Adjust measurement range 
    // Access:    public
    // Returns: 
    // Qualifier: 
    //***********************************
void INAReader::Calibration()
{
    INA_batmeasure_object_ptr -> calibrate_32v_3200mA();
    INA_pvmeasure_object_ptr -> calibrate_32v_3200mA();
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
    pv_volt = INA_pvmeasure_object_ptr -> read_bus_voltage();
    pv_curr = INA_pvmeasure_object_ptr -> read_current_mA();
    pv_power = INA_pvmeasure_object_ptr -> read_power_mW();
    battery_volt = INA_batmeasure_object_ptr -> read_bus_voltage();
    battery_curr = INA_batmeasure_object_ptr -> read_current_mA();
    battery_power = INA_batmeasure_object_ptr -> read_power_mW();
}
    //************************************
    // Method:    INAReader::getBattVolt
    // Description:    Reading battery voltage value
    // Access:    public
    // Returns:    battery_volt
    // Qualifier:
    //***********************************
float INAReader::getBattVolt()
{
    return battery_volt;
}
    //************************************
    // Method:    INAReader::getBattCurr
    // Description:     Reading battery current value
    // Access:    public
    // Returns:    battery_curr
    // Qualifier:
    //***********************************
float INAReader::getBattCurr()
{
    return battery_curr;
}
    //************************************
    // Method:    INAReader::getBattPower
    // Description:    Reading battery energy value
    // Access:    public
    // Returns:    battery_power
    // Qualifier:
    //***********************************
float INAReader::getBattPower()
{
    return battery_power;
}
    //************************************
    // Method:    INAReader::getPVVolt
    // Description:    Reading PV voltage value
    // Access:    public
    // Returns:    pv_volt
    // Qualifier:
    //***********************************
float INAReader::getPVVolt()
{
    return pv_volt;
}
    //************************************
    // Method:    INAReader::getPVCurr
    // Description:    Reading PV current value
    // Access:    public
    // Returns:    pv_curr
    // Qualifier:
    //***********************************
float INAReader::getPVCurr()
{
    return pv_curr;
}
    //************************************
    // Method:    INAReader::getPVPower
    // Description:    Reading PV current value
    // Access:    public
    // Returns: pv_power
    // Qualifier:
    //***********************************
float INAReader::getPVPower()
{
    return pv_power;
}
#endif /*_INAREADER_H_*/
