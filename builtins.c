#include "main.h"

/**
 * built_exit - exits the custom shell.
 * @args:  arguments (the exit status)
 * Return: Always returns 0, to terminate execution.
 */
int built_exit(__attribute__((unused)) char **args)
{
	exit(1);
}
/**
 * built_env - print environment
 * @args: arguments
 * Return: Always returns 1, to continue executing.
 */
int built_env(__attribute__((unused)) char **args)
{
	char **ptr;

	ptr = environ;

	while (*ptr)
	{
		printf("%s\n", *ptr);
		ptr++;
	}
	return (1);
}
/**
 * built_cd - change directory.
 * @args: arguments
 * Return: Always returns 1, to continue executing.
 */
int built_cd(char **args)
{
	size_t bfsize = 1024;
	char *home_dir = 0, *homedir = _getenv("HOME");
	char *old_dir = 0, *olddir = _getenv("OLDPWD");
	char pwd[1024];

	_strcpy(old_dir, olddir);

	if (args[1] == NULL)
	{
		_strcpy(home_dir, homedir);


		chdir(home_dir);
		getcwd(pwd, bfsize);

		free(home_dir);
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("lsh");
		}
	}
	return (1);
}
/**
 * built_help - print help.
 * @args: arguments.
 * Return: Always returns 1, to continue executing.
 */
int built_help(__attribute__((unused)) char **args)
{
	printf("Stephen Brennan's LSH\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in:\n");
	printf("Use the man command for information on other programs.\n");
	return (1);
}

/**
 * get_built_func - return built function
 * @s: char
 * Return: function (char **)
 */
int (*get_built_func(char *s))(char **)
{
	built_t fs[] = {
		{"cd", built_cd},
		{"env", built_env},
		{"help", built_help},
		{"exit", built_exit},
		{NULL, NULL}
	};
	int i;

	i = 0;
	while (i < 4)
	{
		if (_strcmp(fs[i].fc, s) == 0)
			return (fs[i].f);
		i++;
	}
	return (NULL);
}
