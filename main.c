#include "main.h"
/**
 * main - entry point
 *
 * Return: 0 on success
 *
 */

int main(void)
{
	char *buf = NULL;
	args_t args;
	node_t node;

	node = build_node();

	while (EOF)
	{
		/* print prompt */
		/* if (isatty(fileno(stdin))) */
		if (isatty(STDIN_FILENO))
			write(1, "#cisfun$ ", 10);
		buf = read_line();
		if (buf == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(1, "\n", 1);
			break;
		}

		else
		{
			args = split_line(buf);
			execute(args.argv, node.path);
			delete_memory(args.argv, args.argc);
			free(buf);
		}
	}

	free_list(node.path);

	return (0);
}
