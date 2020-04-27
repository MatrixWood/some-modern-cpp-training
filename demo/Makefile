CXX = clang++
CXXFLAGS = -std=c++17 -Wall

SOURCES=$(wildcard *.cpp)
BINARIES=$(patsubst %.cpp,./%,$(SOURCES))

default: $(BINARIES)

./%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(BINARIES)