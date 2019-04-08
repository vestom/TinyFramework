/*
 * Timer.cpp
 *
 *  Created on: Oct 19, 2016
 *      Author: tov
 */
#include "TF/Timer.h"

#include "TF/Log.h"


namespace TF {

//Timer::Timer() {
//	// TODO Auto-generated constructor stub
//
//}
//
//Timer::~Timer() {
//	// TODO Auto-generated destructor stub
//}


#ifdef __linux__
#include <time.h>

long Timer::get_ms(void) {
	struct timespec ts;
	int ret = clock_gettime(CLOCK_MONOTONIC, &ts);
	if (ret) { Log::error("clock_gettime() : %i", ret); }
	return ((ts.tv_sec * 1000) + (ts.tv_nsec/1000000));
}

long Timer::get_tick(void) {
	struct timespec ts;
	int ret = clock_gettime(CLOCK_MONOTONIC, &ts);
	if (ret) { Log::error("clock_gettime() : %i", ret); }
	return (ts.tv_nsec);
}

#endif

} /* namespace TF */

