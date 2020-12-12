EXENAME = sihunhh2-annieli2-vhu3
OBJS = pagerank.o reddit.o printfw.o fwpath.o graph.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

# Custom Clang version enforcement logic:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu") 
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
endif
else
ifneq ($(strip $(SKIP_EWS_CHECK)),True)
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif
endif

all: fw pagerank test $(EXENAME)

fw: fw_test1 fw_test2 fw_test3 printfw fwpath

test: output_msg catchmain.o pagerank-test.o reddit.o graph.o
	$(LD) catchmain.o pagerank-test.o graph.o reddit.o $(LDFLAGS) -o test

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME) : output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

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

pagerank-test.o : tests/pagerank-test.cpp cs225/catch/catch.hpp reddit.cpp reddit.h
	$(CXX) $(CXXFLAGS) tests/pagerank-test.cpp

clean :
	rm pagerank.o reddit.o graph.o fwpath.o fw_test1.o fw_test2.o fw_test3.o printfw.o fwpath pagerank fw_test1 fw_test2 fw_test3 printfw pagerank-test.o catchmain.o test