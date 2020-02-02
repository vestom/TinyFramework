/*
 * Time.cpp
 *
 *  Created on: Oct 19, 2016
 *      Author: tov
 */
#include "TF/TF.h"
#ifdef _TF_OS_LINUX_

#include "TF/Time.h"
#include "TF/Log.h"


namespace TF {

#include <time.h>

TimeStamp Time::get_ms(void) {
    struct timespec ts;
    int ret = clock_gettime(CLOCK_MONOTONIC, &ts);
    if (ret) { Log::error("clock_gettime() : %i", ret); }
    return ((ts.tv_sec * 1000) + (ts.tv_nsec/1000000));
}

TimeStamp Time::get_tick(void) {
    struct timespec ts;
    int ret = clock_gettime(CLOCK_MONOTONIC, &ts);
    if (ret) { Log::error("clock_gettime() : %i", ret); }
    return (ts.tv_nsec);
}

} /* namespace TF */

#endif

