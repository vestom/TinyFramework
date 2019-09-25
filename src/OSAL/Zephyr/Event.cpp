/*
 * Event.cpp
 *
 *  Created on: Oct 25, 2019
 *      Author: tov
 */

#include "TF/TF.h"
#ifdef _TF_OS_ZEPHYR_

#include "TF/Event.h"
#include "TF/Log.h"


namespace TF {

Event::Event() {
    // Binary semaphore (limit 1)
    k_sem_init(&mutex_id, 0, 1);
}


Event::~Event() {
}


bool Event::wait(unsigned timeout_ms) {
    s32_t timeout;
    if (timeout_ms == 0) {
        timeout = K_FOREVER;
    } else {
        timeout = K_MSEC(timeout_ms);
    }
    int ret = k_sem_take(&mutex_id, timeout);
    return (ret == 0);
}


void Event::set() {
    k_sem_give(&mutex_id);
}


bool Event::is_set() {
    unsigned ret = k_sem_count_get(&mutex_id);
    return (ret != 0);
}


} /* namespace TF */

#endif
