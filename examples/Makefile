-include make.inc

CPPFLAGS = -I../src
CXXFLAGS = -std=c++11 -O2 -march=native
OMPFLAGS = -fopenmp 
WARNFLAGS = -Wall -pedantic -Wextra


all: clean arraytools spvec

arraytools: $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(WARNFLAGS) $(OMPFLAGS) arraytools.cpp -o arraytools
	
spvec: $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(WARNFLAGS) $(OMPFLAGS) spvec.cpp -o spvec

clean:
	rm -rf arraytools spvec
