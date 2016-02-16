/*
 * Beth Boose proj 1 alastlog
 * passwdfunc.c handle passwd functions
 */

#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>

struct passwd *pwd;

struct passwd *getpwdbyusr(char *name) {
    pwd = getpwnam(name);
    endpwent();
    return pwd;
}

struct passwd *getpwdbyuid(uid_t uid) {
    pwd = getpwuid( uid );
    return pwd;
}

void printname(uid_t uid) {
    struct passwd *pwd;


    setpwent();
    while ((pwd = getpwent()) != NULL) {
        if (pwd->pw_uid == uid) {
            printf("name=%s\n", pwd->pw_name);
            break;
        }
    }
    endpwent();
}


