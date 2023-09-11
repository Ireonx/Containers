CXX = g++
CFLAGS = -lstdc++ -std=c++17 -Wall -Werror -Wextra
TEST_FLAGS = -lgtest -pthread -lgmock -fprofile-arcs -ftest-coverage

EXECUTABLE = test

OPEN_REPORT :=
LEAKS :=

HEADERS = s21_containers.h s21_containersplus.h
SOURCES_ALL = $(wildcard */s21_*.cc)
OBJ_LIBRARY := $(patsubst %.cc, %.o, $(SOURCES_ALL))
TEST_FILES = $(wildcard */test_*.cc)
LCOV_LINKER_OPTIONS = 
LCOV_COVERAGE_FLAGS = 

SRC_LIST_TEST = ./list/test_list.cc
SRC_STACK_TEST = ./stack/test_stack.cc
SRC_QUEUE_TEST = ./queue/test_queue.cc
SRC_MAP_TEST = ./map/test_map.cc
SRC_SET_TEST = ./set/test_set.cc
SRC_MULTISET_TEST = ./multiset/test_multiset.cc
SRC_VECTOR_TEST = ./vector/test_vector.cc
SRC_ARRAY_TEST = ./array/test_array.cc

ifeq ($(shell uname -s), Linux)
	TEST_FLAGS= -lgtest -lpthread -fprofile-arcs -ftest-coverage
	OPEN_REPORT += xdg-open
	LEAKS += valgrind --leak-check=full -s -q --track-origins=yes
endif

ifeq ($(shell uname -s), Darwin)
	OPEN_REPORT += open
	LEAKS += leaks -atExit --
endif

all: clean test

%.o: %.cc $(HEADERS)
	$(CXX) $(LCOV_COVERAGE_FLAGS) $(CFLAGS) -c $< -o $@

test: clean
	$(CXX) $(CFLAGS) $(TEST_FLAGS) $(LCOV_LINKER_OPTIONS) $(TEST_FILES) test_start.cc -o test
	rm -rf *.o

gcov_report: clean add_coverage test
	./test
	lcov --exclude='/usr/include/*' -t "test" -o test.info -c -d .
	genhtml -o report test.info
	$(OPEN_REPORT) report/index.html
	rm -f *.gcda *.gcno


ifeq (${OS}, Linux)
	cd report && firefox coverage_report.html
else
	cd report && open coverage_report.html
endif


add_coverage:
 	$(eval LCOV_COVERAGE_FLAGS += -fprofile-arcs -ftest-coverage)
 	$(eval LCOV_LINKER_OPTIONS += -fprofile-arcs)

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -i */*.cpp 
	rm -rf .clang-format

clean:
	rm -rf *.out *.o *.a check */*.gcda */*.gcno test *.info *.gcda *.gcno report
	rm -rf report/

leaks_check: test
	@$(LEAKS) ./$(EXECUTABLE)

fsanitize_check:
	@$(CXX) -fsanitize=address $(CFLAGS) $(SOURCE) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_list:
	@$(CXX) $(CFLAGS) $(SRC_LIST_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_stack:
	@$(CXX) $(CFLAGS) $(SRC_STACK_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_queue:
	@$(CXX) $(CFLAGS) $(SRC_QUEUE_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_map:
	@$(CXX) $(CFLAGS) $(SRC_MAP_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_set:
	@$(CXX) $(CFLAGS) $(SRC_SET_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_multiset:
	@$(CXX) $(CFLAGS) $(SRC_MULTISET_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_vector:
	@$(CXX) $(CFLAGS) $(SRC_VECTOR_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_array:
	@$(CXX) $(CFLAGS) $(SRC_ARRAY_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

run:
	./$(EXECUTABLE)

.PHONY: all clean test gcov_report style clang_format leaks_check run
