#include "baml.h"
#include <string.h>

char const	*g_format_b[] = {"=(", " ", "\'", ")"};
char const	*g_format_p[] = {" = [", ", ", "\"", "]"};

char	arg_type(int ac, char **av)
{
	if (ac == 1)
		return (0);
	else if (ac == 2)
	{
		if (av[1][0] == '-')
			return (0);
		return (1);
	}
	return (1);
}

static char const	**set_format(char c)
{
	switch(c)
	{
		case 'b':
			return (g_format_b);
		case 'p':
			return (g_format_p);
		case 'r':
			return (g_format_p);
		default:
			arg_error();
	}
	return (0);
}

static char	find_strarg(char *arg)
{
	arg += 2;
	if (!strcmp(arg, "bash"))
		return ('b');
	else if (!strcmp(arg, "python"))
		return ('p');
	else if (!strcmp(arg, "ruby"))
		return ('r');
	return (0);
}

char const	**check_mode(char *arg, int *start_index)
{
	if (start_index)
		*start_index = 1;
	if (!strncmp(arg, "--", 2))
		return (set_format(find_strarg(arg)));
	else if (*arg == '-' && strlen(arg) == 2)
		return (set_format(*(arg + 1)));
	else
	{
		if (start_index)
			*start_index = 0;
		return (set_format('b'));
	}
}
