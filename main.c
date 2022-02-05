#include <stdio.h>
#include <stdlib.h>
#include "libbaml/baml.h"
#include "libbaml/read.h"

int	main(int ac, char **av)
{
	printf("%s\n", read_entry(ac, av));
}
