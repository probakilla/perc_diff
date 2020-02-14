CC=gcc
CFLAGS=-Wall -Werror -shared -O2 -fPIC
LIB=percdiff.so
LIB_DIR=lib

all: compile

compile:
	$(CC) $(CFLAGS) -o $(LIB) percdiff.c
	mkdir $(LIB_DIR)
	mv $(LIB) $(LIB_DIR)

run:
	python3 percdiff.py -d 456,123

run-empty:
	python3 percdiff.py

clean:
	rm -rf lib
