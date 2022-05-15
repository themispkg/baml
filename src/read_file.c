#include "baml.h"

static void	check_entry(t_fstate *fstate, char *line)
{
	fstate->is_entry = 0;
	while (*line && isspace(*line))
		line++;
	if (!strncmp(line, "->", 2))
	{
		if (strstr(line + 2, "->"))
			fstate->invalid = 1;
		else
			fstate->is_entry = 1;
	}
}

static void	check_header(t_fstate *fstate, char *line, ssize_t len)
{
	ssize_t	term_index;

	fstate->is_header = 0;
	term_index = find_index(line, ';');
	if (term_index != -1 && term_index != len - 1)
		fstate->invalid = 1;
	else if (term_index == len - 1)
	{
		if (len == 1)
			fstate->invalid = 1;
		else
			fstate->is_header = 1;
	}
}

static void	read_line(t_fstate *fstate, char *line, ssize_t len)
{
	fstate->is_entry = 0;
	fstate->is_header = 0;
	fstate->invalid = 0;
	check_entry(fstate, line);
	check_header(fstate, line, len);
	if (fstate->invalid)
		val_error(fstate);
	if (fstate->is_entry && fstate->is_header)
		col_error(fstate);
}

int	read_file(FILE *fp, char const **format, char *fname)
{
	char		*line;
	size_t		linecapp;
	ssize_t		len;
	t_fstate	fstate = {fname, 0, 0, 0, 0, 0, 0};

	while (!fstate.invalid)
	{
		fstate.line_nbr++;
		line = NULL;
		linecapp = 0;
		len = getline(&line, &linecapp, fp);
		if (len == -1)
			break ;
		line[--len] = 0;
		read_line(&fstate, line, len);
		if (fstate.is_header)
			print_header(&fstate, format, line, len);
		else if (fstate.is_entry && fstate.has_header)
			print_entry(&fstate, format, line, len);
		free(line);
	}
	if (fstate.has_header)
		printf("%s\n", format[3]);
	return (1);
}
