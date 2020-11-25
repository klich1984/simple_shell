#include "holberton.h"
#define _GNU_SOURCE

/**
* execute_command - prompts a message and gets user input
* @command: comand
* @args: arguments
* @bt: list_builtin
* Return: integer
*/

int execute_command(char *command, char **args, builtin *bt)
{
	builtin *bt_found = NULL;
	int pid = 0, status;

	bt_found = check_builtin(command, bt);

	if (bt_found != NULL)
		return (bt_found->function());

	pid = fork();
	if (pid == 0)
	{
		if (execve(command, args, __environ) == -1)
		{
			return (-1);
		}
	}
	else
		wait(&status);
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
	if (isatty(STDIN_FILENO) == 1)
	{
		prompt_size = string_size(text);

		if (write(STDOUT_FILENO, text, prompt_size) == -1)
		{
			perror("t-sh");
		}
	}
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
* @argc: amount of arguments
* @argv: arguments
* @env: environment
* Return: 0 always
*/

int main(int argc, char **argv, char **env)
{
	builtin bt[] = {
		{0, "env", print_env},
		{1, "exit", exit_sh},
		{-1, NULL, NULL}
	};

	if (argc > 1)
	{
		print_errors(argv[0], argv[1], "Can't open ", 0, 1);
		return (-1);
	}

	start_loop(bt, argv[0], env);
	return (0);
}

/**
* trans_arguments - transforms the arguments
* @ac: arguments
* @bt: builtin list
* @av: name of the program
* @c: amount of loops
* @env: environment
* Return: path to the command
*/
char *trans_arguments(char **ac, builtin *bt, char *av, int c, char **env)
{
	char *aux = NULL;
	struct stat statbuf;

	if (check_builtin(ac[0], bt) == NULL)
	{
		if (stat(ac[0], &statbuf) == -1)
		{
			aux = concat_path(ac[0], env);
			if (aux ==  NULL)
			{
				print_errors(av, ac[0], "not found\n", c, 0);
				return (NULL);
			}
		} else
			aux = ac[0];
	} else
	{
		if (size_dptr(ac) > 1)
		{
			return (NULL);
		}
		aux = ac[0];
	}
	return (aux);
}

/**
* start_loop - starts the inifinite loop
* @bt: struct whit arguments builtin
* @argv: name of the program
* @env: environment
* Return: Noting
*/

void start_loop(builtin *bt, char *argv, char **env)
{
	int coun_loop = 0;
	char *line = NULL, **arguments = NULL, *path = NULL;

	while (++coun_loop)
	{
		line = prompt("(&) ");
		if (!line)
		{
			if (isatty(STDIN_FILENO) != 0)
				write(1, "\n", 1);
			exit(0);
		} else if (string_size(line) == 0)
		{
			free(line);
			continue;
		}
		arguments = divide_line(line, " ");
		path = trans_arguments(arguments, bt, argv, coun_loop, env);
		if (path == NULL)
		{
			free(arguments);
			free(line);
			continue;
		}
		if (execute_command(path, arguments, bt) == -1)
		{
			if (line != path && path != arguments[0])
				free(path);

			free(arguments);
			free(line);
			exit(-1);
		}
		if (line != path && path != arguments[0])
		{
			free(path);
		}
		free(arguments);
		free(line);
	}
}
