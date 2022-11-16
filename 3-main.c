#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/**
 * main - read input from user
 * @ac: number of arguments
 B
 * @av: list of arguements strings
 *
 * Return: Always 0
 */
int main(int ac, char **av)
{
	string_t *split_str;
	char *value = _getenv("PATH");
	unsigned int i = 0;

	if (value == NULL)
	{
		write(2, "does not exist\n", 20);
		return (1);
	}
	split_str = split_string(value, ":");
	if (split_str == NULL)
	{
		write(2, "error while splitting string\n", 20);
		return (1);
	}
	while (split_str->str[i])
	{
		write(1, split_str->str[i], strlen(split_str->str[i]));
		write(1, "\n", 1);
		++i;
	}

	return (0);
}
