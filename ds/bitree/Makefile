CXX=g++
CXXFLAGS=-g -Wall

all: test pmcb thrd

test: binarytree.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

pmcb: PreMidCreateBiTree.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

thrd: ThreadBiTree.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f test.* pmcb.* thrd.*
