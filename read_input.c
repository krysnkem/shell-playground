#include <stdio.h>
#include <stdlib.h>

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

	printf("#cisfun$ ");
	characters = getline(&buffer, &bufsize, stdin);
	if (characters != -1)
		return (buffer);

	return (NULL);
}
