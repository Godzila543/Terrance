CC=gcc
CFLAGS=-I. -lpigpio -Wall -pthread -lrt
DEPS = step.h
OBJ = step.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
