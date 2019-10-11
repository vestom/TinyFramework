/*
 * Mutex.h
 *
 *  Created on: Oct 20, 2016
 *      Author: tov
 */

#ifndef TF_MUTEX_H_
#define TF_MUTEX_H_

#ifdef _TF_OS_LINUX_
#include <pthread.h>
#endif
#ifdef _TF_OS_FREERTOS_
#include "FreeRTOS.h"
#include "os_semphr.h"
#endif
#ifdef _TF_OS_ZEPHYR_
#endif

namespace TF {

class Mutex {
public:
	Mutex();
	virtual ~Mutex();
	void lock();
	void unlock();

private:

#ifdef _TF_OS_LINUX_
	pthread_mutex_t mutex_id;
#endif
#ifdef _TF_OS_FREERTOS_
	SemaphoreHandle_t mutex_id;
#endif
#ifdef _TF_OS_ZEPHYR_
	struct k_mutex mutex_id;
#endif

};

} /* namespace TF */

#endif /* TF_MUTEX_H_ */
