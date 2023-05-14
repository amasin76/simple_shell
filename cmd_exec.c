#include "main.h"
#include <stdio.h>

/**
 * builtin_command - Executes a built-in cmd if it is found
 * @args: The arguments of the cmd
 * @builtins: An array of built-in cmds
 * @num_builtin: Count of built-in cmds
 * Return: Index of the built-in cmd that was executed, or 0 if none was found
 */
int builtin_command(char **args, command *builtins, int num_builtin)
{
	int i;

	for (i = 0; i < num_builtin; i++)
	{
		if (args[0] && _strcmp(args[0], builtins[i].name) == 0)
		{
			builtins[i].func(args);
			break;
		}
	}
	return (i);
}

/**
 * external_command - Self explain
 * @args: The arguments of the command
 * @status: The status of the command
 */
void external_command(char **args, int *status)
{
	pid_t pid;
	int ret, wstatus;
	char *full_path = NULL;

	/* Check if the command is an absolute path */
	if (args[0][0] == '/')
		full_path = args[0];
	/* OR find the full path of the command */
	else
		full_path = find_command(args[0]);

	if (full_path)
	{
		pid = fork();
		if (pid == 0)
		{
			ret = execve(full_path, args, NULL);
			if (ret == -1)
				perror(args[0]);
			if (full_path != args[0])
				free(full_path);
			_exit(ret);
		}
		else
			wait(&wstatus);
		/* Get the exit status of the child */
		if (WIFEXITED(wstatus))
			*status = WEXITSTATUS(wstatus);
	}
	else
		_fprintf(STDERR_FILENO, "%s: command not found\n", args[0]);
}

/**
 * execute_command - Executes a command
 * @args: The arguments of the command
 * @status: The status of the command
 */
void execute_command(char **args, int *status)
{
	command *builtins = get_builtins();
	int i, num_builtin = num_builtins();

	i = builtin_command(args, builtins, num_builtin);

	/* If it's not a builtin command */
	if (i == num_builtin)
		external_command(args, status);
}
