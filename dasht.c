/*
 * Beth Boose proj 1 alastlog
 * dasht.c handle -t and no options selected
 *  functionality
 */

#include <pwd.h>
#include <time.h>
#include <utmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "dasht.h"
#include "llib.h"
#include "lloutput.h"
#include "passwdfunc.h"

struct passwd *pwd;
struct lastlog llbuf[DEF_NUMRECS];
int fd;
int cur;
int num;

long gettimeframe(char* daystr){
    long timeframe;
    char *endofdaystr;
    errno = 0;
    // convert input
    long days = strtol(daystr, &endofdaystr, 10);    
    if (errno != 0) {
        return -1;
    }
    
    if ((days) <= 0) {
        return -1;
    }
    timeframe = days * DAYS_FACTOR;
    return timeframe;
}

/* print all users who logged in since days
 * if days is -1, return all users
 * FIXME - catch integer overflow
 * FIXME - catch not a number
 * FIXME - handle -tf
 */
void printusers(char *daystr, char *filename) {
    struct passwd *pwd;
    long timeframe; /* convert number of days to epoch */
    cur = 0;
    num = 0;

    if (filename == NULL) {
        filename = LLFILE;
    }

    timeframe = gettimeframe(daystr);
    if( timeframe <= 0 ) {
        fprintf(stderr, "please select a valid number greater than 0\n");
        exit(EXIT_FAILURE);
    }

    // open lastlog
    if ((fd = lastlog_open(filename)) == -1) { // open lastlog
        fprintf(stderr, "could not open selected lastlog file");
        exit(EXIT_FAILURE);
    }

    struct lastlog *llrec = NULL;
    unsigned long currenttime = (unsigned long) time(NULL); // right now
    print_header();
    while ((pwd = getpwent()) != NULL) { // loop thru passwd

        /* find this uid in buffer - if its not there, keep it moving
         * don't reload unless you can't find it
         */
        llrec = lastlog_next(fd, &cur, &num, llbuf);

        if (llrec != NULL) {
            long stampplustimeframe = llrec->ll_time + timeframe;
            
            if (( llrec->ll_line[0] != '\0' ) 
                    && ( stampplustimeframe > currenttime ) ) {
                printf("got something %s", llrec->ll_line);
                printf(" %s\n", llrec->ll_host);
            }
        }

    }
}



