#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <unistd.h>
#include "sys/stat.h"
#include "sys/types.h"
#include <sys/wait.h>
#include <fcntl.h>

#define BUFFER_SIZE 2048
#define MAX_CMDS 10
#define MAX_ARGS 10

typedef unsigned int uint;
typedef struct shell shell;

/**
 * struct command - Struct contains builtins command name and function pointer
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
 * @args: An array of strings containing arguments from the user input
 * @commands: An array of strings containing commands from the user input
 * @environ_copy: An array of strings containing a copy of the environ
 * @builtins: A pointer to an array of containing about the builtin commands
 * @num_builtins: The count of builtin commands
 * @cmd_count: The count of commands in the user input
 * @status: The exit status of the last command executed
 * @run: A boolean whether or not the shell should continue running
 */
struct shell
{
	char *input;
	char **args;
	char **commands;
	char **environ_copy;
	command *builtins;
	int num_builtins;
	int cmd_count;
	int status;
	int run;
};

extern char **environ;

/* main */
void init_shell(shell *sh);
void free_shell(shell *sh);

/* input */
void read_input(shell *sh);
char **parse_command(char *cmd);

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
void copy_environ(shell *sh);

/* utils_num */
int _atoi(const char *str);
int _itoa(long n, char s[], int base, int sign);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
void free_double(char ***ptr);

/* utils_str */
uint _strlen(char *s);
void reverse_str(char s[]);
int _stoa(char *s, char *buf);
int _strcmp(const char *s1, const char *s2, size_t n);
void *_memcpy(void *dest, const void *src, size_t n);
char *_strdup(const char *s);
char *_strtok(char *str, char *delim);

#endif
