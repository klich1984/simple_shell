#include "holberton.h"

/**
* free_pointers - free pointers
* @line: line
* @path: absolute path
* @arguments: arguments
* Return: Noting
*/
void free_pointers(char *line, char *path, char **arguments)
{
	if (line != path && path != arguments[0])
	{
		free(path);
	}
	free(arguments);
	free(line);
}
