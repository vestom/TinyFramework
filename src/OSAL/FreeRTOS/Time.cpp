/*
 * Time.cpp
 *
 *  Implementaton for FreeRTOS OS
 */
#include "TF/TF.h"
#ifdef _TF_OS_FREERTOS_

#include "TF/Time.h"

#include "FreeRTOS.h"
#include "os_task.h"

namespace TF {

TimeStamp Time::get_ms(void) {
    return (TimeStamp)xTaskGetTickCount()*1000/configTICK_RATE_HZ;
}

TimeStamp Time::get_tick(void) {
    return (xTaskGetTickCount());
}

} /* namespace TF */

#endif
