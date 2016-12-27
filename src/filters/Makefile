FILE = filter

# Compiler and linker you want to use
CC = g++
LD = g++

# Location of the linter for style checking
LINT = ../cpplint.py

# Additional include directorys. Whatever you think you need goes here
INCLUDE = /home/halbritl/Dokumente/thesis/src/include
LIBS = -L/usr/X11R6/lib

# Linker flags you want to use go here
LDFLAGS = -lpthread -lX11 -lm

# Set warnings to be displayed
WARNINGS = -Wall

# Set language standard
STD = c++11

# Files to be removed by make clean
RM = *.o \
     *.png \
     $(FILE)Main \
     core


all: compile checkstyle

compile: $(FILE)Main

# Link
%Main: %Main.o %.o
	$(LD) -I $(INCLUDE) -o $@ $^ $(LIBS) $(LDFLAGS) $(WARNINGS) -std=$(STD)

# Compile
%.o: %.cpp
	$(CC) -I $(INCLUDE) -g -c $^ -std=$(STD) $(WARNINGS)

checkstyle:
	python $(LINT) *.cpp *.h

# Delete binarys and object files
clean:
	rm -f $(RM)
