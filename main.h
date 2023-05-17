#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <unistd.h>
#include "sys/stat.h"
#include "sys/types.h"
#include <sys/wait.h>
#include <fcntl.h>

#define BUFFER_SIZE 2048

typedef unsigned int uint;
typedef struct shell shell;

/**
 * struct command - Struct to store a command name and function pointer
 * @name: Pointer to the command name string
 * @func: Pointer to the function associated with the command
 */
typedef struct command
{
	char *name;
	void (*func)(shell *);
} command;

/**
 * struct shell - Struct contains information about the shell environment
 * @input: A pointer to a string containing the user's input
 * @args: An array of strings containing the arguments from the user's input
 * @builtins: A pointer to an array of containing about the builtin commands
 * @num_builtins: The number of builtin commands
 * @status: The exit status of the last command executed
 */
struct shell
{
	char *input;
	char **args;
	int num_builtins;
	command *builtins;
	int status;
};

extern char **environ;

/* main */
void init_builtins(shell *sh);

/* input */
char *read_line(void);
char **read_input(char **input);

/* builtins */
void cmd_setenv(shell *sh);
void cmd_unsetenv(shell *sh);
command *get_builtins(void);

/* cmd_exec */
void execute_command(shell *sh);

/* find_cmd */
char *find_command(char *command);

/* builtins */
void cmd_setenv(shell *sh);
void cmd_unsetenv(shell *sh);

/* _printf */
void _printf(const char *fmt, ...);
void _fprintf(int fd, const char *fmt, ...);
void _sprintf(char *str, const char *fmt, ...);

/* utils_sys */
ssize_t _getline(char **lineptr, size_t *n, int fd);
char *_getenv(const char *name);
char **copy_environ(void);

/* utils_num */
int _atoi(const char *str);
int _itoa(long n, char s[], int base, int sign);
void *_realloc(void *ptr, size_t old_size, size_t new_size);

/* utils_str */
uint _strlen(char *s);
void reverse_str(char s[]);
int _stoa(char *s, char *buf);
int _strcmp(const char *s1, const char *s2, size_t n);
void *_memcpy(void *dest, const void *src, size_t n);
char *_strdup(const char *s);
char *_strtok(char *str, char *delim);

#endif
