# TinyFramework

## Description

TinyFramework is a minimal C++ framework for embedded use. (e.g. on Microcontrollers)
It is intended as a minimal Object Oriented wrapper around common RTOS features like tasks,
semaphores etc. and providing an OS/HW abstraction layer to avoid using the complex
OS API directly to allow easier usage, porting and testing.
The API is somewhat inspired by Python classes (Event, PySerial etc.).
This software is MIT licensed and use for whatever purpose is granted. However offering back
improvements is encouraged.

### OS abstractions
- Zephyr OS
- Linux
- FreeRTOS (partial)

## Guidelines
- Only expose actually used features. Rather evolve and tailor the API to be lean and fit for purpose
  rather than building in tons of unused provisions.
- API breakage is allowed, but backwards compatibility is preferred (e.g. by adding default arguments).
- Handle errors at the lowest level. Avoid punting errors upwards, instead add liberal logging.
- Use native C/C++ types including stdint instead of OS specific types.
- Avoid large stack allocation. Using class members instead will enable static allocation.
- Log and debug strings should be as short as possible.

These features should be avoided to ensure fitness for embedded systems:
- Dynamic memory allocations - class members preferred, stack secondary.
- Exceptions
- stdlib (use only with great care regarding dynamic memory allocation and threading re-entrance!)
- stdio (printf() etc.) - should only be used in the logging system

## Todo
- Doxygenize to document API
- Make OS specific header files to allow cleaner API level include files and more inlining
- Make logging macros instead of functions (to be able to remove debug code from compilation etc.)
- Make logging buffered, less invasive and support OS backends (Zephyr? semihosting?)
- Improve test
