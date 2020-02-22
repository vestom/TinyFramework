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
#include "TF/GPIO.h"
#include "TF/Event.h"
#include <drivers/uart.h>
#endif

// Configurables
#ifndef TF_SERIAL_RX_FIFO_SIZE
#define TF_SERIAL_RX_FIFO_SIZE 16
#endif
#ifndef TF_SERIAL_TX_FIFO_SIZE
#define TF_SERIAL_TX_FIFO_SIZE 16
#endif


namespace TF {

/// Serial communication class
class Serial {
public:
    /// \param txen is used to indicate if a GPIO should be used to enable
    /// a serial transmitter (e.g. for EIA485)
    Serial(GPIO *txen=NULL): gpio_txen(txen) {};

#ifdef _TF_OS_LINUX_
    ~Serial();
#endif

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
    GPIO *gpio_txen;    // GPIO to use for TX Enable

#ifdef _TF_OS_LINUX_
    int fd;
#endif
#ifdef _TF_OS_ZEPHYR_
    struct device *z_uart_dev;
    struct device *z_gpio_dev;
    static void z_uart_isr(Serial *pThis);
    u8_t rx_fifo[TF_SERIAL_RX_FIFO_SIZE];
    u8_t tx_fifo[TF_SERIAL_TX_FIFO_SIZE];
    volatile size_t	rx_head = 0, rx_tail = 0;
    volatile size_t	tx_head = 0, tx_tail = 0;
    Event rx_event;
#endif

};

} /* namespace TF */

#endif /* TF_SERIAL_H_ */
