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

/**
 * cmd_env - prints the current environment
 * @args: command line arguments
 */
static void cmd_env(char **args)
{
	uint i;
	(void)(args);

	if (!environ)
	{
		_fprintf(STDERR_FILENO, "Error: environ is NULL\n");
		return;
	}
	for (i = 0; environ[i]; i++)
		_printf("%s\n", environ[i]);
}

static command builtins[] = {
	{"exit", cmd_exit},
	{"env", cmd_env},
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
