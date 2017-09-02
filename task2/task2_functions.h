/*
 * author: Aidan Taylor-Lynch
 * studentID: 24205230
 * start date: 18/8/17
 * last modified: 2/9/17
 * description: this file contains the function prototypes for all the functions used in the advanced CLI.
 */
void clear(void);
void cd(char*);
void ls(char*);
void echo(char*);
void help(void);
void quit(void);
void create(char*);
void copy(char*, char*);
void run(char*);
void halt(char*);
void search(char*, char*);
extern int running; /* declaring global variable so functions in task2_functions can access it */
