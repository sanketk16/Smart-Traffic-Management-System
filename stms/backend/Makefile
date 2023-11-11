CC=gcc
CFLAGS=-I.

OBJ = main.o traffic_light.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

stms: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core stms