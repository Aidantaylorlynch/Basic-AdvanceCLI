# author: Aidan Taylor-Lynch
# studentID: 24205230
# start date: 18/8/17
# last modified:
# description:

task1: task1.o task1_functions.o
	gcc -Wall task1.o task1_functions.o -o task1

task1.o: task1.c
	gcc -c task1.c

task1_functions.o: task1_functions.c task1_functions.h
	gcc -c task1_functions.c task1_functions.h

clean:
	rm *.o task1 *.gch
