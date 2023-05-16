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
 * @str: The string to be tokenized
 * @delim: The delimiter used for tokenization
 *
 * Return: A pointer to the next token in the string
 */

char *_strtok(char *str, char *delim)
{
	static char *last;
	char *token;

	if (str != NULL)
		last = str;

	if (last == NULL || *last == '\0')
		return (NULL);

	token = last;

	while (*last != '\0')
	{
		if (*last == *delim)
		{
			*last = '\0';
			last++;
			return (token);
		}
		last++;
	}
	return (token);
}
