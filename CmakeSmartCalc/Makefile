CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
LIBS = -lcheck -lsubunit -lgcov -lm
CHECKFLAGS = $(shell pkg-config --flags --libs check)
GCOVFLAGS = -fprofile-arcs -ftest-coverege

DIRFUNC = SmartCalc

rebuild: clean install

install:
	@mkdir -p build
# @cd $(DIRFUNC) && make
	@cd build && cmake ..
	@cd build && make
	@mv build/Smart_calc SmartCalcV1.0
	@make run

run:
	@./SmartCalcV1.0

clean:
	@rm -rf build
	@rm -rf logs
	@rm -rf SmartCalcV1.0
	@cd $(DIRFUNC) && make clean
	clear