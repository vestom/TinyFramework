/*
 * Mutex.cpp
 *
 *  Created on: Sep 24, 2019
 *      Author: tov
 */

#include "TF/TF.h"
#ifdef _TF_OS_ZEPHYR_

#include "TF/Mutex.h"
#include "TF/Log.h"


namespace TF {

Mutex::Mutex() {
    k_mutex_init(&mutex_id);
}

//Mutex::~Mutex() {
//}

void Mutex::lock() {
    int ret = k_mutex_lock(&mutex_id, K_FOREVER);
    if(ret != 0) { Log::error("k_mutex_lock(): %i", ret); }
}

void Mutex::unlock() {
    k_mutex_unlock(&mutex_id);
}

} /* namespace TF */

#endif
