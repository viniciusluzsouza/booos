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
#include "Scheduler.h"

namespace BOOOS
{

volatile Task * Task::__running;
int Task::__tid_counter;
const int Task::STACKSIZE;
Task * Task::__main;
std::queue<Task*> Task::__ready;
int Task::_count=0;


//...


Task::Task(void (*entry_point)(void*), int nargs, void * arg){
	_state = READY;
	getcontext(&this->_context);
	_stack = (char*)malloc(STACKSIZE);
	if (_stack){
		this->_context.uc_stack.ss_sp = _stack;
		this->_context.uc_stack.ss_size = STACKSIZE;
		this->_context.uc_stack.ss_flags = 0;
		//this->_context.uc_link = 0;
		this->_context.uc_link = (ucontext*)-1;
	} else {
		exit(1);
	}
	makecontext(&this->_context, (void(*)()) entry_point, nargs, arg);
	__tid_counter++;
	_tid = __tid_counter;
	__ready.push(this);
	_count++;
}

Task::Task(){
	getcontext(&_context);
	_tid = __tid_counter;
	_state = READY;
	_count++;
}

Task::~Task(){
	free(_stack);
}

void Task::pass_to(Task * t, State s){
	this->_state = s;
	__running = t;
	if (s == READY) __ready.push(this);
	swapcontext(&this->_context, &t->_context);

}

void Task::exit(int code){
	_count--;
	__tid_counter--;
	pass_to((Task*) Scheduler::self(), FINISHING);

}

void Task::init(){
	__tid_counter = 0;
	__main = new Task();
	__running = __main;
	__main->_state = RUNNING;
}

void Task::yield(){
	pass_to((Task*) Scheduler::self(), READY);
}



} /* namespace BOOOS */
