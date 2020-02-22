/*
 * zephyr_extras.cpp
 * Abstract zephyr specific console functions
 *
 *  Created on: 2020-02-22
 *      Author: tov
 */
#include "TF/TF.h"
#ifdef _TF_OS_ZEPHYR_

#include "TF/Zephyr/zephyr_extras.h"
#include <ctype.h>

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
