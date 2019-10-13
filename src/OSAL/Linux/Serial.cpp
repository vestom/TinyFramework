/*
 * Serial.cpp
 *
 *  Created on: Oct 19, 2016
 *      Author: tov
 */

#include "TF/TF.h"
#ifdef _TF_HAL_LINUX_

#include "TF/Serial.h"
#include "TF/Log.h"

#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
//#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <sys/ioctl.h> /* ioctl() */
#include <errno.h>   /* errno */
#include <string.h>   /* strerror() */


namespace TF {

Serial::Serial() {
    fd = 0;
}

Serial::~Serial() {
    if(fd) {
        close(fd);
        Log::debug("Closed serial");
    }
}

bool Serial::open() {
    int ret;
    struct termios options;

    fd = ::open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);	// O_NDELAY = No delay
    if(fd == -1) { Log::error("Could not open /dev/ttyUSB0: %s", strerror(errno)); return false; }
    //ret = fcntl(fd, F_SETFL, FNDELAY);	// Do not block
    ret = fcntl(fd, F_SETFL, 0);	// Blocking behaviour
    if(ret == -1) { Log::error("fcntl() failed: %s ", strerror(errno)); return false; }

    // Get the current options for the port...
    ret = tcgetattr(fd, &options);
    if(ret) { Log::error("tcgetattr() failed with %i", ret); return false; }
    // Set the baud rates to 19200...
    ret = cfsetispeed(&options, B19200);
    if(ret) { Log::error("cfsetispeed() failed with %i", ret); return false; }
    ret = cfsetospeed(&options, B19200);
    if(ret) { Log::error("cfsetospeed() failed with %i", ret); return false; }
    // Parity 8N1
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    // Disable HW flow ctrl
    options.c_cflag &= ~CRTSCTS;
    // Enable the receiver and set local mode...
    options.c_cflag |= (CLOCAL | CREAD);
    // Raw input
    options.c_lflag = 0;
    options.c_iflag = 0;
    // Raw output
    options.c_oflag = 0;
    // Set the new options for the port...
    ret = tcsetattr(fd, TCSANOW, &options);
    if(ret) { Log::error("tcsetattr() failed with %i", ret); return false; }

    return true;
}

int Serial::read(uint8_t* buffer, unsigned count) {
    int ret = ::read(fd, buffer, count);
    if (ret == -1) { Log::error("Serial read(\"..\", %i) failed: %s", count, strerror(errno)); }
    return ret;
}

void Serial::write(uint8_t* buffer, unsigned count) {
    int ret = ::write(fd, buffer, count);
    if (ret != (int)count) Log::error("Serial write(\"..\", %i) failed: . Returned %i", count, ret);
}

void Serial::flushRxBuffer(void) {
    int ret = tcflush(fd, TCIFLUSH);
    if(ret) { Log::error("tcflush() failed with %i", ret); }
}

int Serial::getRxBytes(void) {
    int bytes;
    int ret = ioctl(fd, FIONREAD, &bytes);
    if(ret) { Log::error("ioctl() failed with %i", ret); }
    return bytes;
}

} /* namespace TF */

#endif
