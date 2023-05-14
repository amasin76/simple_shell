#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <unistd.h>
#include "sys/stat.h"
#include "sys/types.h"
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_SIZE 1024

typedef unsigned int uint;

/**
 * struct command - Struct to store a command name and function pointer
 * @name: Pointer to the command name string
 * @func: Pointer to the function associated with the command
 */
typedef struct command
{
	char *name;
	void (*func)(char **);
} command;

/* main */
void execute_command(char **args, int *status,
					 command *builtins, int num_builtins);

/* _printf */
void _printf(const char *fmt, ...);
void _fprintf(int fd, const char *fmt, ...);
void _sprintf(char *str, const char *fmt, ...);

/* input */
char *read_line(void);
char **read_input(char **input);

/* find_cmd */
char *find_command(char *command);

/* builtins */
int num_builtins(void);
command *get_builtins(void);

/* utils_num */
int _atoi(const char *str);
int _itoa(long n, char s[], int base, int sign);
/* utils_str */
uint _strlen(char *s);
void reverse_str(char s[]);
int _stoa(char *s, char *buf);
int _strcmp(const char *s1, const char *s2);
void *_memcpy(void *dest, const void *src, size_t n);
char *_strdup(const char *s);

#endif
