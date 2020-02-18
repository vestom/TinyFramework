/*
 * Mutex.h
 *
 *  Created on: Oct 20, 2016
 *      Author: tov
 */

#ifndef TF_MUTEX_H_
#define TF_MUTEX_H_

#include "TF/TF.h"

#ifdef _TF_OS_LINUX_
#include <pthread.h>
#endif
#ifdef _TF_OS_FREERTOS_
#include "os_semphr.h"
#endif
#ifdef _TF_OS_ZEPHYR_
#endif

namespace TF {

/// Mutual exclusion to protect access of data from multiple locations
class Mutex {
public:
    Mutex();
    ~Mutex();
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


/// Automatically lock and unlock a Mutex as a stack variable (like std::auto_ptr)
class AutoMutex {
public:
    AutoMutex(Mutex &_mutex): mutex(_mutex) { mutex.lock(); }
    ~AutoMutex() { mutex.unlock(); }

private:
    Mutex &mutex;
};


} /* namespace TF */

#endif /* TF_MUTEX_H_ */
