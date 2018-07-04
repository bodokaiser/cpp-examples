CXX := /usr/local/opt/llvm/bin/clang++
CXXFLAGS := -std=c++17

build: main.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o

.PHONY: clean
