CC = cc
CFLAGS = -std=c11 -Wall -g $(shell pkg-config --cflags jansson)
LDFLAGS = $(shell pkg-config --libs jansson)
SOURCES = command.c handlers.c inventory.c item.c list.c location.c map.c person.c utilities.c vector.c linenoise.c main.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = text-game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o $(EXECUTABLE)
