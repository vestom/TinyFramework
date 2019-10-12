/*
 * Log.h
 *
 *  Created on: Oct 19, 2016
 *      Author: tov
 */

#ifndef TF_LOG_H_
#define TF_LOG_H_

#include "TF/TF.h"

namespace TF {

class Log {
public:
	//Log();
	//~Log();

	static void debug(const char *printf_format, ...);
	static void error(const char *printf_format, ...);

	static void setLogDebug(bool on);
	static void setLogError(bool on);

	static bool getLogDebug(void)	{ return logDebugOn; }

private:
	static bool logDebugOn;
	static bool logErrorOn;
};

} /* namespace TF */

#endif /* TF_LOG_H_ */
