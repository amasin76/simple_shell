#include "main.h"

/**
 * _atoi - convert a string of digits into an integer
 * @str: the string to be converted
 * Return: the converted integer
 */
int _atoi(const char *str)
{
	uint i = 0, result = 0, sign = 1;

	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;

	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}

	for (; str[i] >= '0' && str[i] <= '9'; i++)
		result = result * 10 + (str[i] - '0');

	return (sign * result);
}

/**
 * _itoa - convert a integer to a string in the given base (n)
 * @x: the integer to convert
 * @s: the output string
 * @base: the base of the number
 * @sign: whether or not to include a sign character
 * Return: the length of the string.
 */
int _itoa(long x, char s[], int base, int sign)
{
	uint n, i = 0, neg = 0;

	if (sign && x < 0)
	{
		neg = 1;
		n = -x;
	}
	else
		n = x;

	do
		s[i++] = n % base + '0';
	while ((n /= base) > 0);

	if (neg)
		s[i++] = '-';

	s[i] = '\0';
	reverse_str(s);
	return (i);
}
