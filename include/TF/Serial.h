/*
 * Serial.h
 *
 *  Created on: Oct 19, 2016
 *      Author: tov
 */

#ifndef TF_SERIAL_H_
#define TF_SERIAL_H_

#include "TF/TF.h"

#ifdef _TF_OS_ZEPHYR_
#include "TF/Event.h"
#include <drivers/uart.h>
#endif

namespace TF {

class Serial {
public:
    Serial();
    ~Serial();

    /// Open the serial port
    /// Return true if OK and false on error
    bool open(const char *port, unsigned baudrate=19200);

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

#ifdef _TF_OS_ZEPHYR_
    #define TF_SERIAL_FIFO_SIZE 16

    struct device *z_uart_dev;
    struct device *z_gpio_dev;
    static void z_uart_isr(Serial *pThis);
    u8_t rx_fifo[TF_SERIAL_FIFO_SIZE];
    u8_t tx_fifo[TF_SERIAL_FIFO_SIZE];
    volatile size_t	rx_head = 0, rx_tail = 0;
    volatile size_t	tx_head = 0, tx_tail = 0;
    Event rx_event;
#endif

};

} /* namespace TF */

#endif /* TF_SERIAL_H_ */
