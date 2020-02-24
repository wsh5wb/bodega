CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++17 -g 
CXX := g++-8

build:
	@mkdir -p build/
	cd build/ && cmake .. && cmake --build .

clean:
	rm -rf build/

.PHONY: build, clean