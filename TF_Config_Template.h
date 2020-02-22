// Template file for configuring TinyFramework
// Tailor and rename to TF_Config.h and ensure it is within compiler include path

// Select log output
//#define _TF_LOG_FILE_ stderr

// Enable low level debug
//#define _TF_DEBUG_

// Set size of serial FIFOs
//#define TF_SERIAL_RX_FIFO_SIZE 16
//#define TF_SERIAL_TX_FIFO_SIZE 16

// Zephyr: Enable dynamic memory support
// Needs CONFIG_HEAP_MEM_POOL_SIZE=XXX set in Zephyr project
//#define TF_ZEPHYR_DYNAMIC_MEMORY
// Zephyr: Enable debug printouts when using dynamic memory
//#define TF_DEBUG_ZEPHYR_DYNAMIC_MEMORY