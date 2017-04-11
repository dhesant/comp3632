CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=
SOURCES=cribdrag.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=cribdrag

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *~ *.o $(EXECUTABLE)
