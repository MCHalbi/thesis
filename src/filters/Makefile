################################################################################
# Configuration                                                                #
################################################################################

# Location of the config file
CONFIG_FILE = ../Makefile.config
# Explicitly check for the config file
ifeq ($(wildcard $(CONFIG_FILE)),)
$(error $(CONFIG_FILE) not found.)
endif
include $(CONFIG_FILE)

SOURCE_PATH = ./
FILES = filter
LIST = $(addprefix $(BIN_PATH), $(addsuffix Main, $(FILES)))

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
     $(LIST) \
     core

################################################################################
# Build                                                                        #
################################################################################

all: compile checkstyle

compile: $(LIST)

# Link
$(BIN_PATH)%Main: $(addprefix $(SOURCE_PATH), %Main.o %.o)
	$(LD) -I $(INCLUDE) -o $@ $^ $(LIBS) $(LDFLAGS) $(WARNINGS) -std=$(STD)

# Compile
%.o: %.cpp
	$(CC) -I $(INCLUDE) -g -c $^ $(WARNINGS) -std=$(STD)

checkstyle:
	python $(LINT_PATH) *.cpp *.h

# Delete binarys and object files
clean:
	rm -f $(RM)
