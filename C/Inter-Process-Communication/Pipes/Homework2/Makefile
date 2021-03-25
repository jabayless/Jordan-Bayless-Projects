# variable assignment for the program we’re building:
programs =LowAlpha HighAlpha Math Starter

CC = gcc
CFLAGS = -std=c11 -g -Wall

build: $(programs)

LowAlpha: LowAlpha.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $?

clean:
	-rm -f *.o *.gch $(target)
