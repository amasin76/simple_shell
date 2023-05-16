#include "main.h"

/**
 * cmd_exit - exits the program
 * @sh: Pointer to the shell structure
 */
static void cmd_exit(shell *sh)
{
	free(sh->input);

	if (sh->args[1])
		exit(_atoi(sh->args[1]));
	else
		exit(0);
}

/**
 * cmd_env - prints the current environment
 * @sh: Pointer to the shell structure
 */
static void cmd_env(shell *sh)
{
	uint i;
	(void)(sh);

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
