CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
  GTEST_PREFIX := $(shell brew --prefix googletest 2>/dev/null || echo "")
  ifneq ($(GTEST_PREFIX),)
    GTEST_INCLUDE := -I$(GTEST_PREFIX)/include
    GTEST_LIBS := -L$(GTEST_PREFIX)/lib -lgtest -lgtest_main -pthread
  else
    GTEST_INCLUDE := -I/usr/local/include
    GTEST_LIBS := -L/usr/local/lib -lgtest -lgtest_main -pthread
  endif
else
  GTEST_INCLUDE :=
  GTEST_LIBS := -lgtest -lgtest_main -pthread
endif

GRAPH_DIR = graph
ALG_DIR   = algorithms
TEST_DIR  = tests
BUILD_DIR = build

GRAPH_LIB = s21_graph.a
ALG_LIB   = s21_graph_algorithms.a
TEST_BIN  = test_graph

GRAPH_SRC = $(wildcard $(GRAPH_DIR)/*.cpp)
ALG_SRC   = $(wildcard $(ALG_DIR)/*.cpp)
TEST_SRC  = $(wildcard $(TEST_DIR)/*.cpp)

GRAPH_OBJ = $(patsubst $(GRAPH_DIR)/%.cpp,$(BUILD_DIR)/$(GRAPH_DIR)/%.o,$(GRAPH_SRC))
ALG_OBJ   = $(patsubst $(ALG_DIR)/%.cpp,$(BUILD_DIR)/$(ALG_DIR)/%.o,$(ALG_SRC))
TEST_OBJ  = $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/$(TEST_DIR)/%.o,$(TEST_SRC))

.PHONY: all clean test $(GRAPH_LIB) $(ALG_LIB)

all: $(GRAPH_LIB) $(ALG_LIB) $(TEST_BIN)

app: $(GRAPH_LIB) $(ALG_LIB)
	mkdir -p build/app
	$(CXX) -c cli/Main.cpp -o main.o
	$(CXX) main.o s21_graph.a s21_graph_algorithms.a -o build/app/simple_navigator
	rm -f main.o

run: app
	./build/app/simple_navigator

$(GRAPH_LIB): $(GRAPH_OBJ)
	ar rcs $@ $^

$(ALG_LIB): $(ALG_OBJ)
	ar rcs $@ $^

$(BUILD_DIR)/$(GRAPH_DIR)/%.o: $(GRAPH_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(GRAPH_DIR) -c $< -o $@

$(BUILD_DIR)/$(ALG_DIR)/%.o: $(ALG_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(GRAPH_DIR) -I$(ALG_DIR) -c $< -o $@

$(BUILD_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(GTEST_INCLUDE) -I$(GRAPH_DIR) -I$(ALG_DIR) -c $< -o $@

$(TEST_BIN): $(GRAPH_LIB) $(ALG_LIB) $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJ) $(GRAPH_LIB) $(ALG_LIB) $(GTEST_LIBS)

clean:
	rm -rf $(BUILD_DIR) $(GRAPH_LIB) $(ALG_LIB) $(TEST_BIN)

test: $(TEST_BIN)
	./$(TEST_BIN)

style_check:
	cp ../materials/linters/.clang-format .
	clang-format -n */*.cpp */*.h
	clang-format -i */*.cpp */*.h
	rm -f .clang-format

