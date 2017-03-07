CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=virus3.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=virus3

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *~ *.o $(EXECUTABLE)

victim: all
	cp victim.cpp.bkp victim.cpp
	./virus3 victim.cpp
