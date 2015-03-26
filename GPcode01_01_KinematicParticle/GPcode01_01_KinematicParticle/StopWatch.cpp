#include "StopWatch.h"

CStopWatch::CStopWatch() {
#ifdef WIN32
	QueryPerformanceFrequency(&frequency);
	startCount.QuadPart = 0;
	endCount.QuadPart = 0;
#else
	startCount.tv_sec = startCount.tv_usec = 0;
	endCount.tv_sec = endCount.tv_usec = 0;
#endif
	startTimeInMicroSec = endTimeInMicroSec = 0.0;
}

void CStopWatch::start() {
#ifdef WIN32
	QueryPerformanceCounter(&startCount);
#else
	gettimeofday(&startCount, NULL);
#endif
}

void CStopWatch::stop() {
#ifdef WIN32
	QueryPerformanceCounter(&endCount);
#else
	gettimeofday(&endCount, NULL);
#endif
}

double CStopWatch::getElapsedTime(){
#ifdef WIN32
	startTimeInMicroSec = startCount.QuadPart * (1000000.0 / frequency.QuadPart);
	endTimeInMicroSec = endCount.QuadPart * (1000000.0 / frequency.QuadPart);
#else
	startTimeInMicroSec = (startCount.tv_sec * 1000000.0) + startCount.tv_usec;
	endTimeInMicroSec = (endCount.tv_sec * 1000000.0) + endCount.tv_usec;
#endif  
	return endTimeInMicroSec - startTimeInMicroSec;
}