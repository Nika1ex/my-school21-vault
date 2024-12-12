CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
TARGET = ../build

all: door_struct list_test stack_test

door_struct: dmanager_module.o
	$(CC) $(FLAGS) dmanager_module.o -o $(TARGET)/Quest_1

list_test: list_test.o list.o
	$(CC) $(FLAGS) list_test.o list.o -o $(TARGET)/Quest_2

stack_test: stack_test.o stack.o 
	$(CC) $(FLAGS) stack_test.o stack.o -o $(TARGET)/Quest_3

dmanager_module.o: dmanager_module.c
	$(CC) $(FLAGS) -c dmanager_module.c -o dmanager_module.o

list_test.o: list_test.c
	$(CC) $(FLAGS) -c list_test.c -o list_test.o

list.o: list.c
	$(CC) $(FLAGS) -c list.c -o list.o

stack_test.o: stack_test.c
	$(CC) $(FLAGS) -c stack_test.c -o stack_test.o

stack.o: stack.c
	$(CC) $(FLAGS) -c stack.c -o stack.o

clean:
	rm -rf *.o $(TARGET)/*

rebuild: clean all