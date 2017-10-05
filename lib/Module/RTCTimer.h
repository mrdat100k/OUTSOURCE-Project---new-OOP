/*!
 * \file RTCTimer.h
 * \summary file chứa lớp đối tượng đồng hồ thời gian thực
 * 
 * \author
 *
 * \date October 2017
 *
 *
 */
#ifndef _RTCTIMER_H_
#define _RTCTIMER_H_
#include <mbed.h>
class RTC_Timer{
public:
	/*Constructor khởi tạo đối tượng đồng hồ thời gian thực*/
	RTC_Timer() :timer_state(false), second(0), minute(0), hour(0), day(0){
        set_time(0);
	}
<<<<<<< HEAD
	/*Phương thức reset đồng hồ*/
=======

	/*
	Reset timer
	*/
>>>>>>> d0462c14f9039c6e9bfa754c894ef2ebecdd70bf
	void Reset(){
		timer_state = true;
		set_time(0);
		second = 0;
		minute = 0;
		hour = 0;
		day = 0;
	}

	void Off(){
		timer_state = false;
	}

	void On(){
		timer_state = true;
	}
	void ChangeState()
	{
		timer_state = !timer_state;
	}

	bool GetState(){
		return timer_state;
	}
	void Update(){
			/* Update timer*/
			seconds = time(NULL); /*TODO: bo sung header cho ham time */
			second = seconds % 60;
			minute = seconds % 3600 / 60;
			hour = seconds % 86400 / 3600;
	}

	int GetSecond(){
		return second;
	}

	int GetMinute(){
		return minute;
	}

	int GetHour(){
		return hour;
	}
	uint32_t GetSecond_s()
	{
		return time(NULL);
	}




private:
	bool timer_state;
	uint8_t second, minute, hour, day;
	uint32_t seconds;

};
#endif /*_RTCTIMER_H_*/
