# Sources for decrypt function
C_SRCS = change.cpp

# Sources for encrypt function
A_SRCS = 

##################################################
# DO NOT TOUCH BELOW THIS (Makefile Magic)
##################################################

CC=g++
CFLAGS=-Wall -std=c++11
LDFLAGS=

C_OBJS=$(C_SRCS:.cpp=.o)
A_OBJS=$(A_SRCS:.cpp=.o)

all: release

debug: CFLAGS+=-g -DDEBUG
debug: LDFLAGS+=-g
debug: release

release: change

change: $(C_OBJS)
	$(CC) $(LDFLAGS) $^ -o change

anonymize: $(A_OBJS)
	$(CC) $(LDFLAGS) $^ -o anonymize

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *~ $(C_OBJS) $(A_OBJS) change anonymize
