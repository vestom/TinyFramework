/*
 * Thread.cpp
 *
 *  Created on: Oct 19, 2016
 *      Author: tov
 */

#include "TF/TF.h"
#ifdef _TF_OS_FREERTOS_

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

    // Create Task 1
    ret = xTaskCreate(reinterpret_cast<TaskFunction_t>(&thread_func), "TaskX", configMINIMAL_STACK_SIZE, (void*)this, 1, &thread_id);
    if(ret != pdPASS) {
        // Task could not be created
        Log::error("xTaskCreate(): %s", ret);
    } else {
        // Set priority
        /// TODO: Implement priority
        //////vTaskPrioritySet( thread_id, 2 );
    }
}

void Thread::kill(void) {
	if(thread_id) {
	    vTaskDelete(thread_id);
		thread_id = 0;
	}
	Log::debug("Thread killed");
}

void Thread::sleep_ms(unsigned milliseconds) {
    vTaskDelay(pdMS_TO_TICKS(milliseconds));
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
