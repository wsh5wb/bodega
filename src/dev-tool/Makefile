CPPFLAGS ?= -w -MMD -MP -std=c++17 -g 
LDFLAGS ?= -lstdc++fs
CXX := g++-8
OFILES := $(shell ls build/ | grep "\.o")

build: $(OFILES)
	@mkdir -p build/
	cd build/ && CXX=$(CXX) cmake .. 
	cd build/ && CMAKE_CXX_FLAGS="$(CPPFLAGS)" cmake --build .

clean:
	rm -rf build/

.PHONY: build, clean