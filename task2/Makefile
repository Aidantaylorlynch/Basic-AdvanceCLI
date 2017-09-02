# author: Aidan Taylor-Lynch
# studentID: 24205230
# start date: 18/8/17
# last modified:
# description:

task2: task2.o task2_functions.o
	gcc -Wall task2.o task2_functions.o -o task2

task2.o: task2.c
	gcc -c task2.c

task2_functions.o: task2_functions.c task2_functions.h
	gcc -c task2_functions.c task2_functions.h

clean:
	rm *.o task2 *.gch
