
#include "dashu.h"
#include "dasht.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <getopt.h>


static const char *optstr = "t:u:f:h?";

static void print_usage() {
    printf("Usage: alastlog [options]\n");
    printf("Options: \n");
    printf("-t N days   print alastlog records more recent than N days\n");
    printf("-u USER     print alastlog record for USER\n");
    printf("-f FILENAME print alastlog records from FILENAME\n");
    printf("-h          print usage\n");
}

int main(int argc, char * argv[]) {
    int opt; 
    opt = getopt(argc, argv, optstr);

    while (opt != -1) {

        switch (opt) {
            case 't':
                printusers(optarg, NULL);
                break;
            case 'u':
                printuser(optarg);
                break;
            case 'f':
                printf("f\n");
                break;
            case 'h':
                printf("h\n");
                print_usage();
                break;
            default:
                print_usage();
                break;
        }
        opt = getopt(argc, argv, optstr);
    }

    exit(EXIT_SUCCESS);
}
