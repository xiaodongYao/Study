#pragma once
//////////////////////////////////////////////////////////////////////////////
// Timer.h
// =======
// High Resolution Timer.
// This timer is able to measure the elapsed time with 1 micro-second accuracy in both Windows, Linux and Unix system 
// 此计时器能够在 Windows、Linux 和 Unix 系统中以 1 微秒的精度测量经过的时间 
//  AUTHOR: Yao xiao dong
// CREATED: 2025-02-12
//
// Copyright (c) 2025 yao xiao dong
//////////////////////////////////////////////////////////////////////////////

#include <windows.h>

class Timer
{
public:
	Timer();									// default constructor
	~Timer();									// default destructor	

	void start();								// start timer
	void stop();								// stop the timer

	double getElapsedTime();					// get elapsed time in second
	double getElapsedTimeInSec();				// get elapsed time in second (same as getElapsedTime)
	double getElapsedTimeInMilliSec();			// get elapsed time in milli-second
	double getElapsedTimeInMicroSec();			// get elapsed time in micro-second

protected:


private:

	double startTimeInMicroSec;				// starting time in micro-second
	double endTimeInMicroSec;				// ending time in micro-second
	int stopped;							// stop flag

	//LARGE_INTEGER 是 Windows 编程中用于表示 64 位有符号整数的联合体类型，常用于高精度计时、文件操作和大整数计算等场景。
	// 通过 LowPart、HighPart 和 QuadPart，可以灵活地访问 64 位整数的不同部分。
	LARGE_INTEGER frequency;				// ticks per second
	LARGE_INTEGER startCount;				// starting count
	LARGE_INTEGER endCount;					// ending count
};