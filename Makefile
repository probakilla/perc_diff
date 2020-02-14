CC=gcc
CFLAGS=-Wall -Werror -shared -O2 -fPIC

all: compile

compile:
	$(CC) $(CFLAGS) -o percdiff.so percdiff.c

run:
	python3 percdiff.py -d 456,123

run-empty:
	python3 percdiff.py

clean:
	rm percdiff.so
