#include "main.h"
#include <stdio.h>

/**
 * main - Entry point for the shell program
 * Return: The status code of the last command executed
 */
int main(void)
{
	int status = 0, should_run = 1;
	char *input = NULL, **args = NULL;
	int num_builtin = num_builtins();
	command *builtins = get_builtins();

	while (should_run)
	{
		if (isatty(STDIN_FILENO))
			_printf("myshell> ");

		args = read_input(&input);
		if (args == NULL)
			break;

		execute_command(args, &status, builtins, num_builtin);

		free(input);
		free(args);
	}
	return (status);
}

/**
 * execute_command - Executes a command
 * @args: The arguments of the command
 * @status: The status of the command
 * @builtins: An array of builtin commands
 * @num_builtins: The number of builtin commands
 */
void execute_command(char **args, int *status,
					 command *builtins, int num_builtins)
{
	int i, wstatus;
	char *full_path = NULL;

	/* Check if the first argument is a builtin command */
	for (i = 0; i < num_builtins; i++)
	{
		if (args[0] && _strcmp(args[0], builtins[i].name) == 0)
		{
			builtins[i].func(args);
			break;
		}
	}
	/* If it's not a builtin command */
	if (i == num_builtins)
	{
		int ret;
		pid_t pid = fork();

		if (pid == 0)
		{
			if (args[0][0] == '/')
				ret = execve(args[0], args, NULL);
			else
			{
				full_path = find_command(args[0]);
				if (full_path != NULL)
				{
					ret = execve(full_path, args, NULL);
					free(full_path);
				}
			}
			_exit(ret);
		}
		else
			wait(&wstatus);

		if (WIFEXITED(wstatus))
			*status = WEXITSTATUS(wstatus);
	}
}
