#include "baml.h"

static void	pass_space(char **line, ssize_t *len)
{
	while (**line && isspace(**line))
	{
		(*line)++;
		(*len)--;
	}
}

static void	parse_line(char *line, ssize_t len)
{
	ssize_t check_p;
	ssize_t scan;
	char	temp;

	check_p = 0;
	scan = 0;
	while (scan < len)
	{
		if (is_quote(line[scan]))
		{
			temp = line[scan];
			line[scan] = 0;
			printf("%s\\%c", &line[check_p], temp);
			line[scan] = temp;
			check_p = scan + 1;
		}
		scan++;
	}
	printf("%s", &line[check_p]);
}

void	print_header(t_fstate *state, char const **fmt, char *line, ssize_t len)
{
	pass_space(&line, &len);
	line[--len] = 0;
	if (state->has_header)
		printf("%s\n", fmt[3]);
	parse_line(line, len);
	printf("%s", fmt[0]);
	state->has_header = 1;
	state->has_entry = 0;
}

void	print_entry(t_fstate *state, char const **fmt, char *line, ssize_t len)
{
	pass_space(&line, &len);
	line += 2;
	len -= 2;
	pass_space(&line, &len);
	if (state->has_entry)
		printf("%s", fmt[1]);
	printf("%s", fmt[2]);
	parse_line(line, len);
	printf("%s", fmt[2]);
	state->has_entry = 1;
}
