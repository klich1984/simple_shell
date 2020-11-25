#include "holberton.h"

/**
 *  _getenv - search string
 *  @name: String to search
 *	@env: environment
 *  Return: Pointer to the string
 */
char *_getenv(const char *name, char **env)
{
	char *ptr = NULL;
	char **list = NULL;
	int size = 0;
	int i = 0, j = 0;

	list = env;
	for (i = 0; list[i] != NULL; i++)
	{
		for (j = 0; name[j] == list[i][j]; j++)
		{
		}
		if (name[j] == '\0' && list[i][j] == '=')
		{
			/*liberar malloc*/
			size = string_size(list[i]);
			ptr = malloc(size + 1);
			if (ptr == NULL)
			{
				return (NULL);
			}
			ptr = _strcpy(ptr, list[i]);
			return (ptr);
		}
	}
	if (name[j] == '\0' && list[i][j] == '=')
	{
		size = string_size(list[i]);
		ptr = malloc(size + 1);
		if (ptr == NULL)
		{
			return (NULL);
		}
		_strcpy(ptr, list[i]);
	}
	return (ptr);
}

/**
 *  exit_sh - exits the current shell
 *  Return: void
 */
int exit_sh(void)
{
	return (-1);
}

/**
 *  print_env - prints the current environment
 *  Return: always 0
 */
int print_env(void)
{
	int i = 0, j = 0;
	char **env = __environ;

	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '\0')
		{
			write(1, &(env[i][j]), 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

/**
 *  equal_strings - prints the current environment
 *  @s1: string to be compared
 *  @s2: string to be compared
 *  Return: always 0
 */
int equal_strings(char *s1, char *s2)
{
	int i = 0;

	if (string_size(s1) != string_size(s2))
	{
		return (-1);
	}

	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	return (0);
}

/**
 *  check_builtin - prints the current environment
 *  @str: string to be compared
 *  @bt: string to be compared
 *  Return: 0 if found a builtin -1 if not
 */
builtin *check_builtin(char *str, builtin *bt)
{
	int i = 0;

	while (bt[i].command != NULL)
	{
		if (equal_strings(bt[i].command, str) == 0)
		{
			return (&(bt[i]));
		}
		i++;
	}
	return (NULL);
}
