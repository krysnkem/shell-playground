#include <string.h>
#include <stdlib.h>

char **split_string(char str[])
{
	char *delim = " ", *token, **string_array;
	unsigned int i = 0;
	unsigned int count_words = 1;

	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] != ' ')
			++count_words;
		++i;
	}

	string_array = malloc(sizeof(*string_array) * (count_words));
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

	return (string_array);

}
