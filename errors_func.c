#include "holberton.h"

/**
* free_pointers - frees pointers
* @path: pointer to free
* @arguments: pointer to free
* @line: pointer to free
* Return: void
*/
void free_pointers(char *path, char **arguments, char *line)
{
	if (path != *arguments)
		free(path);
	if (arguments)
		free(arguments);
	if (path != line && line)
		free(line);
}

/**
 * count_digits - Counter arrays
 * @number: value have counted
 * Return: size
 */
int count_digits(int number)
{
	int size = 0;

	if (number == 0)
		return (1);

	while (number != 0)
	{
		number /= 10;
		size++;
	}
	return (size);
}
/**
 * trans_number - Pointer that contain the revert numbers
 * @number: to revert
 * @size: size of array
 * Return: pointer revert
 */
char *trans_number(int number, int size)
{
	char *ptr, *ptrRev;
	int i = 0, j = 0;

	ptr = malloc(size * sizeof(char) + 1);
	if (ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (number == 0)
	{
		ptr[0] = '0';
		ptr[1] = '\0';
		return (ptr);
	}
	ptrRev = malloc(size * sizeof(char) + 1);
	if (ptrRev == NULL)
	{
		free(ptr);
		free(ptrRev);
		return (NULL);
	}
	while (i < size)
	{
		ptr[i] = (number % 10) + '0';
		number /= 10;
		i++;
	}
	ptr[i] = '\0';
	while (ptr[j] != '\0')
	{
		ptrRev[j] = ptr[i - 1];
		i--;
		j++;
	}
	ptrRev[j] = '\0';
	free(ptr);
	return (ptrRev);
}
/**
 * print_errors - Print errors
 * @arg: pointer pos1
 * @line: pointer pos2
 * @err: pointer pos3
 * @count: number of error
 * @con: conditional
 * Return: Noting
 */
void print_errors(char *arg, char *line, char *err, int count, int con)
{
		int size_coun_err = 0, size_arg = 0, size_line = 0, size_error = 0;
		char *number_trans = NULL;

		size_arg = string_size(arg);
		size_error = string_size(err);
		size_line = string_size(line);
		size_coun_err = count_digits(count);
		number_trans = trans_number(count, size_coun_err);
		write(STDERR_FILENO, arg, size_arg);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, number_trans, size_coun_err);
		write(STDERR_FILENO, ": ", 2);
		if (con == 0)
		{
			write(STDERR_FILENO, line, size_line);
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, err, size_error + 1);
		} else
		{
			write(STDERR_FILENO, err, size_error + 1);
			write(STDERR_FILENO, line, size_line);
			write(STDERR_FILENO, "\n", 1);
		}
}
