CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
TARGET = ../build

all: state_sort state_search

state_sort: state_sort.o state.o
	$(CC) $(FLAGS) state_sort.o state.o -o $(TARGET)/Quest_1

state_search: state_search.o state.o
	$(CC) $(FLAGS) state_search.o state.o -o $(TARGET)/Quest_2

state_sort.o: state_sort.c
	$(CC) $(FLAGS) -c state_sort.c -o state_sort.o

state.o: state.c
	$(CC) $(FLAGS) -c state.c -o state.o

state_search.o: state_search.c
	$(CC) $(FLAGS) -c state_search.c -o state_search.o

clean:
	rm -rf *.o $(TARGET)/*

rebuild: clean all

clang-format_copy: 
	cp ../materials/linters/.clang-format .clang-format
	
clang-format: clang-format_copy
	clang-format -n *.h *.c
	clang-format -i *.h *.c

leaks:
	leaks -atExit -- $(TARGET)/Quest_1
	leaks -atExit -- $(TARGET)/Quest_2