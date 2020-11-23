#include "holberton.h"

/**
* execute_command - prompts a message and gets user input
* @command: comand
* @args: arguments
* @bt: list_builtin
* Return: integer
*/

int execute_command(char command, char *args, builtin *bt)
{
	int i = 0;

	while (bt[i].command != NULL)
	{
		if (equal_strings(bt[i].command, command) == 0)
		{
		bt[i].function();
		return (0);
		}
		i++;
	}
	if (execve(command, args, __environ) == -1)
	{
		return (-1);
	}
	return (0);
}

/**
* prompt - prompts a message and gets user input
* @text: text to be displayed as prompt
* Return: arguments as input recieved
*/

char *prompt(char *text)
{
	char *line = NULL;
	size_t size = 0;
	int prompt_size = 0, i = 0;

	if (!text)
	{
		perror("Prompt message can't be NULL");
		return (NULL);
	}
	prompt_size = string_size(text);
	/*
	*       must use #include <unistd.h>
	*/
	if (write(STDOUT_FILENO, text, prompt_size) == -1)
	{
		perror("t-sh");
	}
	/*
	*       Liberar!
	*/
	if (getline(&line, &size, stdin) == -1)
	{
		free(line);
		return (NULL);
	}
	while (line[i] != '\0')
	{
		if (line[i] == '\n' || line[i] == EOF)
		{
		line[i] = '\0';
		}
		i++;
	}
	return (line);
}

/**
* main - main function
* Return: 0 always
*/

int main(void)
{
	builtin bt[] = {
		{"env", print_env},
		{"exit", exit_sh},
		{NULL, NULL}
	};

	start_loop(bt);
	return (0);
}

/**
* start_loop - starts the inifinite loop
* @bt: struct whit arguments builtin
* Return: Noting
*/

void start_loop(builtin *bt)
{
	char *line = NULL;
	char **arguments = NULL;
	char *path = NULL;
	int i;
	int pid, status, pr = 0, path_status;
	struct stat statbuf;

	while (1)
	{
		line = prompt("prueba shell (&) ");
		if (!line || string_size(line) == 0)
		{
		write(1, "\n", 1);
		exit(0);
		}
		arguments = divide_line(line, " ");
		if (check_builtin(arguments[0], bt) == -1)
		{
		pr = stat(arguments[0], &statbuf);
		if (pr == -1)
		{
			path = concat_path(arguments[0]);
			if (path ==  NULL)
			{
			free(arguments);
			free(line);
			perror("not found");
			continue;
			}
		} else
			path = arguments[0];
		} else
		{
		if (size_dptr(arguments) > 1)
		{
			perror("sh: too many arguments");
			continue;
		}
		path = arguments[0];
		}
		pid = fork();
		if (pid == 0)
		{
		execute_command(path, arguments, bt);
		}
		else
		{
		wait(&status);
		}
		if (path != NULL)
		free(path);
		free(arguments);
		if (path != line)
		free(line);
	}
}
