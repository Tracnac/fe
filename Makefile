CC=gcc
# CFLAGS:=-O3 -Wall -Wextra -Wsign-conversion -pedantic -std=c99 -march=native
CFLAGS:=-Wall -Wextra -pedantic -std=c89 -march=native
LDFLAGS=-lm -g
EXEC=fe
OBJ = ./src/fe.c
OBJ += ./src/fe_math.c

all: $(EXEC)

fe: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o *.so $(EXEC)
