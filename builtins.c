#include "main.h"
#include <stdio.h>

/**
 * cmd_exit - exits the program
 * @sh: Pointer to the shell structure
 */
static void cmd_exit(shell *sh)
{
	int status = 0;

	if (sh->args[1])
		status = _atoi(sh->args[1]);

	free(sh->input);
	exit(status);
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

/**
 * cmd_cd - Change the current working directory
 * @sh: Pointer to the shell structure
 */
static void cmd_cd(shell *sh)
{
	char buf[BUFFER_SIZE];
	char *new_dir, *old_dir;

	old_dir = getcwd(buf, BUFFER_SIZE);

	if (!sh->args[1])
		new_dir = _getenv("HOME");
	else if (_strcmp(sh->args[1], "-", -1) == 0)
	{
		new_dir = _getenv("OLDPWD");
		_printf("%s\n", new_dir);
	}
	else
		new_dir = sh->args[1];

	if (chdir(new_dir) != 0)
		perror("cd");

	setenv("OLDPWD", old_dir, 1);
	setenv("PWD", getcwd(buf, BUFFER_SIZE), 1);
}

/**
 * cmd_setenv - Set or update the value of an environment variable
 * @sh: Pointer to the shell structure
 */
static void cmd_setenv(shell *sh)
{
	int result;

	if (sh->args[1] == NULL || sh->args[2] == NULL)
	{
		_fprintf(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n");
		return;
	}

	result = _setenv(sh->args[1], sh->args[2], 1);

	if (result == -1)
		_fprintf(STDERR_FILENO, "Failed to set environment variable\n");
}

command *get_builtins(void)
{
	static command builtins[] = {
		{"exit", cmd_exit},
		{"env", cmd_env},
		{"cd", cmd_cd},
		{"setenv", cmd_setenv},
		{NULL, NULL},
	};
	return (builtins);
}
