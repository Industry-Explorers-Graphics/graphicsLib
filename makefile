CC= gcc
FLAGS= -std=c99 -lm
CFLAGS= -std=c99 -Wall -fPIC
LDFLAGS= -v -shared -L /usr/local/lib

TARGET 	= libkandrawer.so
SOURCES	= render.c draw.c
HEADERS	= render.h
OBJECTS	= $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

%.o:%.c
	$(CC) $(CFLAGS) -c $< >$@

draw: $(HEADERS) $(TARGET) draw.c
	$(CC) draw.c -o draw -L /home/odroid/Projects/graphicsLib/ -l draw  -lm
