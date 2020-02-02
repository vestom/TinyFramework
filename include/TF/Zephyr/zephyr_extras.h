// Abstract zephyr specific console functions
#ifdef _TF_OS_ZEPHYR_
#include <console/console.h>
#include <ctype.h>


// <stdio.h> helpers
#define getchar()   (console_getchar())
#define putchar(c)  (console_putchar(c))
#define puts(s)     (console_write(NULL,s,sizeof(s)))

// Implement fgets() from <stdio.h>
#ifndef fgets
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
#endif //fgets

// Implement atoi() from <stdlih.h>
#ifndef atio
int atoi(const char * str) {
    int result = 0, neg = 0;
    while(isspace(*str)) { str++; } // Skip initial whitespace
    if(*str=='+')   { str++; }      // Skip + sign
    else if(*str=='-')   { neg = 1; str++; }    // Negative?
    while(isdigit(*str)) { result*=10; result+=((*str++)-'0'); }
    if(neg) result = -result;
    return result;
}
#endif // atoi

#endif
