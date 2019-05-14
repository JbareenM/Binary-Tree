#!make -f

all: test
	./$<
demo:  Demo.o 
	clang++-5.0 -std=c++17 $^ -o demo

test:  Test.o 
	clang++-5.0 -std=c++17 $^ -o test

%.o: %.cpp range.hpp chain.hpp zip.hpp
	clang++-5.0 -std=c++17 --compile $< -o $@

clean:
	rm -f *.o demo test
