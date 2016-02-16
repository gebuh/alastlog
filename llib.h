/* 
 * File:   llib.h
 * Author: Beth Boose
 * functions for navigating/buffering lastlog
 */

#include <utmp.h>
#include <sys/types.h>
#include <unistd.h>

#define LLFILE "/var/log/lastlog"  /* default value for lastlog */
#define DEF_NUMRECS 5
#define LLSIZE ( sizeof ( struct lastlog ) )

int lastlog_open( char *filename );
struct lastlog *lastlog_next(int fd, int *curptr, int *numptr, 
        struct lastlog *llbuf);
int lastlog_close(int fd);
int lastlog_reload(int fd, int *curptr, int *numptr, struct lastlog *llbuf);
off_t seekinll  ( int fd_ll, uid_t uid, int offset );

