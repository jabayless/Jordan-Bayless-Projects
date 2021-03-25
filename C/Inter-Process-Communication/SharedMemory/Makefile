# variable assignment for the program we’re building:
programs=LowAlpha HighAlpha Math Starter CharacterReader

CC = gcc
CFLAGS = -std=gnu99 -g -Wall

build: $(programs)

LowAlpha: LowAlpha.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $? -lrt

HighAlpha: HighAlpha.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $? -lrt

Math: Math.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(@) $? -lrt

Starter: Starter.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(@) $? -lrt

clean:
	-rm -f *.o *.gch $(target)
	rm /dev/shm/SHM_*
