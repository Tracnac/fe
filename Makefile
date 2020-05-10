CC=gcc
# CFLAGS:=-O3 -DFE_STANDALONE -Wall -Wextra -Wsign-conversion -pedantic -std=c99 -march=native
CFLAGS:=-DFE_STANDALONE -Wall -Wextra -pedantic -std=c89 -march=native
LDFLAGS=-lm
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
	rm -rf *.o $(EXEC)
