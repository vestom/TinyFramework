/*
 * Event.h
 *
 *  Created on: Oct 20, 2016
 *      Author: tov
 */

#ifndef TF_EVENT_H_
#define TF_EVENT_H_

#include <pthread.h>

namespace TF {

class Event {
public:
	Event();
	virtual ~Event();

	// Wait for event to be set
	// Set timeout to 0 to wait forever
	// Will return false if wait timed out without being set
	bool wait(unsigned timeout_ms = 0);

	// Set the event and signal any waiting threads
	void set();

	bool is_set()	{ return flag; }

private:
    volatile bool	flag;
	pthread_mutex_t mutex_id;
    pthread_cond_t  cond_id;
};

} /* namespace TF */

#endif /* TF_EVENT_H_ */
