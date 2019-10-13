/*
 * Event.cpp
 *
 *  Created on: Oct 20, 2016
 *      Author: tov
 */

#include "TF/TF.h"
#ifdef _TF_OS_LINUX_

#include "TF/Event.h"
#include "TF/Log.h"
#include <pthread.h>
#include <string.h>
#include <errno.h>


namespace TF {

Event::Event() {
    int ret = pthread_mutex_init(&mutex_id, 0);
    if(ret) { Log::error("pthread_mutex_init() failed"); }
    ret = pthread_cond_init(&cond_id, NULL);
    if(ret) { Log::error("pthread_cond_init() failed"); }
    flag = false;
}

Event::~Event() {
    int ret = pthread_cond_destroy(&cond_id);
    if(ret) { Log::error("pthread_cond_destroy() failed"); }
    ret = pthread_mutex_destroy(&mutex_id);
    if(ret) { Log::error("pthread_mutex_destroy() failed"); }
}

bool Event::wait(unsigned timeout_ms) {
    struct timespec ts;
    int ret;

    if(timeout_ms) {
        ret = clock_gettime(CLOCK_REALTIME, &ts);
        if (ret) { Log::error("clock_gettime(): %s", strerror(errno)); }
        ts.tv_sec += timeout_ms / 1000;
        ts.tv_nsec += (timeout_ms % 1000) * 1000000;
    }

    ret = pthread_mutex_lock(&mutex_id);
    if(ret) { Log::error("pthread_mutex_lock(): %s", strerror(ret)); }

    while (!flag) {
        if(timeout_ms) {	ret = pthread_cond_timedwait(&cond_id, &mutex_id, &ts); }
        else {				ret = pthread_cond_wait(&cond_id, &mutex_id); }
        if(ret == ETIMEDOUT) {
            ret = pthread_mutex_unlock(&mutex_id);
            if(ret) { Log::error("pthread_mutex_unlock(): %s", strerror(ret)); }
            return false;
        } else if(ret) { Log::error("pthread_cond_wait(): %s", strerror(ret)); }
    }
    flag = false;

    ret = pthread_mutex_unlock(&mutex_id);
    if(ret) { Log::error("pthread_mutex_unlock(): %s", strerror(ret)); }

    return true;
}


void Event::set() {
    flag = true;
    int ret = pthread_cond_signal(&cond_id);
    if(ret) { Log::error("pthread_cond_signal(): %s", strerror(ret)); }
}


bool Event::is_set()   { return flag; }


} /* namespace TF */

#endif
