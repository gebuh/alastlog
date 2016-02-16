
# This is a makefile.  A makefile contains rules that tell
# how to build a program, often from separate source files
#
# This sample makefile shows how to build dumputmp from
# the two source files dumputmp.c and utmplib.c
#
# You must modify this file so it contains rules to make
# your solution to the project
# (note: the indented lines MUST start with a single tab
#
CFLAGS = -Wall
SRC = $(wildcard *.c)
DEPS := $(wildcard *.h)
OBJS := $(SRC: .c=.o)
	
alastlog: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)
	
clean:
	rm -f *.o core alastlog
	