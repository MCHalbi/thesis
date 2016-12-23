# Compiling parameters
FILE       = filter
INCLUDE    = /usr/local/include
LIBS       = -lpthread -lX11 -lm -L/usr/X11R6/lib
FLAGS      = -Wall -std=c++11

all: compile checkstyle

compile: $(FILE)Main

# Link
%Main: %Main.o %.o
	g++ $(FLAGS) -I $(INCLUDE) -o $@ $^ $(LIBS)

# Compile
%.o: %.cpp
	g++ $(FLAGS) -I $(INCLUDE) -g -c $^

checkstyle:
	python ../cpplint.py *.cpp *.h

# Delete binarys and object files
clean:
	rm -f *.o
	rm -f $(FILE)Main
	rm -f core
	rm -f *.png
