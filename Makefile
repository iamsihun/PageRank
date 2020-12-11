CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

all: main fw

fw : fw.o reddit.o 
	$(LD) fw.o reddit.o graph.o $(LDFLAGS) -o fw

main : main.o reddit.o
	$(LD) main.o reddit.o graph.o $(LDFLAGS) -o main



fw.o : fw.cpp 
	$(CXX) $(CXXFLAGS) fw.cpp 

main.o : main.cpp 
	$(CXX) $(CXXFLAGS) main.cpp

reddit.o : reddit.cpp reddit.h
	$(CXX) $(CXXFLAGS) reddit.cpp graph.cpp


clean :
	rm main.o reddit.o main graph.o fw.o fw