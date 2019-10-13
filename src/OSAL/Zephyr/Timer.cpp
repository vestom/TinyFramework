/*
 * Timer.cpp
 *
 *  Implementaton for Zephyr OS
 */
#include "TF/TF.h"
#ifdef _TF_OS_ZEPHYR_

#include "TF/Timer.h"

#include "zephyr.h"

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
    return (TimeStamp)k_uptime_get();
}

TimeStamp Timer::get_tick(void) {
    return (k_cycle_get_32());
}

} /* namespace TF */

#endif
