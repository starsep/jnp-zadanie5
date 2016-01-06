CXXFLAGS = -std=c++11 -O2 -Wall -Wunused -Wshadow -pedantic -g
COMPILER = g++

all: test test2 test3
test: priorityqueue.hh test.cc
	${COMPILER} ${CXXFLAGS} test.cc -o test

test2: priorityqueue.hh test2.cc
	${COMPILER} ${CXXFLAGS} test2.cc -o test2

test3: priorityqueue.hh test3.cc
	${COMPILER} ${CXXFLAGS} test3.cc -o test3

clean:
	rm -f test test2 test3

