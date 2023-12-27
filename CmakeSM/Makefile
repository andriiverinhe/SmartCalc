CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
LIBS = -lcheck -lsubunit -lgcov -lm
CHECKFLAGS = $(shell pkg-config --flags --libs check)
GCOVFLAGS = -fprofile-arcs -ftest-coverege

DIRFUNC = SmartCalc

all: install 

rebuild: clean install

install:
	@mkdir -p build
# @cd $(DIRFUNC) && make
	@cd build && cmake ..
	@cd build && make
	@mv build/Smart_calc SmartCalcV1.0
	@make run

uninstall:
	@rm -rf SmartCalcV1.0
run:
	@./SmartCalcV1.0

gcov_report:
	@cd SmartCalc && make gcov_report

test:
	@cd SmartCalc && make test

clean:
	@rm -rf build
	@rm -rf logs
	@rm -rf SmartCalcV1.0 
	@rm -rf SmartCalcDist.zip SmartCalcDist	
	@cd $(DIRFUNC) && make clean
	clear


dist: clean
	@mkdir -p SmartCalcDist
	@rsync -av --exclude='SmartCalcDist' * SmartCalcDist/
	@zip -r SmartCalcDist.zip SmartCalcDist
	@rm -r SmartCalcDist	