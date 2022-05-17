#include "main.h"

/**
 * history_dis - Display History Of User Input Simple Shell
 * @c:Parsed Command
 * @s:Statue Of Last Excute
 * Return: 0 on Success or -1 on Failure
 */
int history_dis(__attribute__((unused))char **c, __attribute__((unused))int s)
{
	char *filename = ".simple_shell_history";
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	int counter = 0;
	char *er;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		return (-1);
	}
	while ((getline(&line, &len, fp)) != -1)
	{
		counter++;
		er = _itoa(counter);
		PRINTER(er);
		free(er);
		PRINTER(" ");
		PRINTER(line);

	}
	if (line)
		free(line);
	fclose(fp);
	return (0);
}
/**
 * _bstrcat - concatenates 2 strings, places source BEFORE dest
 * @dest: destination string
 * @src: source string
 * Return: Finally concatenated string
 */
char *_bstrcat(char *dest, char *src)
{
	char *temp = NULL;

	if (dest && src)
	{
		temp = _strdup(dest);
		if (!temp)
			return (NULL);
		_memset(dest, '\0', _strlen(dest));
		if (src)
		{
			_strcpy(dest, src);
		}
		if (temp)
		{
			_strcat(dest, temp);
		}
		free(temp);
	}
	return (dest);
}

/**
 * estrcat - concatenate starting in middle of string
 * @dest: destination string
 * @src: source string
 * @i: index of string
 * Return: altered string
 */
char *estrcat(char *dest, char *src, int i)
{
	int ii = 0;

	if (dest && src)
	{
		for (; src[ii]; i++, ii++)
		{
			dest[i] = src[ii];
		}
		dest[i] = '\0';
	}
	return (dest);
}

/**
 * funkycat - used to create path strings
 * @dest: destination string
 * @middle: extra char(s) for middle of string
 * @src: source string
 * Return: altered string
 */
char *funkycat(char *dest, char *middle, char *src)
{
	if (dest && src && middle)
	{
		_strcat(dest, middle);
		_strcat(dest, src);
	}
	else
		return (NULL);
	return (dest);
}
