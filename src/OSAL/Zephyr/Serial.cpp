/*
 * Serial.cpp
 *
 *  Created on: Sep 25, 2019
 *      Author: tov
 */

#include "TF/TF.h"
#ifdef _TF_OS_ZEPHYR_

#include "TF/Serial.h"
#include "TF/Log.h"
#include <zephyr.h>
#include <drivers/gpio.h>
#include <drivers/uart.h>

//#define TF_SERIAL_POLLED        1
#define TF_SERIAL_TXEN_CONTROL  1
#define TF_SERIAL_TXEN_PORT     "GPIOA"
#define TF_SERIAL_TXEN_PIN      1
#define TF_SERIAL_TEST_PIN      0

namespace TF {

Serial::Serial() {
}

Serial::~Serial() {
}

bool Serial::open(unsigned baudrate) {
    int ret;
    z_uart_dev = device_get_binding("UART_2");
    if(z_uart_dev == NULL) { Log::error("device_get_binding()"); return false; }

#ifdef TF_SERIAL_TXEN_CONTROL
    z_gpio_dev = device_get_binding(TF_SERIAL_TXEN_PORT);
    if(z_gpio_dev == NULL) { Log::error("device_get_binding()"); return false; }
    gpio_pin_configure(z_gpio_dev, TF_SERIAL_TXEN_PIN, GPIO_DIR_OUT);
    gpio_pin_write(z_gpio_dev, TF_SERIAL_TXEN_PIN, 0);
//gpio_pin_configure(z_gpio_dev, TF_SERIAL_TEST_PIN, GPIO_DIR_OUT);
#endif

    // Configure
    struct uart_config cfg = {
        .baudrate   = baudrate,
        .parity     = UART_CFG_PARITY_NONE,
        .stop_bits  = UART_CFG_STOP_BITS_1,
        .data_bits  = UART_CFG_DATA_BITS_8,
        .flow_ctrl  = UART_CFG_FLOW_CTRL_NONE
    };
    ret = uart_configure(z_uart_dev, &cfg);
    if(ret) { Log::error("uart_configure(): %i", ret); return false; }

    uart_irq_callback_user_data_set(z_uart_dev, (uart_irq_callback_user_data_t)&z_uart_isr, (void *)this);
    uart_irq_rx_enable(z_uart_dev);

    return true;
}

int Serial::read(uint8_t* buffer, unsigned count) {
    for (unsigned n=0; n<count; n++) {
        while(getRxBytes() == 0) {  // Wait until something is received
            rx_event.wait();
        };
        buffer[n] = rx_fifo[rx_tail];
        rx_tail = (rx_tail+1) % sizeof(rx_fifo);
    }
    return count;
}

void Serial::write(uint8_t* buffer, unsigned count) {
    if(z_gpio_dev) {    // Assert TX enable
        gpio_pin_write(z_gpio_dev, TF_SERIAL_TXEN_PIN, 1);
    }

    // Polled
    for(unsigned n=0; n<count; n++) {
#ifdef TF_SERIAL_POLLED
        uart_poll_out(z_uart_dev, buffer[n]);
#else   // Interrupt driven
        while(((tx_head - tx_tail) % sizeof(tx_fifo)) >= sizeof(tx_fifo)-1) { // Buffer full
            k_sleep(1); // OK to busy wait due to FIFO
        }
        tx_fifo[tx_head] = buffer[n];
        tx_head = (tx_head+1) % sizeof(tx_fifo);
#endif
        uart_irq_tx_enable(z_uart_dev); // Enable transmission
    }
}

void Serial::flushRxBuffer(void) {
    unsigned key = irq_lock();
    rx_head = rx_tail = 0;
    irq_unlock(key);
}

int Serial::getRxBytes(void) {
    return (rx_head - rx_tail) % sizeof(rx_fifo);
}


void Serial::z_uart_isr(Serial *pThis) {
//    static int test = 0;
    int ret;
    int tx_ready, tx_complete;
    size_t rx_bytes;
    uart_irq_update(pThis->z_uart_dev); // Must always be called once in beginning
// gpio_pin_write(pThis->z_gpio_dev, 0, (test++)&1);

    // Rx
    ret = uart_irq_rx_ready(pThis->z_uart_dev);
    while(ret > 0) {
        // Drain buffer
        ret = uart_fifo_read(pThis->z_uart_dev, pThis->rx_fifo+pThis->rx_head, 1);
        if(ret) {
            rx_bytes = (pThis->rx_head - pThis->rx_tail) % sizeof(rx_fifo);
            // If RX FIFO is not full, advance head
            // otherwise just overwrite last byte...
            if (rx_bytes < sizeof(rx_fifo)-1) {
                pThis->rx_head = (pThis->rx_head+1) % sizeof(rx_fifo);
            }
        }
        pThis->rx_event.set();
    }

    // Tx
    tx_ready = uart_irq_tx_ready(pThis->z_uart_dev);
    while(tx_ready > 0 && (pThis->tx_tail != pThis->tx_head)) {
        ret = uart_fifo_fill(pThis->z_uart_dev, pThis->tx_fifo+pThis->tx_tail, 1);
        if(ret) {
            pThis->tx_tail = (pThis->tx_tail+1) % sizeof(tx_fifo);
        }
        tx_ready = uart_irq_tx_ready(pThis->z_uart_dev);
    }

    // Tx complete
    tx_complete = uart_irq_tx_complete(pThis->z_uart_dev);
    if((tx_complete > 0) && (pThis->tx_tail == pThis->tx_head)) {
        uart_irq_tx_disable(pThis->z_uart_dev); // Turn off!
        if(pThis->z_gpio_dev) {     // Deassert TXEN
            gpio_pin_write(pThis->z_gpio_dev, TF_SERIAL_TXEN_PIN, 0);
        }
    }
}


} /* namespace TF */

#endif
