# Makefile
# CPA, 2023
# Authors: Miguel Rodrigues & Sérgio Estêvão
CXX=g++
CXXFLAGS=-std=c++20 -O2 -Wall -Wextra -Werror -pedantic
LDLIBS=-lpapi

.PHONY: all clean


TARGETS=colproduct lineproduct ompproduct
all: $(TARGETS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDLIBS)

ompproduct: ompproduct.cpp
	$(CXX) $(CXXFLAGS) -fopenmp $< -o $@ $(LDLIBS)

clean:
	$(RM) $(TARGETS)
