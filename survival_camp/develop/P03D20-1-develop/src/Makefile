CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
TARGET = ../build/graph

all: graph.o rendering.o polish.o opn_convert.o stack.o
	$(CC) $(FLAGS) graph.o rendering.o polish.o opn_convert.o stack.o -o $(TARGET)

graph.o: graph.c
	$(CC) $(FLAGS) -c graph.c -o graph.o

rendering.o: rendering.c
	$(CC) $(FLAGS) -c rendering.c -o rendering.o

opn_convert.o: opn_convert.c
	$(CC) $(CFLAGS) -c opn_convert.c -o opn_convert.o
	
stack.o: stack.c  
	$(CC) $(CFLAGS) -c stack.c -o stack.o

polish.o: polish.c
	$(CC) $(CFLAGS) -c polish.c -o polish.o

clean:
	rm -rf *.o $(TARGET)

rebuild: clean all

clang-format_copy: 
	cp ../materials/linters/.clang-format .clang-format
	
clang-format: clang-format_copy
	clang-format -i *.c *.h

leaks:
	leaks -atExit -- ../build/graph

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem .