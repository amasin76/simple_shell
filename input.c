#include "main.h"
#include <string.h>
#include <stdio.h>

/**
 * read_line - reads a line from stdin
 * Return: pointer to the line read, or NULL if EOF is reached
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		if (feof(stdin))
		{
			return (NULL);
		}
		else
		{
			_fprintf(STDERR_FILENO, "Error: read failed\n");
			exit(EXIT_FAILURE);
		}
	}

	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
 * read_input - reads input from the user and stores it in an array of strings
 * @input: pointer to a string that will be used to store the user's input
 * Return: pointer to an array of strings containing the user's input
 */
char **read_input(char **input)
{
	int i = 0, args_size = 10;
	char **args, **new_args;

	*input = read_line();
	if (*input == NULL)
		return (NULL);

	args = malloc(args_size * sizeof(char *));
	if (args == NULL)
	{
		_fprintf(STDERR_FILENO, "Error: memory allocation failed\n");
		exit(EXIT_FAILURE);
	}

	args[i] = strtok(*input, " ");
	while (args[i])
	{
		i++;
		if (i >= args_size)
		{
			args_size *= 2;
			new_args = malloc(args_size * sizeof(char *));
			if (new_args == NULL)
			{
				_fprintf(STDERR_FILENO, "Error: memory allocation failed\n");
				exit(EXIT_FAILURE);
			}
			_memcpy(new_args, args, i * sizeof(char *));
			free(args);
			args = new_args;
		}
		args[i] = strtok(NULL, " ");
	}
	return (args);
}
