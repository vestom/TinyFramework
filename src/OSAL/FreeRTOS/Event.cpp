/*
 * Event.cpp
 *
 *  Created on: Oct 20, 2016
 *      Author: tov
 */

#include "TF/TF.h"
#ifdef _TF_OS_FREERTOS_

#include "TF/Event.h"
#include "TF/Log.h"


namespace TF {

Event::Event() {
    mutex_id = xSemaphoreCreateBinary();
    if(mutex_id == 0) { Log::error("Could not initialize Binary Semaphore"); }
}


Event::~Event() {
    if (mutex_id) vSemaphoreDelete(mutex_id);
}


bool Event::wait(unsigned timeout_ms) {
    TickType_t timeout;
    if (timeout_ms == 0) {
        timeout = portMAX_DELAY;
    } else {
        timeout = pdMS_TO_TICKS(timeout_ms);
    }
    BaseType_t ret = xSemaphoreTake(mutex_id, timeout);
    return (ret == pdPASS);
}


void Event::set() {
    BaseType_t ret = xSemaphoreGive(mutex_id);
    if(ret != pdPASS) { Log::error("xSemaphoreGive(): %i", ret); }
}


bool Event::is_set() {
    UBaseType_t ret = uxSemaphoreGetCount(mutex_id);
    return ret;
}


} /* namespace TF */

#endif
