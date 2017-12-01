/******************************************************************************
 * @file    PowerOnSelfTest.h
 * @author   Dua Nguyen
 * @TODO: dịch cái này
 * @brief    Quản lý POST của các ngoại vi, đưa ra thông báo cho người dùng
 * qua cổng truyền nối tiếp và trả về một xâu kí tự để hiển thị trên lcd.
 * @date     Nov. 2017
 * @date modified 2017/11/25
 * @version 1.0.0
 * Copyright(C) 2017
 * All rights reserved.
 *
 *****************************************************************************/
#ifndef LIB_POST_POWERONSELFTEST_H_
#define LIB_POST_POWERONSELFTEST_H_
/** Class: PowerOnSelfTest
 *  A class handles all hardware power on self test
 * Example:
 * @code
 * @TODO: update
 * @endcode
 */
class PowerOnSelfTest {
protected:
    bool POST_result;
public:
    /************************************
     * Method:  PowerOnSelfTest::PowerOnSelfTest
     * @brief: PowerOnSelfTest constructor
     * Access: public
     * Returns:
     * Qualifier:
     * @TODO <nothing>
    ***********************************/
    PowerOnSelfTest ();
    /*PowerOnSelfTest destructor*/
    ~PowerOnSelfTest ();
    /** @brief: handle power on self test for ina219 (push notification)
     *  @param: value - a boolean argument pass or false the test
     *  @return: a noti string to display on lcd.
     */
    const char* POST_INA219(bool value);
    /** @brief: handle power on self test for SD Card (push notification)
     *  @param: value - a boolean argument pass or false the test
     *  @return: a noti string to display on lcd.
     */
    const char* POST_SDCard(bool value);
    /** @brief: handle power on self test for IO Expander (push notification)
     *  @param: value - a boolean argument pass or false the test
     *  @return: a noti string to display on lcd.
     */
    const char* POST_IOExpander(bool value);
    bool GetResult();
};
#endif /*LIB_POST_POWERONSELFTEST_H_*/
