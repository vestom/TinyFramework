/*
 * Thread.h
 *
 *  Created on: Oct 19, 2016
 *      Author: tov
 */

#ifndef TF_THREAD_H_
#define TF_THREAD_H_

#ifdef _TF_OS_LINUX_
#include <pthread.h>
#endif

namespace TF {

class Thread {
public:
	Thread();
	virtual ~Thread();

	enum class Priority {
		HIGH = 2,
		NORMAL = 1
	};

	// Start the thread
	void start(Priority pri = Priority::NORMAL);

	// Kill the thread
	void kill(void);


	static void sleep_ms(unsigned milliseconds);

protected:
	// Override this function
	virtual void run(void) = 0;

private:
#ifdef _TF_OS_LINUX_
	pthread_t thread_id;	// Thread ID
#endif
	// Static thread function
	static void	thread_func(Thread *p_this);

};

} /* namespace TF */


#endif /* TF_THREAD_H_ */
