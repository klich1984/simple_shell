#include "holberton.h"

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
	{
		if (bt_found->type == 0)
		{
			pid = fork();

			if (pid == 0)
			{
				bt_found->function();
				free_pointers(command, args, NULL);
				exit(1);
			}
			else
				wait(&status);
		} else
		{
			free_pointers(command, args, NULL);
			return (bt_found->function());
		}
		return (0);
	}

	pid = fork();

	if (pid == 0)
	{
		if (execve(command, args, __environ) == -1)
		{
			free_pointers(command, args, NULL);
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
	prompt_size = string_size(text);
	/*
	*       must use #include <unistd.h>
	*/
	if (write(STDOUT_FILENO, text, prompt_size) == -1)
	{
		perror("t-sh");
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
* Return: 0 always
*/

int main(int argc, char **argv)
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

	start_loop(bt, argv[0]);
	return (0);
}

/**
* trans_arguments - transforms the arguments
* @args: arguments
* @bt: builtin list
* @argv: name of the program
* @coun_loop: amount of loops
* Return: path to the command
*/
char *trans_arguments(char **args, builtin *bt, char *argv, int coun_loop)
{
	char *aux = NULL;
	struct stat statbuf;

	if (check_builtin(args[0], bt) == NULL)
	{
		if (stat(args[0], &statbuf) == -1)
		{
			aux = concat_path(args[0]);
			if (aux ==  NULL)
			{
				print_errors(argv, args[0], "not found\n", coun_loop, 0);
				return (NULL);
			}
		} else
			aux = args[0];
	} else
	{
		if (size_dptr(args) > 1)
		{
			return (NULL);
		}
		aux = args[0];
	}
	return (aux);
}

/**
* start_loop - starts the inifinite loop
* @bt: struct whit arguments builtin
* @argv: name of the program
* Return: Noting
*/

void start_loop(builtin *bt, char *argv)
{
	int coun_loop = 0;
	char *line = NULL, **arguments = NULL, *path = NULL;

	while (++coun_loop)
	{
		line = prompt("(&) ");
		if (!line)
		{
			write(1, "\n", 1);
			exit(0);
		} else if (string_size(line) == 0)
		{
			free(line);
			continue;
		}
		arguments = divide_line(line, " ");

		path = trans_arguments(arguments, bt, argv, coun_loop);

		if (path == NULL)
		{
			free_pointers(NULL, arguments, line);
			continue;
		}
		if (execute_command(path, arguments, bt) == -1)
			exit(-1);
		free_pointers(path, arguments, line);
	}
}
