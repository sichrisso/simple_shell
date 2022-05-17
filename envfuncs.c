#include "main.h"
/**
 * _parse_path - function to get the list of path's
 * @env: list of path's
 * @pat: pointer to save the path
 * @flag: pointer to an integer
 * Return: Pointer to the path
 */

char *_parse_path(char *env[], char *pat, int *flag)
{
	int c = 0, j = 0;
	char *var, *tok, *temp;
	struct stat st;

	for (c = 0; env[c] != NULL; c++)
		if (_strncmp(env[c], "PATH=", 5) == 0)
			break;
	var = _strdup(env[c]);
	tok = strtok(var, ":");
	for (j = 0; tok != NULL; j++)
	{
		temp = NULL;
		temp = malloc(sizeof(char) * _strlen(tok) + _strlen(pat) + 2);
		temp[0] = '\0';
		_strcat(temp, tok);
		_strcat(temp, "/");
		_strcat(temp, pat);
		if (stat(temp, &st) == 0)
		{
			*flag = 1;
			free(var);
			return (temp);
		}
		tok = strtok(NULL, ":");
		free(temp);
	}
	free(var);
	return (pat);
}
