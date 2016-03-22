#!/bin/make
SHELL=/bin/bash

.SUFFIXES: .$(c++SrcSuf)

#Define the virtual paths
vpath %.cpp src/
vpath %.hpp inc/
vpath %.o obj/

#Set the name of the program to be compiled
PROGRAM = monteFit
VERSION = $(shell git describe --abbrev=0 --tags)

#Set some of the compile options
CXX = g++
CINCLUDEDIRS = -Iinc
CXXFLAGS = -fPIC -std=c++0x -g -Wall $(CINCLUDEDIRS) -p
LDLIBS = -ldl -lpthread
c++SrcSuf = cpp

#Make the object list and prefix the object directory
OBJS = main.o MonteFit.o VandleFunction.o GaussianFunction.o
OBJDIR = obj
OBJS_W_DIR = $(addprefix $(OBJDIR)/,$(OBJS))

all: $(OBJS_W_DIR) $(PROGRAM)

$(OBJS_W_DIR): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(PROGRAM): $(OBJS_W_DIR)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $^ -o $@

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean so doc
clean: 
	@echo "Cleaning..."
	@$(RM) -f $(OBJDIR)/*.o $(PROGRAM) *~ src/*~ include/*~

doc: doc/doxyfile
	@doxygen $^
