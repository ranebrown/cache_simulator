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
CFLAGS = -Wall -Wextra -g $(INCLUDES) -std=c99 -O3

# Paths to required libraries
LFLAGS = -L /usr/local/lib

# The specific libraries that project depends on
LIBS = -lm

# config file
# ?= uses default unless it is overwritten
conf ?= ../config/default.txt

# trace name
trace ?= ../traces/traces_short/tr1.gz

# All source files
SRCS = $(wildcard $(SRCDIR)/*.c)

# All object files
OBJS := $(SRCS:$(SRCDIR)/%.c=%.o)

# name of executable
MAIN = sim.exe

# make all
.PHONY: all
all: $(MAIN)

$(MAIN): $(OBJS)
	@echo "Compiling executable: $(MAIN)"
	@$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)
	@echo

# Automatically builds all object files from source files
# -c option compiles but does not link (create object files)
# -o is output filename
$(OBJS): %.o : $(SRCDIR)/%.c
	@echo "Compiling object file: $@"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo

# unit test setup
TESTFLAG = -lcheck

TESTSRCS = $(wildcard $(TESTDIR)/*.c) #add in any .c files from test dir

TESTOBJS := $(TESTSRCS:$(TESTDIR)/%.c=%.o) #convert names of all .c files to .o

MAINOBJS := $(filter-out main.o, $(OBJS)) #remove main.o from list of .o files (check doesn't use main)

$(TESTOBJS): %.o : $(TESTDIR)/%.c #compile but don't link .o files
	@echo "Compiling object file: $@"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo

# unit test executables
TEXCS = $(TESTOBJS:%.o=%.exe)

# check target - compile the executable for each test file
$(TEXCS): %.exe: %.o $(MAINOBJS)
	@echo "Compiling unit test executable: $@"
	@$(CC) $(CFLAGS) $(TESTFLAG) $(LFLAGS) $(LIBS) -o $@ $^
	@echo

# make and run unit tests
# makefile info: structure using $TESTEX here and above so target isn't rebuilt if no changes
# this is the same way main is set up
.PHONY: check
check: $(TEXCS)
	@for test in $^;  do \
		if [ $${test} = 'test_readTrace.exe' ]; then \
			zcat < ../traces/traces_short/tr1.gz | ./$${test}; \
		else \
			./$${test}; \
		fi; \
		echo; \
	done

# run main executable
.PHONY: run
run: $(MAIN)
	@zcat < $(trace) | ./$(MAIN) $(conf) $(trace)

# generate doxygen documentation
doc:
	@echo "Generating documentation..."
	@echo ""
	@doxygen ../doc/doxygen.config
	@echo ""

# phony is used in case there is a file named clean
# @ suppresses command at shell
.PHONY: clean
clean:
	@if [ `find . -name "*.exe" | head -1` ]; then rm *.exe; fi;
	@if [ `find . -name "*.o" | head -1` ]; then rm *.o; fi;
	@echo "Cleaning..."
	@echo "Operation complete :)"
	@echo
