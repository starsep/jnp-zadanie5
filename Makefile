CXXFLAGS = -std=c++11 -O2 -Wall -Wunused -Wshadow -pedantic -g
COMPILER = g++

test: priorityqueue.hh test.cc
	 ${COMPILER} ${CXXFLAGS} test.cc -o test

clean:
	rm -f test

