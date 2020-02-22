/*
 * Event.h
 *
 *  Created on: Oct 20, 2016
 *      Author: tov
 */

#ifndef TF_EVENT_H_
#define TF_EVENT_H_

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

/// Event is a binary semaphore used to signal some event across threads
class Event {
public:
    Event();

#ifndef _TF_OS_ZEPHYR_
    ~Event();
#endif

    // Wait for event to be set
    // Set timeout to 0 to wait forever
    // Will return false if wait timed out without being set
    bool wait(unsigned timeout_ms = 0);

    // Set the event and signal any waiting threads
    void set();

    // Test event without waiting or clearing
    bool is_set();

private:

#ifdef _TF_OS_LINUX_
    volatile bool   flag;
    pthread_mutex_t mutex_id;
    pthread_cond_t  cond_id;
#endif
#ifdef _TF_OS_FREERTOS_
    SemaphoreHandle_t mutex_id;
#endif
#ifdef _TF_OS_ZEPHYR_
    struct k_sem mutex_id;
#endif

};

} /* namespace TF */

#endif /* TF_EVENT_H_ */
