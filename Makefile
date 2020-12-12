OBJS = pagerank.o reddit.o printfw.o fwpath.o graph.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

all: fw pagerank test

fw: fw_test1 fw_test2 fw_test3 printfw fwpath

test: catchmain.o test.o reddit.o graph.o
	$(LD) catchmain.o test.o graph.o reddit.o $(LDFLAGS) -o test

fw_test1 : fw_test1.o reddit.o graph.o 
	$(LD) fw_test1.o reddit.o graph.o $(LDFLAGS) -o fw_test1

fw_test2 : fw_test2.o 
	$(LD) fw_test2.o reddit.o graph.o $(LDFLAGS) -o fw_test2

fw_test3 : fw_test3.o 
	$(LD) fw_test3.o reddit.o graph.o $(LDFLAGS) -o fw_test3

printfw : printfw.o 
	$(LD) printfw.o reddit.o graph.o $(LDFLAGS) -o printfw

fwpath : fwpath.o 
	$(LD) fwpath.o reddit.o graph.o $(LDFLAGS) -o fwpath

pagerank : pagerank.o reddit.o graph.o
	$(LD) pagerank.o reddit.o graph.o $(LDFLAGS) -o pagerank

fw_test1.o : tests/fw_test1.cpp data/FW_test1.tsv
	$(CXX) $(CXXFLAGS) tests/fw_test1.cpp

fw_test2.o : tests/fw_test2.cpp data/FW_test2.tsv
	$(CXX) $(CXXFLAGS) tests/fw_test2.cpp

fw_test3.o : tests/fw_test3.cpp data/FW_test3.tsv
	$(CXX) $(CXXFLAGS) tests/fw_test3.cpp

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

catchmain.o : cs225/catch/catchmain.cpp cs225/catch/catch.hpp
	$(CXX) $(CXXFLAGS) cs225/catch/catchmain.cpp

test.o : tests/test.cpp cs225/catch/catch.hpp reddit.cpp reddit.h
	$(CXX) $(CXXFLAGS) tests/test.cpp

clean :
	rm pagerank.o reddit.o graph.o fwpath.o fw_test1.o fw_test2.o fw_test3.o printfw.o fwpath pagerank fw_test1 fw_test2 fw_test3 printfw test.o catchmain.o test