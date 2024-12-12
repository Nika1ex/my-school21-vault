CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
TARGET = ../build

all: print_module bst_create_test

print_module: print_module.o main_module_entry_point.o
	$(CC) $(FLAGS) print_module.o main_module_entry_point.o -o $(TARGET)/Quest_1

bst_create_test: bst.o bst_create_test.o
	$(CC) $(FLAGS) bst.o bst_create_test.o -o $(TARGET)/Quest_3

main_module_entry_point.o: main_module_entry_point.c
	$(CC) $(FLAGS) -c main_module_entry_point.c -o main_module_entry_point.o

print_module.o: print_module.c
	$(CC) $(FLAGS) -c print_module.c -o print_module.o

bst.o: bst.c
	$(CC) $(FLAGS) -c bst.c -o bst.o

bst_create_test.o: bst_create_test.c
	$(CC) $(FLAGS) -c bst_create_test.c -o bst_create_test.o

clean:
	rm -rf *.o $(TARGET)/*

rebuild: clean all