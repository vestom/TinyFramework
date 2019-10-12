# TinyFramework

## Description

TinyFramework is a minimal C++ framework for embedded use.
It is intended as a minimal Object Oriented wrapper around common OS features like tasks, 
semaphores etc. and providing an OS/HW abstraction layer to avoid using the OS API directly 
to allow easy porting and testing.
The API is intended to be somewhat similar to Python classes (Event, PySerial etc.).

### OS abstractions
- Linux
- Zephyr OS
- FreeRTOS (partial)

## Guidelines
- Only expose actually used features. Rather evolve and tailor the API for purpose than building in tons of provisions.
- API breakage is allowed, but backwards compatibility is preferred (e.g. by adding default arguments).
- Handle errors at the lowest level. Avoid punting errors upwards, but add liberal logging.
- Use native C/C++ types including stdint instead of OS specific types.
- Avoid large stack allocation. Using class members instead will enable static allocation.
- Log and debug strings should be as short as possible.

These features should be avoided to ensure fitness for embedded systems:
- Dynamic memory allocations
- Exceptions
- stdlib
- stdio (printf() etc.)