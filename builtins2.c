#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * update_environment - Update the environment with the new variable
 * @name: The name of the environment variable
 * @value: The value of the environment variable
 * @env_var: The new environment variable string
 * @env_var_len: The length of the environment variable string
 * @env: Pointer to the environment variable array
 */

void update_environment(const char *name, const char *value,
	char *env_var, size_t env_var_len, char **env)
{
	size_t env_count = 0;
	char **env_ptr = env;

	while (*env_ptr != NULL)
	{
		env_count++;
		env_ptr++;
	}

	char **new_environ = realloc(env, (env_count + 2) * sizeof(char *));

	if (new_environ == NULL)
	{
		_fprintf(STDERR_FILENO, "Failed to allocate memory\n");
		free(env_var);
		return;
	}
	env = new_environ;
	env[env_count] = env_var;
	env[env_count + 1] = NULL;
}

/**
 * cmd_setenv - Set or update the value of an environment variable
 * @name: The name of the environment variable
 * @value: The value to set for the environment variable
 * @overwrite: Flag indicating whether to overwrite an existing variable
 *
 * Return: On success, return 0. On failure, return -1.
 */

int cmd_setenv(const char *name, const char *value, int overwrite)
{
	if (name == NULL || value == NULL)
	{
		_fprintf(STDERR_FILENO, "Usage: cmd_setenv VARIABLE VALUE\n");
		return (-1);
	}

	size_t name_len = _strlen(name);
	size_t value_len = _strlen(value);
	size_t env_var_len = name_len + value_len + 2; /* +2 for '=' and '\0' */

	char **env;

	for (env = environ; *env != NULL; env++)
	{
		if (_strcmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{
			if (overwrite == 0)
				return (0);
			break;
		}
	}

	char *env_var = malloc(env_var_len);

	if (env_var == NULL)
	{
		_fprintf(STDERR_FILENO, "Failed to allocate memory\n");
		return (-1);
	}

	_sprintf(env_var, "%s=%s", name, value);
	if (*env == NULL)
		update_environment(name, value, env_var, env_var_len, env);
	else
	{
		free(*env);
		*env = env_var;
	}

	return (0);
}

/*To DO: unsetenv*/
