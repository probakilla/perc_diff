CC=gcc
CFLAGS=-Wall -Werror -shared -O2 -fPIC
LIB=percdiff.so
LIB_DIR=lib

INSTALL_DIR=$(HOME)/bin

all: compile

compile:
	$(CC) $(CFLAGS) -o $(LIB) percdiff.c
	mkdir $(LIB_DIR)
	mv $(LIB) $(LIB_DIR)

run:
	python3 percdiff.py -d 456,123

run-empty:
	python3 percdiff.py

install:
	cp percdiff.py $(INSTALL_DIR)/percdiff
	mkdir -p $(INSTALL_DIR)/lib
	cp lib/percdiff.so $(INSTALL_DIR)/lib/percdiff.so
	sudo chmod +x $(INSTALL_DIR)/percdiff

uninstall:
	rm $(INSTALL_DIR)/percdiff
	rm $(INSTALL_DIR)/lib/percdiff.so

clean:
	rm -rf lib
