/*
 * Task.h
 *
 *  Created on: Aug 15, 2014
 *      Author: arliones
 */

#ifndef TASK_H_
#define TASK_H_

#include <queue>
#include <ucontext.h>

namespace BOOOS {

class Task {
public:
	enum State {
		READY,
		WAITING,
		RUNNING,
		FINISHING
	};

	static const int STACKSIZE = 32*1024;
	static int __tid_counter;

	Task(void (*entry_point)(void*), int nargs, void * arg);
	virtual ~Task();

	int tid() { return _tid; }
	State state() { return _state; }

	void pass_to(Task * t, State s = READY);

	void exit(int code);

	static Task * self() { return (Task*) __running; }
	static void init();

private:

	Task();
	char *_stack;

	static volatile Task * __running;
	ucontext_t _context;

	State _state;
	int _tid; // task ID

	static Task * __main;
};

} /* namespace BOOOS */

#endif /* TASK_H_ */
