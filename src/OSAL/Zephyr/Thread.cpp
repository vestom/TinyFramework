/*
 * Thread.cpp
 *
 *  Created on: Sep 24, 2019
 *      Author: tov
 */

#include "TF/TF.h"
#ifdef _TF_OS_ZEPHYR_

#include "TF/Thread.h"
#include "TF/Log.h"

//#include <time.h>
//#include <string.h>

namespace TF {

Thread::Thread() {
}

Thread::~Thread() {
    if(thread_id) {
        kill();
    }
}


void Thread::start(k_thread_stack_t *zephyr_stack, size_t stack_size, Priority pri) {
    if(thread_id) { Log::error("Attempt to start() an existing thread"); return; }

    int priority = 1;   // Default priority
    if(pri == Priority::HIGH) {
        priority = 0;
    }

    thread_id = k_thread_create(&thread_data, zephyr_stack, stack_size,
                                reinterpret_cast<k_thread_entry_t>(&thread_func),
                                (void*)this, NULL, NULL,
                                priority, 0, K_NO_WAIT);
    Log::debug("Starting thread: stacksize %i", stack_size);
}


void Thread::kill(void) {
    if(thread_id) {
        k_thread_abort(thread_id);
        thread_id = 0;
    }
    Log::debug("Thread killed");
}


void Thread::sleep_ms(unsigned milliseconds) {
    k_sleep(milliseconds);
}


void Thread::startScheduler(void) {
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

#endif
