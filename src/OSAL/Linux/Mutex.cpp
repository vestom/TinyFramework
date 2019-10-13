/*
 * Mutex.cpp
 *
 *  Created on: Oct 20, 2016
 *      Author: tov
 */

#include "TF/TF.h"
#ifdef _TF_OS_LINUX_

#include "TF/Mutex.h"
#include "TF/Log.h"

#include <pthread.h>


namespace TF {

Mutex::Mutex() {
    int ret = pthread_mutex_init(&mutex_id, NULL);
    if(ret) { Log::error("Could not initialize mutex"); }
}

Mutex::~Mutex() {
    int ret = pthread_mutex_destroy(&mutex_id);
    if(ret) { Log::error("Could not destroy mutex"); }
}

void Mutex::lock() {
    int ret = pthread_mutex_lock(&mutex_id);
    if(ret) { Log::error("Could not lock mutex"); }
}

void Mutex::unlock() {
    int ret = pthread_mutex_unlock(&mutex_id);
    if(ret) { Log::error("Could not unlock mutex"); }
}

} /* namespace TF */

#endif
