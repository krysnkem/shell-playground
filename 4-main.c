#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int _strlen(char *s);
char *_strncat(char *dest, char *src, int n);

/**
 * main - read input from user
 * @ac: number of arguments
 * @av: list of arguements strings
 *
 * Return: Always 0
 */
int main(int ac, char **av)
{
	unsigned int i = 1, j;
	char *dir, *paths_str = _getenv("PATH");
	string_t *dirs_path;
	struct stat statbuf;
	int size;

	if (paths_str == NULL)
	{
		write(2, "variable doesnot exist\n", 30);
		return (1);
	}
	dirs_path = split_string(paths_str, ":");
	if (dirs_path == NULL)
	{
		write(2, "Failed to split string\n", 15);
		return(1);
	}
	while (av[i])
	{
		j = 0;
		while (dirs_path->str[j])
		{
			size = (strlen(dirs_path->str[j]) + strlen(av[i])) + 2;
			dir = malloc(size);
			if (dir == NULL)
			{
				write(2, "malloc error\n", 20);
				return (1);
			}
			strcat(dir, dirs_path->str[j]);
			strcat(dir, "/");
			strcat(dir, av[i]);
			dir[size - 1] = '\0';
			if (stat(dir, &statbuf) == 0)
			{
				write(1, dir, strlen(dir));
				write(1, "\n", 1);
			}
			++j;

		}
		++i;
	}
	free(paths_str);
	free(dir);
	j = 0;
	free(dirs_path->str);
	free(dirs_path);
	return (0);
}


/**
 * _strncat - concatenates two strings together
 * @dest: destination string
 * @src: source string
 * @n: bytes to copy
 *
 * Return: destination string
 **/

char *_strncat(char *dest, char *src, int n)
{
	int max, src_len, dest_len;
	int i;

	src_len = _strlen(src);
	dest_len = _strlen(dest);

	if (n >= src_len)
		max = src_len;
	else
		max = n;
	i = 0;
	while (i < max)
	{
		dest[dest_len + i] = src[i];
		++i;
	}
	return (dest);
}

/**
 * _strlen - returns the length of a string
 * @s: the string
 *
 * Return: the length of a string
 */

int _strlen(char *s)
{
	int count;

	count = 0;
	while (*(s + count) != '\0')
	{
		++count;
	}
	return (count);
}
