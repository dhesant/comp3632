# Sources for exectuables
C_SRCS = change.cpp functions.cpp
A_SRCS = anonymize.cpp functions.cpp
AF_SRCS = anonymize_full.cpp functions_full.cpp

##################################################
# DO NOT TOUCH BELOW THIS (Makefile Magic)
##################################################

CC=g++
CFLAGS=-Wall -std=c++11 -O3
LDFLAGS=

C_OBJS=$(C_SRCS:.cpp=.o)
A_OBJS=$(A_SRCS:.cpp=.o)
AF_OBJS=$(AF_SRCS:.cpp=.o)

all: release

debug: CFLAGS+=-g -DDEBUG
debug: LDFLAGS+=-g
debug: release

release: change anonymize anonymize_full

change: $(C_OBJS)
	$(CC) $(LDFLAGS) $^ -o change

anonymize: $(A_OBJS)
	$(CC) $(LDFLAGS) $^ -o anonymize

anonymize_full: $(AF_OBJS)
	$(CC) $(LDFLAGS) $^ -o anonymize_full

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *~ $(C_OBJS) $(A_OBJS) $(AF_OBJS) change anonymize anonymize_full
