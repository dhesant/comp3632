# Sources for decrypt function
D_SRCS=decrypt.cpp decrypt_library.cpp

# Sources for encrypt function
E_SRCS=

##################################################
# DO NOT TOUCH BELOW THIS (Makefile Magic)
##################################################

CC=g++
CFLAGS=-Wall -std=c++11
LDFLAGS=

D_OBJS=$(D_SRCS:.cpp=.o)
E_OBJS=$(E_SRCS:.cpp=.o)

all: decrypt

decrypt: $(D_OBJS)
	$(CC) $(LDFLAGS) $^ -o decrypt

encrypt: $(E_OBJS)
	$(CC) $(LDFLAGS) $^ -o encrypt

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *~ $(D_OBJS) $(E_OBJS) decrypt encrypt
