#include "Simulator.h"

// Constructor
CSimulator::CSimulator(){ }

// initialization
void CSimulator::init(void) {}

// Actions to be performed at every frame
void CSimulator::actionsBeforeFrame(double dt, double currentTime) {

}

void CSimulator::actions(double dt, double currentTime) {
	actionsBeforeFrame(dt, currentTime);

	actionsAfterFrame(dt, currentTime);
}

void CSimulator::actionsAfterFrame(double dt, double currentTime) {

}

// Control Event Handlers
void CSimulator::stop() {

}

void CSimulator::pause() {

}

void CSimulator::resume() {

}