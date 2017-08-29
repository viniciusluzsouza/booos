/*
* BOOOS.h
*
*  Created on: Aug 14, 2014
*      Author: arliones
*/

#include <BOOOS.h>
#include <Task.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

namespace BOOOS {

BOOOS * BOOOS::__booos = 0;
BOOOS::SCHED_TYPE BOOOS::SCHED_POLICY = BOOOS::SCHED_FCFS; // Select here the scheduling algorithm
bool BOOOS::SCHED_PREEMPT = false;
bool BOOOS::SCHED_AGING = false;


BOOOS::BOOOS(bool verbose) : _verbose(verbose) {
	if(__booos != 0) panic();
	__booos = this;

	if(_verbose) std::cout << "Welcome to BOOOS - Basic Object Oriented Operating System!" << std::endl;

    // turn off stdout buffer to avoid run conditions during context switch
    setvbuf(stdout, 0, _IONBF, 0);

	// Call init routines of other components

	Task::init();
}

BOOOS::~BOOOS() {
	// Call finish routines of other components (if any)


	if(_verbose) std::cout << "BOOOS ended... Bye!" << std::endl;
}

void BOOOS::panic() {
	std::cerr << "BOOOSta! Panic!" << std::endl;
	while(true);
}

} /* namespace BOOOS */
