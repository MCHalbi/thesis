FILE    = cimg_test_01
INCLUDE = /misc/student/halbritl/CImg
LIBS    = -lpthread -lX11 -lm
FLAGS   = -Wall -std=c++11

all: compile checkstyle

compile: $(FILE)

%: %.cpp
	g++ -o $@ $^ -I $(INCLUDE) $(FLAGS) $(LIBS)

checkstyle:
	python ../cpplint.py *.cpp

# Delete binarys and object files
clean:
	rm -f *.o
	rm -f $(FILE)
	rm -f core
