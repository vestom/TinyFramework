/*
 * Mutex.h
 *
 *  Created on: Oct 20, 2016
 *      Author: tov
 */

#ifndef TF_MUTEX_H_
#define TF_MUTEX_H_

#include <pthread.h>

namespace TF {

class Mutex {
public:
	Mutex();
	virtual ~Mutex();
	void lock();
	void unlock();

private:
	pthread_mutex_t mutex_id;

};

} /* namespace TF */

#endif /* TF_MUTEX_H_ */
