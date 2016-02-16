/* handle alastlog output formating */

#include <stdio.h>
#include <time.h>
#include <utmp.h>
#include "lloutput.h"

/*
 * TODO - CLEAN UP title FORMATTING
 */
void print_header() {
    printf("Username    Port    From    Latest\n");
}
/* TODO - CLEAN UP FORMATTING
 * TODO HANDLE NEVER LOGGED IN USER 
 */
void show_info(char *name, struct lastlog *llbufp) {
    printf("%s", name); 
    printf(" ");
    printf("%-12.12s", llbufp->ll_line); 
    printf(" ");
    printf("%.16s", llbufp->ll_host);
    printf(" ");
    show_time(llbufp->ll_time, DATE_FMT);
    printf("\n");

}

void show_time(time_t timeval, char *fmt) {
    char result[MAXDATELEN];
    struct tm *tp = localtime(&timeval);
    strftime(result, MAXDATELEN, fmt, tp);
    fputs(result, stdout);
}

