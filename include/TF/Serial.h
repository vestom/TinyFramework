/*
 * Serial.h
 *
 *  Created on: Oct 19, 2016
 *      Author: tov
 */

#ifndef TF_SERIAL_H_
#define TF_SERIAL_H_

#include <stdint.h>

namespace TF {

class Serial {
public:
	Serial();
	virtual ~Serial();

	/// Open the serial port
	/// Return true if OK and false on error
	bool open(void);

	/// Blocking read with timeout
	int read(uint8_t *buffer, unsigned count);

	/// Unblocking write. May block if transmit buffer is full
	void write(uint8_t *buffer, unsigned count);

	/// Flush receive buffer
	void flushRxBuffer(void);

	/// Return number of bytes in Rx buffer
	int getRxBytes(void);


private:
	int fd;

};

} /* namespace TF */

#endif /* TF_SERIAL_H_ */
