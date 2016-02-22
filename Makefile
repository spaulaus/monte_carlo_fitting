#!/bin/make
SHELL=/bin/bash

.SUFFIXES: .$(c++SrcSuf)

#Define the virtual paths
vpath %.cpp src/
vpath %.hpp inc/
vpath %.o obj/

#Set some paths to install the shared objects to
SO_INSTALL_PATH = /home/vincent/programs/lib
HEADER_INSTALL_PATH = /home/vincent/programs/include

#Set the name of the program to be compiled
PROGRAM = example
VERSION = $(shell git describe --abbrev=0 --tags)

#Set some of the compile options
CXX = g++
CINCLUDEDIRS = -Iinc
CXXFLAGS = -fPIC -g -std=c++11 -Wall $(CINCLUDEDIRS)
LDLIBS = -ldl -lpthread
c++SrcSuf = cpp

#Add the ROOT config stuff to the compilation
ROOTCONFIG   := root-config
CXXFLAGS     += $(shell $(ROOTCONFIG) --cflags)
LDFLAGS      += $(shell $(ROOTCONFIG) --ldflags)
LDLIBS       += $(shell $(ROOTCONFIG) --libs) -lRooFit -lRooFitCore

#Define Objects
MAINO = main.o
TESTCLASSO = TestClass.o

#DefineSharedObject
SO_NAME = $(subst .o,.so,lib$(TESTCLASSO))
SO_NAME_W_VERSION = $(addsuffix .$(VERSION),$(SO_NAME))
SO_NAME_FULL=$(addprefix $(OBJDIR)/,$(SO_NAME_W_VERSION))

#Define the name of the header for the SO
HEADER_NAME = $(subst .o,.hpp,$(TESTCLASSO))

#Make the object list and prefix the object directory
OBJS = $(MAINO) $(TESTCLASSO)
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

so: $(HEADER_NAME)
	g++ -shared $(OBJDIR)/$(TESTCLASSO)  -o $(SO_NAME_FULL)
	cp $(SO_NAME_FULL) $(SO_INSTALL_PATH)
	ln -sf $(SO_INSTALL_PATH)/$(SO_NAME_W_VERSION) $(SO_INSTALL_PATH)/$(SO_NAME)
	cp $^ $(HEADER_INSTALL_PATH)

doc: doc/doxyfile
	@doxygen $^
