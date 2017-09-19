/*
 * Scheduler.cc
 *
 *  Created on: 09/09/2017
 *      Author: vini
 */
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <ucontext.h>
#include <queue>
#include "Task.h"
#include "Scheduler.h"

using namespace std;
using namespace BOOOS;

Scheduler * Scheduler::__dispatcher;


//Construtor da classe scheduler
Scheduler::Scheduler() : Task(dispatcher,0,0) {
	this->_state = SCHEDULER;
}

//Destrutor da classe scheduler
Scheduler::~Scheduler(){
	free(__dispatcher);
}


//Inicializador da classe scheduler
void Scheduler::init(){
	if (not __dispatcher) __dispatcher = new Scheduler();

}

//Método despachador (determina a proxima tarefa a executar)
void Scheduler::dispatcher(void*){
	while (__ready.size() > 0){
		Task * next = self()->choose_next();
		if (next){
			self()->pass_to(next, SCHEDULER);
		}
	}
	self()->pass_to(Task::__main, Task::FINISHING);
}

Task * Scheduler::choose_next(){
	if ( __ready.size() > 0){
		Task * umaTask = __ready.front();
		__ready.pop();
		return umaTask;
	}
	return NULL;
}
