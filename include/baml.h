#ifndef BAML_H
# define BAML_H

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>

# define INV_REPLACE '_'

typedef struct	s_fstate
{
	char	*fname;
	size_t	line_nbr;
	char	is_entry;
	char	is_header;
	char	has_entry;
	char	has_header;
	char	invalid;
}				t_fstate;

char		arg_type(int ac, char **av);
char const	**check_mode(char *first_arg, int *start_index);

int			read_file(FILE *fp, char const **format, char *fname);

void		print_header(t_fstate *st, char const **fmt, char *val, ssize_t ln);
void		print_entry(t_fstate *st, char const **fmt, char *val, ssize_t ln);

ssize_t		find_index(char *str, char c);

char		is_quote(char c);

void		arg_error(void);
void		val_error(t_fstate *st);
void		col_error(t_fstate *st);

#endif
