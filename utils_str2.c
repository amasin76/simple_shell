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
