#include "Simulator.h"
#include <stdlib.h>include
// Constructor
CSimulator::CSimulator(){  }

CSimulator::~CSimulator() { }


void CSimulator::actions(double dt, double currentTime) {
	doBeforeSimulation(dt, currentTime);
    doSimulation(dt, currentTime);
	doAfterSimulation(dt, currentTime);
}



// Control Event Handlers
void CSimulator::stop() {

}

void CSimulator::pause() {

}

void CSimulator::resume() {

}