CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
TARGET = ../build

all: strlen_tests strcmp_tests strcpy_tests

strlen_tests: s21_string_test_with_strlen_tests.o s21_string.o
	$(CC) $(FLAGS) s21_string_test_with_strlen_tests.o s21_string.o -o $(TARGET)/Quest_1

strcmp_tests: s21_string_test_with_strcmp_tests.o s21_string.o
	$(CC) $(FLAGS) s21_string_test_with_strcmp_tests.o s21_string.o -o $(TARGET)/Quest_2

strcpy_tests: s21_string_test_with_strcpy_tests.o s21_string.o
	$(CC) $(FLAGS) s21_string_test_with_strcpy_tests.o s21_string.o -o $(TARGET)/Quest_3

s21_string_test_with_strlen_tests.o: s21_string_test.c
	$(CC) $(FLAGS) -D S21_STRLEN_TEST -c s21_string_test.c -o s21_string_test_with_strlen_tests.o

s21_string_test_with_strcmp_tests.o: s21_string_test.c
	$(CC) $(FLAGS) -D S21_STRCMP_TEST -c s21_string_test.c -o s21_string_test_with_strcmp_tests.o

s21_string_test_with_strcpy_tests.o: s21_string_test.c
	$(CC) $(FLAGS) -D S21_STRCPY_TEST -c s21_string_test.c -o s21_string_test_with_strcpy_tests.o

s21_string.o: s21_string.c
	$(CC) $(FLAGS) -c s21_string.c -o s21_string.o

clean:
	rm -rf *.o $(TARGET)/*

rebuild: clean all