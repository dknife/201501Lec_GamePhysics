#ifndef _STOPWATCH_YMKANG_H
#define _STOPWATCH_YMKANG_H

#ifdef WIN32   // Windows system specific
#include <windows.h>
#else          // Unix based system specific
#include <sys/time.h>
#endif

class StopWatch {
#ifdef WIN32
    LARGE_INTEGER frequency;                    // ticks per second
    LARGE_INTEGER startCount;                   //
    LARGE_INTEGER endCount;                     //
#else
    timeval startCount;                         //
    timeval endCount;                           //
#endif
	double startTimeInMicroSec;
    double endTimeInMicroSec;
public:
	StopWatch();
	void start();				// start StopWatch and record time to "startCount"
	void stop();				// stop StopWatch and record time to "endCount"
	double getElapsedTime();    // return the elapsed time at the last stop since the last start (microsec)
};

#endif