#ifndef _TONGMYONG_YMKANG_SIMPLE_SIMULATOR_2015_
#define _TONGMYONG_YMKANG_SIMPLE_SIMULATOR_2015_


////////////////////////////////
//
// Simulator Interface
//
// Young-Min Kang
// Tongmyong University

class CSimulator {
    bool bRunning;
    
public:
	// Constructor and destructor
	CSimulator();
    virtual ~CSimulator();
    
	// initialization
	virtual void init(void)=0;
    // clean
    virtual void clean(void)=0;
    
    void actions(double dt, double currentTime);

    
	// Control Event Handlers
    void start();
	void stop();
	void pause();
	void resume();
    
private:
    // virtual functions containing actions to be preformed at every frame
    //
    // Actions to be performed before the simulation frame
    virtual void doBeforeSimulation(double dt, double currentTime) = 0;
    // Simulation is done here
    virtual void doSimulation(double dt, double currentTime) = 0;
    // Actions to be performed after the simulation frame
    virtual void doAfterSimulation(double dt, double currentTime) = 0;
    
    // visualization
    virtual void visualize(void) = 0;
};

#endif