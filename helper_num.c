#include "shell.h"
/**
 * long_to_string - converts a number to a string.
 * @number: number to convert into string.
 * @string: buffer to save the number as string.
 * @base: base to convert number
 * Return: void
 */
void long_to_string(long number, char *string, int base)
{
	int i = 0, iNegative = 0;
	long cociente = number;
	char l[] = {"0123456789abcdef"};

	if (cociente == 0)
		string[i++] = '0';

	if (string[0] == '-')
		iNegative = 1;

	while (cociente)
	{
		if (cociente < 0)
			string[i++] = l[-(cociente % base)];
		else
			string[i++] = l[cociente % base];
		cociente /= base;
	}
	if (iNegative)
		string[i++] = '-';

	string[i] = '\0';
	str_reverse(string);
}


/**
 * _atoi - convert a string to an integer.
 * @s: the string
 * Return: string num or 0.
 */
int _atoi(char *s)
{
	int sin = 1;
	unsigned int num = 0;
	/*1- analisys sign*/
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sin *= -1;
		if (*s == '+')
			sin *= +1;
		s++;
	}

	/*2 - extract the number */
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		num = (num * 10) + (*s - '0');
		s++;
	}
	return (num * sin);
}

/**
 * count_characters - count character
 * @string: pointer char
 * @character: string with  chars to be counted
 * Return: string num or 0.
 */
int count_characters(char *string, char *character)
{
	int x = 0, count = 0;

	for (; string[x]; x++)
	{
		if (string[x] == character[0])
			count++;
	}
	return (count);
}
