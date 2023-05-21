#include "main.h"

/**
 * write_str - Writes a string to a file descriptor
 * @fd: The file descriptor to write to
 * @s: The string to write
 */
void write_str(int fd, char *s)
{
	(!s) && (s = "(null)");
	write(fd, s, _strlen(s));
}

/**
 * _strdup - Duplicates a string
 * @s: The string to duplicate
 * Return: Pointer to the duplicated string, or NULL if fails
 */
char *_strdup(const char *s)
{
	int i;
	char *result;

	result = malloc(sizeof(char) * (_strlen((char *)s) + 1));
	if (result == NULL)
		return (NULL);

	for (i = 0; s[i]; i++)
		result[i] = s[i];

	result[i] = '\0';

	return (result);
}

/**
 * _strtok - Tokenizes a string by a given delimiter
 * @str: the string to split
 * @delim: The delimiter used for tokenization
 * Return: A pointer to the next token in the string
 */
char *_strtok(char *str, char *delim)
{
	int i;
	char *curr;
	static char *next;

	(str) ? (curr = str) : (curr = next);

	if (!curr)
		return (NULL);
	/* Skip leading delimiters */
	while (*curr)
	{
		for (i = 0; delim[i]; i++)
			if (*curr == delim[i])
				break;

		if (!delim[i])
			break;
		curr++;
	}
	if (!*curr)
		return (NULL);
	/* Find the end of the token */
	next = curr;
	while (*next)
	{
		for (i = 0; delim[i]; i++)
			if (*next == delim[i])
				break;
		if (delim[i])
			break;
		next++;
	}
	if (*next)
	{
		*next = '\0';
		next++;
	}
	return (curr);
}

/**
 * _strtok_r - tokenizes a string using a delimiter (safe)
 * @str: The string to split
 * @delim: The delimiter character used to split the string
 * @saveptr: pointer to save the position of the next token
 *
 * used instead of _strtok because it is reentrant and can be safely used in
 * multi-process. The _strtok function uses a static variable to keep track of
 * the position in the string between calls, which can cause issues if the
 * function is called from multiple threads or if it is called recursively.
 *
 * Return: pointer to the start of the token, or NULL if no more tokens
 */
char *_strtok_r(char *str, const char *delim, char **saveptr)
{
	char *token_start, *token_end;
	const char *d;

	if (str == NULL)
		str = *saveptr;
	token_start = str;
	while (*token_start != '\0')
	{
		for (d = delim; *d != '\0'; d++)
			if (*token_start == *d)
				break;
		if (*d == '\0')
			break;
		token_start++;
	}
	if (*token_start == '\0')
	{
		*saveptr = token_start;
		return (NULL);
	}
	token_end = token_start;
	while (*token_end != '\0')
	{
		for (d = delim; *d != '\0'; d++)
			if (*token_end == *d)
				break;
		if (*d != '\0')
			break;
		token_end++;
	}
	if (*token_end != '\0')
	{
		*token_end = '\0';
		*saveptr = token_end + 1;
	}
	else
		*saveptr = token_end;

	return (token_start);
}
