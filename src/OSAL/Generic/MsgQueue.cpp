/*
 * MsgQueue.cpp
 *
 *  Created on: Oct 19, 2016
 *      Author: tov
 */

#include "TF/TF.h"

#include "TF/MsgQueue.h"
#include "TF/Log.h"
#include <string.h>


namespace TF {

MsgQueue::MsgQueue() {
}

MsgQueue::~MsgQueue() {
    // TODO Auto-generated destructor stub
}

void TF::MsgQueue::send(uint8_t* msg, size_t nBytes) {
    if(nBytes > MAX_MSG_LEN) {
        Log::error("send(): nBytes = %u too big", nBytes);
        nBytes = MAX_MSG_LEN;
    }
    mutex.lock();
    if (num_msg >= MAX_NUM_MSG) {
        Log::error("MsgQueue is full");
    } else {
            size_t index = (tail+num_msg) % MAX_NUM_MSG;
            memcpy((void*)msg_data[index], (void*)msg, nBytes);
            msg_size[index] = nBytes;
            num_msg++;
            txevent.set();
    }
    mutex.unlock();
}

int TF::MsgQueue::receive(uint8_t* buffer, size_t maxBytes, unsigned timeout_ms) {
    while (num_msg == 0) {
        txevent.wait(timeout_ms);
    }
    mutex.lock();
    size_t numBytes = ((maxBytes < msg_size[tail]) ? maxBytes : msg_size[tail]); // MIN
    memcpy((void*)buffer, (void*)msg_data[tail], numBytes);
    tail = (tail+1) % MAX_NUM_MSG;
    num_msg--;
    mutex.unlock();
    return numBytes;
}

int TF::MsgQueue::getMessagesInQueue() {
    return (num_msg);
}

} /* namespace TF */
