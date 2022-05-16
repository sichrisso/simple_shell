#include "main.h"

/**
 * _toktok - function to divide the arguments
 * @buf: pointer to a string
 * Return: a variable contain the command
 */
char **_toktok(char *buf)
{
	char **arr, *tok;
	int j = 0;

	arr = malloc(sizeof(char *) * 32);
	tok = strtok(buf, " \n\r\t");

	for (j = 0; tok != NULL; j++)
	{
		arr[j] = tok;
		tok = strtok(NULL, " \n\r\t");
	}
	arr[j] = NULL;
	return (arr);
}
/**
 * countword - counts words from command line string
 * @str: string passed via main
 * @delim: delimiter character
 * Return: int (count)
 */
size_t countword(char *str, char delim)
{
	size_t i, count = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == delim || str[i + 1] == '\0')
			count++;
	}
	return (count);
}
