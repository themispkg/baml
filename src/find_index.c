#include "baml.h"

ssize_t	find_index(char *str, char c)
{
	ssize_t	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	return (-1);
}
