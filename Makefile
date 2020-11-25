CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

main : main.o
	$(LD) main.o $(LDFLAGS) -o main

main.o : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

clean :
	rm main.o main