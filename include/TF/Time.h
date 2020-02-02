/*
 * Time.h
 *
 *  Created on: Oct 19, 2016
 *      Author: tov
 */

#ifndef TF_TIME_H_
#define TF_TIME_H_

#include "TF/TF.h"

namespace TF {

typedef unsigned long TimeStamp;
typedef signed long TimeDelta;

class Time {
public:
    Time(TimeStamp _timeout_ms = 0) : timeout_ms(_timeout_ms)	{ reset(); };
    ~Time() {};

    /// Reset timer to current time
    void reset(void)	{ timestamp = get_ms(); };

    /// Set timer to have expired
    void expire(void)	{ timestamp = get_ms() - timeout_ms; };

    /// Set timer timeout
    void set_timeout_ms(TimeStamp _timeout_ms)	{ timeout_ms = _timeout_ms; };

    /// Get timer timeout
    TimeStamp get_timeout_ms()	{ return timeout_ms; };

    /// Return true if timer has expired
    /// Will wait _at least_ the requested timeout value (e.g. 1ms => [1;2])
    bool is_expired(void)	const	{ return ( (get_ms()-timestamp) > timeout_ms); }; // Overflow OK!

    /// Get number of milliseconds since timer reset
    TimeStamp get_elapsed_ms(void)   const	{ return (get_ms()-timestamp); };

    /// Get number of milliseconds until timer expires
    /// Value is negative if timer has expired
    TimeDelta get_remaining_ms(void)   const	{ return (TimeDelta)timeout_ms-get_elapsed_ms(); };

    /// Get number of milliseconds since beginning
    static TimeStamp get_ms(void);

    /// Get high res tick of platform defined resolution (may often roll over)
    static TimeStamp get_tick(void);

private:
    // milliseconds to timeout
    TimeStamp timeout_ms;

    // timestamp of last reset
    TimeStamp timestamp;
};

} /* namespace TF */

#endif /* TF_TIMER_H_ */
