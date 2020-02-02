/*
 * Time.cpp
 *
 *  Implementaton for Zephyr OS
 */
#include "TF/TF.h"
#ifdef _TF_OS_ZEPHYR_

#include "TF/Time.h"

#include "zephyr.h"

namespace TF {

TimeStamp Time::get_ms(void) {
    return (TimeStamp)k_uptime_get();
}

TimeStamp Time::get_tick(void) {
    return (k_cycle_get_32());
}

} /* namespace TF */

#endif
