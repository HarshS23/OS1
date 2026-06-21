SHELL := /bin/bash
PATH := /opt/homebrew/opt/coreutils/libexec/gnubin:$(PATH)
export PATH

.PHONY: all build run clean

all: run

build:
	MAKE=gmake ./build.sh

run: build
	qemu-system-i386 -kernel kernel/OS1.kernel

clean:
	./clean.sh