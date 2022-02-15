INCLUDE = -Iinclude
CFLAGS = $(INCLUDE)
LIBS = lib/libfdr.a

CC = gcc
EXECUTABLES = bin/kripto 
              


all: $(EXECUTABLES)

clean:
	rm -f bin/*

bin/kripto: src/main.c 
	$(CC) $(CFLAGS) -o bin/kripto src/main.c $(LIBS)





