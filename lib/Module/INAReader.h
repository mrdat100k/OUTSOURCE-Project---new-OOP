/*!
 * \file INAReader.h
 * \summary file lớp đối tượng cảm biến đo dòng
 * \
 * \author
 *
 * \date October 2017
 *
 *
 */
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
    //***********************************
    INAReader(INA219* batt_INA_ptr, INA219* pv_INA_ptr)
    {
        INA_batmeasure_object_ptr = batt_INA_ptr;
        INA_pvmeasure_object_ptr = pv_INA_ptr;
        Calibration();
    }
    /*
    hiệu chỉnh lại dải đo cảm biến
    */
    void Calibration();
    /*
    Hàm cập nhật giá trị đo từ cảm biến vào đối tượng
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
    // Description:  phương thức hiệu chỉnh thang đo cảm biến
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
    // Description:  phương thức cập nhật giá trị đo từ cảm biến về đối tượng
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
    // Description: lấy giá trị điện áp pin
    // Access:    public
    // Returns: battery_volt
    // Qualifier:
    //***********************************
float INAReader::getBattVolt()
    {
        return battery_volt;
    }
    //************************************
    // Method:    INAReader::getBattCurr
    // Description: lấy giá trị dòng điện vào pin
    // Access:    public
    // Returns: battery_curr
    // Qualifier:
    //***********************************
float INAReader::getBattCurr()
    {
        return battery_curr;
    }
    //************************************
    // Method:    INAReader::getBattPower
    // Description: lấy giá trị công suất sạc pin
    // Access:    public
    // Returns: battery_power
    // Qualifier:
    //***********************************
float INAReader::getBattPower()
    {
        return battery_power;
    }
    //************************************
    // Method:    INAReader::getPVVolt
    // Description: lấy giá trị điện áp PV
    // Access:    public
    // Returns: pv_volt
    // Qualifier:
    //***********************************
float INAReader::getPVVolt()
    {
        return pv_volt;
    }
    //************************************
    // Method:    INAReader::getPVCurr
    // Description: lấy giá trị dòng điện qua PV
    // Access:    public
    // Returns: pv_curr
    // Qualifier:
    //***********************************
float INAReader::getPVCurr()
    {
        return pv_curr;
    }
    //************************************
    // Method:    INAReader::getPVPower
    // Description: lấy giá trị công suất PV
    // Access:    public
    // Returns: pv_power
    // Qualifier:
    //***********************************
float INAReader::getPVPower()
    {
        return pv_power;
    }
#endif /*_INAREADER_H_*/
