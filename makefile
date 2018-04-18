#Brandon Gower-Winter
#Makefile for Assignment 1 CSC3022H
#Originally created on 26/02/2018

CC := g++
CCFLAGS := -std=c++11
SRCDIR := src
BUILDDIR := build
EXECUTABLE := bin/driver

SRCFLEXT := cpp

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCFLEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCFLEXT)=.o))

$(EXECUTABLE) : $(OBJECTS)
	@echo Starting Link...
	$(CC) $(CCFLAGS)  $^ -o $(EXECUTABLE)
	@echo Link Complete

$(BUILDDIR)/%.o : $(SRCDIR)/%.$(SRCFLEXT)
	$(CC) $(CCFLAGS) -c -o $@ $<

run:
	./$(EXECUTABLE)

clean:
	rm -f build/*.o
