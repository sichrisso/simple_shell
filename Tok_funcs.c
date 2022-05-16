#include "main.h"

/**
 * tokenArray - creates an array of tokens
 * @cmd: string passed from main to tokenize
 * @delim: delimiter character
 * Return: NULL if failed or 2darray if success
 */

char **tokenArray(char *cmd, char *delim)
{
	char *token = NULL;
	char **toks;
	int i = 0;
	int len = 0;
	size_t wordcount = 0;

	if (!cmd)
		return (NULL);
	len = _strlen(cmd);
	if (cmd[len - 1] == '\n')
		cmd[len - 1] = '\0';
	wordcount = countword(cmd, delim[0]);
	toks = malloc(sizeof(char *) * (wordcount + 1));
	if (toks == NULL)
		return (NULL);
	token = strtok(cmd, delim);
	while (token != NULL)
	{
		toks[i] = _strdup(token);
		if (toks[i] == NULL)
		{
			free_toks(toks);
			return (NULL);
		}
		token = strtok(NULL, delim);
		i++;
	}
	toks[i] = token;
	return (toks);
}

/**
 * free_toks - free vertical index of toks
 * @toks: array passed from tokenArray
 * Return: void
 */
void free_toks(char **toks)
{
	int i = 0;

	if (toks == NULL)
		return;
	while (toks[i] != NULL)
	{
		free(toks[i]);
		i++;
	}
	free(toks);
}
/**
 * check_delim - Checks If A Character Match Any Char *
 * @c: Character To Check
 * @str: String To Check
 * Return: 1 Succes, 0 Failed
 */
unsigned int check_delim(char c, const char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}

/**
 * _strtok - Token A String Into Token (strtrok)
 * @str: String
 * @delim: Delimiter
 * Return: Pointer To The Next Token Or NULL
 */
char *_strtok(char *str, const char *delim)
{
	static char *ts;
	static char *nt;
	unsigned int i;

	if (str != NULL)
		nt = str;
	ts = nt;
	if (ts == NULL)
		return (NULL);
	for (i = 0; ts[i] != '\0'; i++)
	{
		if (check_delim(ts[i], delim) == 0)
			break;
	}
	if (nt[i] == '\0' || nt[i] == '#')
	{
		nt = NULL;
		return (NULL);
	}
	ts = nt + i;
	nt = ts;
	for (i = 0; nt[i] != '\0'; i++)
	{
		if (check_delim(nt[i], delim) == 1)
			break;
	}
	if (nt[i] == '\0')
		nt = NULL;
	else
	{
		nt[i] = '\0';
		nt = nt + i + 1;
		if (*nt == '\0')
			nt = NULL;
	}
	return (ts);
}
