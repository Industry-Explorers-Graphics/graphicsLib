C	= gcc
FLAGS	= -std=c99 -lm
CFLAGS	= -Wall

TARGET 	= draw.so
SOURCES	= render.c draw.c
HEADERS	= render.h
OBJECTS	= $(SOURCES:.c=.o)

all:	
	$(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(FLAGS) $(CFLAGS) -o $(TARGET) $(OBJECTS)
