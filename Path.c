#include "main.h"
/**
 * find_path - finds the path
 * @toks: token array
 * Return: Full path if command exists, or NULL if not
 */
char *find_path(char **toks)
{
	size_t i = 0, signal = 0, len = 0, len2 = _strlen(toks[0]), indicator = 0;
	char *newstr = NULL;
	char **path = NULL;
	struct stat statvar;

	for (i = 0; environ[i]; i++) /* <- Loop through environ to find PATH */
		if (_strncmp(environ[i], "PATH=", 5) == 0)
		{indicator = 1;
			break; }
	if (indicator == 0)
		return (toks[0]);
	newstr = _strdup(environ[i] + 5);
	if (!newstr)
		return (toks[0]);
	newstr = check_cwd(newstr), path = tokenArray(newstr, ":");
	if (!path) /* ^ Is cwd specified in PATH? */ /* ^ Create 2d array for paths */
		return (toks[0]);
	free(newstr), newstr = NULL;
	if (exact_path(path, toks) == 1) /* <- Does input match an exact path? */
		return (toks[0]);
	for (i = 0; path[i]; i++) /* <- Append command string to each path */
	{len = _strlen(path[i]), path[i] = _realloc(path[i], len, len + len2 + 2);
		funkycat(path[i], "/", toks[0]); }
	for (i = 0; path[i]; i++) /* <- Loop through PATH array */
	{	/* Use stat to check if command exists */
		if (stat(path[i], &statvar) == 0)
		{
			signal = 1;
			break;
		}
	}
	if (signal == 1) /* <- If valid command is found */
	{
		len = _strlen(path[i]), toks[0] = _realloc(toks[0], len2, len + 1);
		_strcpy(toks[0], path[i]), free_toks(path);
		return (toks[0]); /* <- Return the path to the command */
	}
	free(newstr), free_toks(path);
	return (toks[0]); /* <- Otherwise, return user input */
}
/**
 * check_path - checks if user has given a full path
 * @str: input string
 * Return: path, if it exists, or NULL otherwise
 */
char *check_path(char *str)
{
	int i = 0, count = 0, count2 = 0, count3 = 0;
	char *newstr = NULL;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == '/')
			count++;
	}
	if (count == 0)
		return (NULL);
	for (i = 0; str[i]; i++)
	{
		if (str[i] == '/')
			count2++;
		if (count == count2)
			break;
		count3++;
	}
	newstr = malloc(sizeof(char) * count3 + 1);
	if (!newstr)
		return (NULL);
	_strncpy(newstr, str, count3);
	return (newstr);
}
/**
 * check_cwd - checks if current directory is in the PATH
 * @pathstr: string which holds the full PATH
 * Return: Altered string if current directory found, or original string if not
 */
char *check_cwd(char *pathstr)
{
	int i = 0;
	int len = _strlen(pathstr);
	char *temp = NULL;

	if (pathstr[0] == ':')
	{
		pathstr = _realloc(pathstr, len + 1, len + 2);
		_bstrcat(pathstr, ".");
		return (pathstr);
	}
	if (pathstr[len - 1] == ':')
	{
		pathstr = _realloc(pathstr, len + 1, len + 2);
		_strcat(pathstr, ".");
		return (pathstr);
	}
	for (i = 0; pathstr[i]; i++)
	{
		if (pathstr[i] == ':' && pathstr[i + 1] == ':')
		{
			pathstr = _realloc(pathstr, len + 1, len + 2);
			temp = _strdup(pathstr + (i + 1));
			pathstr[i + 1] = '.';
			estrcat(pathstr, temp, i + 2);
			free(temp);
			break;
		}
	}
	return (pathstr);
}
/**
 * exact_path - checks if user has given an exact path
 * @path: 2d array holding path strings
 * @toks: 2d array holding input strings
 * Return: 1 if match, 0 if no match
 */
int exact_path(char **path, char **toks)
{
	int i = 0;
	char *newstr = NULL;

	for (i = 0; path[i]; i++)
	{
		newstr = check_path(toks[0]);
		if (_strcmp(path[i], newstr) == 0)
		{
			free(newstr);
			free_toks(path);
			return (1);
		}
		else
		{
			if (newstr)
				free(newstr);
			newstr = NULL;
		}
	}
	return (0);
}
