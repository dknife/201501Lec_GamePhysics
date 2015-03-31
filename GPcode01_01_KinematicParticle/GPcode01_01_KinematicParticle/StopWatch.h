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

#ifdef WIN32
typedef LARGE_INTEGER _timeCountType;
#else
typedef timeval _timeCountType;
#endif

class CStopWatch {
    bool bStarted;
    bool bPaused;
    
#ifdef WIN32
	_timeCountType frequency; // ticks per seconds (required only on Windows)
#endif
	_timeCountType startCount;
	_timeCountType endCount;
    _timeCountType checkCount;
    _timeCountType tempCount;
    _timeCountType pauseStart;
    _timeCountType pauseEnd;
    
    void    getCurrentTime(_timeCountType* timeData);
    double  diffTimeInMicroSec(_timeCountType timePre, _timeCountType timeNext);
    void    addMicroSeconds(_timeCountType* orgTime, double timeToBeAddedInMicroSec);
    
    void initTime();
    
    // public methods
public:
	CStopWatch();
	void start();       // start StopWatch
    void stop();        // stops StopWatch
    void pause();
    void resume();
    
    // time checking
    double checkAndComputeDT();     // check time and returns the "delta time" since the previous time check (in microsec)
	double getTotalElapsedTime();   // return the total elapsed time since the StopWatch started (in microsec)
};

#endif