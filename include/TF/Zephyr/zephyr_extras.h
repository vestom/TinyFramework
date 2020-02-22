/*
 * zephyr_extras.h
 * Abstract zephyr specific console functions
 *
 *  Created on: Sep 29, 2019
 *      Author: tov
 */
#ifndef TF_ZEPHYR_EXTRAS_H_
#define TF_ZEPHYR_EXTRAS_H_

#include "TF/TF.h"
#ifdef _TF_OS_ZEPHYR_
#include <console/console.h>

// Add various functions missing from Zephyrs newlibc

// Implement heap allocation routines (See: https://docs.zephyrproject.org/latest/reference/kernel/memory/heap.html)
#ifdef TF_ZEPHYR_DYNAMIC_MEMORY

#define malloc(s) (_tf_malloc(s, __FILE__, __LINE__))
#define free(p) (_tf_free(p, __FILE__, __LINE__))

inline void* _tf_malloc(size_t size, const char *file, int line) {
    void *p = k_malloc(size);
    #ifdef TF_DEBUG_ZEPHYR_DYNAMIC_MEMORY
        TF::Log::debug("malloc(%u): %p, %s:%i", size, p, file, line);
    #endif
    return p;
}

inline void _tf_free(void *p, const char *file, int line) {
    k_free(p);
    #ifdef TF_DEBUG_ZEPHYR_DYNAMIC_MEMORY
        TF::Log::debug("free(%p), %s:%i", p, file, line);
    #endif
}
#endif // TF_ZEPHYR_DYNAMIC_MEMORY

// <stdio.h> helpers
#define getchar()   (console_getchar())
#define putchar(c)  (console_putchar(c))
#define puts(s)     (console_write(NULL,s,sizeof(s)))

// fgets() from <stdio.h>
char * fgets(char *str, int maxlen, void * unused);

// atoi() from <stdlih.h>
int atoi(const char * str);

#endif /* _TF_OS_ZEPHYR_ */
#endif /* TF_ZEPHYR_EXTRAS_H_ */
