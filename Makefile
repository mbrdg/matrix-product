# Makefile
# CPA @ M.EIC, 2023
# Authors: Miguel Rodrigues & Sérgio Estêvão
CXX=g++
CXXFLAGS=-std=c++20 -O2 -Wall -Wextra -Werror -pedantic
LDLIBS=-lpapi

.PHONY: all clean

TARGETS=colproduct rowproduct ompproduct
all: $(TARGETS)

%: src/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@.out $(LDLIBS)

ompproduct: src/ompproduct.cpp
	$(CXX) $(CXXFLAGS) -fopenmp $< -o $@.out $(LDLIBS)

clean:
	$(RM) *.out
