/* llib.c - buffering functions for alastlog
 * int lastlog_open(file)
 * struct lastlog *lastlog_next() - ptr to next struct or NULL on EOF or read err
 * int lastlog_close()
 */

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <utmp.h>
#include<unistd.h>
#include "llib.h"

/* just open the file, do your own error handling */
int lastlog_open(char *filename) {
    int fd = open(filename, O_RDONLY);
    return fd;
}

/* handle cur and num in calling func*/
struct lastlog *lastlog_next(int fd, int *curptr, int *numptr, 
        struct lastlog *llbuf) {
    struct lastlog *recp;

    if (fd == -1) {
        fprintf(stderr, "this is not a valid file descriptor\n");
        return NULL;
    }

    if (*curptr == *numptr) { // reload
        
        if (lastlog_reload(fd, curptr, numptr, llbuf) == -1) {
            printf("reached end of lastload \n");
            return NULL;
        }
    }
    recp = &(llbuf[*curptr]);
    (*curptr)++;
    return recp;
}

/* read next records into buffer
 * return num records read or 0 - EOF or -1 for
 * error
 */
int lastlog_reload(int fd, int *curptr, int *numptr, struct lastlog *llbuf) {
    int amt_read;
    amt_read = read(fd, llbuf, DEF_NUMRECS * LLSIZE);
    if (amt_read < 0) {
        return -1;
    }
   
    *numptr = amt_read / LLSIZE;
    *curptr = 0;
    return *numptr;
}

/* if file is open close it and mark the fd as closed */
int lastlog_close(int fd) {
    int rv = 0;
    if (fd != -1) {
        rv = close(fd);
        fd = -1;
    }
    return rv;
}

/** find a location in fd_ll based on uid and offset
 * if offset = SEEK_SET start at the beginning of file
 * offset = SEEK_CUR move relative to starting point
 * offset = SEEK_END go to the end of the file
 * lseek takes a number of bytes (in this case uid, because of the way
 * lastlog works - a the distance from the beginning of lastlog db)
 * the type of offset and returns the distance from the beginning of 
 * your file discriptor
 */
off_t seekinll(int fd, uid_t uid, int offsettype) {
    off_t offset = lseek(fd, uid*LLSIZE, offsettype);
    return offset;
}
