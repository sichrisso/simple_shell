#include "main.h"

/**
 * *read_line - read line for stdin
 * Return: Success or Fail
 */
char *read_line(void)
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
 * print_echo - Excute Normal Echo
 * @cmd: Parsed Command
 * Return: 0 Succes -1 Fail
 */
int print_echo(char **cmd)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
	if (execve("/bin/echo", cmd, environ) == -1)
	{
		return (-1);
	}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		return (-1);
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}
/**
 * split_line - function that splits line
 * @buf: the line to split
 * Return: splitted line
 */
args_t split_line(char *buf)
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

/**
 * delete_memory - delete memory in double pointer
 * @table: double pointer
 * @value: size to free
 */
void delete_memory(char **table, int value)
{
	int i;

	for (i = 0; i < value; i++)
		free(table[i]);
	free(table);
}
