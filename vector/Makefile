CXX := /usr/local/opt/llvm/bin/clang++
CXXFLAGS := -std=c++17

SOURCES := $(shell find src -name '*.cpp')
OBJECTS :=  $(SOURCES:%.cpp=%.o)

build: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(notdir $^) -o $@
	@rm *.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -Isrc -c $<

clean:
	rm *.o

.PHONY: clean
