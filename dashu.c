/*
 * Beth Boose proj 1 alastlog
 * dashu.c handle -u functionality
 */

#include "llib.h"
#include "lloutput.h"
#include "passwdfunc.h"
#include <stdio.h>
#include <utmp.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

struct passwd *pwd;
struct lastlog llbuf[DEF_NUMRECS]; /* pointer to current buffer */


int fd;
off_t offset;

/**
 * FIXME HANDLE -uf
 * @param name
 */
void printuser(char *name) {
    /* get uid from passwd we only need the id tho */
    pwd = getpwdbyusr(name);
    if (pwd == NULL) {
        fprintf(stderr, "I can't help you if you don't give me "
                "a valid user name\n");
        exit(EXIT_FAILURE);
    } else {
        if ((fd = lastlog_open(LLFILE)) == -1) {
            fprintf(stderr, "could not open lastlog file");
            exit(EXIT_FAILURE);
        }

        if ((seekinll(fd, pwd->pw_uid, SEEK_SET)) == -1) {
            fprintf(stderr, "could not find user in lastlog file");
            exit(EXIT_FAILURE);
        }

        int cur = 0;
        int num = 0;

        /* overkill, but ... get the buffer starting at what we're 
         * looking for, in this case, I don't care how many records
         * were read, as long as its a positive amt  */
        struct lastlog *llrec = lastlog_next(fd, &cur, &num, llbuf);
        if (llrec != NULL) {
            print_header();
            show_info(pwd->pw_name, llrec);
        }

        lastlog_close(fd);

    }

}



