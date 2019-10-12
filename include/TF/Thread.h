/*
 * Thread.h
 *
 *  Created on: Oct 19, 2016
 *      Author: tov
 */

#ifndef TF_THREAD_H_
#define TF_THREAD_H_

#include "TF/TF.h"

// TODO: refactor OS specific data
#ifdef _TF_OS_LINUX_
#include <pthread.h>
#endif
#ifdef _TF_OS_FREERTOS_
#include "FreeRTOS.h"
#include "os_task.h"
#endif
#ifdef _TF_OS_ZEPHYR_
#endif

namespace TF {

class Thread {
public:

	Thread();
	virtual ~Thread();

	enum class Priority {
		HIGH = 2,
		NORMAL = 1
	};

#ifdef _TF_OS_ZEPHYR_
	// Define stack statically with: K_THREAD_STACK_DEFINE(zephyr_stack, STACK_SIZE);
	void start(k_thread_stack_t *zephyr_stack, size_t stack_size, Priority pri = Priority::NORMAL);
#else
	// Start the thread
	void start(Priority pri = Priority::NORMAL);
#endif

	// Kill the thread
	void kill(void);

	// Sleep a number of milliseconds. 0 will yield.
	static void sleep_ms(unsigned milliseconds);

	// Never ending function to be called at end of main
	// Needed for e.g. FreeRTOS
	static void startScheduler(void);

protected:
	// Override this function
	virtual void run(void) = 0;

private:
    // Static thread function
    static void thread_func(Thread *p_this);

#ifdef _TF_OS_LINUX_
	pthread_t thread_id;	// Thread ID
#endif
#ifdef _TF_OS_FREERTOS_
	TaskHandle_t thread_id;
#endif
#ifdef _TF_OS_ZEPHYR_
	k_tid_t thread_id;
	struct k_thread thread_data;
#endif

};

} /* namespace TF */


#endif /* TF_THREAD_H_ */
