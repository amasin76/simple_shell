#include "main.h"

/**
 * read_line - reads a line from stdin
 * Return: pointer to the line read, or NULL if EOF is reached
 * @sh: Pointer to the shell structure
 */
char *read_line(shell *sh)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = _getline(&line, &len, STDIN_FILENO);

	if (nread == -1)
	{
		sh->run = 0;
		free(line);
		return (NULL);
	}

	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
 * read_input - Reads input from the user and stores it in a shell struct
 * @sh: Pointer to the shell structure
 */
void read_input(shell *sh)
{
	int i = 0;
	char *cmd;

	sh->input = read_line(sh);
	if (!sh->input)
		return;

	cmd = sh->input;
	/* Tokenize by semicolons and store the first command in the commands */
	sh->commands[i] = _strtok(cmd, ";");

	/* Continue tokenizing after first command succeeded */
	while (sh->commands[i])
	{
		i++;
		if (i >= MAX_CMDS)
		{
			_fprintf(STDERR_FILENO, "Error: too many commands\n");
			exit(EXIT_FAILURE);
		}
		sh->commands[i] = _strtok(NULL, ";");
	}
	sh->cmd_count = i;
}

/**
 * parse_command - Parses a command string into an array of arguments
 * @sh: Pointer to the shell structure
 * @cmd: The command string to be parsed
 * Return: Pointer to the array of arguments, or NULL if command is empty
 */
void parse_command(shell *sh, char *cmd)
{
	int i = 0;
	char *start, *end;
	static char *args[MAX_ARGS];

	/* Trim the start of the command */
	start = cmd;
	while (*start == ' ' || *start == '\t')
		start++;

	/* Trim the end of the command */
	end = start + _strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t'))
		end--;

	/* Check if the command is empty */
	if (start >= end)
		return;

	args[i] = _strtok(cmd, " ");
	while (args[i])
	{
		i++;
		if (i >= MAX_ARGS)
		{
			_fprintf(STDERR_FILENO, "Error: too many arguments\n");
			exit(EXIT_FAILURE);
		}
		args[i] = _strtok(NULL, " ");
	}
	sh->args = args;
}
