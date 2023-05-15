#include "main.h"

/**
 * main - Entry point for the shell program
 * Return: The status code of the last command executed
 */
int main(void)
{
	int should_run = 1;
	shell sh = {NULL};

	sh.builtins = get_builtins();
	sh.num_builtins = num_builtins();

	while (should_run)
	{
		if (isatty(STDIN_FILENO))
			_printf("myshell> ");

		sh.args = read_input(&sh.input);
		if (sh.args == NULL)
			break;

		execute_command(&sh);

		free(sh.input);
	}
	return (sh.status);
}
