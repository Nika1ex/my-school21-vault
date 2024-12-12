CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
TARGET = ../../build

all: Quest_3

Quest_3: main_executable_module.o data_io.o data_stat.o data_process.o decision.o
	$(CC) $(FLAGS) main_executable_module.o data_io.o data_stat.o data_process.o decision.o -o $(TARGET)/Quest_3

main_executable_module.o: main_executable_module.c
	$(CC) $(FLAGS) -c main_executable_module.c -o main_executable_module.o

data_io.o: ../data_libs/data_io.c
	$(CC) $(FLAGS) -c ../data_libs/data_io.c -o data_io.o

data_stat.o: ../data_libs/data_stat.c
	$(CC) $(FLAGS) -c ../data_libs/data_stat.c -o data_stat.o

data_process.o: ../data_module/data_process.c
	$(CC) $(FLAGS) -c ../data_module/data_process.c -o data_process.o

decision.o: ../yet_another_decision_module/decision.c
	$(CC) $(FLAGS) -c ../yet_another_decision_module/decision.c -o decision.o

clean:
	rm -rf *.o *.a $(TARGET)/*

rebuild: clean all

main_executable_module_with_macro.o: main_executable_module.c ../data_libs/data_io_macro.h
	$(CC) $(FLAGS) -DDATA_IO_MACRO_H -c main_executable_module.c -o main_executable_module_with_macro.o

build_with_macro: main_executable_module_with_macro.o data_io.o data_stat.o data_process.o decision.o
	$(CC) $(FLAGS) main_executable_module_with_macro.o data_io.o data_stat.o data_process.o decision.o -o $(TARGET)/Quest_4

data_stat.a: data_stat.o
	ar -rcs data_stat.a data_stat.o

build_with_static: main_executable_module.o data_io.o data_process.o decision.o data_stat.a
	$(CC) $(FLAGS) data_stat.a main_executable_module.o data_io.o data_process.o decision.o -o $(TARGET)/Quest_5

data_process.so: 
	$(CC) $(FLAGS) -c -fPIC ../data_module/data_process.c 
	$(CC) $(FLAGS) -c -fPIC ../data_libs/data_stat.c
	$(CC) $(FLAGS) -shared -o data_process.so data_process.o data_stat.o

build_with_dynamic: FLAGS+=-DUSE_DYNAMIC
build_with_dynamic: main_executable_module.o data_io.o decision.o data_process.so
	$(CC) $(FLAGS) data_process.so main_executable_module.o data_io.o decision.o -o $(TARGET)/Quest_6 
	mv data_process.so $(TARGET)