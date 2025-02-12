#pragma once
//////////////////////////////////////////////////////////////////////////////
// Timer.h
// =======
// High Resolution Timer.
// This timer is able to measure the elapsed time with 1 micro-second accuracy in both Windows, Linux and Unix system 
// �˼�ʱ���ܹ��� Windows��Linux �� Unix ϵͳ���� 1 ΢��ľ��Ȳ���������ʱ�� 
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

	//LARGE_INTEGER �� Windows ��������ڱ�ʾ 64 λ�з������������������ͣ������ڸ߾��ȼ�ʱ���ļ������ʹ���������ȳ�����
	// ͨ�� LowPart��HighPart �� QuadPart���������ط��� 64 λ�����Ĳ�ͬ���֡�
	LARGE_INTEGER frequency;				// ticks per second
	LARGE_INTEGER startCount;				// starting count
	LARGE_INTEGER endCount;					// ending count
};