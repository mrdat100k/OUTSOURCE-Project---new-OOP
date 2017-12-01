# Uncomment lines below if you have problems with $PATH
#SHELL := /bin/bash
#PATH := /usr/local/bin:$(PATH)

#add all files
SOURCES = $(wildcard src/*) $(wildcard lib/INA/*) $(wildcard lib/IO/*) $(wildcard lib/Keyboard/*) $(wildcard lib/LCD/*) $(wildcard lib/RTC/*) $(wildcard test/*)



# linting using cpplint for python: https://github.com/google/styleguide/tree/gh-pages/cpplint
lint:
	 python cpplint.py --linelength=120 ${SOURCES} 

# perform unit test
unit_test:
	platformio test

# build then upload to device, print size of the sections in a firmware/program
all:
	platformio run -t upload -t size

# clean project
clean:
	platformio run -t clean

# Check or update installed PIO Core packages, Development Platforms and global Libraries. 
update:
	platformio -f update

build:
	platformio run

# Print makefile variable, use for debugging
print-%  : ; @echo $* = $($*)

