CC := /usr/local/opt/llvm/bin/clang++
CCFLAGS := -std=c++17

build: main.o

%.o: %.cc
	$(CC) $(CCFLAGS) $< -o $@

clean:
	rm *.o

.PHONY: clean
