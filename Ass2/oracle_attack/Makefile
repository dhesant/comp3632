# Sources for decrypt function
D_SRCS = decrypt.cpp decrypt_library.cpp

# Sources for encrypt function
E_SRCS = encrypt.cpp decrypt_library.cpp

##################################################
# DO NOT TOUCH BELOW THIS (Makefile Magic)
##################################################

CC=g++
CFLAGS=-Wall -std=c++11
LDFLAGS=

D_OBJS=$(D_SRCS:.cpp=.o)
E_OBJS=$(E_SRCS:.cpp=.o)

all: release

debug: CFLAGS+=-g -DDEBUG
debug: LDFLAGS+=-g
debug: release

release: decrypt encrypt

decrypt: $(D_OBJS)
	$(CC) $(LDFLAGS) $^ -o decrypt

encrypt: $(E_OBJS)
	$(CC) $(LDFLAGS) $^ -o encrypt

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *~ $(D_OBJS) $(E_OBJS) decrypt encrypt
