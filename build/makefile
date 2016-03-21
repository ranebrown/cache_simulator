# cache simulator makefile

# directories
SRCDIR = ../src
BUILDDIR = build
TESTDIR = ../test
INCDIR = ../inc

# Compiler to use
CC = clang

# Include paths for header files
INCLUDES = -I $(INCDIR) -I /usr/local/include

# Compiler flags
CFLAGS = -Wall -Wextra -g $(INCLUDES)

# Paths to required libraries
LFLAGS = -L /usr/local/lib

# The specific libraries that project depends on
LIBS = -lm

# All source files
SRCS = $(wildcard $(SRCDIR)/*.c)

# All object files
OBJS := $(SRCS:$(SRCDIR)/%.c=%.o)

# name of executable
MAIN = sim

# make all
all: $(MAIN)

$(MAIN): $(OBJS)
	@echo "Compiling executable $(MAIN)..."
	@$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)
	@echo "Operation complete :)"

# Automatically builds all object files from source files
# -c option compiles but does not link (create object files)
# -o is output filename
$(OBJS): %.o : $(SRCDIR)/%.c
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c $< -o $@

# unit test setup
TESTFLAG = -lcheck

TESTSRCS = $(wildcard $(TESTDIR)/*.c) #add in any .c files from test dir

TESTOBJS := $(TESTSRCS:$(TESTDIR)/%.c=%.o) #convert names of all .c files to .o

MAINOBJS := $(filter-out main.o, $(OBJS)) #remove main.o from list of .o files (check doesn't use main)

$(TESTOBJS): %.o : $(TESTDIR)/%.c #compile but don't link .o files
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c $< -o $@

# name of executable
TESTEX = check_sim

$(TESTEX): $(TESTOBJS) $(MAINOBJS)# compile executable for test
	@echo "Compiling executable $(TESTEX)..."
	@$(CC) $(CFLAGS) $(TESTFLAG) -o $(TESTEX) $(TESTOBJS) $(MAINOBJS) $(LFLAGS) $(LIBS)
	@echo "Operation complete :)"
	@echo
	@./$(TESTEX)

# make and run unit tests
# makefile info: structure using $TESTEX here and above so target isn't rebuilt if no changes
# this is the same way main is set up
check: $(TESTEX)

# This is used in case there is a file named clean
# @ suppresses command at shell
.PHONY: clean
clean:
	@if [ -e $(MAIN) ]; then rm $(MAIN); fi;
	@if [ -e $(TESTEX) ]; then rm $(TESTEX); fi;
	@if [ `find . -name "*.o" | head -1` ]; then rm *.o; fi;
	@if [ `find . -name "*.txt" | head -1` ]; then rm *.txt; fi;
	@echo "Cleaning..."
	@echo "Operation complete :)"

