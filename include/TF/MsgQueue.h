/*
 * MsgQueue.h
 *
 *  Created on: Oct 19, 2016
 *      Author: tov
 */

#ifndef TF_MSGQUEUE_H_
#define TF_MSGQUEUE_H_

#include <stdint.h>

#include "TF/Mutex.h"
#include "TF/Event.h"

namespace TF {

class MsgQueue {
public:
	MsgQueue();
	virtual ~MsgQueue();

	void send(uint8_t *buffer, size_t nBytes);

	/// Receive a message
	/// Returns number of bytes received
	int receive(uint8_t *buffer, size_t maxBytes, unsigned timeout_ms=0);

	/// Returns number of messages available in queue
	int getMessagesInQueue();

	static const unsigned MAX_MSG_LEN = 256;
	static const unsigned MAX_NUM_MSG = 16;

private:
	Event txevent;
	Mutex mutex;
	volatile uint8_t msg_data[MAX_MSG_LEN][MAX_NUM_MSG];
	volatile size_t  msg_size[MAX_NUM_MSG];
	volatile size_t tail;
	volatile size_t num_msg;
};

} /* namespace TF */

#endif /* TF_MSGQUEUE_H_ */
