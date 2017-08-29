/*
 * Task.cc

 *
 *  Created on: Feb 27, 2014
 *      Author: arliones
 */
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <ucontext.h>
#include "Task.h"

namespace BOOOS
{

volatile Task * Task::__running;
int Task::__tid_counter;
const int Task::STACKSIZE;
Task * Task::__main;

//...


Task::Task(void (*entry_point)(void*), int nargs, void * arg){
	getcontext(&this->_context);
	_stack = (char*)malloc(STACKSIZE);
	if (_stack){
		this->_context.uc_stack.ss_sp = _stack;
		this->_context.uc_stack.ss_size = STACKSIZE;
		this->_context.uc_stack.ss_flags = 0;
		this->_context.uc_link = 0;
		makecontext(&this->_context, (void(*)()) entry_point, nargs, arg);
		if (__tid_counter == 0) {
			this->_tid = 2;
			__tid_counter = 2;
		} else {
			__tid_counter++;
			this->_tid = __tid_counter;
		}
		this->_state = READY;
	}
}

Task::Task(){
	getcontext(&_context);
	_tid = __tid_counter;
	_state = READY;
}

Task::~Task(){
	free(_stack);

}

void Task::pass_to(Task * t, State s){
	swapcontext(&this->_context, &t->_context);
	this->_state = s;
	__running = t;

}

void Task::exit(int code){
	swapcontext(&this->_context, &__main->_context);

}

void Task::init(){
	__tid_counter = 0;
	__main = new Task();
	__running = __main;
	__main->_state = RUNNING;

}

} /* namespace BOOOS */
