/* 
 * File:   passwdfunc.h
 * Author: Beth Boose
 * functions for retrieving user info from passwd
 */

#include <pwd.h>

struct passwd *getpwdbyusr ( char *name );
struct passwd *getpwdbyuid(uid_t uid);
void printname(uid_t uid);


