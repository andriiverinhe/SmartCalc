CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -lm
LIBS = -lcheck -lsubunit -lgcov -lm
CHECKFLAGS = $(shell pkg-config --flags --libs check)
CFLAGS_COVERAGE = -fprofile-arcs -ftest-coverage

# Пути к исходным файлам
STACK_SOURCES = $(wildcard ./function/stack/*.c)
CALCULATOR_SOURCES = $(wildcard ./function/calculator/*.c)

# Пути к объектным файлам
STACK_OBJECTS = $(patsubst ./function/stack/%.c, OBJ/stack/%.o, $(STACK_SOURCES))
CALCULATOR_OBJECTS = $(patsubst ./function/calculator/%.c, OBJ/calculator/%.o, $(CALCULATOR_SOURCES))

# Путь к исходным файлам тестов
TEST_SOURCE = $(wildcard ./test/*.c)
# Пути к объектным файлам тестов
TEST_OBJECT = $(patsubst ./test/%.c, OBJ/test/%.o, $(TEST_SOURCE))

# Имя библиотеки
LIBRARY = SmartCalcV1_0.a

# Правило для сборки библиотеки
all: $(LIBRARY)

$(LIBRARY): $(STACK_OBJECTS) $(CALCULATOR_OBJECTS)
	ar rcs $@ $^ -lm

# Target for compiling and running tests
test: $(TEST_OBJECT) $(LIBRARY)
	$(CC) $(CFLAGS) $(CHECKFLAGS) $(TEST_OBJECT) $(LIBRARY) -o test_suite $(LIBS)
	./test_suite
	
valgrind: test
	valgrind --tool=memcheck --leak-check=yes --log-file="valgrind.log" ./test_suite


peer: gcov_report gcov_html

gcov_report: CFLAGS += $(CFLAGS_COVERAGE)
gcov_report: clean $(LIBRARY) $(TEST_OBJECT) $(STACK_OBJECTS) $(CALCULATOR_OBJECTS)
	$(CC) $(CFLAGS) $(CHECKFLAGS) -o test_suite $(TEST_OBJECT) $(STACK_OBJECTS) $(CALCULATOR_OBJECTS) $(LIBS) -lm
	./test_suite
	gcov -o OBJ/stack/ $(STACK_SOURCES)
	gcov -o OBJ/calculator/ $(CALCULATOR_SOURCES)
	rm -rf ./OBJ/test*
	gcovr -r . --html-details -o coverage_report.html
	@mkdir -p OBJ_gcov
	@mv *.gcov *.html *.css OBJ_gcov
# @mv OBJ_gcov/coverage_report.html .


gcov_html: coverage_report.html
	@xdg-open ./coverage_report.html || echo "Не удалось открыть HTML-файл."


OBJ/stack/%.o: ./function/stack/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -lm 

OBJ/calculator/%.o: ./function/calculator/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -lm 

OBJ/test/%.o: ./test/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CHECKFLAGS) -c $< -o $@

clean_test:
	rm -rf OBJ/test/ test_suite

clean_gcov:
	rm -rf *.gcno *.gcda *.gcov coverage_report.html *.html *.css OBJ_gcov

clean:clean_test clean_gcov
	rm -rf OBJ/ $(LIBRARY)
