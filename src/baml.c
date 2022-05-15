#include "baml.h"

void	read_args(int ac, char **av)
{
	char const	**format;
	FILE		*fp;
	int			scan;

	format = check_mode(*av, &scan);
	while (scan < ac)
	{
		fp = fopen(av[scan], "r");
		if (fp)
		{
			read_file(fp, format, av[scan]);
			fclose(fp);
		}
		else
			perror(av[scan]);
		scan++;
	}
}

void	read_stdin(int ac, char **av)
{
	char const	**format;

	if (ac > 1)
		av++;
	format = check_mode(*av, NULL);
	read_file(stdin, format, "stdin");
}

int	main(int ac, char **av)
{
	if (arg_type(ac, av))
		read_args(ac - 1, av + 1);
	else
		read_stdin(ac, av);
	return (0);
}
