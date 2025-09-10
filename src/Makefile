CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror
TEST_FLAGS = -lgtest -lgtest_main -pthread

all:  libs/libstack.a libs/libqueue.a libs/libgraph.a libs/libgraph_algorithms.a
	mkdir -p build
	$(CXX) -c cli/main.cpp -o main.o
	$(CXX) main.o -L./libs -lgraph -lgraph_algorithms -o build/simple_navigator
	rm -f main.o
	./build/simple_navigator

libs/libstack.a: containers/stack.cpp containers/stack.h
	mkdir -p libs
	$(CXX) $(CXXFLAGS) containers/stack.cpp -c
	ar rcs libs/libstack.a stack.o
	rm -f stack.o

libs/libqueue.a: containers/queue.cpp containers/queue.h
	mkdir -p libs
	$(CXX) $(CXXFLAGS) containers/queue.cpp -c
	ar rcs libs/libqueue.a queue.o
	rm -f queue.o

libs/libgraph.a: graph/graph.cpp graph/graph.h
	mkdir -p libs
	$(CXX) $(CXXFLAGS) -c graph/graph.cpp -o graph.o  
	ar rcs libs/libgraph.a graph.o
	rm -f graph.o

libs/libgraph_algorithms.a: graph_algorithms/graph_algorithms.cpp graph_algorithms/graph_algorithms.h
	mkdir -p libs
	$(CXX) $(CXXFLAGS) -c graph_algorithms/graph_algorithms.cpp -o graph_algorithms.o  
	ar rcs libs/libgraph_algorithms.a graph_algorithms.o
	rm -f graph_algorithms.o

test: libs/libstack.a libs/libqueue.a libs/libgraph.a libs/libgraph_algorithms.a tests/*.cpp 
	mkdir -p build
	$(CXX) $(CXXFLAGS) tests/*.cpp -L./libs -lstack -lqueue -lgraph -lgraph_algorithms -o build/test $(TEST_FLAGS)
	./build/test

style_check:
	cp ../materials/linters/.clang-format .
	clang-format -n */*.cpp */*.h
	clang-format -i */*.cpp */*.h
	rm -f .clang-formats

clean:
	rm -rf stack_test libs build