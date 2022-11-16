#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

/**
 * execute_fwe - creates a new process and excutes
 * input command
 * @argv: array of arguments in string format
 * @fn: name of the executable file
 *
 * Return: on success (0)
 */

void execute_fwe(char *argv[], char *fn)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror(fn);
		exit(1);
	}
	if (child_pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror(fn);
			exit(2);
		}
	}
	else
	{
		wait(&status);
	}
}

/**
 * read_input - Entry point
 *
 * Return: Always 0
 */
char *read_input(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t characters;

	write(1, "#cisfun$ ", 10);
	characters = getline(&buffer, &bufsize, stdin);
	if (characters != -1)
		return (buffer);

	return (NULL);
}

/**
 * create_shell - creates a shell to that accepts single command
 * @fn: file name of the executable
 *
 * Return: Always 0
 */


int create_shell(char *fn)
{
	unsigned int i = 0, j;
	string_t *splitted_str;
	char **operand_str, *userInput = read_input();

	if (userInput == NULL)
	{
		write(1, "\n", 2);
		return (1);
	}
	splitted_str = split_string(userInput, " ");
	if (splitted_str == NULL)
	{
		write(1, "\n", 2);
		return (2);
	}
	operand_str = malloc(sizeof(*operand_str) * (splitted_str->num_memb + 1));
	if (operand_str == NULL)
		return (3);

	while (splitted_str->str[i])
	{
		operand_str[i] = malloc(strlen(splitted_str->str[i]));
		if (operand_str[i] == NULL)
		{
			free_grid(operand_str, i + 1);
			return (4);
		}
		j = 0;
		while (splitted_str->str[i][j] != '\n')
		{
			operand_str[i][j] = splitted_str->str[i][j];
			j++;
		}
		operand_str[i][j] = '\0';
		++i;
	}
	operand_str[i] = NULL;
	execute_fwe(operand_str, fn);
	free_grid(splitted_str->str, splitted_str->num_memb + 1);
	free(splitted_str);
	free_grid(operand_str, i + 1);
	return (0);
}


/**
 * split_string - splits a string into and arry of stings
 * @str: the string to be splitted
 * @delim: the delimitter string
 *
 * Return: pointer to the array of strings or NULL on failure
 */

string_t *split_string(char str[], char *delim)
{
	char *token, **string_array;
	unsigned int i = 0, j;
	unsigned int count_words = 1;
	string_t *op_string = malloc(sizeof(string_t));

	while (str[i])
	{
		j = 0;
		while (delim[j] && str[i + j] && delim[j] == str[i + j])
			++j;
		if (delim[j] == '\0')
			++count_words;
		if (str[i + j] == '\0' && delim[j] != '\0')
			break;
		++i;
	}
	string_array = malloc(sizeof(*string_array) * (count_words + 1));
	if (string_array == NULL)
		return (NULL);
	token = strtok(str, delim);
	i = 0;
	while (token)
	{
		string_array[i] = token;
		token = strtok(NULL, delim);
		++i;
	}
	string_array[i] = NULL;
	op_string->str = string_array;
	op_string->num_memb = count_words;

	return (op_string);

}

/**
 * free_grid - frees a 2 dimensional grid
 * @grid: pointer to grid
 * @height: the height of the grid
 *
 */
void free_grid(char **grid, int height)
{
	int i;

	i = 0;
	while (i < height)
	{
		free(*(grid + i));
		++i;
	}
	free(grid);
}
