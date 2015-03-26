#ifndef _TONGMYONG_YMKANG_SIMPLE_SIMULATOR_2015_
#define _TONGMYONG_YMKANG_SIMPLE_SIMULATOR_2015_

class CSimulator {

public:
	CSimulator() {};

	void init(void);
	void ActionsBeforeFrame(double dt, double elapsedTime);
	void Actions(double dt, double elapsedTime);
	void ActionsAfterFrame(double dt, double elapsedTime);
	
	// Control Event Handlers
	void stop();
	void pause();
	void resume();
};

#endif