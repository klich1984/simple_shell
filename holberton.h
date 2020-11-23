#ifndef __HOLBERTON__H
#define __HOLBERTON__H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/**
 *  struct builtin - builtins struct
 *  @command: command to execute
 *  @function: function that gets executed when that command is called
 */

typedef struct builtin
{
	char *command;
	int (*function)(void);
} builtin;

void start_loop(builtin *bt);
int execute_command(char command, char* args, builtin *bt);
int check_builtin(char *str, builtin *bt);
int equal_strings(char *s1, char *s2);
int exit_sh(void);
int print_env(void);
char *concat_path(char *command);
void concat_string(char *dest, char *src, int offset);
char **divide_path(char *str);
char **copydptr(char **dest, char **src, int size);
void free_dptr(char **ptr);
int size_dptr(char **ptr);
char *_getenv(const char *name);
char *_strcpy(char *dest, char *src);
char **divide_line(char *line, char *delim);
int _count_token(char *line, char *delim);
char *prompt(char *text);
int string_size(char *str);

#endif