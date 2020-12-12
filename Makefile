CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

all: fw_test1 fw_test2 fw_test3 printfw fwpath pagerank 

fw_test1 : fw_test1.o reddit.o graph.o
	$(LD) fw_test1.o reddit.o graph.o $(LDFLAGS) -o fw_test1

fw_test2 : fw_test2.o reddit.o graph.o
	$(LD) fw_test2.o reddit.o graph.o $(LDFLAGS) -o fw_test2

fw_test3 : fw_test3.o reddit.o graph.o
	$(LD) fw_test3.o reddit.o graph.o $(LDFLAGS) -o fw_test3

printfw : printfw.o reddit.o graph.o
	$(LD) printfw.o reddit.o graph.o $(LDFLAGS) -o printfw

fwpath : fwpath.o reddit.o graph.o
	$(LD) fwpath.o reddit.o graph.o $(LDFLAGS) -o fwpath

pagerank : pagerank.o reddit.o graph.o
	$(LD) pagerank.o reddit.o graph.o $(LDFLAGS) -o pagerank

fw_test1.o : fw_test1.cpp
	$(CXX) $(CXXFLAGS) fw_test1.cpp

fw_test2.o : fw_test2.cpp
	$(CXX) $(CXXFLAGS) fw_test2.cpp

fw_test3.o : fw_test3.cpp
	$(CXX) $(CXXFLAGS) fw_test3.cpp

printfw.o : printfw.cpp
	$(CXX) $(CXXFLAGS) printfw.cpp

fwpath.o : fwpath.cpp 
	$(CXX) $(CXXFLAGS) fwpath.cpp 

pagerank.o : pagerank.cpp
	$(CXX) $(CXXFLAGS) pagerank.cpp 

reddit.o : reddit.cpp reddit.h 
	$(CXX) $(CXXFLAGS) reddit.cpp

graph.o : graph.cpp graph.h
	$(CXX) $(CXXFLAGS) graph.cpp


clean :
	rm pagerank.o reddit.o graph.o fwpath.o fw_test1.o fw_test2.o fw_test3.o printfw.o fwpath pagerank fw_test1 fw_test2 fw_test3 printfw