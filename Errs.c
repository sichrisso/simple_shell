#include "main.h"

#define INT_DECIMAL_STRING_SIZE(int_type)
/**
 *  _prerror - Print Custome Error
 * @argv:Program Name
 * @c:Error Count
 * @cmd:Command
 * Return: Void
 */
void _prerror(char **argv, int c, char **cmd)
{
	char *er = _itoa(c);

	PRINTER(argv[0]);
	PRINTER(": ");
	PRINTER(er);
	PRINTER(": ");
	PRINTER(cmd[0]);
	PRINTER(": Illegal number: ");
	PRINTER(cmd[1]);
	PRINTER("\n");
	free(er);
}
/**
 * errorhandler - handles error message text
 * @av: argument vector
 * @input: user input
 * @count: for line number
 *
 */
void errorhandler(char *av, char *input, int count)
{
	char *newstr = NULL, *countstr = NULL;
	int len = _strlen(av);
	int len2 = _strlen(input);
	int len3 = 0;

	countstr = _itoa(count);
	if (!countstr)
		return;
	len3 = _strlen(countstr);
	newstr = malloc(sizeof(char) * (len + len2 + len3 + 5));
	if (!newstr)
		return;
	_memset(newstr, '\0', (len + len2 + len3 + 5));
	_strcpy(newstr, av);
	_strcat(newstr, ": ");
	_strcat(newstr, countstr);
	_strcat(newstr, ": ");
	_strcat(newstr, input);
	perror(newstr);
	free(newstr);
	free(countstr);
}
/**
 * execError - handles error message text for execve
 * @av: argv
 * @input: user input
 * @count: for line #
 * Return: void
 */
void execError(char *av, char *input, int count)
{
	char *newstr = NULL, *countstr = NULL;
	int len = _strlen(av);
	int len2 = _strlen(input);
	int len3 = 0;

	countstr = int_to_str(count);
	if (!countstr)
		return;
	len3 = _strlen(countstr);
	newstr = malloc(sizeof(char) * (len + len2 + len3 + 17));
	if (!newstr)
		return;
	_memset(newstr, '\0', (len + len2 + len3 + 17));
	_strcpy(newstr, av);
	_strcat(newstr, ": ");
	_strcat(newstr, countstr);
	_strcat(newstr, ": ");
	_strcat(newstr, input);
	_strcat(newstr, ": not found\n");
	len = _strlen(newstr);
	write(2, newstr, len);
	free(newstr);
	free(countstr);
}
/**
 * int_to_str - converts int to string
 * @count: the int to convert, represents line number
 * Return: converted string
 */
char *int_to_str(int count)
{
	char *temp;
	unsigned int neg;
	int i, rem, num, n, len, x;

	n = count;
	num = n;
	len = i = 0;
	/* Find integer length */
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	x = len;
	if (num == 0)
	{
		temp = malloc(2);
		temp[0] = '0';
		temp[1] = '\0';
		return (temp);
	}
	/* Skip negative numbers */
	else
		temp = malloc(len + 2), neg = num;
	for (; i < len; i++)
	{
		rem = neg % 10;
		neg /= 10;
		temp[x - (i + 1)] = (rem + '0');
	}
	temp[x] = '\0';
	return (temp);
}
