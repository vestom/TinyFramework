/*
 * Mutex.cpp
 *
 *  Created on: Oct 20, 2016
 *      Author: tov
 */

#include "TF/TF.h"
#ifdef _TF_OS_FREERTOS_

#include "TF/Mutex.h"
#include "TF/Log.h"


namespace TF {

Mutex::Mutex() {
	mutex_id = xSemaphoreCreateMutex();
	if(mutex_id == 0) { Log::error("Could not initialize mutex"); }
}

Mutex::~Mutex() {
	if (mutex_id) vSemaphoreDelete(mutex_id);
}

void Mutex::lock() {
    BaseType_t ret = xSemaphoreTake(mutex_id, portMAX_DELAY);
	if(ret != pdPASS) { Log::error("xSemaphoreTake(): %i", ret); }
}

void Mutex::unlock() {
    BaseType_t ret = xSemaphoreGive(mutex_id);
    if(ret != pdPASS) { Log::error("xSemaphoreGive(): %i", ret); }
}

} /* namespace TF */

#endif
