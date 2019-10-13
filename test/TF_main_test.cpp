/*
 * TF_main_test.cpp
 *
 *  Created on: Oct 19, 2016
 *      Author: tov
 */


#include <stdio.h>
#include "TF/TF.h"

// Avoid compiling if source file is added by accident in top project
#ifdef _TF_TEST_


#include "TF/Log.h"
#include "TF/Serial.h"
#include "TF/Thread.h"
#include "TF/Timer.h"
#include "TF/Event.h"
#include "TF/MsgQueue.h"


TF::Event event;
TF::MsgQueue queue;
TF::Serial serial;

class MyThread1 : public TF::Thread {
    void run() {
        while(1) {
            TF::Log::debug("MyThread1");
            queue.send((uint8_t*)"MSG1", 256);
            queue.send((uint8_t*)"MSG2", 8);
            TF::Thread::sleep_ms(100);
        }
    }
};

class MyThread2 : public TF::Thread {
    void run() {
        char string[8];
        while(1) {
            queue.receive((uint8_t*)string, sizeof(string));
            TF::Log::debug(string);
        }
    }
};

class MyThread3 : public TF::Thread {
    void run() {
        uint8_t rxBuffer[32];
        char str[256];
        int ret, rest;

        serial.flushRxBuffer();
        while(1) {
//			TF::Log::debug("Read()...");
            serial.flushRxBuffer();
            ret = serial.read(rxBuffer, 1);
            if (ret != 1) { TF::Log::debug("read() returned %i", ret); }
            rest = serial.getRxBytes();
            if (rest>0) {
                rest = ((rest > 15) ? 15 : rest);
                ret += serial.read(rxBuffer+1, rest);
            }
            // Bin2Hex
            for (int n=0; n<ret; ++n) {
                snprintf(str+n*2, sizeof(str)-n*2, "%02X", (unsigned)rxBuffer[n]);
            }
            TF::Log::debug("Received [%u] : %s @ %li us", ret, str, TF::Timer::get_tick()/1000);
        }
    }
};


int main(int argc, char *argv[]) {
//	TF::Log::setLogDebug(false);
    TF::Log::error("Test");
    TF::Log::debug("Test");
    TF::Thread::sleep_ms(0);

    MyThread1 myThread1; myThread1.start();
    MyThread2 myThread2; myThread2.start();

//	TF::Thread::sleep_ms(10);
    MyThread3 myThread3; myThread3.start();
    TF::Thread::sleep_ms(10);
    uint8_t buffer[5] = {0x01, 0x02, 0x0F, 0xF0, 0x00};
//	serial.write(buffer, 5);

    TF::Thread::sleep_ms(10000);
    return 0;
}

#endif // _TF_TEST_

