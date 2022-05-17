#include "main.h"

/**
 * *readline - read line for stdin
 * Return: Success or Fail
 */
char *readline(void)
{
	char *buf = NULL;
	size_t bufsize = 0;

	fflush(stdin);
	if (getline(&buf, &bufsize, stdin) == -1)
	{
		free(buf);
		return (NULL);
	}
	return (buf);
}
/**
 * splitline - Generate argv vector
 * @buf: Line to be splitted
 * Return: double pointer char
 */

args_t splitline(char *buf)
{
	args_t argts;
	char **argv;
	char *temp;
	char *delim = " \t\n";
	char *token;
	int count = 0;

	temp = malloc((_strlen(buf) + 1) * sizeof(char));
	if (temp == NULL)
		exit(1);
	temp = _strcpy(temp, buf);
	token = strtok(buf, delim);
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, delim);
	}
	argv = (char **) malloc((count + 1) * sizeof(char *));
	/*
	* if (argv == NULL)
	* return (NULL);
	*/
	token = strtok(temp, delim);
	count = 0;
	while (token != NULL)
	{
		argv[count] = (char *) _calloc((_strlen(token) + 1), sizeof(char));
		argv[count] = _strcpy(argv[count], token);
		count++;
		token = strtok(NULL, delim);
	}
	argv[count] = NULL;
	argts.argc = count;
	argts.argv = argv;

	free(temp);
	return (argts);
}
