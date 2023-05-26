#include "shell.h"
/**
 * _strtok - separates strings with delimiters
 * @line: pointer to array we receive in getline
 * @delim: characters to split string
 * Return: A pointer to the token
*/
char *_strtok(char *line, char *delim)
{
	int y;
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (y = 0; delim[y] != '\0'; y++)
		{
			if (*str == delim[y])
			break;
		}
		if (delim[y] == '\0')
			break;
	}
	copystr = str;
	if (*copystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (y = 0; delim[y] != '\0'; y++)
		{
			if (*str == delim[y])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}
	return (copystr);
}
