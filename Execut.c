#include "main.h"
/**
 * launch - launch commands
 * @argv: arguments
 * Return: Success or Fail
 */
int launch(char **argv)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("Error:");
		}
	}
	else if (pid < 0)
	{
		perror("#cisfun$ ");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		/* wait(NULL); */
	}

	return (1);
}
/**
 * execute - function for function calls
 * @argv: double pointer
 * @path: PATH array
 * Return: none
 */
int execute(char **argv, path_t *path)
{
	int (*built)(char **);
	/* int i; */
	char *concat;
	struct stat st;

	if (argv[0] == NULL)
		return (1);
	if (argv[0][0] == '/' || argv[0][0] == '.')
		return (launch(argv));

	built = get_built_func(argv[0]);

	if (built != NULL)
		return (built(argv));

	while (path)
	{
		concat = malloc((_strlen(path->str) + 1) * sizeof(char));
		_strcpy(concat, path->str);
		/* debe cambiar */
		concat = realloc(concat,
				sizeof(char) * ((_strlen(path->str) + _strlen(argv[0]) + 1)));
		concat = _strcat(concat, argv[0]);
		if (stat(concat, &st) == 0)
		{
			free(argv[0]);
			argv[0] = malloc((_strlen(concat) + 1) * sizeof(char));
			argv[0] = _strcpy(argv[0], concat);
			free(concat);
			return (launch(argv));
		}
		else
			free(concat);
		path = path->next;
	}

	return (1);
}
/**
 * handle_builtin - Handle Builtin Command
 * @cmd: Parsed Command
 * @er:statue of last Excute
 * Return: -1 Fail 0 Succes (Return :Excute Builtin)
 */

int handle_builtin(char **cmd, int er)
{
	 bul_t bil[] = {
		{"cd", change_dir},
		{"env", dis_env},
		{"help", display_help},
		{"echo", echo_bul},
		{"history", history_dis},
		{NULL, NULL}
	};
	int i = 0;

	while ((bil + i)->command)
	{
		if (_strcmp(cmd[0], (bil + i)->command) == 0)
		{
			return ((bil + i)->fun(cmd, er));
		}
		i++;
	}
	return (-1);
}
/**
 * check_cmd - Excute Simple Shell Command (Fork,Wait,Excute)
 *
 * @cmd:Parsed Command
 * @input: User Input
 * @c:Shell Excution Time Case of Command Not Found
 * @argv:Program Name
 * Return: 1 Case Command Null -1 Wrong Command 0 Command Excuted
 */
int check_cmd(char **cmd, char *input, int c, char **argv)
{
	int status;
	pid_t pid;

	if (*cmd == NULL)
	{
		return (-1);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return (-1);
	}

	if (pid == 0)
	{
		if (_strncmp(*cmd, "./", 2) != 0 && _strncmp(*cmd, "/", 1) != 0)
		{
			path_cmd(cmd);
		}

		if (execve(*cmd, cmd, environ) == -1)
		{
			print_error(cmd[0], c, argv);
			free(input);
			free(cmd);
			exit(EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	wait(&status);
	return (0);
}
/**
 * signal_to_handel - Handle ^C
 * @sig:Captured Signal
 * Return: Void
 */
void signal_to_handel(int sig)
{
	if (sig == SIGINT)
	{
		PRINTER("\n$ ");
	}
}
