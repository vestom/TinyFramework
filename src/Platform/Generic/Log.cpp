/*
 * Log.cpp
 *
 *  Created on: Oct 19, 2016
 *      Author: tov
 */

#include "TF/Log.h"
#include "TF/Timer.h"

#include <stdio.h>
#include <stdarg.h>



namespace TF {

bool Log::logDebugOn = true;
bool Log::logErrorOn = true;

Log::Log() {
	// TODO Auto-generated constructor stub

}

Log::~Log() {
	// TODO Auto-generated destructor stub
}

void Log::debug(const char* printf_format, ...) {
	if(logDebugOn) {
		va_list arglist;
		va_start(arglist, printf_format);
		fprintf(stderr, "%ld ", TF::Timer::get_ms());
		fprintf(stderr, " DBG: ");
		vfprintf(stderr, printf_format, arglist);
		fprintf(stderr, "\n");
		va_end(arglist);
	}
}

void Log::error(const char* printf_format, ...) {
	if(logErrorOn) {
		va_list arglist;
		va_start(arglist, printf_format);
		fprintf(stderr, "%ld ", TF::Timer::get_ms());
		fprintf(stderr, "!ERR: ");
		vfprintf(stderr, printf_format, arglist);
		fprintf(stderr, "\n");
		va_end(arglist);
	}
}

void Log::setLogDebug(bool on) {
	logDebugOn = on;
}

void Log::setLogError(bool on) {
	logErrorOn = on;
}

} /* namespace TF */

