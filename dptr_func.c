#include "holberton.h"

/**
 *	size_dptr - counts the size of a double ptr
 *	@ptr: ptr to count
 *	Return: double ptr
 */
int size_dptr(char **ptr)
{
	int i = 0;

	while (ptr[i] != NULL)
	{
		i++;
	}
	return (i);
}

/**
 *  _count_token - divides a line
 *  @line: line to be divided
 *  @delim: delimitator
 *
 *  Return: array of arguments
 */
int _count_token(char *line, char *delim)
{
	int coun_tokens = 0, i = 0;

	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			i++;
		else
		{
			if (line[i + 1] == ' ' || line[i + 1] == '\0'
			|| line[i + 1] == *delim)
				coun_tokens++;
			i++;
		}
	}
	return (coun_tokens);
}

/**
 *  free_dptr - frees a double pointer
 *  @ptr: pointer to be freed
 *
 *  Return: void
 */
void free_dptr(char **ptr)
{
	int i = 0;

	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

/**
 *	copydptr - copies all elements of a double pointer to another
 *	@dest: pointer to copy to
 *	@src: pointer to copy from
 *  @size: size of the src pointer
 *	Return: double ptr
 */
char **copydptr(char **dest, char **src, int size)
{
	int i = 0, s_size = 0;

	while (i < size)
	{
		s_size = string_size(src[i]);
		if (src[i] != NULL)
		{
			dest[i] = malloc((s_size + 1) * sizeof(char));
			if (dest[i] == NULL)
			{
				free_dptr(dest);
				return (NULL);
			}
			_strcpy(dest[i], src[i]);
		}
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

/**
 *	concat_string - concats a string into another one given an offset
 *	@dest: pointer to copy to
 *	@src: pointer to copy from
 *  @offset: offset index
 *	Return: void
 */
void concat_string(char *dest, char *src, int offset)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i + offset] = src[i];
		i++;
	}
}
