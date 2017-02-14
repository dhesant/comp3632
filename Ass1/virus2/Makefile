CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=virus2.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=virus2

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *~ *.o $(EXECUTABLE)
