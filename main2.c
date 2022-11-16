#include "main.h"
#include <stdio.h>

/**
 * main - test _getenv
 *
 * Return: Always (0)
 */
int main(void)
{
	printf("%s\n", _getenv("PATH"));
	return (0);
}
