/*
 * Timer.cpp
 *
 *  Implementaton for FreeRTOS OS
 */
#include "TF/TF.h"
#ifdef _TF_OS_FREERTOS_

#include "TF/Timer.h"

#include "FreeRTOS.h"
#include "os_task.h"

namespace TF {

//Timer::Timer() {
//	// TODO Auto-generated constructor stub
//
//}
//
//Timer::~Timer() {
//	// TODO Auto-generated destructor stub
//}

TimeStamp Timer::get_ms(void) {
    return (TimeStamp)xTaskGetTickCount()*1000/configTICK_RATE_HZ;
}

TimeStamp Timer::get_tick(void) {
	return (xTaskGetTickCount());
}

} /* namespace TF */

#endif
