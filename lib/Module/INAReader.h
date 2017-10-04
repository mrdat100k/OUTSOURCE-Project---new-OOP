#ifndef _INAREADER_H_
#define _INAREADER_H_
#include <var.h>
class INAReader{
public:
	//************************************
	// Method:    INAReader::INAReader
	// Description:  INAReader constructor
	// Access:    public
	// Returns:
	// Qualifier:
	//************************************
	INAReader(INA219* batt_INA_ptr, INA219* pv_INA_ptr)
	{
      INA_batmeasure_object_ptr = batt_INA_ptr;
      INA_pvmeasure_object_ptr = pv_INA_ptr;
			Calibration();
	}
	void Calibration();
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
void INAReader::Calibration()
    {
	      INA_batmeasure_object_ptr -> calibrate_32v_3200mA();
		    INA_pvmeasure_object_ptr -> calibrate_32v_3200mA();
    }
void INAReader::Scan()
    {
		pv_volt = INA_pvmeasure_object_ptr -> read_bus_voltage();
		pv_curr = INA_pvmeasure_object_ptr -> read_current_mA();
		pv_power = INA_pvmeasure_object_ptr -> read_power_mW();
		battery_volt = INA_batmeasure_object_ptr -> read_bus_voltage();
		battery_curr = INA_batmeasure_object_ptr -> read_current_mA();
		battery_power = INA_batmeasure_object_ptr -> read_power_mW();
	}
float INAReader::getBattVolt()
    {
		return battery_volt;
	}
float INAReader::getBattCurr()
    {
		return battery_curr;
	}
float INAReader::getBattPower()
    {
		return battery_power;
	}
float INAReader::getPVVolt()
    {
		return pv_volt;
	}
float INAReader::getPVCurr()
    {
		return pv_curr;
	}
float INAReader::getPVPower()
    {
		return pv_power;
	}
	#endif /*_INAREADER_H_*/
