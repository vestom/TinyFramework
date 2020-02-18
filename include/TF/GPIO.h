/*
 * GPIO.h
 *
 *  Created on: Sep 29, 2019
 *      Author: tov
 */

#ifndef TF_GPIO_H_
#define TF_GPIO_H_

#include "TF/TF.h"
#include "TF/Log.h"

namespace TF {

class GPIO_Interface {
public:
    /// Set pin on or off
    virtual void set(bool on) = 0;

    /// Set value of pin
    virtual bool get(void) = 0;
};


// TODO: Refactor OS specific classes to separate files

#ifdef _TF_OS_LINUX_

class GPIO : GPIO_Interface {
public:
    GPIO(const char* _port, unsigned _pin) :
        port(_port),
        pin(_pin)
    { };

    ~GPIO() {};

    void set(bool on) {
        TF::Log::debug("TF::GPIO::set %s %u %c", port, pin, on ? '1':'0');
        value = on;
    }

    bool get(void) {
        return value;
    }

private:
    const char* port;
    const unsigned pin;
    bool value;
};

#endif
#ifdef _TF_OS_FREERTOS_
// TODO:
#endif
#ifdef _TF_OS_ZEPHYR_
#include <drivers/gpio.h>

class GPIO : GPIO_Interface {
public:
    GPIO(const char* port, unsigned _pin) :
        pin(_pin)
    {
        z_gpio_dev = device_get_binding(port);
        if(z_gpio_dev == NULL) { TF::Log::error("GPIO device_get_binding()"); return; }
        gpio_pin_configure(z_gpio_dev, pin, GPIO_DIR_OUT);
    };
    ~GPIO() {};

    void set(bool on) {
        gpio_pin_write(z_gpio_dev, pin, on ? 1:0);
    }

    bool get(void) {
        u32_t value;
        gpio_pin_read(z_gpio_dev, pin, &value);
        return value;
    }

private:
    struct device *z_gpio_dev;
    const unsigned pin;
};

#endif


} /* namespace TF */

#endif /* TF_GPIO_H_ */
