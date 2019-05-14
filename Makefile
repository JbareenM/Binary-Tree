#!make -f
all: demo test

demo: TreeDemo.o Tree.o
	clang++ -std=c++17 $^ -o demo

test: TreeTest.o Tree.o
	clang++ -std=c++17 $^ -o test

%.o: %.cpp
	clang++ -std=c++17 --compile $< -o $@

TreeTest.o: badkan.hpp Tree.hpp

TreeDemo.o: Tree.hpp

clean:
	rm -f *.o demo test
