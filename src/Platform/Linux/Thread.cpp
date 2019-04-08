/*
 * Thread.cpp
 *
 *  Created on: Oct 19, 2016
 *      Author: tov
 */

#include "TF/Thread.h"
#include "TF/Log.h"

#include <time.h>
#include <string.h>

namespace TF {

Thread::Thread() {
	thread_id = 0;
}

Thread::~Thread() {
	if(thread_id) {
		kill();
	}
}

void Thread::start(Priority pri) {
	int ret;
	if(thread_id) { Log::error("Attempt to start() an existing thread"); return; }

	// To allow the Linux executable to set realtime priority the following commands can be used:
	// # Enable realtime shceduling
	// $ sudo setcap CAP_SYS_NICE=eip <file>
	// $ getcap <file>
	// # Test scheduler priority
	// $ chrt -a -p <PID>

	// Set realtime priority (between 1 and 99)
	struct sched_param param = {
			.sched_priority = 1
	};
/*
	// Set priority at task creation
	pthread_attr_t attr;
	ret = pthread_attr_init(&attr);
	if (ret) { Log::error("pthread_attr_init(): %i", ret); }
	ret = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	if (ret) { Log::error("pthread_attr_setschedparam(): %i", ret); }
	ret = pthread_attr_setschedpolicy(&attr, SCHED_RR);
	if (ret) { Log::error("pthread_attr_setschedpolicy(): %i", ret); }
	ret = pthread_attr_setschedparam(&attr, &param);
	if (ret) { Log::error("pthread_attr_setschedparam(): %i", ret); }
*/

	typedef void* (*fptr)(void*);
	ret = pthread_create (&thread_id, NULL /*&attr*/, reinterpret_cast<fptr>(&thread_func), (void*)this);
	if (ret) { Log::error("pthread_create(): %s", strerror(ret)); }
	//	pthread_attr_destroy(&attr);

	// Set priority
	if (pri == Priority::HIGH) {
		ret = pthread_setschedparam(thread_id, SCHED_RR, &param);
		if (ret) { Log::error("pthread_setschedparam(): %s", strerror(ret)); }
	}

}

void Thread::kill(void) {
	if(thread_id) {
		int ret = pthread_cancel(thread_id);
		if(ret) { Log::error("pthread_cancel(): %i", ret); }
		thread_id = 0;
	}
	Log::debug("Thread killed");
}

void Thread::sleep_ms(unsigned milliseconds) {
	struct timespec req = {
			.tv_sec = (long)milliseconds / 1000,
			.tv_nsec = ((long)milliseconds % 1000) * 1000000
	};
	int ret = nanosleep (&req, NULL);
	if (ret) { Log::error("nanosleep() : %i", ret); }
}


void Thread::thread_func(Thread* p_this) {
	if(p_this)	{
		Log::debug("Thread started");
		p_this->run();
		Log::debug("Thread stopped");
		p_this->thread_id = 0;		// Be sure thread ID is invalid
	}
}

} /* namespace TF */
