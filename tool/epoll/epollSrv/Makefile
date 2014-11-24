INCLUDES=-I./
LIBS=-lpthread
CXX=g++
CXXFLAGS=-DUSE_REMOTEINFO

all: epSrv

epSrv: epService.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

clean:
	rm -f epSrv
