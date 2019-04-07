# Makefile for Paraglob-2

# *****************************************************
# Variables to control Makefile operation

CXX = g++
# -O2 results in a decent speedup
CXXFLAGS = -Wall -O2

# ****************************************************
# Targets needed to bring the executable up to date

paraglob.out: benchmark.o paraglob.o AhoCorasickPlus.o
	$(CXX) $(CXXFLAGS) -o paraglob.out benchmark.o AhoCorasickPlus.o paraglob.o -lahocorasick -L./multifast-ac/ahocorasick/build

benchmark.o: benchmark.cpp paraglob.h
	$(CXX) $(CXXFLAGS) -o benchmark.o -c benchmark.cpp -I./multifast-ac/ahocorasick

AhoCorasickPlus.o: AhoCorasickPlus.cpp AhoCorasickPlus.h
	$(CXX) $(CXXFLAGS) -o AhoCorasickPlus.o -c AhoCorasickPlus.cpp -I./multifast-ac/ahocorasick

paraglob.o: paraglob.cpp paraglob.h AhoCorasickPlus.h
	$(CXX) $(CXXFLAGS) -o paraglob.o -c paraglob.cpp

subsystem:
	$(MAKE) -C ./multifast-ac/ahocorasick

