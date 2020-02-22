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
