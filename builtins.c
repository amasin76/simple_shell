#include "main.h"

/**
 * cmd_exit - exits the program
 * @args: command line arguments
 */
static void cmd_exit(char **args)
{
	(void)(args);
	exit(0);
}

static command builtins[] = {
	{"exit", cmd_exit},
};

/**
 * num_builtins - Calculates the number of built-in commands
 * Return: Count of built-in commands
 */
int num_builtins(void)
{
	return (sizeof(builtins) / sizeof(command));
}

/**
 * get_builtins - Self explain
 * Return: Self explain
 */
command *get_builtins(void)
{
	return (builtins);
}
