#include "Simulator.h"
#include <stdlib.h>
#include <stdio.h>
// Constructor
CSimulator::CSimulator(): bRunning(false) {  }

CSimulator::~CSimulator() { }


void CSimulator::actions(double dt, double currentTime) {
    if(bRunning) {
        doBeforeSimulation(dt, currentTime);
        doSimulation(dt, currentTime);
        doAfterSimulation(dt, currentTime);
    }
    visualize();
}



// Control Event Handlers

void CSimulator::start() {
    this->init();
    bRunning = true;
}

void CSimulator::stop() {
    bRunning = false;
    this->clean();
}

void CSimulator::pause() {

}

void CSimulator::resume() {

}

void CSimulator::control(unsigned char key) {
    
}