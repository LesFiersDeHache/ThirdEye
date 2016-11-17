TARGET = prog
LIBS = -lm -lSDLmain -lSDL -lSDL_image $$(pkg-config --libs gtk+-2.0)
	
CC = gcc
GTK_CFLAGS = $$(pkg-config --cflags gtk+-2.0)
CFLAGS = -g -Wall -Wextra -std=c99 $(GTK_CFLAGS)

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC)  $(CFLAGS)  -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
