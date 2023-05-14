#include "main.h"

/**
 * main - Entry point for the shell program
 * Return: The status code of the last command executed
 */
int main(void)
{
	int status = 0, should_run = 1;
	char *input = NULL, **args = NULL;

	while (should_run)
	{
		if (isatty(STDIN_FILENO))
			_printf("myshell> ");

		args = read_input(&input);
		if (args == NULL)
			break;

		execute_command(args, &status);

		free(input);
		free(args);
	}
	return (status);
}
