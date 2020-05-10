# CFLAGS:=-O3 -DFE_STANDALONE -Wall -Wextra -Wsign-conversion -pedantic -std=c99 -march=native
CFLAGS:=-DFE_STANDALONE -Wall -Wextra -pedantic -std=c89 -march=native 
APPNAME:=fe

ifeq ($(OS),Windows_NT)
	APPNAME:=$(APPNAME).exe
	CC:=gcc
	RM:=del /Q
endif

all: fe

fe: src/fe.c 
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(APPNAME)
