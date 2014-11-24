INCLUDES=-I./
CXX=g++
LIBS=-lpthread

all: epClnt

epClnt: epClient.cpp
	$(CXX) $(INCLUDES) $^ -o $@ $(LIBS)

clean:
	rm -f epClnt

