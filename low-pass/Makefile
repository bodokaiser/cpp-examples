CC := /usr/local/opt/llvm/bin/clang++
CCFLAGS := -std=c++17
LDFLAGS := -lfftw3 -L/usr/local/opt/fftw/lib -I/usr/local/opt/fftw/include

SOURCES := $(shell find src -name '*.cc')
OBJECTS :=  $(SOURCES:%.cc=%.o)

build: $(OBJECTS)
	$(CC) $(CCFLAGS) $(LDFLAGS) $(notdir $^) -o $@
	@rm *.o

%.o: %.cc
	$(CC) $(CCFLAGS) -Isrc -c $<

clean:
	rm *.o

.PHONY: clean
