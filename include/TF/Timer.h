/*
 * Timer.h
 *
 *  Created on: Oct 19, 2016
 *      Author: tov
 */

#ifndef TF_TIMER_H_
#define TF_TIMER_H_

namespace TF {

class Timer {
public:
	Timer(long _timeout_ms)	{ timeout_ms = _timeout_ms; reset(); };
	virtual ~Timer() {};

	/// Reset timer to current time
	void reset(void)	{ timestamp = get_ms(); };

	/// Set timer to have expired
	void set(void)	{ timestamp = get_ms() - timeout_ms; };

	/// Return true if timer has expired
	/// Will wait _at least_ the requested timeout value (e.g. 1ms => [1;2])
	bool is_expired(void)	const	{ return ( (get_ms()-timestamp) > timeout_ms); }; // Overflow OK!

	/// Get number of milliseconds since beginning
	static long get_ms(void);

	/// Get high res tick of platform defined resolution (may often roll over)
	static long get_tick(void);

private:
	// milliseconds to timeout
	long timeout_ms;

	// timestamp of last reset
	long timestamp;
};

} /* namespace TF */

#endif /* TF_TIMER_H_ */
