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
	friend class Scheduler;
public:
	enum State {
		READY,
		WAITING,
		RUNNING,
		FINISHING,
		SCHEDULER
	};

	static std::queue<Task*> __ready;
	static const int STACKSIZE = 32*1024;
	static int __tid_counter;
	static int _count;

	Task(void (*entry_point)(void*), int nargs, void * arg);
	virtual ~Task();

	int tid() { return _tid; }
	State state() { return _state; }
	static int count() { return _count; }

	void pass_to(Task * t, State s = READY);

	void exit(int code);

	void yield();

	static Task * self() { return (Task*) __running; }
	static void init();
	Task();

private:

	char *_stack;

	static volatile Task * __running;
	ucontext_t _context;

	State _state;
	int _tid; // task ID

	static Task * __last_task;
	static Task * __main;
};

} /* namespace BOOOS */

#endif /* TASK_H_ */
