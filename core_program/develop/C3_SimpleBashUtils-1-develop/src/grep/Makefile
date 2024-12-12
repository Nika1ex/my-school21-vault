SHELL := /bin/bash
C_FLAGS = -Wall -Werror -Wextra -std=c11
FILES = non-existent.txt test1.txt unreadable.txt test2.txt empty.txt
TARGET = s21_grep
DELIMITER = '.........................................'

all: $(TARGET) tests

s21_grep: s21_grep.o s21_grep_patterns.o ../common/s21_common.o s21_grep_print.o
	gcc $(C_FLAGS) s21_grep.o s21_grep_patterns.o ../common/s21_common.o s21_grep_print.o -o $(TARGET)

%.o: %.c
	gcc $(C_FLAGS) -c $< -o $@

rebuild: delete $(TARGET) clang-format

delete:
	@rm -rf *.o ../common/*.o ../.clang-format $(TARGET) 

clang-format:
	cp ../../materials/linters/.clang-format ../.clang-format
	clang-format -i *.c *.h ../common/*.c ../common/*.h

tests:
	bash s21_grep_tests.sh

valgrind:
	@echo 'Memory test:'
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET) -ivclnhsoe 'grep command' -f regex2.txt $(FILES)
	@echo $(DELIMITER)

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h ../common/*.c ../common/*.h