CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

main : main.o
	$(LD) main.o reddit.o graph.o $(LDFLAGS) -o main

main.o : main.cpp reddit.cpp graph.cpp
	$(CXX) $(CXXFLAGS) main.cpp reddit.cpp graph.cpp

clean :
	rm main.o reddit.o main graph.o