CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
TARGET = ../build/cipher

all: cipher

cipher: cipher.o
	$(CC) $(FLAGS) cipher.o -o $(TARGET)

cipher.o: cipher.c
	$(CC) $(FLAGS) -c cipher.c -o cipher.o

clean:
	rm -rf *.o $(TARGET)

rebuild: clean all

clang-format_copy: 
	cp ../materials/linters/.clang-format .clang-format
	
clang-format: clang-format_copy
	clang-format -n *.h *.c
	clang-format -i *.h *.c

leaks:
	leaks -atExit -- $(TARGET)