-include make.inc

CPPFLAGS = -I../src
CXXFLAGS = -std=c++11 -O2 -march=native
OMPFLAGS = -fopenmp 
WARNFLAGS = -Wall -pedantic -Wextra


all: clean arraytools spmat spvec

arraytools: $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(WARNFLAGS) $(OMPFLAGS) arraytools.cpp -o arraytools

spmat: $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(WARNFLAGS) $(OMPFLAGS) spmat.cpp -o spmat

spvec: $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(WARNFLAGS) $(OMPFLAGS) spvec.cpp -o spvec

clean:
	rm -rf arraytools spmat spvec
