/* header file declaration for output functions in lloutput.c */
#include <utmp.h>
#include <time.h>

#define MAXDATELEN 100
#define TEXTDATE
#ifndef DATE_FMT
#ifdef TEXTDATE
#define DATE_FMT "%a %b %e %H:%M:%S %z %Y" /* text format*/
#else
#define DATE_FMT "%Y-%m-%d %H:%M" /* the default*/
#endif
#endif

void show_info ( char *name, struct lastlog *llbufp );
void show_time ( time_t timeval, char *fmt );
void print_header();
