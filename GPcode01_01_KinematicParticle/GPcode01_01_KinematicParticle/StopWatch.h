#ifndef _STOPWATCH_YMKANG_H
#define _STOPWATCH_YMKANG_H

////////////////////////////////
//
// StopWatch for Measuring Time
//
// Young-Min Kang
// Tongmyong University

#ifdef WIN32   // Windows system specific
#include <windows.h>
#else          // Unix based system specific
#include <sys/time.h>
#endif

class CStopWatch {
#ifdef WIN32
	LARGE_INTEGER frequency;
	LARGE_INTEGER startCount;
	LARGE_INTEGER endCount;
#else
	timeval startCount;
	timeval endCount;
#endif
	double startTimeInMicroSec;
	double endTimeInMicroSec;
public:
	CStopWatch();
	void start();       // start StopWatch and record time to "startCount"
	void stop();        // stop StopWatch and record time to "endCount"
	double getElapsedTime();// return the elapsed time at the last stop since the last start (microsec)
};

#endif