#include "baml.h"
#include <stdlib.h>
#include <stdio.h>

void	arg_error(void)
{
	printf("INVALID ARGUMENTS\n");
	exit(EXIT_FAILURE);
}

void	val_error(t_fstate *st)
{
	printf("INVALID VALUE AT LINE %ld IN FILE %s\n", st->line_nbr, st->fname);
	exit(EXIT_FAILURE);
}

void	col_error(t_fstate *st)
{
	printf("TYPE COLLISION AT LINE %ld IN FILE %s\n", st->line_nbr, st->fname);
	exit(EXIT_FAILURE);
}
