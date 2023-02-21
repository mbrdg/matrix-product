# Makefile
# CPA, 2023
# Authors: Miguel Rodrigues & Sérgio Estêvão
CXX=g++
CXXFLAGS=-std=c++20 -O3 -Wall -Wextra -Werror -pedantic
LDLIBS=-lpapi

.PHONY: all clean


TARGETS=colproduct lineproduct
all: $(TARGETS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDLIBS)

clean:
	$(RM) colproduct lineproduct
