#include "main.h"
#include <string.h>
#include <stdlib.h>

/**
 * _getenv - gets the value of an environment variable
 * @name: environment variable to be gotten
 *
 * Return: the address to the first character in that variable or NULL on
 * failure
 */
char *_getenv(const char *name)
{
	unsigned int i = 0, j, n, count = 0, pos;
	char *value;


	while (environ[i])
	{
		j = 0;
		while (environ[i][j] == name[j] && name[j] != '\0')
			++j;
		if (name[j] == '\0')
		{ 
			pos = j;
			while (environ[i][pos])
			{
				++count;
				++pos;
			}

			value = malloc(count + 1);
			if (value == NULL)
				return (NULL);
			n = 0;
			++j;
			while (environ[i][j] != '\0')
			{
				value[n] = environ[i][j];
				++j;
				++n;
			}
			value[n] = '\0';
			return (value);
		}
		++i;
	}
	return (NULL);
}
