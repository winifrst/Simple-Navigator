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
ALG_DIR = algorithms
CONTAINERS_DIR = containers
CLI_DIR = cli
TEST_DIR = tests
BUILD_DIR = build

GRAPH_LIB = $(BUILD_DIR)/s21_graph.a
ALG_LIB = $(BUILD_DIR)/s21_graph_algorithms.a
STACK_LIB = $(BUILD_DIR)/s21_stack.a
QUEUE_LIB = $(BUILD_DIR)/s21_queue.a
TEST_BIN = $(BUILD_DIR)/test_graph
APP_BIN = $(BUILD_DIR)/app/simple_navigator

GRAPH_SRC = $(wildcard $(GRAPH_DIR)/*.cpp)
ALG_SRC = $(wildcard $(ALG_DIR)/*.cpp)
STACK_SRC = $(wildcard $(CONTAINERS_DIR)/Stack.cpp)
QUEUE_SRC = $(wildcard $(CONTAINERS_DIR)/Queue.cpp)
CLI_SRC = $(wildcard $(CLI_DIR)/*.cpp)
TEST_SRC = $(wildcard $(TEST_DIR)/*.cpp)

GRAPH_OBJ = $(patsubst $(GRAPH_DIR)/%.cpp,$(BUILD_DIR)/$(GRAPH_DIR)/%.o,$(GRAPH_SRC))
ALG_OBJ = $(patsubst $(ALG_DIR)/%.cpp,$(BUILD_DIR)/$(ALG_DIR)/%.o,$(ALG_SRC))
STACK_OBJ = $(patsubst $(CONTAINERS_DIR)/%.cpp,$(BUILD_DIR)/$(CONTAINERS_DIR)/%.o,$(STACK_SRC))
QUEUE_OBJ = $(patsubst $(CONTAINERS_DIR)/%.cpp,$(BUILD_DIR)/$(CONTAINERS_DIR)/%.o,$(QUEUE_SRC))
CLI_OBJ = $(patsubst $(CLI_DIR)/%.cpp,$(BUILD_DIR)/$(CLI_DIR)/%.o,$(CLI_SRC))
TEST_OBJ = $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/$(TEST_DIR)/%.o,$(TEST_SRC))

.PHONY: all s21_graph s21_graph_algorithms s21_stack s21_queue clean test style_check

all: clean app run

app: $(APP_BIN)

run: app
	./$(APP_BIN)

s21_graph: $(GRAPH_LIB)
s21_graph_algorithms: $(ALG_LIB)
s21_stack: $(STACK_LIB)
s21_queue: $(QUEUE_LIB)

$(APP_BIN): $(CLI_OBJ) $(ALG_LIB) $(GRAPH_LIB) $(STACK_LIB) $(QUEUE_LIB)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $(CLI_OBJ) $(ALG_LIB) $(GRAPH_LIB) $(STACK_LIB) $(QUEUE_LIB)

$(GRAPH_LIB): $(GRAPH_OBJ)
	@mkdir -p $(dir $@)
	ar rcs $@ $^

$(ALG_LIB): $(ALG_OBJ)
	@mkdir -p $(dir $@)
	ar rcs $@ $^

$(STACK_LIB): $(STACK_OBJ)
	@mkdir -p $(dir $@)
	ar rcs $@ $^

$(QUEUE_LIB): $(QUEUE_OBJ)
	@mkdir -p $(dir $@)
	ar rcs $@ $^

$(BUILD_DIR)/$(CONTAINERS_DIR)/%.o: $(CONTAINERS_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(CONTAINERS_DIR) -c $< -o $@

$(BUILD_DIR)/$(GRAPH_DIR)/%.o: $(GRAPH_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(GRAPH_DIR) -c $< -o $@

$(BUILD_DIR)/$(ALG_DIR)/%.o: $(ALG_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(GRAPH_DIR) -I$(ALG_DIR) -I$(CONTAINERS_DIR) -c $< -o $@

$(BUILD_DIR)/$(CLI_DIR)/%.o: $(CLI_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(GRAPH_DIR) -I$(ALG_DIR) -I$(CONTAINERS_DIR) -I$(CLI_DIR) -c $< -o $@

$(BUILD_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(GTEST_INCLUDE) -I$(GRAPH_DIR) -I$(ALG_DIR) -I$(CONTAINERS_DIR) -c $< -o $@

$(TEST_BIN): $(TEST_OBJ) $(ALG_LIB) $(GRAPH_LIB) $(STACK_LIB) $(QUEUE_LIB)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJ) $(ALG_LIB) $(GRAPH_LIB) $(STACK_LIB) $(QUEUE_LIB) $(GTEST_LIBS)

test: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -rf $(BUILD_DIR)

style_check:
	cp ../materials/linters/.clang-format .
	find . -name "*.cpp" -o -name "*.hpp" | xargs clang-format -n
	find . -name "*.cpp" -o -name "*.hpp" | xargs clang-format -i
	rm -f .clang-format

gcov_report: clean
	$(MAKE) CXXFLAGS="$(CXXFLAGS) $(GCOV_FLAGS)" $(TEST_BIN)
	./$(TEST_BIN)
	mkdir -p $(GCOV_DIR)
	gcovr -r . \
		--html --html-details -o $(GCOV_DIR)/index.html \
		--exclude='tests/' \
		--exclude='cli/' \
		--exclude-unreachable-branches \
		--print-summary
	@clear
	@echo "-- Gcov HTML report generated in $(GCOV_DIR)/index.html."
	@xdg-open $(GCOV_DIR)/index.html || open $(GCOV_DIR)/index.html || echo "Please open $(GCOV_DIR)/index.html manually."