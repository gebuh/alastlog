/* 
 * File:   dasht.h
 * Author: Beth Boose
 * handle retrieving lastlog entries previous to x days
 * or all if days = -1
 */

#define DAYS_FACTOR 24 * 60 * 60

void printusers( char *daystr, char *filename );

