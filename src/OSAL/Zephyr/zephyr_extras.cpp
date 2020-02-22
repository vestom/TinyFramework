/*
 * zephyr_extras.cpp
 * Abstract zephyr specific console functions
 *
 *  Created on: 2020-02-22
 *      Author: tov
 */
#include "TF/TF.h"
#ifdef _TF_OS_ZEPHYR_
#include "TF/Log.h"

#include "TF/Zephyr/zephyr_extras.h"
#include <ctype.h>


// Pure virtual function error handler for C++
extern "C" void __cxa_pure_virtual() {
    TF::Log::error("__cxa_pure_virtual() called!!");
    k_oops();     // Halt!
}

#ifdef TF_ZEPHYR_DYNAMIC_MEMORY

void * operator new(size_t n) {
    void * const p = malloc(n);
    if(p == NULL) {
        TF::Log::error("new(%u) failed!!", n);
        k_oops();     // Halt!
    }
    return p;
}

void operator delete(void * p) {
    free(p);
}

#else // TF_ZEPHYR_DYNAMIC_MEMORY
// Provide a dummy delete function for virtual destructors
void operator delete(void * p) {
    TF::Log::error("delete(%p) called!!", p);
    k_oops();     // Halt!
}
#endif // TF_ZEPHYR_DYNAMIC_MEMORY

// Implement fgets() from <stdio.h>
char * fgets(char *str, int maxlen, void * unused) {
    int n=0;
    char c;
    while(n < maxlen-1) {
        c = getchar();
        if(c == '\r') { c = '\n'; } // Convert return to newline
        str[n++] = c;
        if(c == '\n') break;
    }
    if(n > 0) str[n] = 0;
    return str;
}

// Implement atoi() from <stdlih.h>
int atoi(const char * str) {
    int result = 0, neg = 0;
    while(isspace(*str)) { str++; } // Skip initial whitespace
    if(*str=='+')   { str++; }      // Skip + sign
    else if(*str=='-')   { neg = 1; str++; }    // Negative?
    while(isdigit(*str)) { result*=10; result+=((*str++)-'0'); }
    if(neg) result = -result;
    return result;
}

#endif
