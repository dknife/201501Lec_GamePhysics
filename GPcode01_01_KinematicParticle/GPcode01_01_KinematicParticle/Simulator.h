#ifndef _TONGMYONG_YMKANG_SIMPLE_SIMULATOR_2015_
#define _TONGMYONG_YMKANG_SIMPLE_SIMULATOR_2015_

class CSimulator {

public:
	// Constructor
	CSimulator();

	// initialization
	void init(void);

	// actions to be preformed at every frame
	void actionsBeforeFrame(double dt, double currentTime);
	void actions(double dt, double currentTime);
	void actionsAfterFrame(double dt, double currentTime);
	
	// Control Event Handlers
	void stop();
	void pause();
	void resume();
};

#endif