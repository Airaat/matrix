AR = ar
CC = gcc
BIN = test
ARGLAGS = rcs
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
LIBFLAGS = -lcheck -lm
GCOV_FLAGS = --coverage

OS=$(shell uname -s)
ifeq ($(OS), Linux)
	LIBFLAGS+=-lsubunit
endif

.PHONY: all rebuild clean test gcov_report leaks clang

all: s21_matrix.a

rebuild: clean all

clean:
	@rm -rf a.out *.a $(BIN) *.o report *.g* *.info *.dSYM


s21_matrix.a: 
	@$(CC) -c $(CFLAGS) src/s21_*.c
	@$(AR) $(ARGLAGS) s21_matrix.a *.o
	@rm *.o

test: s21_matrix.a
	@$(CC) $(CFLAGS) -o $(BIN) src/tests/*.c s21_matrix.a $(LIBFLAGS)
	./$(BIN)



gcov_report: s21_matrix.a
	@$(CC) $(GCOV_FLAGS) $(CFLAGS) -o $(BIN) src/tests/*.c s21_matrix.a $(LIBFLAGS)
	./$(BIN)
	@lcov -t "gcov_report" -o gcov_report.info -c -d .
	@genhtml -o report gcov_report.info
	@rm -rf *.g* *.info
	@open ./report/index.html

leaks: s21_matrix.a
	@$(CC) $(CFLAGS) -o $(BIN) src/tests/*.c s21_matrix.a $(LIBFLAGS)
	@valgrind --tool=memcheck --leak-check=yes ./$(BIN)

clang:
	@clang-format --style=Google -n src/*.c src/*.h src/tests/*.c src/tests/*.h
	@clang-format --style=Google -i src/*.c src/*.h src/tests/*.c src/tests/*.h